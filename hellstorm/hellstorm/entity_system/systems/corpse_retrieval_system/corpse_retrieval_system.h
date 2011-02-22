//
//  corpse_retrieval_system.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <stddef.h>

namespace hs
{
	class entity_manager;
	class entity;

	class corpse_retrieval_system
	{
	public:
		corpse_retrieval_system(entity_manager *manager);
		~corpse_retrieval_system();
		
		void collect_corpses(void);
		
	protected:
		entity_manager *em;
		
		entity **ent_cache;
		size_t cache_size;
	};
}