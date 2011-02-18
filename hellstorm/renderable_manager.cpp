//
//  renderable_manager.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "renderable_manager.h"
#include "hellstorm.h"
#include <cstdio>
#include <stdlib.h>

namespace hs 
{
	renderable_manager g_renderable_manager;
	
	renderable_manager::renderable_manager()
	{
		memset(resources_by_handle, 0x00, MAX_RESOURCES * sizeof(renderable *));		
	}
	
	resource_handle renderable_manager::get_free_handle(void)
	{
		for (resource_handle i = 1; i < MAX_RESOURCES; i++)
			if (resources_by_handle[i] == 0)
				return i;
		
		std::printf("** RenderableManager error:\n\t[!] NO RESOURCE SLOTS FREE! MAX_RESOURCES: %i\n", MAX_RESOURCES);
		abort();
		return -1;
	}
}