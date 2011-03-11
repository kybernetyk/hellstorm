//
//  game_logic_system.h
//  hellstorm
//
//  Created by jrk on 26/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <stddef.h>
#include <vector>

namespace hs
{
	class entity_manager;
	class entity;
}

namespace game
{
	class hs::entity_manager;
	class hs::entity;
	struct game_board_element;
	
	class game_logic_system
	{
	public:
		game_logic_system(hs::entity_manager *manager);
		~game_logic_system();
		
		void update(double dt);
		
	protected:
		void handle_state_check_for_chains();
		void check_horizontal();
		void check_vertical();
		
		void handle_state_move_gbos();
		void handle_state_gbos_need_disconnect();
		void disconnect_pill(hs::entity *pill);
		
		std::vector<hs::entity *> marked_for_removal;
		
		hs::entity_manager *em;
		
		hs::entity **ent_cache;
		size_t cache_size;
	};
}