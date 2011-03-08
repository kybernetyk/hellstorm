//
//  game_scene.h
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "hellstorm.h"
#include "psycho_bg_system.h"
#include "game_board_system.h"
#include "player_system.h"
#include "game_logic_system.h"
#include "hud_system.h"
#include "popup_system.h"

namespace game 
{
	
	class game_scene : public hs::scene
	{
	public:
		void init(void);
		void shutdown(void);
		
		void update(double dt);
		void render(void);
		
		int scene_type(void);
		
		~game_scene();

	protected:
		void handle_state_changes(void);
		void create_next_level_button();
		void next_level_button_pressed();
		int pressed_button;
		
		hs::entity_manager *em;
		hs::corpse_retrieval_system *cs;
		hs::render_system *rs;
		hs::particle_system *ps;
		hs::action_system *as;
		hs::animation_system *ans;
		hs::ui_system *ui_sys;
		
		psycho_bg_system *bg_system;
		game_board_system *gb_system;
		player_system *plr_system;
		game_logic_system *logic_system;
		hud_system *hud_sys;
		popup_system *popup_sys;
	};

}