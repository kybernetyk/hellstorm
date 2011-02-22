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

#include <cstdio>

namespace game 
{
	hs::entity_manager *em;
	hs::corpse_retrieval_system *cs;
	hs::render_system *rs;
	hs::particle_system *ps;
	hs::action_system *as;
	hs::animation_system *ans;

	psycho_bg_system *bg_system;
	
	double d = 0.0;
	
	menu_scene::~menu_scene()
	{
		std::printf("menu scene dtor\n");
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
		
		bg_system = new psycho_bg_system(em);
		
		factory::create_psycho_back(em);
		factory::create_borders_and_raster(em);

	}
	
	void menu_scene::shutdown(void)
	{
		delete ps;
		delete rs;
		delete as;
		
		em->remove_all_entities();
		delete em;
	}
	
	void menu_scene::update(double dt)
	{
		//we must collect the corpses from the last frame
		//as the entity-manager's isDirty property is reset each frame
		//so if we did corpse collection at the end of update
		//the systems wouldn't know that the manager is dirty 
		//and a shitstorm of dangling references would rain down on them
		cs->collect_corpses();
		

		ans->update(dt);
		as->update(dt);
		bg_system->update(dt);
		ps->update(dt);
		
		if (hs::g_input.has_touched_down())
			printf("has touched down!\n");
		if (hs::g_input.has_moved())
			printf("has moved!\n");
		if (hs::g_input.has_touched_up())
			printf("has touched up!\n");
		
		/*
		if (hs::g_input.get_last_event() != hs::inputevent_none)
		{
			printf("last input event: %i\n", hs::g_input.get_last_event());
		}*/
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