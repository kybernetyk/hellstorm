//
//  game_factory.cpp
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_factory.h"
#include "psycho_bg_system.h"
#include "game_board_system.h"
#include "game_utils.h"
#include "player_system.h"

namespace game 
{
	namespace factory
	{
		void create_psycho_back(hs::entity_manager *em)
		{
			hs::entity *sunb = hs::factory::create_sprite(em, 
														  "sunburst_1.png", 
														  hs::vec3d_make(rand()%(int)hs::cfg::screen.size.w, rand()%(int)hs::cfg::screen.size.h, -4.5), 
														  hs::anchor_center);
			
			sunb->add<comp_psycho_marker>()->type = e_psycho_type_sunburst; 
			sunb->get<comp_psycho_marker>()->rot_speed = -60.0;
			sunb->get<hs::comp::renderable>()->alpha = 0.1;
			sunb->get<comp_psycho_marker>()->velocity = hs::vec2d_make(13.0, -42.0);

			hs::comp::name *name = sunb->add<hs::comp::name>();
			name->text = "psycho sunburst #1";

			
//			sunb = hs::factory::create_sprite(em, 
//											  "sunburst_1.png", 
//											  hs::vec3d_make(rand()%(int)hs::cfg::screen.size.w, rand()%(int)hs::cfg::screen.size.h, -4.6), 
//											  hs::anchor_center);
//			
//			sunb->add<comp_psycho_marker>()->type = e_psycho_type_sunburst;
//			sunb->get<comp_psycho_marker>()->rot_speed = -40.0;
//			sunb->get<comp_psycho_marker>()->velocity = hs::vec2d_make(23.0, 12.0);
//			sunb->get<hs::comp::renderable>()->alpha = 0.1;
//
//			sunb = hs::factory::create_sprite(em, 
//											  "sunburst_1.png", 
//											  hs::vec3d_make(rand()%(int)hs::cfg::screen.size.w, rand()%(int)hs::cfg::screen.size.h, -4.55), 
//											  hs::anchor_center);
//			
//			sunb->add<comp_psycho_marker>()->type = e_psycho_type_sunburst;
//			sunb->get<comp_psycho_marker>()->rot_speed = 50.0;
//			sunb->get<comp_psycho_marker>()->velocity = hs::vec2d_make(-43.0, -12.0);
//			sunb->get<hs::comp::renderable>()->alpha = 0.1;
//
//		
		}
		
		void create_borders(hs::entity_manager *em)
		{
			hs::entity *rast = 0;
			

			
			rast = hs::factory::create_sprite(em, 
											  "lower.png", 
											  hs::vec3d_make(hs::cfg::screen.size.w/2, 0, 4.0),
											  hs::vec2d_make(0.5, 0.0));
			hs::comp::name *name = rast->add<hs::comp::name>();
			name->text = "dingens (lower.png)";
			
			rast = hs::factory::create_sprite(em, 
											  "upper.png", 
											  hs::vec3d_make(hs::cfg::screen.size.w/2, hs::cfg::screen.size.h, 4.0),
											  hs::vec2d_make(0.5, 1.0));
			name = rast->add<hs::comp::name>();
			name->text = "dingens (upper.png)";

		}
		

		void create_raster(hs::entity_manager *em)
		{
			hs::entity *rast = 0;
			rast = hs::factory::create_sprite(em, "rahmen.png", hs::vec3d_screen_center(9.0), hs::anchor_center);
			hs::comp::name *name = rast->add<hs::comp::name>();
			name->text = "border (rahmen.png)";

			return;
			rast = hs::factory::create_sprite(em, "raster_3.png", hs::vec3d_screen_center(7.0), hs::anchor_center);

			name = rast->add<hs::comp::name>();
			name->text = "raster (raster_3.png)";
		}
	}
	
