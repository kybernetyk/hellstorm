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
	hs::render_system *rs;
	
	menu_scene::~menu_scene()
	{
		std::printf("menu scene dtor\n");
	}
	
	void menu_scene::init(void)
	{
		em = new hs::entity_manager();
		rs = new hs::render_system(em);
		
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
		
		delete rs;
		
		em->remove_all_entities();
		delete em;
	}
	
	void menu_scene::update(double dt)
	{
	//	std::printf("update %i\n", q);		
//		pe->update(dt);
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
	}
	
	int menu_scene::scene_type()
	{
		return 1;
	}
}