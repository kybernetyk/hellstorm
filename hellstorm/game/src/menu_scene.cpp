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
#include "game_globals.h"
#include "settings_scene.h"

#include <cstdio>

namespace game 
{
	menu_scene::~menu_scene()
	{
		std::printf("menu scene dtor\n");
	}
	
	static hs::entity *logo;
	static hs::entity *logo_blink;
	static hs::entity *alpha_shade;
	
	static double r,g,b;
	static double d;
	
	
	hs::entity *menu_scene::create_menu_button(std::string filename, hs::vec3d pos, int tag)
	{
		hs::entity *but = 0;
		
		but = hs::ui::create_button_from_file(em, filename, pos);
		but->get<hs::ui::button>()->tag_ptr = &button_tag;
		but->get<hs::ui::button>()->tag = tag;
		
		return but;
	}
	void menu_scene::create_difficulty_menu()
	{
		std::vector<hs::entity *>::iterator it = buttons.begin();
		
		while (it != buttons.end())
		{
			hs::entity *b = *it;
			em->add_component<hs::comp::mark_of_death>(b);
			
			b->get<hs::ui::button>()->graphic->add<hs::comp::mark_of_death>();
		
			++it;
		}
		buttons.clear();
		
		create_menu_button("easy_button.cfg", 
						   hs::vec3d_make(160, 260, 0.0),
						   e_button_easy);
		create_menu_button("medium_button.cfg", 
						   hs::vec3d_make(160, 180, 0.0),
						   e_button_medium);
		create_menu_button("hard_button.cfg", 
						   hs::vec3d_make(160, 100, 0.0),
						   e_button_hard);

	}
	void menu_scene::init(void)
	{
		hs::audio_system::play_music("Menu.mp3");
		
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
	//	factory::create_borders(em);
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
		
		hs::entity *b = create_menu_button("play_button.cfg", 
						   hs::vec3d_make(178, 275, 0.0),
						   e_button_start);
		buttons.push_back(b);
		
		b = create_menu_button("settings_button.cfg", 
						   hs::vec3d_make(110, 197, 0.0), 
						   e_button_settings);
		buttons.push_back(b);
		
		b = create_menu_button("scores_button.cfg", 
						   hs::vec3d_make(200, 128, 0.0),
						   e_button_scores);
		buttons.push_back(b);
		
		b = create_menu_button("more_button.cfg", 
						   hs::vec3d_make(145, 60, 0.0), 
						   e_button_more);
		buttons.push_back(b);
		
//		hs::factory::create_particle_emitter(em, "disturbed_sparks.pex", PE_DUR_FROM_FILE, hs::vec3d_make(5, 100, 9.0), true);
//		hs::factory::create_particle_emitter(em, "disturbed_sparks.pex", PE_DUR_FROM_FILE, hs::vec3d_make(30, 460, 9.0), true);
//		hs::factory::create_particle_emitter(em, "subtle_sparks.pex", PE_DUR_FROM_FILE, hs::vec3d_make(30, 460, 8.9), true);

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
		
		d += dt * ( cos(60.0 * M_PI * dt) * M_PI ) * M_PI;
		r = sin(d);
		g = cos(d);
		b = atan(d);
		logo_blink->get<hs::comp::renderable>()->color = hs::color3f_make(r, g, b);
		
		ui_system->update(dt);
		if (button_tag != e_button_none)
		{
			std::string fns[] = 
			{
				"wackno5.mp3",
				"Trance1.mp3",
				"RealTechno.mp3"
			};
			
			std::string s = fns[rand()%3];
				
			
			switch (button_tag) 
			{
				case e_button_start:
					create_difficulty_menu();
					break;
				
				case e_button_easy:
					global::g_state.level = 1;
					global::g_state.score = 0;		
					global::g_state.difficulty = global::difficulty_easy;
					hs::audio_system::play_music(s);
					hs::g_game->set_scene(new game_scene());
					break;
				case e_button_medium:
					global::g_state.level = 1;
					global::g_state.score = 0;		
					global::g_state.difficulty = global::difficulty_medium;
					hs::audio_system::play_music(s);
					hs::g_game->set_scene(new game_scene());
					break;
				case e_button_hard:
					global::g_state.level = 1;
					global::g_state.score = 0;		
					global::g_state.difficulty = global::difficulty_hard;
					hs::audio_system::play_music(s);
					hs::g_game->set_scene(new game_scene());
					break;
					
				case e_button_scores:
					hs::post_notification("show_highscores");
					break;
				case e_button_more:
					hs::post_notification("show_more");
					break;
					
				case e_button_settings:
					hs::g_game->push_scene(new settings_scene());
					break;
			
			}
			hs::audio_system::play_sound("click.mp3");
			button_tag = e_button_none;	
		}
		
		ans->update(dt);
		as->update(dt);
		bg_system->update(dt);
		ps->update(dt);
		
		cs->collect_corpses();
	}
	
	void menu_scene::render()
	{
		rs->render();
	}
	
	int menu_scene::scene_type()
	{
		return 1;
	}
}