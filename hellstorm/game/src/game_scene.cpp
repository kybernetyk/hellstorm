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
	bool _init_map[defs::board_num_of_cols][defs::board_num_of_rows];
	
	const int tag_button_none = 0;
	const int tag_button_next = 1;
	
	void game_scene::init(void)
	{

		hs::audio_system::play_music("drmario.mp3");
		
		em = new hs::entity_manager();
		cs = new hs::corpse_retrieval_system(em);
		rs = new hs::render_system(em);
		ps = new hs::particle_system(em);
		as = new hs::action_system(em);
		ans = new hs::animation_system(em, as);
		ui_sys = new hs::ui_system(em);

		bg_system = new psycho_bg_system(em);
		gb_system = new game_board_system(em);
		plr_system = new player_system(em);
		logic_system = new game_logic_system(em);
		hud_sys = new hud_system(em);
		
		popup_sys = new popup_system(em);
		
		hs::factory::create_sprite(em, "background_noraster.png", hs::vec3d_screen_center(-5.0), hs::anchor_center);
		factory::create_psycho_back(em);
		factory::create_borders(em);
		factory::create_raster(em);
		
		pressed_button = 0;
		
		int num_of_virii = global::g_state.level + 1;
		global::g_state.virii_left = num_of_virii;

		memset(_init_map, 0x00, defs::board_num_of_cols * defs::board_num_of_rows * sizeof(bool));
		int c,r,f;
		
		while (1)
		{
			num_of_virii--;
			if (num_of_virii < 0)
				break;
			
			c = rand()%defs::board_num_of_cols;
			r = rand()%defs::board_num_of_rows/2;
			f = rand()%4;
			
			if (_init_map[c][r])
				continue;
			_init_map[c][r] = true;
			
			factory::create_virus(em, c, r, (e_gbo_color)f);	
		}

		global::g_state.current_state = global::e_gs_idle;
		global::g_state.next_pill = (factory::e_doublepill_type)(rand()%16);
		
//		hs::factory::create_particle_emitter(em, "matrix_screen.pex", PE_DUR_FROM_FILE, hs::vec3d_make(320/2, 480, 9.0), true);
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
		delete ui_sys;
		delete bg_system;
		delete gb_system;
		delete plr_system;
		delete logic_system;
		delete hud_sys;
		delete popup_sys;
	}
	
	void game_scene::create_next_level_button()
	{
		hs::entity *but = 0;
		
		but = hs::ui::create_button_from_file(em, "play_button.cfg", hs::vec3d_make(160, 150, 5.0));
		but->get<hs::ui::button>()->tag_ptr = &pressed_button;
		but->get<hs::ui::button>()->tag = tag_button_next;
	}
	
	void game_scene::next_level_button_pressed()
	{
		global::g_state.level++;
		hs::g_game->set_scene(new game_scene());
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
					if (global::g_state.virii_left <= 0)
					{
						global::g_state.current_state = global::e_gs_no_virus_left;
						global::g_state.next_pill = (factory::e_doublepill_type)(rand()%16);
					}
					else
					{
						factory::create_player_pill(em, defs::player_spawn_col , defs::player_spawn_row, global::g_state.next_pill);
						global::g_state.next_pill = (factory::e_doublepill_type)(rand()%16);
						global::g_state.current_state = global::e_gs_player_active;
					}
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
				case global::e_gs_no_virus_left:
					global::g_state.current_state = global::e_gs_level_summary;
					break;
				case global::e_gs_level_summary:
					hs::factory::create_text_label(em, 
												   "impact20.fnt", 
												   "YAY LEVEL PFERDIG!",
												   hs::vec3d_screen_center(7.0));
					
					create_next_level_button();
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
		popup_sys->update(dt);
		
		ui_sys->update(dt);
		if (global::g_state.current_state == global::e_gs_level_summary && global::g_state.old_state == global::g_state.current_state)
		{
			if (pressed_button == tag_button_next)
			{
				next_level_button_pressed();
				hs::audio_system::play_sound("click.mp3");
			}
		}
		
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