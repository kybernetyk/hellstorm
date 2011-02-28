//
//  game_scene.cpp
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_scene.h"
#include "game_factory.h"
#include "game_utils.h"
#include "game_globals.h"
#include "game_logic_system.h"
#include "menu_scene.h"

namespace game 
{
	game_scene::~game_scene()
	{
		std::printf("game scene dtor\n");
	}

	void game_scene::init(void)
	{
		hs::audio_system::play_music("RealTechno.mp3");
		
		em = new hs::entity_manager();
		cs = new hs::corpse_retrieval_system(em);
		rs = new hs::render_system(em);
		ps = new hs::particle_system(em);
		as = new hs::action_system(em);
		ans = new hs::animation_system(em, as);
		bg_system = new psycho_bg_system(em);
		gb_system = new game_board_system(em);
		plr_system = new player_system(em);
		logic_system = new game_logic_system(em);
		
		hs::factory::create_sprite(em, "background.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		factory::create_psycho_back(em);
		factory::create_borders(em);
		factory::create_raster(em);
		
		factory::create_virus(em, 1, 5, e_gbo_yellow);
		factory::create_virus(em, 2, 2, e_gbo_blue);
		
		//factory::create_player_pill(em, 4, defs::board_num_of_rows-1, factory::e_dp_blue_green);
		
		global::g_state.current_state = global::e_gs_idle;
//
//
//		factory::create_pill(em, 4, 5, factory::e_dp_red_blue, factory::left);
//		factory::create_pill(em, 5, 5, factory::e_dp_red_blue, factory::right);
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
		delete gb_system;
		delete plr_system;
		delete logic_system;
	}
	
	void game_scene::handle_state_changes(void)
	{
		if (global::g_state.current_state != global::g_state.old_state)
		{
			global::e_game_state tmp = global::g_state.current_state;
			
			switch (global::g_state.current_state) 
			{
				case global::e_gs_idle:
					printf("oh we're idle ... let's do eet!\n");
					global::g_state.current_state = global::e_gs_player_need_respawn;
					break;
				case global::e_gs_player_need_respawn:
					factory::create_player_pill(em, 3, defs::board_num_of_rows-1, (factory::e_doublepill_type)(rand()%16));
					global::g_state.current_state = global::e_gs_player_active;
					break;
				case global::e_gs_player_landed:
					global::g_state.current_state = global::e_gs_check_for_chains;
					break;
				case global::e_gs_player_landed_ontop:
					printf("OMG DIE DIE DIE\n");
					global::g_state.current_state = global::e_gs_game_over;
					break;
				case global::e_gs_no_chains:
					printf("NO CHAINS! :(\n");
					global::g_state.current_state = global::e_gs_player_need_respawn;
					break;
				case global::e_gs_chains_marked:
					printf("YAY WE GOT CHAINS!\n");
					global::g_state.current_state = global::e_gs_move_gbos;
					break;
				case global::e_gs_move_gbos:
					//let the game board move all entities
					//global::g_state.current_state = global::e_gs_player_need_respawn;
					break;
				case global::e_gs_gbos_falling:
					//game board system let's them fall
					break;
				case global::e_gs_game_over:
					printf("OH GAME OVER :(\n");
					//hs::g_game->pop_scene();
					hs::g_game->set_scene(new menu_scene());
					break;
				default:
					break;
			}
			
			global::g_state.old_state = tmp;
		}
//
//		if (global::g_state.current_state != global::g_state.old_state)
//			handle_state_changes();
	}
	
	void game_scene::update(double dt)
	{
		//we must collect the corpses from the last frame
		//as the entity-manager's isDirty property is reset each frame
		//so if we did corpse collection at the end of update
		//the systems wouldn't know that the manager is dirty 
		//and a shitstorm of dangling references would rain down on them
		handle_state_changes();

		ans->update(dt);
		as->update(dt);
		bg_system->update(dt);
		ps->update(dt);
		
		gb_system->update(dt);
		plr_system->update(dt);
		logic_system->update(dt);

		
//		if (hs::g_input.has_touched_down())
//			printf("has touched down!\n");
//		if (hs::g_input.has_moved())
//			printf("has moved!\n");
//		if (hs::g_input.has_touched_up())
//		{
//			printf("has touched up!\n");
//			
//		//	hs::g_game->pop_scene();
//		}
		
		
		cs->collect_corpses();

		/*
		 if (hs::g_input.get_last_event() != hs::inputevent_none)
		 {
		 printf("last input event: %i\n", hs::g_input.get_last_event());
		 }*/
	}
	
	void game_scene::render()
	{
		rs->render();
	}
	
	int game_scene::scene_type()
	{
		return 2;
	}
}