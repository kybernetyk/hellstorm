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
		
		hs::entity *create_player_pill (hs::entity_manager *em, int col, int row, int type);
		hs::entity *create_virus (hs::entity_manager *em, int col, int row, e_gbo_color type);

	}
}