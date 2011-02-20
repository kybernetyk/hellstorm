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
	hs::action_system *as;
	
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
		as = new hs::action_system(em);
		
		hs::factory::create_sprite("game_back.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		
		hs::factory::create_text_label("impact20.fnt", "oh hai!", hs::vec3d_screen_center());

		hs::factory::create_atlas_sprite("bubbles.png", hs::vec3d_make(rand()%320, rand()%480, -1.0), hs::rect_make(0.0, 0.0, 41.0, 41.0));

		//		
		for (int i = 0; i < hs::cfg::entity_system.entity_pool_size-20; i++)
		{
			hs::factory::create_atlas_sprite("bubbles.png", hs::vec3d_make(rand()%320, rand()%480, -1.0), hs::rect_make(0.0, 0.0, 41.0, 41.0));
		}
		
		hs::entity *fire = hs::factory::create_particle_emitter("cool.pex", -1.0, hs::vec3d_screen_center(1.0), true);
		hs::audio_system::play_music("music.mp3");
		
		/*hs::move_by_action *actn = new hs::move_by_action(10.0, hs::vec2d_make(100.0, 100.0));
		as->add_action_to_entity(fire, actn);
		
		actn->append_action( new hs::move_to_action(10.0, hs::vec2d_make(0.0, 0.0)) );*/
		
		
		hs::action *a = new hs::move_by_action(10.0, hs::vec2d_make(100.0, 0.0));
		hs::action *b = new hs::move_by_action(10.0, hs::vec2d_make(0.0, 100.0));

		a->append_action(b);
		a->append_action(new hs::move_to_action(10.0, hs::vec2d_screen_center()));
		
		as->add_action_to_entity(fire, a);
		
//		as->add_action_to_entity(fire, b);
		
	/*	
		hs::move_to_action *actn2 = new hs::move_to_action();
		actn2->destination = hs::vec2d_make(0.0, 480.0);
		actn2->duration = 5.0;
		hs::action_append_action(actn, actn2);
		
		hs::move_to_action *actn3 = new hs::move_to_action();
		actn3->destination = hs::vec2d_make(320.0, 480.0);
		actn3->duration = 2.0;
		hs::action_append_action(actn, actn3);

		hs::move_to_action *actn4 = new hs::move_to_action();
		actn4->destination = hs::vec2d_make(320.0, 0);
		actn4->duration = 5.0;
		hs::action_append_action(actn, actn4);

		hs::move_to_action *actn5 = new hs::move_to_action();
		actn5->destination = hs::vec2d_screen_center();
		actn5->duration = 2.0;
		hs::action_append_action(actn, actn5);
*/		
		
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
		
		d += dt;
		if (d >= 1.0)
		{
			d = 0.0;
			hs::audio_system::play_sound("click.mp3");
		}

		as->update(dt);		
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