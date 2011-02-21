//
//  render_system.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <vector>

namespace hs
{
	class entity_manager;
	class renderable;
	class entity;
	
	class render_system
	{
	public:
		render_system(entity_manager *manager);
		~render_system();
		void render(void);
		
	protected:
		entity_manager *em;

		entity **ent_cache;
		size_t cache_size;
	};
	
}