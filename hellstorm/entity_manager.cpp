//
//  entity_manager.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "entity_manager.h"
#include "hellstorm.h"

namespace hs 
{
#pragma mark -
#pragma mark component
	component::component()
	{
		family_id = 0;
	}
	
	component::~component()
	{
	}
	
#pragma mark -
#pragma mark entity

	component *entity::get_by_id(uid family_id)
	{
		return ent_mgr->get_component(this, family_id);
	}
	
#pragma mark -
#pragma mark entity manager
	entity_manager::entity_manager()
	{
		printf("EntityManager startup:\n{\n");
		printf("\t[*] Entity Slots: %i\n", MAX_ENTITIES);
		printf("\t[*] Component Slots per Entity: %i\n", MAX_COMPONENTS_PER_ENTITY);
		printf("\t[!] don't exceed these limits without adjusting the #defines!\n");
		printf("\t[!] no checks/asserts will be made for this! you will crash and burn!\n}\n");
		
		is_dirty = true;
		current_guid = 1;
		
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			entities[i] = NULL;
			for (int j = 0; j < MAX_COMPONENTS_PER_ENTITY; j++)
			{
				components[i][j] = NULL;
			}
		}
	}
	
	uid entity_manager::get_next_available_manager_id(void)
	{
		for (uid i = 1; i < MAX_ENTITIES; i++)
			if (entities[i] == NULL)
				return i;
		
		printf("no entity slots left!\n");
		abort();
		return -1;
	}
	
	uid entity_manager::get_next_available_guid(void)
	{
		return current_guid++;
	}
	
	void entity_manager::register_entity(entity *e)
	{
		is_dirty = true;
		e->ent_mgr = this;
		e->manager_id = get_next_available_manager_id();
		e->guid = get_next_available_guid();
		entities[e->manager_id] = e;
	}
	
	entity *entity_manager::new_entity(void)
	{
		entity *e = new entity();
		register_entity(e);
		return e; 
	}
	
	entity *entity_manager::get_entity(uid entity_manager_id)
	{
		return entities[entity_manager_id];
	}
	
	void entity_manager::remove_entity(uid entity_manager_id)
	{
		is_dirty = true;
		entity *e = entities[entity_manager_id];
		remove_all_components(e);
		entities[entity_manager_id] = NULL;
		delete e;
	}
	
	void entity_manager::remove_all_entities(void)
	{
		is_dirty = true;
		entity *e = NULL;
		
		for (uid i = 0; i < MAX_ENTITIES; i++)
		{
			e = entities[i];
			if (e)
				remove_entity(e->manager_id);
		}
	}
	
	void entity_manager::remove_all_components(entity *e)
	{
		is_dirty = true;
		
		component *c = NULL;
		for (uid i = 0; i < MAX_COMPONENTS_PER_ENTITY; i++)
		{
			c = components[e->manager_id][i];
			delete c;
			components[e->manager_id][i] = NULL;
		}
	}
}