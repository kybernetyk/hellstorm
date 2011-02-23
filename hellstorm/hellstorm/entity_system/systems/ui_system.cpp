//
//  ui_system.cpp
//  hellstorm
//
//  Created by jrk on 23/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ui_system.h"
#include "hellstorm.h"

namespace hs 
{
	namespace ui
	{
		uid control::family_id = 0;
	}
	
	ui_system::ui_system(entity_manager *manager)
	{
		em = manager;
		comp::register_component_class<ui::control>();

		ent_cache = new entity*[cfg::entity_system.entity_pool_size];
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = 0;
	}
	
	ui_system::~ui_system()
	{
		
	}
	
	void ui_system::update(double dt)
	{
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = em->get_entities_posessing_component(ui::control::family_id, ent_cache, cfg::entity_system.entity_pool_size);

		entity *current_entity;
		ui::control *current_control;
		
		for (uid i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			current_control = em->get_component<ui::control>(current_entity);
			printf("control lol: %p\n", current_control);
		}

	}
}