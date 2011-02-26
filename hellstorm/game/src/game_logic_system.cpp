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
			}
			
		}

	}

	
	void game_logic_system::update(double dt)
	{
		if (global::g_state.current_state == global::e_gs_check_for_chains &&
			global::g_state.current_state == global::g_state.old_state)
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
					current_entity->add<hs::comp::mark_of_death>();
			}
			if (marked_for_removal.size() > 0)
				global::g_state.current_state = global::e_gs_chains_marked;
			else
				global::g_state.current_state = global::e_gs_no_chains;
		}
	}
}
