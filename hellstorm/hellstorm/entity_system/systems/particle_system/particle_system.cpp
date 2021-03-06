//
//  particle_system.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particle_system.h"
#include "hellstorm.h"

namespace hs 
{
	particle_system::particle_system(entity_manager *manager)
	{
		em = manager;
		skiptimer = 0;
		
		ent_cache = new entity*[cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);

	}

	particle_system::~particle_system()
	{
		delete [] ent_cache;
	}
	
	void particle_system::update(double dt)
	{
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		uid qry[] = 
		{
			comp::particle_emitter::family_id,
			comp::position::family_id
		};
		cache_size = em->get_entities_possesing_components(qry, 2, ent_cache, cfg::entity_system.entity_pool_size);

		entity *current_entity = NULL;
		comp::particle_emitter *current_pe = NULL;
		comp::position *current_pos = NULL;
		
		for (uid i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			
			current_pe = em->get_component<comp::particle_emitter>(current_entity);
			if (current_pe)
			{
				if (current_pe->ren_type == comp::RENDERABLETYPE_PARTICLE_EMITTER &&
					current_pe->pe->should_handle())
				{
					current_pos = em->get_component<comp::position>(current_entity);
					
					current_pe->pe->position.x = current_pos->origin.x;
					current_pe->pe->position.y = current_pos->origin.y;
					current_pe->pe->update(dt);
					
					if (!current_pe->pe->should_handle())
					{
						em->add_component<comp::mark_of_death>(current_entity);
					}
				}
			}
		}
	}
}