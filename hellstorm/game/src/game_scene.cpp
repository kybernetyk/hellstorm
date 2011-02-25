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

	hs::entity *pill = 0;

	hs::vec3d pixel_for_colrow(int col, int row)
	{
		return hs::vec3d_make((col*32) + defs::board_x_offset, (row*32)+defs::board_y_offset, defs::board_z);
	}
	
	
	
	hs::entity *game_scene::create_pill (int col, int row, int type)
	{
		hs::vec2d pill_anchor = hs::vec2d_make(0.25, 0.5);
		int x_off = type % 8;
		int y_off = 1 + (type / 8);
		printf("row = %i -> %i\n", row, y_off);
		
		hs::entity *ret = hs::factory::create_atlas_sprite(em, 
										 "game_sheet.png", 
										 pixel_for_colrow(col, row),
										 hs::rect_make(x_off * 64.0, y_off * 64.0, 64.0, 32.0),
										 pill_anchor);

		hs::comp::renderable *r = ret->get<hs::comp::renderable>();
		r->alpha = 0.9;
		
		return ret;
	}
	
	hs::entity *game_scene::create_virus (int col, int row, int type)
	{
		double xsrc = 4 * 32 + type * 64;
		double ysrc = 8 * 32;
		
		hs::entity *ret = hs::factory::create_atlas_sprite(em, 
														   "game_sheet.png", 
														   pixel_for_colrow(col, row),
														   hs::rect_make(xsrc, ysrc, 34.0, 32.0));
		
		return ret;
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
		factory::create_borders(em);
		factory::create_raster(em);
		
		create_virus(3, 5, 0);
		create_virus(3, 6, 1);
		create_virus(3, 7, 2);
		create_virus(3, 8, 3);
		
		create_pill(0, 0, 0);
		create_pill(1, 1, 1);
		create_pill(2, 2, 2);
		create_pill(3, 3, 8);
		
		pill = create_pill(4, 4, 15);
		
//		hs::comp::position *pos = e->get<hs::comp::position>();
//		pos->rot = 90.0;

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
		
		
		hs::comp::position *pos = pill->get<hs::comp::position>();
		pos->rot += dt * 90.0;

		
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