//
//  psycho_bg_system.cpp
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "psycho_bg_system.h"

#include "hellstorm.h"

namespace test_game 
{
	hs::uid comp_psycho_marker::family_id = 0;
	
	psycho_bg_system::psycho_bg_system(hs::entity_manager *manager)
	{
		hs::comp::register_component_class<comp_psycho_marker>();
		
		printf("comp_psycho_marker::family_id =  %i\n", comp_psycho_marker::family_id);
		
		em = manager;
		ent_cache = new hs::entity*[hs::cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(hs::entity *)*hs::cfg::entity_system.entity_pool_size);
	}
	
	psycho_bg_system::~ psycho_bg_system()
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
		
		for (hs::uid i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			
			current_marker = em->get_component<comp_psycho_marker>(current_entity);
			printf("marker type: %i\n", current_marker->type);
		}
		if (cache_size > 0)
			printf("..\n");
	}
}
