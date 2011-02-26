//
//  game_globals.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_globals.h"
#include "hellstorm.h"
#include "game_board_system.h"

namespace game 
{
	namespace global
	{
		hs::entity *board_map[defs::board_num_of_cols][defs::board_num_of_rows];
		state g_state;
		
		void update_board_map(hs::entity **entities, size_t num_of_entities)
		{
			memset(board_map, 0x00, sizeof(hs::entity *)*defs::board_num_of_cols * defs::board_num_of_rows);
			
			hs::entity *tmp;
			game_board_element *tgbo;
			for (size_t i = 0; i < num_of_entities; i++)
			{
				tmp = entities[i];
				tgbo = tmp->ent_mgr->get_component<game_board_element>(tmp);
				
				board_map[tgbo->col][tgbo->row] = tmp;
			}
		}
	}
}