	namespace factory
	{
		e_gbo_color cols[] = 
		{
			e_gbo_red, e_gbo_red,
			e_gbo_green, e_gbo_red,
			e_gbo_yellow, e_gbo_red,
			e_gbo_blue, e_gbo_red,
			
			e_gbo_red, e_gbo_green,
			e_gbo_green, e_gbo_green,
			e_gbo_yellow, e_gbo_green,
			e_gbo_blue, e_gbo_green,
			
			e_gbo_red, e_gbo_yellow,
			e_gbo_green, e_gbo_yellow,
			e_gbo_yellow, e_gbo_yellow,
			e_gbo_blue, e_gbo_yellow,
			
			e_gbo_red, e_gbo_blue,
			e_gbo_green, e_gbo_blue,
			e_gbo_yellow, e_gbo_blue,
			e_gbo_blue, e_gbo_blue
		};
		
		hs::entity *create_player_pill(hs::entity_manager *em, int col, int row, e_doublepill_type type)
		{
			hs::vec2d pill_anchor = hs::vec2d_make(0.25, 0.5);
			int x_off = type % 8;
			int y_off = 1 + (type / 8);
			
			hs::entity *ret = hs::factory::create_atlas_sprite(em, 
															   "game_sheet.png", 
															   pixel_for_colrow(col, row),
															   hs::rect_make(x_off * 64.0, y_off * 64.0, 64.0, 32.0),
															   pill_anchor);
			hs::comp::renderable *r = ret->get<hs::comp::renderable>();
			r->alpha = 0.9;
			
			comp_player *player = ret->add<comp_player>();
			player->center_col = col;
			player->center_row = row;
			player->aux_col = col+1;
			player->aux_row = row;
			player->center_color = cols[type*2];
			player->aux_color = cols[type*2+1];
			player->double_pill_type = type;
			player->fall_time = 1.0 * global::g_state.difficulty;
			
			hs::comp::name *name = ret->add<hs::comp::name>();
			name->text = "player pill";
			
			hs::entity *shading = hs::factory::create_atlas_sprite(em, 
																 "game_sheet.png",
																 pixel_for_colrow(col, row),
																 hs::rect_make(0, 416, 64, 32),
																   pill_anchor);

			player->shading_guid = shading->guid;
			return ret;
		}
		
		hs::entity *create_pill(hs::entity_manager *em, int col, int row, e_doublepill_type type, e_left_right subtype)
		{
			hs::vec2d pill_anchor = hs::vec2d_make(0.5, 0.5);
			int x_off = type % 8;
			int y_off = 1 + (type / 8);
			
			hs::entity *ret = hs::factory::create_atlas_sprite(em, 
															   "game_sheet.png", 
															   pixel_for_colrow(col, row),
															   hs::rect_make(x_off * 64.0+subtype*32, y_off * 64.0, 32.0, 32.0),
															   pill_anchor);
			hs::comp::renderable *r = ret->get<hs::comp::renderable>();
			r->alpha = 0.9;

			game_board_element *gbo = ret->add<game_board_element>();
			gbo->col = col;
			gbo->row = row;
			gbo->type = e_gbo_type_pill;
			gbo->state = e_gbo_state_idle;
			gbo->color = cols[type*2+subtype];

			hs::comp::name *name = ret->add<hs::comp::name>();
			name->text = "normal pill";

			return ret;
		}
		
		hs::entity *create_virus(hs::entity_manager *em, int col, int row, e_gbo_color type)
		{
			double xsrc = 4 * 32 + type * 64;
			double ysrc = 8 * 32;
			
			hs::entity *ret = hs::factory::create_atlas_sprite(em, 
															   "game_sheet.png", 
															   pixel_for_colrow(col, row),
															   hs::rect_make(xsrc, ysrc, 26.0, 26.0));

			game_board_element *gbo = ret->add<game_board_element>();
			gbo->col = col;
			gbo->row = row;
			gbo->type = e_gbo_type_virus;
			gbo->state = e_gbo_state_idle;
			gbo->color = type;

			hs::comp::name *name = ret->add<hs::comp::name>();
			name->text = "virus";

			return ret;
		}

	}
}