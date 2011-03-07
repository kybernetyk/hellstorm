//
//  game_logic_system.cpp
//  hellstorm
//
//  Created by jrk on 26/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_logic_system.h"
#include "hellstorm.h"
#include "game_factory.h"
#include "game_globals.h"
#include <vector>

namespace game 
{
	game_logic_system::game_logic_system(hs::entity_manager *manager)
	{
		em = manager;
		ent_cache = new hs::entity*[hs::cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
	}
	
	game_logic_system::~game_logic_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}

#pragma mark -
#pragma mark state check chains
	void game_logic_system::check_horizontal(void)
	{
		game_board_element *current_gbo;
		hs::entity *current_entity;
		
		std::vector<hs::entity *> tmp;
		
		for (int row = 0; row < defs::board_num_of_rows; row++)
		{
			int sum = 0;
			e_gbo_color cur_col = e_gbo_invalid;

			for (int col = 0; col < defs::board_num_of_cols; col++)
			{
				current_entity = global::board_map[col][row];
				if (!current_entity)
				{
					if (sum >= 4)
						marked_for_removal.insert(marked_for_removal.end(), tmp.begin(), tmp.end());
					
					tmp.clear();
					cur_col = e_gbo_invalid;
					sum = 0;
					continue;
				}
				current_gbo = current_entity->get<game_board_element>();
				
				if(sum == 0 || cur_col != current_gbo->color)
				{
					if (sum >= 4)
						marked_for_removal.insert(marked_for_removal.end(), tmp.begin(), tmp.end());
					
					cur_col = current_gbo->color;	
					tmp.clear();
					sum = 1;
					tmp.push_back(current_entity);
				}
				else
				{
					sum ++;
					tmp.push_back(current_entity);
				}
			}
			if (sum >= 4)
			{
				marked_for_removal.insert(marked_for_removal.end(), tmp.begin(), tmp.end());
				tmp.clear();
			}
			
		}

	}
	
	void game_logic_system::check_vertical(void)
	{
		game_board_element *current_gbo;
		hs::entity *current_entity;
		
		std::vector<hs::entity *> tmp;
		
		//vert
		for (int col = 0; col < defs::board_num_of_cols; col++)
		{
			int sum = 0;
			e_gbo_color cur_col = e_gbo_invalid;
			
			for (int row = 0; row < defs::board_num_of_rows; row++)
			{
				current_entity = global::board_map[col][row];
				if (!current_entity)
				{
					if (sum >= 4)
						marked_for_removal.insert(marked_for_removal.end(), tmp.begin(), tmp.end());
					
					tmp.clear();
					cur_col = e_gbo_invalid;
					sum = 0;
					continue;
				}
				current_gbo = current_entity->get<game_board_element>();
				
				if(sum == 0 || cur_col != current_gbo->color)
				{
					if (sum >= 4)
						marked_for_removal.insert(marked_for_removal.end(), tmp.begin(), tmp.end());
					
					cur_col = current_gbo->color;	
					tmp.clear();
					sum = 1;
					tmp.push_back(current_entity);
				}
				else
				{
					sum ++;
					tmp.push_back(current_entity);
				}
			}
			if (sum >= 4)
			{
				marked_for_removal.insert(marked_for_removal.end(), tmp.begin(), tmp.end());
				tmp.clear();
			}
			
		}

	}

