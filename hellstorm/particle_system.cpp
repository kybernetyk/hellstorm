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
				if (current_pe->ren_type == RENDERABLETYPE_PARTICLE_EMITTER &&
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
	
	entity *particle_system::create_particle_emitter(std::string filename, double duration, vec2d position, bool autostart)
	{
		entity_manager *em = entity::ent_mgr;
		
		entity *e = em->new_entity();
		
		comp::position *pos = em->add_component<comp::position>(e);
		pos->origin = position;
		
		comp::particle_emitter *pe = em->add_component<comp::particle_emitter>(e);
		pe->pe = g_renderable_manager.acquire_particle_emitter(filename);
		pe->z = 5.0;
		
		if (duration != 0.0)
			pe->pe->set_duration(duration);
		
		if (autostart)
		{
			pe->pe->reset();
			pe->pe->start();
		}
		
		return e;
	}
	
	entity *particle_system::create_particle_emitter(hs::particle_emitter *existing_em, double duration, vec2d position, bool autostart)
	{
		entity_manager *em = entity::ent_mgr;
		
		entity *e = em->new_entity();
		
		comp::position *pos = em->add_component<comp::position>(e);
		pos->origin = position;
		
		comp::particle_emitter *pe = em->add_component<comp::particle_emitter>(e);
		pe->pe = existing_em;
		pe->z = 5.0;
		
		if (duration != 0.0)
			pe->pe->set_duration(duration);
		
		if (autostart)
		{
			pe->pe->reset();
			pe->pe->start();
		}

		return e;
	}

}