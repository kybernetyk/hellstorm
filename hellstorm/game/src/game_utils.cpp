//
//  game_utils.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_utils.h"
namespace game
{
	hs::vec3d pixel_for_colrow(int col, int row)
	{
		return hs::vec3d_make((col*32) + defs::board_x_offset, (row*32)+defs::board_y_offset, defs::board_z);
	}

	hs::vec3d pixel_for_colrow(double col, double row)
	{
		return hs::vec3d_make((col*32.0) + defs::board_x_offset, (row*32.0)+defs::board_y_offset, defs::board_z);
	}

}