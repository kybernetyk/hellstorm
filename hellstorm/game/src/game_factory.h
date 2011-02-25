//
//  game_factory.h
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "hellstorm.h"
#include "game_board_system.h"

namespace game 
{
	namespace factory
	{
		void create_psycho_back(hs::entity_manager *em);
		void create_borders(hs::entity_manager *em);
		void create_raster(hs::entity_manager *em);
		
		
		enum e_doublepill_type
		{
			e_dp_red_red,
			e_dp_green_red,
			e_dp_yellow_red,
			e_dp_blue_red,
			
			e_dp_red_green,
			e_dp_green_green,
			e_dp_yellow_green,
			e_dp_blue_green,
			
			e_dp_red_yellow,
			e_dp_green_yellow,
			e_dp_yellow_yellow,
			e_dp_blue_yellow,
			
			e_dp_red_blue,
			e_dp_green_blue,
			e_dp_yellow_blue,
			e_dp_blue_blue
		};

		enum e_singlepill_type
		{
			e_sp_red_right,
			e_sp_green_right,
			e_sp_yellow_right,
			e_sp_blue_right,
			e_sp_red_left,
			e_sp_green_left,
			e_sp_yellow_left,
			e_sp_blue_left
		};
		
		enum e_left_right
		{
			left,
			right
		};
		
		//player controlled pill
		hs::entity *create_player_pill(hs::entity_manager *em, int col, int row, e_doublepill_type type);

		//static pill (half)
		hs::entity *create_pill(hs::entity_manager *em, int col, int row, e_doublepill_type type, e_left_right subtype);
		
		//virus
		hs::entity *create_virus(hs::entity_manager *em, int col, int row, e_gbo_color type);
	}
}