//
//  game_globals.h
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
	namespace global
	{
		extern hs::entity *board_map[defs::board_num_of_cols][defs::board_num_of_rows];
		void update_board_map(hs::entity **entities, size_t num_of_entities);
	}
}