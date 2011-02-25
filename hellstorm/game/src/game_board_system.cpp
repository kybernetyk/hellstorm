//
//  game_board_system.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_board_system.h"
#include "game_utils.h"
namespace game 
{
	hs::uid game_board_element::family_id = 0;
	
	game_board_system::game_board_system(hs::entity_manager *manager)
	{
		em = manager;
		hs::comp::register_component_class<game_board_element>();
		
		ent_cache = new hs::entity*[hs::cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
		
		memset(ent_map, 0x00, sizeof(hs::entity *)*defs::board_num_of_cols * defs::board_num_of_rows);
	}
	
	game_board_system::~game_board_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}
	
	void game_board_system::make_map(void)
	{
		memset(ent_map, 0x00, sizeof(hs::entity *)*defs::board_num_of_cols * defs::board_num_of_rows);
		
		hs::entity *tmp;
		game_board_element *tgbo;
		for (size_t i = 0; i < cache_size; i++)
		{
			tmp = ent_cache[i];
			tgbo = em->get_component<game_board_element>(tmp);
			
			ent_map[tgbo->col][tgbo->row] = tmp;
		}
			
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

		make_map();
		
		for (size_t i = 0; i < cache_size; i++)
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
					handle_state_falling();
				default:
					break;
			}
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
		
		hs::entity *e = ent_map[col][row];
		if (e)
			return false;
		
		return true;
	}
	
#pragma mark -
#pragma mark handle state
	void game_board_system::change_state(e_gbo_state new_state)
	{
		current_gbo->state = new_state;
	}
	
	
	void game_board_system::handle_state_idle(void)
	{
		
	}
	
	void game_board_system::handle_state_falling(void)
	{
		current_gbo->timer -= current_dt;

		if (current_gbo->timer <= 0.0)
		{
			current_gbo->timer = current_gbo->fall_time;
			current_gbo->row--;
		}
		
		if (!can_move_down())
			change_state(e_gbo_state_idle);
		
		current_pos->origin = pixel_for_colrow(current_gbo->col, current_gbo->row);
	}
}