//
//  game_utils.h
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#import "hellstorm.h"

namespace game 
{
	namespace defs
	{
		const double board_x_offset = 64.0;
		const double board_y_offset = 32.0;
		const double board_z = 0.0;
		
		const int board_num_of_cols = 7;
		const int board_num_of_rows = 12;
	}

	hs::vec3d pixel_for_colrow(int col, int row);
	hs::vec3d pixel_for_colrow(double col, double row);
}