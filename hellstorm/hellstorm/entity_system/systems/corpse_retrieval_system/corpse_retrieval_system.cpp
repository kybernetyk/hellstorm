//
//  corpse_retrieval_system.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "corpse_retrieval_system.h"
#include "hellstorm.h"

namespace hs 
{
	corpse_retrieval_system::corpse_retrieval_system(entity_manager *manager)
	{
		em = manager;
		ent_cache = new entity*[cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
	}
	
	corpse_retrieval_system::~corpse_retrieval_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}

	void corpse_retrieval_system::collect_corpses(void)
	{
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = em->get_entities_posessing_component(comp::mark_of_death::family_id, ent_cache, cfg::entity_system.entity_pool_size);		
		
//		std::vector<entity *> entities;
//		em->get_entities_posessing_component(entities, comp::mark_of_death::family_id);
//		
		
//		entity *current_entity = NULL;
		
//		std::vector<entity *>::const_iterator it = entities.begin();
//		while(it != entities.end())
//		{
//			current_entity = *it;
//			++it;
		for (uid i = 0; i < cache_size; i++)
		{
			em->remove_entity(ent_cache[i]->manager_id);
		}
	}
}
