//
//  settings_scene.h
//  hellstorm
//
//  Created by jrk on 23/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "hellstorm.h"
#include "psycho_bg_system.h"

namespace game
{
	class settings_scene : public hs::scene
	{
	public:
		void init(void);
		void shutdown(void);
		
		void update(double dt);
		void render(void);
		
		int scene_type(void);
		
		
		hs::entity *create_button(std::string filename, hs::vec3d pos, int tag);
	protected:
		hs::entity_manager *em;
		hs::corpse_retrieval_system *cs;
		hs::render_system *rs;
		hs::particle_system *ps;
		hs::action_system *as;
		hs::animation_system *ans;
		hs::ui_system *ui_system;
		psycho_bg_system *bg_system;
		
		int button_tag;
		
		hs::entity *music_btn;
		hs::entity *sound_btn;
		
		static const int tag_button_none = 0;
		static const int tag_button_music = 1;
		static const int tag_button_sound = 2;
		static const int tag_button_back = 3;

		void create_sound_button();
		void toggle_sound();

		void create_music_button();
		void toggle_music();
	};
	
}