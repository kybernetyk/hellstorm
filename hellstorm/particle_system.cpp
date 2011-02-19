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
	}
	
	void particle_system::update(double dt)
	{
		std::vector<entity *> entities;
		em->get_entities_possesing_components(entities, comp::particle_emitter::family_id, comp::position::family_id, ARGLIST_END);
		
		std::vector<entity *>::const_iterator it = entities.begin();
		
		entity *current_entity = NULL;
		comp::particle_emitter *current_pe = NULL;
		comp::position *current_pos = NULL;
		
		while (it != entities.end())
		{
			current_entity = *it;
			++it;
			
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