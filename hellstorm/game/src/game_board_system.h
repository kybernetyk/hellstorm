//
//  game_board_system.h
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "hellstorm.h"
#include "game_utils.h"

namespace game 
{
	enum e_gbo_state
	{
		e_gbo_state_idle,
		e_gbo_state_falling
	};
	
	enum e_gbo_type
	{
		e_gbo_type_pill,
		e_gbo_type_virus
	};
	
	enum e_gbo_color
	{
		e_gbo_red = 0,
		e_gbo_blue = 1,
		e_gbo_green = 2,
		e_gbo_yellow = 3,
		e_gbo_invalid
	};
	
	struct game_board_element : public hs::component
	{
		static hs::uid family_id;
		e_gbo_state state;
		e_gbo_type type;
		e_gbo_color color;
		int col, row;
		double timer;
		double fall_time;

		game_board_element()
		{
			state = e_gbo_state_idle;
			col = row = 0;

			timer = fall_time = 1.0;
			type = e_gbo_type_pill;
			color = e_gbo_red;
		}
	};
		
	class game_board_system
	{
	public:
		game_board_system(hs::entity_manager *manager);
		~game_board_system();
		void update(double dt);

	protected:
		hs::entity_manager *em;
		hs::entity **ent_cache;
		size_t cache_size;
		
		double current_dt;
		hs::entity *current_entity;
		hs::comp::position *current_pos;
		game_board_element *current_gbo;
		
		bool can_move_down(void);
		
		void handle_state_idle(void);
		void handle_state_falling(void);
		void change_state(game_board_element *gbo, e_gbo_state new_state);
	};
}