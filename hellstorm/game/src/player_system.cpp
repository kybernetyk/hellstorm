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
		double rot = current_pos->rot + 90.0;

		int col_offset = cos(DEG2RAD(rot));
		int row_offset = sin(DEG2RAD(rot));

		int test_col = player->center_col + col_offset;
		//int test_row = player->center_row + row_offset;
		
		int test_row = (current_pos->origin.y-defs::board_y_offset)/32.0 + row_offset;

//			return hs::vec3d_make((col*32.0) + defs::board_x_offset, (row*32.0)+defs::board_y_offset, defs::board_z);

		
		if (test_col < 0 || 
			test_row < 0 || 
			test_col >= defs::board_num_of_cols || 
			test_row >= defs::board_num_of_rows)
			return;
		
	

//		
//
//		hs::entity *test_ent = global::board_map[test_col][test_row];
//		if (test_ent)
//		{
//			hs::rect aux_rc;
//			aux_rc.x = current_pos->origin.x - 16 + col_offset * 32.0;
//			aux_rc.y = current_pos->origin.y - 16 + row_offset * 32.0;
//			aux_rc.w = 32.0;
//			aux_rc.h = 30.0;
//
//			hs::rect test_rc;
//			hs::vec3d test_pos = pixel_for_colrow(test_col, test_row);
//			test_rc.x = test_pos.x - 16.0;
//			test_rc.y = test_pos.y - 16.0;
//			test_rc.w = 32.0;
//			test_rc.h = 30.0;
//			
//			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
//				test_rc.h = 26.0;
//			
//			if (hs::rect_intersect_rect(&aux_rc, &test_rc))
//				return;
//
//		}
		
		if (global::board_map[test_col][test_row])
			return;
		
		current_pos->rot += 90.0;
		if (current_pos->rot >= 360.0)
			current_pos->rot = 0.0;

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

		/* center */
		if (global::board_map[c_test_col][player->center_row])
		{	
			hs::entity *test_ent = global::board_map[c_test_col][player->center_row];
			
			hs::rect center_rc;
			center_rc.x = current_pos->origin.x - 16;
			center_rc.y = current_pos->origin.y - 16;
			center_rc.w = 32.0;
			center_rc.h = 30.0;

			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(c_test_col, player->center_row);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;
			
			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&center_rc, &test_rc))
				return;
		}
		
		if (player->center_row > 0 && global::board_map[c_test_col][player->center_row-1])
		{			
			hs::entity *test_ent = global::board_map[c_test_col][player->center_row-1];

			hs::rect center_rc;
			center_rc.x = current_pos->origin.x - 16;
			center_rc.y = current_pos->origin.y - 16;
			center_rc.w = 32.0;
			center_rc.h = 30.0;
			
			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(c_test_col, player->center_row-1);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;

			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&center_rc, &test_rc))
				return;
		}
		/* -- center */
		
		/* aux */
		if (global::board_map[a_test_col][player->aux_row])
		{	
			hs::entity *test_ent = global::board_map[a_test_col][player->aux_row];
			
			hs::rect aux_rc;
			aux_rc.x = current_pos->origin.x - 16;
			aux_rc.y = current_pos->origin.y - 16;
			aux_rc.w = 32.0;
			aux_rc.h = 30.0;
			
			int diff = player->aux_row - player->center_row;
			aux_rc.y += diff * 32.0;
			diff = player->aux_col - player->center_col;
			aux_rc.x += diff * 32.0;
			
			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(a_test_col, player->aux_row);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;
			
			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&aux_rc, &test_rc))
				return;
		}

		if (player->aux_row > 0 && global::board_map[a_test_col][player->aux_row-1])
		{	
			hs::entity *test_ent = global::board_map[a_test_col][player->aux_row-1];
			
			hs::rect aux_rc;
			aux_rc.x = current_pos->origin.x - 16;
			aux_rc.y = current_pos->origin.y - 16;
			aux_rc.w = 32.0;
			aux_rc.h = 30.0;
			
			int diff = player->aux_row - player->center_row;
			aux_rc.y += diff * 32.0;
			diff = player->aux_col - player->center_col;
			aux_rc.x += diff * 32.0;
			
			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(a_test_col, player->aux_row-1);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;
			
			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&aux_rc, &test_rc))
				return;
		}


		/* -- aux */
		
		player->center_col = c_test_col;
		player->aux_col = a_test_col;

		
