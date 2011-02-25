//
//  psycho_bg_system.cpp
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "psycho_bg_system.h"

#include "hellstorm.h"

namespace game 
{
	hs::uid comp_psycho_marker::family_id = 0;
	
	psycho_bg_system::psycho_bg_system(hs::entity_manager *manager)
	{
		hs::comp::register_component_class<comp_psycho_marker>();
		
		em = manager;
		ent_cache = new hs::entity*[hs::cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
	}
	
	psycho_bg_system::~psycho_bg_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}
	
	void psycho_bg_system::update(double dt)
	{
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);

		hs::uid qry[] = 
		{
			comp_psycho_marker::family_id,
			hs::comp::position::family_id
		};
		size_t qry_size = sizeof(qry)/sizeof(hs::uid);
		
		cache_size = em->get_entities_possesing_components(qry, qry_size, ent_cache, hs::cfg::entity_system.entity_pool_size);
		
		hs::entity *current_entity = NULL;
		comp_psycho_marker *current_marker = 0;
		hs::comp::renderable *current_renderable = 0;
		hs::comp::position *current_position = 0;
	
		for (hs::uid i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			current_marker = em->get_component<comp_psycho_marker>(current_entity);
			current_renderable = em->get_component<hs::comp::renderable>(current_entity);
			current_position = em->get_component<hs::comp::position>(current_entity);

			if (current_marker->type == e_psycho_type_sunburst) 
			{
				current_position->rot += dt * current_marker->rot_speed;
			}
			
			current_position->origin.x += dt * current_marker->velocity.x;
			current_position->origin.y += dt * current_marker->velocity.y;
			
			if (current_position->origin.x < 0 ||
				current_position->origin.x > hs::cfg::screen.size.w)
			{
				float f = 0.0;
				
				if (current_position->origin.x < 0)
				{
					f = 1.0;
					current_position->origin.x = 0;
				}
				
				if (current_position->origin.x > hs::cfg::screen.size.w)
				{
					current_position->origin.x = hs::cfg::screen.size.w;	
					f = -1.0;
				}
				
				int r = rand()%100 + 10;
				
				current_marker->velocity.x = r * f;
			}

			if (current_position->origin.y < 0 ||
				current_position->origin.y > hs::cfg::screen.size.h)
			{
				float f = 0.0;
				
				if (current_position->origin.y < 0)
				{
					f = 1.0;
					current_position->origin.y = 0;
				}
				
				if (current_position->origin.y > hs::cfg::screen.size.h)
				{
					current_position->origin.y = hs::cfg::screen.size.h;	
					f = -1.0;
				}

				current_marker->velocity.y *= -1.0;
				int r = rand()%100 + 10;
				
				current_marker->velocity.y = r * f;
			}
		}
	}
}
