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
		
		hs::entity *ent = em->new_entity();
		
		hs::comp::position *pos = em->add_component<hs::comp::position>(ent);
		pos->origin = hs::vec2d_make(320/2,480/2);
		
		hs::comp::sprite *sprite = em->add_component<hs::comp::sprite>(ent);
		sprite->res_handle = hs::g_renderable_manager.acquire_resource<hs::quad>("game_back.png");
		sprite->z = -3.0;
				
		ent = em->new_entity();
		pos = em->add_component<hs::comp::position>(ent);
		pos->origin = hs::vec2d_make(320/2,480/2);
		
		hs::comp::text_label *label = em->add_component<hs::comp::text_label>(ent);
		label->res_handle = hs::g_renderable_manager.acquire_resource<hs::bitmap_font>("impact20.fnt");
		label->text = "oh hai!";
		label->z = -2.0;
		
		for (int i = 0; i < hs::cfg::entity_system.entity_pool_size-20; i++)
		{
			ent = em->new_entity();
			pos = em->add_component<hs::comp::position>(ent);
			pos->origin = hs::vec2d_make(rand()%320, rand()%480);
			
			hs::comp::atlas_sprite *as = em->add_component<hs::comp::atlas_sprite>(ent);
			as->res_handle = hs::g_renderable_manager.acquire_resource<hs::atlas_quad>("bubbles.png");
			as->src_rect = hs::rect_make(0.0, 0.0, 41.0, 41.0);
			as->z = -2.1;
		}
		
		hs::particle_system::create_particle_emitter("cool.pex", 10.0, hs::vec2d_make(100, 100), true);
		
		hs::audio_system::play_music("music.mp3");
		
//		ent = em->new_entity();
//		pos = em->add_component<hs::comp::position>(ent);
//		pos->origin = hs::vec2d_make(220/2,480/2-100);
//		
//		pe = em->add_component<hs::comp::particle_emitter>(ent);
//		pe->pe = hs::g_renderable_manager.acquire_particle_emitter("cool.pex");
//		pe->z = 0.0;
//		pe->pe->position = hs::vec3d_make(100, 100, 0.0);
//		pe->pe->set_duration(-1.0);
//		pe->pe->start();
		
//		hs::resource_handle q = hs::g_renderable_manager.acquire_resource<hs::quad>("game_back.png");
//		hs::quad *qd = hs::g_renderable_manager.get_resource<hs::quad>(&q);
//		qd->position = hs::vec3d_make(320/2, 480/2, -5.0);
//		
//		hs::resource_handle f = hs::g_renderable_manager.acquire_resource<hs::bitmap_font>("impact20.fnt");
//		hs::bitmap_font *fp = hs::g_renderable_manager.get_resource<hs::bitmap_font>(&f);
//		fp->position = hs::vec3d_make(320/2, 480/2, -4.0);
//		
//		hs::resource_handle pe = hs::g_renderable_manager.acquire_particle_emitter("cool.pex");
//		pe->position = hs::vec3d_make(320/2, 480/2, -3.0);
//		pe->set_duration(-1.0);
//		pe->reset();
//		pe->start();
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
		
//		hs::quad *qd = hs::g_renderable_manager.get_resource<hs::quad>(&q);
//		qd->render_content();
//		
//		hs::bitmap_font *fp = hs::g_renderable_manager.get_resource<hs::bitmap_font>(&f);
//		fp->render_content("ficken!");
//		
//		pe->render_content();
		em->is_dirty = false;
	}
	
	int menu_scene::scene_type()
	{
		return 1;
	}
}