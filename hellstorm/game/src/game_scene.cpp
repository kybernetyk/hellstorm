//
//  game_scene.cpp
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_scene.h"
#include "game_factory.h"

namespace game 
{
	game_scene::~game_scene()
	{
		std::printf("game scene dtor\n");
	}
	
	void game_scene::init(void)
	{
		em = new hs::entity_manager();
		cs = new hs::corpse_retrieval_system(em);
		rs = new hs::render_system(em);
		ps = new hs::particle_system(em);
		as = new hs::action_system(em);
		ans = new hs::animation_system(em, as);
		bg_system = new psycho_bg_system(em);
		
		
		hs::factory::create_sprite(em, "background.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		factory::create_psycho_back(em);
		factory::create_borders_and_raster(em);
		
	}
	
	void game_scene::shutdown(void)
	{
		printf("game scene shutdown!\n");
		em->remove_all_entities();
		delete em;
		delete cs;
		delete rs;
		delete ps;
		delete as;
		delete ans;
		delete bg_system;
	}
	
	void game_scene::update(double dt)
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
		{
			printf("has touched up!\n");
			
			hs::g_game->pop_scene();
		}
		
		/*
		 if (hs::g_input.get_last_event() != hs::inputevent_none)
		 {
		 printf("last input event: %i\n", hs::g_input.get_last_event());
		 }*/
	}
	
	void game_scene::render()
	{
		rs->render();
		
		em->is_dirty = false;
	}
	
	int game_scene::scene_type()
	{
		return 2;
	}
}