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
				bool valid = true;
				if (hs::g_input.get_current_touch_location().y > 440 &&
					hs::g_input.get_current_touch_location().x > 280)
					valid = false;
				
				if (valid)
				{
					if (hs::g_input.get_current_touch_location().y > 400)
					{
						if (hs::g_input.get_current_touch_location().x < 160)
							rotate_ccw();
						else
							rotate_cw();
					}

					if (hs::g_input.get_current_touch_location().y > 100 &&
						hs::g_input.get_current_touch_location().y < 400 )
					{
						if (hs::g_input.get_current_touch_location().x < 160)
						{
							move_left();
						}
						else
						{
							move_right();
						}
					}

					if (hs::g_input.get_current_touch_location().y < 100)
					{
						player->fast_drop = true;
						player->timer = 0.1;
					}
				}
			}
			
			if (hs::g_input.has_touched_up())
			{
				if (player->fast_drop)
				{
					player->fast_drop = false;
//					player->timer = player->fall_time * global::g_state.difficulty;
				}
			}
			handle_state_falling();
		}
	}

	bool player_system::rotate_ccw(void)
	{
		if (current_pos->rot >= 360.0)
			current_pos->rot = 0.0;

		double rot = current_pos->rot + 90.0;

		int col_offset = cos(DEG2RAD(rot));
		int row_offset = sin(DEG2RAD(rot));

		int test_col = player->center_col + col_offset;
		int test_row = (current_pos->origin.y-defs::board_y_offset)/32.0 + row_offset;
		
		if (test_col < 0 || 
			test_row < 0 || 
			test_col >= defs::board_num_of_cols || 
			test_row >= defs::board_num_of_rows)
			return false;
		
		if (global::board_map[test_col][test_row])
			return false;
		
		current_pos->rot += 90.0;
		if (current_pos->rot >= 360.0)
			current_pos->rot = 0.0;

		player->aux_col = player->center_col + col_offset;
		player->aux_row = player->center_row + row_offset;
		
		hs::audio_system::play_sound("pill_rotate3.wav");
		return true;
	}
	
	bool player_system::rotate_cw(void)
	{
		if (current_pos->rot <= 0.0)
			current_pos->rot = 360.0;

		double rot = current_pos->rot - 90.0;
		
		int col_offset = cos(DEG2RAD(rot));
		int row_offset = sin(DEG2RAD(rot));
		
		int test_col = player->center_col + col_offset;
		int test_row = (current_pos->origin.y-defs::board_y_offset)/32.0 + row_offset;
		
		if (test_col < 0 || 
			test_row < 0 || 
			test_col >= defs::board_num_of_cols || 
			test_row >= defs::board_num_of_rows)
			return false;
		
		if (global::board_map[test_col][test_row])
			return false;
		
		current_pos->rot -= 90.0;
		if (current_pos->rot <= 0.0)
			current_pos->rot = 360.0;
		
		player->aux_col = player->center_col + col_offset;
		player->aux_row = player->center_row + row_offset;
		
		hs::audio_system::play_sound("pill_rotate3.wav");
		return true;
	}
	

	void player_system::move(e_move_direction dir)
	{
		int c_test_col = player->center_col + (int)dir;
		int a_test_col = player->aux_col + (int)dir;
		
		if (c_test_col < 0 || c_test_col >= defs::board_num_of_cols)
			return;
		if (a_test_col < 0 || a_test_col >= defs::board_num_of_cols)
			return;
		
		/*
		 * we're building here bounding boxes from row/col pairs
		 * to get more accurate collision detection than just checking the
		 * empty places in the map
		 */
		
		/* check player center pill */
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
		
		/* check player aux pill */
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
		hs::audio_system::play_sound("pill_move.m4a");
	}
	
	void player_system::move_left(void)
	{
		move(e_move_left);
	}
	
	void player_system::move_right(void)
	{
		move(e_move_right);
	}
	
	void player_system::update_shading()
	{
		hs::entity *shading = em->get_entity_by_guid(player->shading_guid);
		if ((int)current_pos->rot == 0 || (int)current_pos->rot == 360)
		{
			shading->get<hs::comp::position>()->origin.x = current_pos->origin.x;
			shading->get<hs::comp::position>()->origin.y = current_pos->origin.y;
			shading->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(0, 416, 64, 32);
		}
		
		if ((int)current_pos->rot == 90)
		{
			shading->get<hs::comp::position>()->origin.x = current_pos->origin.x-8.0;
			shading->get<hs::comp::position>()->origin.y = current_pos->origin.y+16.0;
			shading->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(64, 416, 32, 64);
		}
		
		if ((int)current_pos->rot == 180)
		{
			shading->get<hs::comp::position>()->origin.x = current_pos->origin.x-30.0;
			shading->get<hs::comp::position>()->origin.y = current_pos->origin.y;
			shading->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(0, 416, 64, 32);
		}
		
		if ((int)current_pos->rot == 270)
		{
			shading->get<hs::comp::position>()->origin.x = current_pos->origin.x-8.0;
			shading->get<hs::comp::position>()->origin.y = current_pos->origin.y-14.0;
			shading->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(64, 416, 32, 64);
		}

	}
	
	void player_system::handle_state_falling(void)
	{
		//maybe move below <= 0.0 ?
		if (!player->fast_drop && player->timer < 0.20)
		{
			if (can_move_down())
				current_pos->origin.y -= current_dt * (1.0/0.20) * 32.0;
		}

		player->timer -= current_dt;
//		printf("%.2f\n", player->timer);
//		printf("fall time: %f\n", player->fall_time);
//		printf("diff: %i\n",global::g_state.difficulty);
		if (player->timer <= 0.0)
		{
			switch (global::g_state.difficulty) 
			{
				case global::difficulty_easy:
					player->timer = 2.0;
					break;
				case global::difficulty_medium:
					player->timer = 1.5;
					break;
				case global::difficulty_hard:
					player->timer = 1.0;
					break;
				default:
					break;
			}

//			player->timer = player->fall_time * global::g_state.difficulty;
			if (player->fast_drop)
				player->timer = 0.1;
			
			
			if (!can_move_down())
			{
				current_entity->add<hs::comp::mark_of_death>();
				current_pos->origin = pixel_for_colrow(player->center_col, player->center_row);
				
				hs::entity *center = factory::create_pill(em, player->center_col, player->center_row, player->double_pill_type, factory::left);
				hs::entity *aux = factory::create_pill(em, player->aux_col, player->aux_row, player->double_pill_type, factory::right);
				
				center->get<game_board_element>()->connected_to_guid = aux->guid;
				aux->get<game_board_element>()->connected_to_guid = center->guid;
				
				center->get<hs::comp::position>()->rot = current_pos->rot;
				aux->get<hs::comp::position>()->rot = current_pos->rot;
				
	
				hs::entity *shading_center = hs::factory::create_atlas_sprite(em, 
																	   "game_sheet.png",
																	   pixel_for_colrow(player->center_col, player->center_row),
																	   hs::rect_make(0, 416, 32, 32));
//				shading_center->get<hs::comp::renderable>()->alpha = 0.9;
				shading_center->get<hs::comp::position>()->origin.z = defs::board_z+0.5;
				center->get<game_board_element>()->shading_guid = shading_center->guid;

				hs::entity *shading_aux = hs::factory::create_atlas_sprite(em, 
																			  "game_sheet.png",
																			  pixel_for_colrow(player->center_col, player->center_row),
																			  hs::rect_make(32, 416, 32, 32));
//				shading_aux->get<hs::comp::renderable>()->alpha = 0.9;
				shading_aux->get<hs::comp::position>()->origin.z = defs::board_z+0.5;
				aux->get<game_board_element>()->shading_guid = shading_aux->guid;

								
				if ((int)current_pos->rot == 0 || (int)current_pos->rot == 360)
				{
					shading_center->get<hs::comp::position>()->origin.x = current_pos->origin.x;
					shading_center->get<hs::comp::position>()->origin.y = current_pos->origin.y;
					
					shading_aux->get<hs::comp::position>()->origin.x = current_pos->origin.x + 32;
					shading_aux->get<hs::comp::position>()->origin.y = current_pos->origin.y;

					shading_center->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(0, 416, 32, 32);
					shading_aux->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(32, 416, 32, 32);					
				}
				
				if ((int)current_pos->rot == 90)
				{
					shading_center->get<hs::comp::position>()->origin.x = current_pos->origin.x;
					shading_center->get<hs::comp::position>()->origin.y = current_pos->origin.y;
					
					shading_aux->get<hs::comp::position>()->origin.x = current_pos->origin.x;
					shading_aux->get<hs::comp::position>()->origin.y = current_pos->origin.y+32;
					
					shading_center->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(64, 448, 32, 32);
					shading_aux->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(64, 416, 32, 32);			
				}
				
				if ((int)current_pos->rot == 180)
				{
					shading_center->get<hs::comp::position>()->origin.x = current_pos->origin.x+2;
					shading_center->get<hs::comp::position>()->origin.y = current_pos->origin.y;
					
					shading_aux->get<hs::comp::position>()->origin.x = current_pos->origin.x-30;
					shading_aux->get<hs::comp::position>()->origin.y = current_pos->origin.y;
					
					shading_center->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(32, 416, 32, 32);
					shading_aux->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(0, 416, 32, 32);					
				}
				
				if ((int)current_pos->rot == 270)
				{
					shading_center->get<hs::comp::position>()->origin.x = current_pos->origin.x;
					shading_center->get<hs::comp::position>()->origin.y = current_pos->origin.y+2;
					
					shading_aux->get<hs::comp::position>()->origin.x = current_pos->origin.x;
					shading_aux->get<hs::comp::position>()->origin.y = current_pos->origin.y-30;
					
					shading_center->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(64, 416, 32, 32);
					shading_aux->get<hs::comp::atlas_sprite>()->src_rect = hs::rect_make(64, 448, 32, 32);					
				}

				em->get_entity_by_guid(player->shading_guid)->add<hs::comp::mark_of_death>();
				//em->remove_entity(em->get_entity_by_guid(player->shading_guid)->manager_id);
				
				if (player->center_row < defs::player_spawn_row &&
					player->aux_row < defs::player_spawn_row)
					global::g_state.current_state = global::e_gs_player_landed;
				else
					global::g_state.current_state = global::e_gs_player_landed_ontop;

				hs::audio_system::play_sound("pill_land.m4a");
				return;
			}
			
			hs::audio_system::play_sound("pill_move.m4a");
			
			player->center_row--;
			player->aux_row--;
			
			current_pos->origin = pixel_for_colrow(player->center_col, player->center_row);
			update_shading();
			return;
		}

		current_pos->origin.x = pixel_for_colrow(player->center_col, player->center_row).x;
		update_shading();
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