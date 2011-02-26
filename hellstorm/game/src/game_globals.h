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
#include "player_system.h"

namespace game
{
	namespace global
	{
		extern hs::entity *board_map[defs::board_num_of_cols][defs::board_num_of_rows];
		void update_board_map(hs::entity **entities, size_t num_of_entities);

		enum e_game_state
		{
			e_gs_unitialized,
			e_gs_idle,
			e_gs_player_need_respawn,
			e_gs_player_active,
			e_gs_player_landed,
			e_gs_player_landed_ontop,
			e_gs_check_for_chains,
			e_gs_chains_marked,
			e_gs_no_chains,
			e_gs_game_over
		};
		
		struct state
		{
			e_game_state old_state;
			e_game_state current_state;
			
			state()
			{
				old_state = current_state = e_gs_unitialized;
			}
		};
		
		extern state g_state;

	}
}