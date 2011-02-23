//
//  menu_scene.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "menu_scene.h"
#include "hellstorm.h"

#include "psycho_bg_system.h"
#include "game_factory.h"
#include "game_scene.h"

#include <cstdio>

namespace game 
{
	menu_scene::~menu_scene()
	{
		std::printf("menu scene dtor\n");
	}
	
	hs::entity *text;
	hs::entity *logo;
	hs::entity *logo_blink;
	hs::entity *alpha_shade;
	
	double r,g,b;
	double d;
	
	
	hs::entity *menu_scene::create_menu_button(std::string caption, hs::vec3d pos, int tag)
	{
		hs::entity *but = 0;
		
		but = hs::ui::creat_button_from_file(em, "menu_button.cfg", hs::vec3d_screen_center(), "play!");
		but->get<hs::ui::button>()->tag_ptr = &button_tag;
		but->get<hs::ui::button>()->tag = tag;
		
		return but;
	}
	
	void menu_scene::init(void)
	{
		hs::audio_system::preload_sound("click.mp3");
		hs::audio_system::preload_music("music.mp3");
		hs::audio_system::play_music("music.mp3");
		
		em = new hs::entity_manager();
		cs = new hs::corpse_retrieval_system(em);
		rs = new hs::render_system(em);
		ps = new hs::particle_system(em);
		as = new hs::action_system(em);
		ans = new hs::animation_system(em, as);
		ui_system = new hs::ui_system(em);
		bg_system = new psycho_bg_system(em);
		
		hs::factory::create_sprite(em, "background_noraster.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		factory::create_psycho_back(em);
		factory::create_borders(em);
		factory::create_raster(em);
		
		logo = hs::factory::create_sprite(em, "logo.png", 
										  hs::vec3d_make(160, 400, 6.0), 
										  hs::anchor_center);
		logo_blink = hs::factory::create_sprite(em, "logo_blink.png", 
										  hs::vec3d_make(160, 400, 6.1), 
										  hs::anchor_center);
//		logo_blink->get<hs::comp::renderable>()->alpha = 0.5;
		
		alpha_shade = hs::factory::create_sprite(em, "logo_blink.png", 
										  hs::vec3d_make(160, 400, 6.2), 
										  hs::anchor_center);
		alpha_shade->get<hs::comp::renderable>()->alpha = 0.5;
//		
		//		logo->get<hs::comp::position>()->scale = hs::vec2d_make(1.9, 1.9);
//		
//		hs::entity *e = hs::factory::create_sprite(em, "logo.png", 
//								   hs::vec3d_make(160, 400, 6.1), 
//								   hs::anchor_center);
//		e->get<hs::comp::renderable>()->alpha = 0.5;
//		e->get<hs::comp::position>()->scale = hs::vec2d_make(1.9, 1.9);
		
		
		//text = hs::factory::create_text_label(em, "impact20.fnt", "Tap Screen To Play!", hs::vec3d_screen_center(0.0));
		
		create_menu_button("play", hs::vec3d_screen_center(0.0), e_button_start);
	}
	
	void menu_scene::shutdown(void)
	{
		em->remove_all_entities();
		delete em;
		delete cs;
		delete rs;
		delete ps;
		delete as;
		delete ans;
		delete bg_system;
		delete ui_system;
	}
	
	void menu_scene::update(double dt)
	{
		//we must collect the corpses from the last frame
		//as the entity-manager's isDirty property is reset each frame
		//so if we did corpse collection at the end of update
		//the systems wouldn't know that the manager is dirty 
		//and a shitstorm of dangling references would rain down on them
		cs->collect_corpses();
		
		d += dt * ( cos(60.0 * M_PI * dt) * M_PI ) * M_PI;
		r = sin(d);
		g = cos(d);
		b = atan(d);
		logo_blink->get<hs::comp::renderable>()->color = hs::color3f_make(r, g, b);
		
		ui_system->update(dt);
		if (button_tag != e_button_none)
		{
			switch (button_tag) 
			{
				case e_button_start:
					hs::g_game->push_scene(new game_scene());
					break;
			}
			button_tag = e_button_none;			
		}
		
		
		
		ans->update(dt);
		as->update(dt);
		bg_system->update(dt);
		ps->update(dt);
	}
	
	void menu_scene::render()
	{
		rs->render();
		
		em->is_dirty = false;
	}
	
	int menu_scene::scene_type()
	{
		return 1;
	}
}