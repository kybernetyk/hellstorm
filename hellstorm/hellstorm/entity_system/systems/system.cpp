//
//  system.cpp
//  hellstorm
//
//  Created by jrk on 8/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "system.h"
#include "hellstorm.h"


namespace hs 
{
	system::system()
	{
		sys_init();
	}
	
	system::~system()
	{
		sys_destroy();
	}
	
	void system::sys_init()
	{
		em = NULL;
		ent_cache = new entity*[cfg::entity_system.entity_pool_size];
		cache_size = 0;
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);		
	}

	void system::sys_destroy()
	{
		delete [] ent_cache;
	}


	void system::set_manager(hs::entity_manager *manager)
	{
		em = manager;
	}
}