//		int c_test_col = player->center_col - 1;
//		int a_test_col = player->aux_col - 1;
//		
//		if (c_test_col < 0 || c_test_col >= defs::board_num_of_cols)
//			return;
//		if (a_test_col < 0 || a_test_col >= defs::board_num_of_cols)
//			return;
//		
//		if (global::board_map[c_test_col][player->center_row] ||
//			global::board_map[a_test_col][player->aux_row])
//			return;
//		
//		player->center_col = c_test_col;
//		player->aux_col = a_test_col;
	}
	
	void player_system::move_right(void)
	{
		int c_test_col = player->center_col + 1;
		int a_test_col = player->aux_col + 1;
		
		if (c_test_col < 0 || c_test_col >= defs::board_num_of_cols)
			return;
		if (a_test_col < 0 || a_test_col >= defs::board_num_of_cols)
			return;
		
		/* center */
		if (global::board_map[c_test_col][player->center_row])
		{	
			hs::entity *test_ent = global::board_map[c_test_col][player->center_row];
			
			hs::rect center_rc;
			center_rc.x = current_pos->origin.x - 16;
			center_rc.y = current_pos->origin.y - 16;
			center_rc.w = 32.0;
			center_rc.h = 30.0;
			
			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(c_test_col, player->center_row);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;
			
			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&center_rc, &test_rc))
				return;
		}
		
		if (player->center_row > 0 && global::board_map[c_test_col][player->center_row-1])
		{			
			hs::entity *test_ent = global::board_map[c_test_col][player->center_row-1];
			
			hs::rect center_rc;
			center_rc.x = current_pos->origin.x - 16;
			center_rc.y = current_pos->origin.y - 16;
			center_rc.w = 32.0;
			center_rc.h = 30.0;
			
			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(c_test_col, player->center_row-1);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;
			
			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&center_rc, &test_rc))
				return;
		}
		/* -- center */
		
		/* aux */
		if (global::board_map[a_test_col][player->aux_row])
		{	
			hs::entity *test_ent = global::board_map[a_test_col][player->aux_row];
			
			hs::rect aux_rc;
			aux_rc.x = current_pos->origin.x - 16;
			aux_rc.y = current_pos->origin.y - 16;
			aux_rc.w = 32.0;
			aux_rc.h = 30.0;
			
			int diff = player->aux_row - player->center_row;
			aux_rc.y += diff * 32.0;
			diff = player->aux_col - player->center_col;
			aux_rc.x += diff * 32.0;
			
			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(a_test_col, player->aux_row);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;
			
			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&aux_rc, &test_rc))
				return;
		}
		
		if (player->aux_row > 0 && global::board_map[a_test_col][player->aux_row-1])
		{	
			hs::entity *test_ent = global::board_map[a_test_col][player->aux_row-1];
			
			hs::rect aux_rc;
			aux_rc.x = current_pos->origin.x - 16;
			aux_rc.y = current_pos->origin.y - 16;
			aux_rc.w = 32.0;
			aux_rc.h = 30.0;
			
			int diff = player->aux_row - player->center_row;
			aux_rc.y += diff * 32.0;
			diff = player->aux_col - player->center_col;
			aux_rc.x += diff * 32.0;
			
			hs::rect test_rc;
			hs::vec3d test_pos = pixel_for_colrow(a_test_col, player->aux_row-1);
			test_rc.x = test_pos.x - 16.0;
			test_rc.y = test_pos.y - 16.0;
			test_rc.w = 32.0;
			test_rc.h = 30.0;
			
			if (test_ent->get<game_board_element>()->type == e_gbo_type_virus)
				test_rc.h = 26.0;
			
			if (hs::rect_intersect_rect(&aux_rc, &test_rc))
				return;
		}

		
//		if (global::board_map[c_test_col][player->center_row] ||
//			global::board_map[a_test_col][player->aux_row])
//			return;
//
		player->center_col = c_test_col;
		player->aux_col = a_test_col;
	}
	
	void player_system::handle_state_falling(void)
	{
		if (player->timer < 0.25)
		{
			if (can_move_down())
				current_pos->origin.y -= current_dt * (1.0/0.25) * 32.0;
		}

		player->timer -= current_dt;

		
		if (player->timer <= 0.0)
		{
			player->timer = player->fall_time;
			player->minxy = false;
			
			if (!can_move_down())
			{
				current_entity->add<hs::comp::mark_of_death>();
				current_pos->origin = pixel_for_colrow(player->center_col, player->center_row);
				
				hs::entity *center = factory::create_pill(em, player->center_col, player->center_row, player->double_pill_type, factory::left);
				hs::entity *aux = factory::create_pill(em, player->aux_col, player->aux_row, player->double_pill_type, factory::right);
				
				center->get<hs::comp::position>()->rot = current_pos->rot;
				aux->get<hs::comp::position>()->rot = current_pos->rot;
				
				if (player->center_row < defs::board_num_of_rows-1 &&
					player->aux_row < defs::board_num_of_rows-1)
					global::g_state.current_state = global::e_gs_player_landed;
				else
					global::g_state.current_state = global::e_gs_player_landed_ontop;
				
				
				printf("NAO IS THE LANDED!\n");
				return;
			}
			
			player->center_row--;
			player->aux_row--;
			
			current_pos->origin = pixel_for_colrow(player->center_col, player->center_row);
		}

	
		current_pos->origin.x = pixel_for_colrow(player->center_col, player->center_row).x;

	}
	
	bool player_system::can_move_down(int num_of_rows_to_move)
	{
		int cc, cr;
		int ac, ar;
		
		cc = player->center_col;
		cr = player->center_row;
		
		ac = player->aux_col;
		ar = player->aux_row;
		
		cr -= num_of_rows_to_move;
		ar -= num_of_rows_to_move;	
		
		if (cr < 0 || ar < 0)
			return false;
		
		if (global::board_map[cc][cr] || 
			global::board_map[ac][ar])
			return false;
		
		return true;
	}

}