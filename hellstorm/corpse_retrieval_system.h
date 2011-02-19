//
//  corpse_retrieval_system.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <vector>

namespace hs
{
	class entity_manager;

	class corpse_retrieval_system
	{
	public:
		corpse_retrieval_system(entity_manager *manager);
		
		void collect_corpses(void);
		
	protected:
		entity_manager *em;
	};
}