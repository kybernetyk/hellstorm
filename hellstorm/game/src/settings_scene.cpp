//
//  settings_scene.cpp
//  hellstorm
//
//  Created by jrk on 23/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "settings_scene.h"
#include "game_factory.h"
#include "menu_scene.h"

namespace game 
{
	hs::entity *settings_scene::create_button(std::string filename, hs::vec3d pos, int tag)
	{
		hs::entity *but = 0;
		
		but = hs::ui::create_button_from_file(em, filename, pos);
		but->get<hs::ui::button>()->tag_ptr = &button_tag;
		but->get<hs::ui::button>()->tag = tag;
		
		return but;
	}
	
	//static hs::entity *text;
	static hs::entity *logo;
	static hs::entity *logo_blink;
	static 	hs::entity *alpha_shade;
	
	static double r,g,b;
	static double d;
	
	
	void settings_scene::init(void)
	{
		//hs::audio_system::play_music("Menu.mp3");
		
		em = new hs::entity_manager();
		cs = new hs::corpse_retrieval_system(em);
		rs = new hs::render_system(em);
		ps = new hs::particle_system(em);
		as = new hs::action_system(em);
		ans = new hs::animation_system(em, as);
		ui_system = new hs::ui_system(em);
		bg_system = new psycho_bg_system(em);
		
		hs::factory::create_sprite(em, "background_noraster2.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		factory::create_psycho_back(em);
		//factory::create_borders(em);
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
		
		
		create_button("play_button.cfg", 
					  hs::vec3d_make(178, 275, 0.0),
					  tag_button_resume);
		//		create_button("settings_button.cfg", 
		//						   hs::vec3d_make(110, 197, 0.0), 
		//						   e_button_settings);
		create_button("scores_button.cfg", 
					  hs::vec3d_make(200, 128, 0.0),
					  tag_button_quit);
		
		//		hs::factory::create_particle_emitter(em, "disturbed_sparks.pex", PE_DUR_FROM_FILE, hs::vec3d_make(5, 100, 9.0), true);
		//		hs::factory::create_particle_emitter(em, "disturbed_sparks.pex", PE_DUR_FROM_FILE, hs::vec3d_make(30, 460, 9.0), true);
		//		hs::factory::create_particle_emitter(em, "subtle_sparks.pex", PE_DUR_FROM_FILE, hs::vec3d_make(30, 460, 8.9), true);
		
	}
	
	void settings_scene::shutdown(void)
	{
		printf("settings scene shutdown!\n");
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
	
	void settings_scene::update(double dt)
	{
		
		d += dt * ( cos(60.0 * M_PI * dt) * M_PI ) * M_PI;
		r = sin(d);
		g = cos(d);
		b = atan(d);
		logo_blink->get<hs::comp::renderable>()->color = hs::color3f_make(r, g, b);
		
		ui_system->update(dt);
		
		switch (button_tag) 
		{
			case tag_button_resume:
				hs::audio_system::play_sound("click.mp3");
				break;
			case tag_button_quit:
				hs::audio_system::play_sound("click.mp3");
				hs::g_game->pop_scene();
				break;
			default:
				break;
		}
		button_tag = tag_button_none;
		
		ans->update(dt);
		as->update(dt);
		bg_system->update(dt);
		ps->update(dt);
		
		cs->collect_corpses();
	}
	
	void settings_scene::render()
	{
		rs->render();
	}
	
	int settings_scene::scene_type()
	{
		return 1;
	}
}