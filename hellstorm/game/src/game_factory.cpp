//
//  game_factory.cpp
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game_factory.h"
#include "psycho_bg_system.h"

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

			//		sunb = hs::factory::create_sprite(em, 
			//										  "sunburst_2.png", 
			//										  hs::vec3d_make(rand()%(int)hs::cfg::screen.size.w, rand()%(int)hs::cfg::screen.size.h, -4.6), 
			//										  hs::anchor_center);
			//		
			//		sunb->add<comp_psycho_marker>()->type = e_psycho_type_sunburst;
			//		sunb->get<comp_psycho_marker>()->rot_speed = -40.0;
			//		sunb->get<comp_psycho_marker>()->velocity = hs::vec2d_make(23.0, 12.0);
			//		sunb->get<hs::comp::renderable>()->alpha = 0.1;
			//
			//		sunb = hs::factory::create_sprite(em, 
			//										  "sunburst_2.png", 
			//										  hs::vec3d_make(rand()%(int)hs::cfg::screen.size.w, rand()%(int)hs::cfg::screen.size.h, -4.55), 
			//										  hs::anchor_center);
			//		
			//		sunb->add<comp_psycho_marker>()->type = e_psycho_type_sunburst;
			//		sunb->get<comp_psycho_marker>()->rot_speed = 50.0;
			//		sunb->get<comp_psycho_marker>()->velocity = hs::vec2d_make(-43.0, -12.0);
			//		sunb->get<hs::comp::renderable>()->alpha = 0.1;

		
		}
		
		void create_borders_and_raster(hs::entity_manager *em)
		{
			hs::entity *rast = 0;
			rast = hs::factory::create_sprite(em, "raster_3.png", hs::vec3d_screen_center(7.0), hs::anchor_center);
			rast->get<hs::comp::renderable>()->alpha = 1.0;
			
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
	}
}