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
	hs::animation_system *ans;
	
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
		ans = new hs::animation_system(em, as);
		
		hs::entity *back = hs::factory::create_sprite("game_back.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		
		hs::factory::create_text_label("impact20.fnt", "oh hai!", hs::vec3d_screen_center());

//		hs::factory::create_atlas_sprite("bubbles.png", hs::vec3d_make(rand()%320, rand()%480, -1.0), hs::rect_make(0.0, 0.0, 41.0, 41.0));
//
//		//		
//		for (int i = 0; i < 220; i++)
//		{
//			hs::factory::create_atlas_sprite("bubbles.png", hs::vec3d_make(rand()%320, rand()%480, -1.0), hs::rect_make(0.0, 0.0, 41.0, 41.0));
//		}
		
		hs::audio_system::play_music("music.mp3");

		hs::entity *fire = hs::factory::create_particle_emitter("cool.pex", PE_LOOP, hs::vec3d_screen_center(1.0), true);
		hs::factory::create_particle_emitter("tss.pex", PE_LOOP, hs::vec3d_make(320/2, 480, 4.0), true);
		hs::factory::create_particle_emitter("stars.pex", PE_LOOP, hs::vec3d_make(0, 0, 4.0), true);
		hs::factory::create_particle_emitter("stars.pex", PE_LOOP, hs::vec3d_make(320, 0, 4.0), true);

		
//		hs::action *a = new hs::move_by_action(10.0, hs::vec2d_make(100.0, 0.0));
//		hs::action *b = new hs::move_by_action(10.0, hs::vec2d_make(0.0, 100.0));
//		a->append_action(new hs::move_to_action(10.0, hs::vec2d_screen_center()));
		
//		as->add_action_to_entity(fire, a);
//		as->add_action_to_entity(fire, b);
		
//		a = new hs::scale_to_action(2.0, hs::vec2d_make(0.5, 0.5));
//		a->append_action(new hs::scale_to_action(1.0, hs::vec2d_make(4.0, 4.0)));
//		a->append_action(new hs::scale_to_action(1.0, hs::vec2d_make(2.0, 2.0)));
//		a->append_action(new hs::scale_by_action(1.0, hs::vec2d_make(6.0, 9.0)));
//		b = new hs::fade_to_action(5.0, 0.5);
//		a->append_action(b);
//		
		
		
		hs::entity *bubble = hs::factory::create_atlas_sprite("bubbles.png", hs::vec3d_make(100.0, 100.0, 4.0), hs::rect_make(0.0, 0.0, 41.0, 41.0));
		hs::action *bac = new hs::move_by_action(3.0, hs::vec2d_make(50.0, 50.0));
		bac->loop_count = 1;
		
		hs::action *blink = new hs::fade_to_action(1.0, 0.0);
		blink->append_action(new hs::fade_to_action(1.0,1.0));
		blink->loop_forever = true;
		
		bac->append_action(blink);
		
		as->add_action_to_entity(bubble, bac);
		
		
		
		hs::entity *clock = hs::factory::create_atlas_sprite("clocks.png", 
															 hs::vec3d_screen_center(6.0),
															 hs::rect_make(0.0, 0.0, 0.0, 0.0));
		
		hs::comp::seq_animation *anim = em->add_component<hs::comp::seq_animation>(clock);
		
		anim->frames_per_second = 24.0;
		anim->start_frame = 0;
		anim->end_frame = 23;
		anim->current_frame = 0;
		anim->loop = true;
		anim->state = hs::comp::ANIM_STATE_PLAY;
		anim->destroy_on_finish = false;
		anim->frame_size = hs::size2d_make(32.0, 32.00);

		
//		as->add_action_to_entity(clock, a);
		
		
		
		
//		a = new hs::rotate_to_action(2.0, -90);
//		as->add_action_to_entity(back, a);
//		
//		a->append_action(new hs::rotate_to_action(2.0,-90));
//		a->append_action(new hs::rotate_to_action(2.0,270.0));
//		a->append_action(new hs::rotate_to_action(2.0,0.0));
//		
//		b = new hs::add_component_action(2.0, new hs::comp::mark_of_death);
//		a->append_action(b);
		
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

		ans->update(dt);
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