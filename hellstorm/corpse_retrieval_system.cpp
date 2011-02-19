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
	}

	void corpse_retrieval_system::collect_corpses(void)
	{
		std::vector<entity *> entities;
		em->get_entities_posessing_component(entities, comp::mark_of_death::family_id);
		
		
		entity *current_entity = NULL;
		
		std::vector<entity *>::const_iterator it = entities.begin();
		while(it != entities.end())
		{
			current_entity = *it;
			++it;
			em->remove_entity(current_entity->manager_id);
		}
	}
}
