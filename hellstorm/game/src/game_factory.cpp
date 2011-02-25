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

namespace game 
{
	namespace factory
	{
		void create_psycho_back(hs::entity_manager *em)
		{
			hs::entity *sunb = hs::factory::create_sprite(em, 
														  "sunburst_2.png", 
														  hs::vec3d_make(rand()%(int)hs::cfg::screen.size.w, rand()%(int)hs::cfg::screen.size.h, -4.5), 
														  hs::anchor_center);
			
			sunb->add<comp_psycho_marker>()->type = e_psycho_type_sunburst; 
			sunb->get<comp_psycho_marker>()->rot_speed = -60.0;
			sunb->get<hs::comp::renderable>()->alpha = 0.1;
			sunb->get<comp_psycho_marker>()->velocity = hs::vec2d_make(13.0, -42.0);

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
		
		}
		
		void create_borders(hs::entity_manager *em)
		{
			hs::entity *rast = 0;
			
			rast = hs::factory::create_sprite(em, "rahmen.png", hs::vec3d_screen_center(9.0), hs::anchor_center);
			
			rast = hs::factory::create_sprite(em, 
											  "lower.png", 
											  hs::vec3d_make(hs::cfg::screen.size.w/2, 0, 4.0),
											  hs::vec2d_make(0.5, 0.0));
			
			rast = hs::factory::create_sprite(em, 
											  "upper.png", 
											  hs::vec3d_make(hs::cfg::screen.size.w/2, hs::cfg::screen.size.h, 4.0),
											  hs::vec2d_make(0.5, 1.0));
			
			
		}
		

		void create_raster(hs::entity_manager *em)
		{
			hs::entity *rast = 0;
			rast = hs::factory::create_sprite(em, "raster_3.png", hs::vec3d_screen_center(7.0), hs::anchor_center);

		}
	}
	
	namespace factory
	{
		hs::entity *create_player_pill (hs::entity_manager *em, int col, int row, int type)
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
			
			game_board_element *gbo = ret->add<game_board_element>();
			gbo->col = col;
			gbo->row = row;
			gbo->type = e_gbo_type_pill;
			gbo->state = e_gbo_state_falling;
			
			return ret;
		}
		
		hs::entity *create_virus (hs::entity_manager *em, int col, int row, e_gbo_color type)
		{
			double xsrc = 4 * 32 + type * 64;
			double ysrc = 8 * 32;
			
			hs::entity *ret = hs::factory::create_atlas_sprite(em, 
															   "game_sheet.png", 
															   pixel_for_colrow(col, row),
															   hs::rect_make(xsrc, ysrc, 34.0, 32.0));

			game_board_element *gbo = ret->add<game_board_element>();
			gbo->col = col;
			gbo->row = row;
			gbo->type = e_gbo_type_virus;
			gbo->state = e_gbo_state_idle;

			return ret;
		}

	}
}