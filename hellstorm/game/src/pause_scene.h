//
//  pause_scene.h
//  hellstorm
//
//  Created by jrk on 11/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "hellstorm.h"
#include "psycho_bg_system.h"

namespace game
{
	class pause_scene : public hs::scene
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
		
		static const int tag_button_none = 0;
		static const int tag_button_resume = 1;
		static const int tag_button_quit = 2;
		static const int tag_button_settings = 3;
	};

}