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
		hs::audio_system::play_music("Versuch3.mp3");
		
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
		hud_sys = new hud_system(em);
		
		hs::factory::create_sprite(em, "background.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		factory::create_psycho_back(em);
		factory::create_borders(em);
		factory::create_raster(em);
		
		factory::create_virus(em, 1, 5, e_gbo_yellow);
		factory::create_virus(em, 2, 2, e_gbo_blue);
		
		global::g_state.current_state = global::e_gs_idle;
		
		global::g_state.score = 0;
		global::g_state.next_pill = (factory::e_doublepill_type)(rand()%16);
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
		delete hud_sys;
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
					factory::create_player_pill(em, defs::player_spawn_col , defs::player_spawn_row, global::g_state.next_pill);
					global::g_state.next_pill = (factory::e_doublepill_type)(rand()%16);
					global::g_state.current_state = global::e_gs_player_active;
					break;
				case global::e_gs_player_landed:
					global::g_state.current_state = global::e_gs_check_for_chains;
					break;
				case global::e_gs_player_landed_ontop:
					global::g_state.current_state = global::e_gs_game_over;
					break;
				case global::e_gs_no_chains:
					global::g_state.current_state = global::e_gs_player_need_respawn;
					break;
				case global::e_gs_chains_marked:
					global::g_state.current_state = global::e_gs_move_gbos;
					break;
				case global::e_gs_move_gbos:
					//let the game board move all entities
					//global::g_state.current_state = global::e_gs_player_need_respawn;
					break;
				case global::e_gs_gbos_falling:
					//game board system lets them fall
					break;
				case global::e_gs_game_over:
					hs::g_game->set_scene(new menu_scene());
					break;
				default:
					break;
			}
			
			global::g_state.old_state = tmp;
		}
	}
	
	void game_scene::update(double dt)
	{
		handle_state_changes();

		ans->update(dt);
		as->update(dt);
		bg_system->update(dt);
		ps->update(dt);
		
		gb_system->update(dt);
		plr_system->update(dt);
		logic_system->update(dt);
		
		hud_sys->update(dt);
		cs->collect_corpses();
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