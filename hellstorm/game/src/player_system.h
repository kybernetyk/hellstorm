//
//  player_system.h
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "hellstorm.h"
#include "game_utils.h"
#include "game_board_system.h"
#include "game_factory.h"

namespace game 
{
	struct comp_player : public hs::component
	{
		static hs::uid family_id;
		int center_col, center_row;
		int aux_col, aux_row;
		
		double timer;
		double fall_time;
		
		e_gbo_color center_color;
		e_gbo_color aux_color;
	
		factory::e_doublepill_type double_pill_type;

		comp_player()
		{
			center_col = 0, center_row = 0;
			aux_col = 1, aux_row = 0;
			
			timer = fall_time = 1.0;
			center_color = e_gbo_red;
			aux_color = e_gbo_red;
			double_pill_type = factory::e_dp_red_red;
		}
	};
	
	enum e_move_direction
	{
		e_move_left = -1,
		e_move_right = 1
	};
	

	class player_system
	{
	public:
		player_system(hs::entity_manager *manager);
		~player_system();
		void update(double dt);
		
	protected:
		hs::entity_manager *em;
		hs::entity **ent_cache;
		size_t cache_size;
		
		double current_dt;
		hs::entity *current_entity;
		hs::comp::position *current_pos;
		comp_player *player;
		
		
		void rotate(void);
		void move_left(void);
		void move_right(void);
		void move(e_move_direction dir);
		
		bool can_move_down(int num_of_rows_to_move = 1);
		
		
		void handle_state_falling(void);
	};
}