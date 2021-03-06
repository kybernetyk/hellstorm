//
//  game_board_system.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_board_system.h"
#include "game_utils.h"
#include "game_globals.h"

namespace game 
{
	hs::uid game_board_element::family_id = 0;
	
	const float gbo_falltime = 0.09; //must be greater than 2*dt!
	
	game_board_system::game_board_system(hs::entity_manager *manager)
	{
		em = manager;
		hs::comp::register_component_class<game_board_element>();
		
		ent_cache = new hs::entity*[hs::cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
	}
	
	game_board_system::~game_board_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}
	
	void game_board_system::update(double dt)
	{
		current_dt = dt;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
		
		hs::uid qry[] = 
		{
			game_board_element::family_id,
			hs::comp::position::family_id
		};
		size_t qry_size = sizeof(qry)/sizeof(hs::uid);
		
		cache_size = em->get_entities_possesing_components(qry, qry_size, ent_cache, hs::cfg::entity_system.entity_pool_size);

		global::update_board_map(ent_cache, cache_size);
		

		int fall_count = 0;

		for (int row = 0; row < defs::board_num_of_rows; row++)
		{
			for (int col = 0; col < defs::board_num_of_cols; col++)
			{
				current_entity = global::board_map[col][row];
				if (!current_entity)
					continue;
				
				current_gbo = current_entity->get<game_board_element>();
				current_pos = current_entity->get<hs::comp::position>();

				switch (current_gbo->state) 
				{
					case e_gbo_state_idle:
						handle_state_idle();
						break;
					case e_gbo_state_falling:
						fall_count ++;
						handle_state_falling();
						break;
					default:
						break;
				}
			}
		}
		
/*		for (size_t i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			current_gbo = current_entity->get<game_board_element>();
			current_pos = current_entity->get<hs::comp::position>();
			
			switch (current_gbo->state) 
			{
				case e_gbo_state_idle:
					handle_state_idle();
					break;
				case e_gbo_state_falling:
					fall_count ++;
					handle_state_falling();
					break;
				default:
					break;
			}
		}*/
		
		if (fall_count == 0 && global::g_state.current_state == global::e_gs_gbos_falling)
			/*&&
			global::g_state.old_state == global::g_state.current_state)    //causes pills falling into each other
			 */
		{
			global::g_state.current_state = global::e_gs_check_for_chains;//global::e_gs_player_need_respawn;
		}
	}
#pragma mark -
#pragma mark coll
	bool game_board_system::can_move_down(void)
	{
		int col = current_gbo->col;
		int row = current_gbo->row;
		row--;
		if (row < 0)
			return false;
		
		hs::entity *e = global::board_map[col][row];
		if (e)
		{
			game_board_element *gbo = e->get<game_board_element>();
			if (gbo->state != e_gbo_state_falling)
				return false;
		}
		
		return true;
	}
	
#pragma mark -
#pragma mark handle state
	void game_board_system::change_state(game_board_element *gbo, e_gbo_state new_state)
	{
		if (gbo->state == e_gbo_state_falling &&
			new_state == e_gbo_state_idle)
		{
			gbo->timer = gbo_falltime;
			gbo->state = e_gbo_state_idle;
			return;
		}
		
		if (gbo->state == e_gbo_state_idle &&
			new_state == e_gbo_state_falling)
		{
			gbo->timer = gbo_falltime;
			gbo->state = e_gbo_state_falling;
			return;
		}
		
		printf("no state transition from %i to %i!\n",gbo->state, new_state);
		abort();
	}
	
	
	void game_board_system::handle_state_idle(void)
	{
		
	}
	
	void game_board_system::handle_state_falling(void)
	{
		if (!can_move_down())
		{
			change_state(current_gbo, e_gbo_state_idle);
			hs::audio_system::play_sound("pill_land.m4a");
			return;
		}

		current_gbo->timer -= current_dt;

		if (current_gbo->timer <= 0.0)
		{
			current_gbo->timer = gbo_falltime;
//			hs::audio_system::play_sound("pill_move.m4a");
			
			global::board_map[current_gbo->col][current_gbo->row] = NULL;
			current_gbo->row--;
			global::board_map[current_gbo->col][current_gbo->row] = current_entity;
			
			hs::entity *shading = em->get_entity_by_guid(current_gbo->shading_guid);
			if (shading)
			{
				shading->get<hs::comp::position>()->origin.y -= 32.0;//
			}

		}
		
		current_pos->origin = pixel_for_colrow(current_gbo->col, current_gbo->row);
		
	}
}