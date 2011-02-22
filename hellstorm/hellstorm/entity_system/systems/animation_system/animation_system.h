//
//  animation_system.h
//  hellstorm
//
//  Created by jrk on 20/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "components.h"
#include <vector>

namespace hs 
{
	class entity;
	class entity_manager;
	class action_system;
	
	class animation_system
	{
	public:
		animation_system(entity_manager *manager, action_system *asystem);
		~animation_system();
		void update(double dt);

	protected:
		void setup_next_animation_or_stop(entity *e, comp::seq_animation *current_animation);
		
	private:
		entity_manager *em;
		action_system *as;

		entity **ent_cache;
		size_t cache_size;
	};
}