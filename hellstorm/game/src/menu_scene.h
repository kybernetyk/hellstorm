//
//  menu_scene.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "hellstorm.h"
#include "psycho_bg_system.h"

namespace game
{
	enum e_menu_button_tag
	{
		e_button_none = 0,
		e_button_start = 1
	};

	class menu_scene : public hs::scene
	{
	public:
		void init(void);
		void shutdown(void);
		
		void update(double dt);
		void render(void);
		
		int scene_type(void);
		
		~menu_scene();

		hs::entity *create_menu_button(std::string caption, hs::vec3d pos, int tag);
		
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
	};
};