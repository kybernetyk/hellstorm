//
//  player_system.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "player_system.h"
#include "game_utils.h"
#include "game_globals.h"

namespace game 
{
	hs::uid comp_player::family_id = 0;
	
	player_system::player_system(hs::entity_manager *manager)
	{
		em = manager;
		hs::comp::register_component_class<comp_player>();
		
		ent_cache = new hs::entity*[hs::cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
	}
	
	player_system::~player_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}
	#define DEG2RAD(x) (0.0174532925 * (x))
	void player_system::update(double dt)
	{
		current_dt = dt;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
		cache_size = em->get_entities_posessing_component(comp_player::family_id, ent_cache, hs::cfg::entity_system.entity_pool_size);
		
		for (int i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			current_pos = current_entity->get<hs::comp::position>();
			player = current_entity->get<comp_player>();
			
			if (hs::g_input.has_touched_down())
			{
				if (hs::g_input.get_current_touch_location().y > 400)
				{
					printf("ROTATE!\n");
					rotate();
				}
				else if (hs::g_input.get_current_touch_location().x < 160)
				{
					move_left();
				}
				else
				{
					move_right();
				}
			}
			handle_state_falling();
		}
	}

	void player_system::rotate(void)
	{
		current_pos->rot += 90.0;
		if (current_pos->rot >= 360.0)
			current_pos->rot = 0.0;
		
		int col_offset = cos(DEG2RAD(current_pos->rot));
		int row_offset = sin(DEG2RAD(current_pos->rot));

		player->aux_col = player->center_col + col_offset;
		player->aux_row = player->center_row + row_offset;
	}
	void player_system::move_left(void)
	{
		int c_test_col = player->center_col - 1;
		int a_test_col = player->aux_col - 1;
		
		if (c_test_col < 0 || c_test_col >= defs::board_num_of_cols)
			return;
		if (a_test_col < 0 || a_test_col >= defs::board_num_of_cols)
			return;
		
		if (global::board_map[c_test_col][player->center_row] ||
			global::board_map[a_test_col][player->aux_row])
			return;
		
		player->center_col = c_test_col;
		player->aux_col = a_test_col;
	}
	
	void player_system::move_right(void)
	{
		int c_test_col = player->center_col + 1;
		int a_test_col = player->aux_col + 1;
		
		if (c_test_col < 0 || c_test_col >= defs::board_num_of_cols)
			return;
		if (a_test_col < 0 || a_test_col >= defs::board_num_of_cols)
			return;

		if (global::board_map[c_test_col][player->center_row] ||
			global::board_map[a_test_col][player->aux_row])
			return;

		player->center_col = c_test_col;
		player->aux_col = a_test_col;
	}

	
	void player_system::handle_state_falling(void)
	{
		player->timer -= current_dt;
		
		if (player->timer <= 0.0)
		{
			player->timer = player->fall_time;
			player->center_row--;
			player->aux_row--;
		}

		if (!can_move_down())
		{
			player->center_row++;
			player->aux_row++;
			current_entity->add<hs::comp::mark_of_death>();
			
			hs::entity *center = factory::create_pill(em, player->center_col, player->center_row, player->double_pill_type, factory::left);
			hs::entity *aux = factory::create_pill(em, player->aux_col, player->aux_row, player->double_pill_type, factory::right);

			center->get<hs::comp::position>()->rot = current_pos->rot;
			aux->get<hs::comp::position>()->rot = current_pos->rot;
		return;
		}
		current_pos->origin = pixel_for_colrow(player->center_col, player->center_row);
	}
	
	bool player_system::can_move_down(void)
	{
		if (player->center_row < 0 || player->aux_row < 0)
			return false;
		
		if (global::board_map[player->center_col][player->center_row] || 
			global::board_map[player->aux_col][player->aux_row])
			return false;
		
		return true;
	}

}