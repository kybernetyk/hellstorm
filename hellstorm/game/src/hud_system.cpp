//
//  hud_system.cpp
//  hellstorm
//
//  Created by jrk on 7/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "hud_system.h"
#include "game_factory.h"
#include "game_globals.h"

namespace game
{
	 hs::rect next_red = {192.0,384.0,20.0,20.0};
	const hs::rect next_blue = {256.0, 384.0, 20.0, 20.0};
	const hs::rect next_green = {320.0, 384.0, 20.0, 20.0};
	const hs::rect next_yellow = {384.0, 384.0, 20.0, 20.0};
	
	struct next_pair
	{
		hs::rect left;
		hs::rect right;
	};
	
/*	enum e_doublepill_type
	{
		e_dp_red_red,
		e_dp_green_red,
		e_dp_yellow_red,
		e_dp_blue_red,
		
		e_dp_red_green,
		e_dp_green_green,
		e_dp_yellow_green,
		e_dp_blue_green,
		
		e_dp_red_yellow,
		e_dp_green_yellow,
		e_dp_yellow_yellow,
		e_dp_blue_yellow,
		
		e_dp_red_blue,
		e_dp_green_blue,
		e_dp_yellow_blue,
		e_dp_blue_blue
	};*/

	
	next_pair next_mapping[] = 
	{
		{next_red, next_red},
		{next_green, next_red},
		{next_yellow, next_red},
		{next_blue, next_red},
		
		{next_red, next_green},
		{next_green, next_green},
		{next_yellow, next_green},
		{next_blue, next_green},

		{next_red, next_yellow},
		{next_green, next_yellow},
		{next_yellow, next_yellow},
		{next_blue, next_yellow},

		{next_red, next_blue},
		{next_green, next_blue},
		{next_yellow, next_blue},
		{next_blue, next_blue}
	};
	
	hud_system::hud_system(hs::entity_manager *manager)
	{
		em = manager;
		ent_cache = new hs::entity*[hs::cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
		
		hs::entity *e = hs::factory::create_text_label(em, "impact20.fnt", "12345", hs::vec3d_make(84, 480-48, 5.0), hs::vec2d_make(0.5, 0.0) );

		score_label = e->get<hs::comp::text_label>();
		
		//__score___
		hs::entity *sprite = hs::factory::create_atlas_sprite(em, 
												  "game_sheet.png", 
												  hs::vec3d_make(84, 480-52, 5.0), 
												  hs::rect_make(384, 256, 114, 10),
												  hs::vec2d_make(0.5, 1.0)
												  );

		
		//__next__
		sprite = hs::factory::create_atlas_sprite(em, 
												  "game_sheet.png", 
												  hs::vec3d_make(268, 480-52, 5.0), 
												  hs::rect_make(128, 384, 52, 10),
												  hs::vec2d_make(0.5, 1.0)
												  );
		
		//next left
		sprite = hs::factory::create_atlas_sprite(em, 
												  "game_sheet.png",
												  hs::vec3d_make(260-5, 480-52, 5.0), 
												  next_mapping[factory::e_dp_red_red].left,
												  hs::vec2d_make(0.5, 0.0)
												  );
		next_left = sprite->get<hs::comp::atlas_sprite>();
		
		sprite = hs::factory::create_atlas_sprite(em, 
												  "game_sheet.png",
												  hs::vec3d_make(260+25-5, 480-52, 5.0), 
												  next_mapping[factory::e_dp_red_red].right,
												  hs::vec2d_make(0.5, 0.0)
												  );
		next_right = sprite->get<hs::comp::atlas_sprite>();
	}
	
	hud_system::~hud_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}
	
	void hud_system::update_next_display()
	{
		next_left->src_rect = next_mapping[global::g_state.next_pill].left;
		next_right->src_rect = next_mapping[global::g_state.next_pill].right;
	}
	
	void hud_system::update_score_display()
	{
		char s[32];
		sprintf(s, "%i", global::g_state.score);
		score_label->text = s;
	}
	
	void hud_system::update(double dt)
	{
		update_next_display();
		update_score_display();
		return;
//		
//		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
//		
//		hs::uid qry[] = 
//		{
//			comp_psycho_marker::family_id,
//			hs::comp::position::family_id
//		};
//		size_t qry_size = sizeof(qry)/sizeof(hs::uid);
//		
//		cache_size = em->get_entities_possesing_components(qry, qry_size, ent_cache, hs::cfg::entity_system.entity_pool_size);
//		
//		hs::entity *current_entity = NULL;
//		comp_psycho_marker *current_marker = 0;
//		hs::comp::renderable *current_renderable = 0;
//		hs::comp::position *current_position = 0;
	}
}