	/*
	 * check for chains of pills+virii and remove them
	 */
	void game_logic_system::handle_state_check_for_chains(void)
	{
		marked_for_removal.clear();
		
		check_vertical();
		check_horizontal();
		
		hs::entity *current_entity;
		
		//kill them! KILL EM ALL!
		std::vector<hs::entity *>::const_iterator it = marked_for_removal.begin();
		while (it != marked_for_removal.end())
		{
			current_entity = *it;
			++it;
			
			//entities can be marked double - dont add component if it exists already;
			if (!current_entity->get<hs::comp::mark_of_death>())
			{	
				global::g_state.score += 100;
				current_entity->add<hs::comp::mark_of_death>();	
			}
		}
		
		if (marked_for_removal.size() > 0)
			global::g_state.current_state = global::e_gs_chains_marked;
		else
			global::g_state.current_state = global::e_gs_no_chains;
	}

#pragma mark -
#pragma mark state move gbos

#define CS_UNDEFINED 0
#define CS_STATIC 1
#define CS_FALL 2
	/*
	 * mark gbos that are not connected to a static as falling
	 */
	void game_logic_system::handle_state_move_gbos(void)
	{
		game_board_element *current_gbo;
		hs::entity *current_entity;
		
		std::vector<hs::entity *> tmp;
		

		int col_state = CS_FALL;
		
		//first mark all fall candidates
		for (int col = 0; col < defs::board_num_of_cols; col++)
		{
			//bottom pill is always static
			col_state = CS_STATIC;
			for (int row = 0; row < defs::board_num_of_rows; row++)
			{
				current_entity = global::board_map[col][row];
				if (!current_entity)
				{
					col_state = CS_FALL;
					continue;
				}
				
				current_gbo = em->get_component<game_board_element>(current_entity);

				//on virus do next column
				if (current_gbo->type == e_gbo_type_virus)
				{
					col_state = CS_STATIC;
					current_gbo->state = e_gbo_state_idle;
				}
				
				if (current_gbo->row == 0)
					col_state = CS_STATIC;

				if (col_state == CS_FALL)
				{
					current_gbo->state = e_gbo_state_falling;
				}
				else
				{
					current_gbo->state = e_gbo_state_idle;
				}
			}
		}

		//2nd remove marks for pills that are connected to statics
		game_board_element *neighbour_gbo;
		hs::entity *neighbour_entity;

		for (int pass = 0; pass < defs::board_num_of_cols; pass++)
		{
			for (int col = 0; col < defs::board_num_of_cols; col++)
			{
				for (int row = 0; row < defs::board_num_of_rows; row++)
				{
					neighbour_entity = NULL;
					
					current_entity = global::board_map[col][row];
					if (!current_entity)
					{
						continue;
					}
					
					current_gbo = em->get_component<game_board_element>(current_entity);

					if (row == 0)
					{
						current_gbo->state = e_gbo_state_idle;
					}

					if (current_gbo->state != e_gbo_state_idle)
						continue;

					//mark connected
					neighbour_entity = em->get_entity_by_guid(current_gbo->connected_to_guid);
					if (neighbour_entity)
					{	
						neighbour_gbo = em->get_component<game_board_element>(neighbour_entity);	
						neighbour_gbo->state = e_gbo_state_idle;
					}
					
					//mark upper
					int r = row;
					while (1)
					{
						if (r == defs::board_num_of_rows-1)
							break;
						
						neighbour_entity = global::board_map[col][r+1];
						if (!neighbour_entity)
							break;
						
						neighbour_gbo = neighbour_entity->get<game_board_element>();
						neighbour_gbo->state = e_gbo_state_idle;
						r++;
					}
				}
			}
		}
		global::g_state.current_state = global::e_gs_gbos_need_disconnect;
	}
	
	/*
	 * remove connections between falling gbos. (also change the graphics to the single pill)
	 */
	void game_logic_system::handle_state_gbos_need_disconnect()
	{
		game_board_element *current_gbo;
		hs::entity *current_entity;

		printf("disconnecting ...\n");
		for (int col = 0; col < defs::board_num_of_cols; col++)
		{
			for (int row = 0; row < defs::board_num_of_rows; row++)
			{
				current_entity = global::board_map[col][row];
				if (!current_entity)
					continue;
				
				current_gbo = em->get_component<game_board_element>(current_entity);
				if (current_gbo->state == e_gbo_state_falling)
					current_gbo->connected_to_guid = 0;
			}
		}
		global::g_state.current_state = global::e_gs_gbos_falling;
	}
	
#pragma mark -
#pragma mark update	
	void game_logic_system::update(double dt)
	{
		//do only if we're in the state and not between 2 states (which could have been set in some earlier system this frame)
		if (global::g_state.current_state == global::g_state.old_state)
		{
			switch (global::g_state.current_state) 
			{
				case global::e_gs_check_for_chains:
					handle_state_check_for_chains();
					break;
				case global::e_gs_move_gbos:
					handle_state_move_gbos();
					break;
				case global::e_gs_gbos_need_disconnect:
					handle_state_gbos_need_disconnect();
					break;
				default:
					break;
			}
		}
	}
}
