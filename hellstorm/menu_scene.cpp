//
//  menu_scene.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "menu_scene.h"
#include "hellstorm.h"
#include <cstdio>

namespace test_game 
{
	hs::entity_manager *em;
	hs::corpse_retrieval_system *cs;
	hs::render_system *rs;
	hs::particle_system *ps;
	
	double d = 0.0;
	
	menu_scene::~menu_scene()
	{
		std::printf("menu scene dtor\n");
	}
	
	void menu_scene::init(void)
	{
		hs::audio_system::preload_sound("click.mp3");
		hs::audio_system::preload_music("music.mp3");
		
		em = new hs::entity_manager();
		cs = new hs::corpse_retrieval_system(em);
		rs = new hs::render_system(em);
		ps = new hs::particle_system(em);

		
		hs::factory::create_sprite("game_back.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		
		hs::factory::create_text_label("impact20.fnt", "oh hai!", hs::vec3d_screen_center());

		hs::factory::create_atlas_sprite("bubbles.png", hs::vec3d_make(rand()%320, rand()%480, -1.0), hs::rect_make(0.0, 0.0, 41.0, 41.0));

		//		
		for (int i = 0; i < hs::cfg::entity_system.entity_pool_size-20; i++)
		{
			hs::factory::create_atlas_sprite("bubbles.png", hs::vec3d_make(rand()%320, rand()%480, -1.0), hs::rect_make(0.0, 0.0, 41.0, 41.0));
		}
		
		hs::factory::create_particle_emitter("cool.pex", -1.0, hs::vec3d_screen_center(-2.0), true);
		hs::audio_system::play_music("music.mp3");
	}
	
	void menu_scene::shutdown(void)
	{
		delete ps;
		delete rs;
		
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
		
		d += dt;
		if (d >= 1.0)
		{
			d = 0.0;
			hs::audio_system::play_sound("click.mp3");
		}
		
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