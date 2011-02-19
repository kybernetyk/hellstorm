//
//  components.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "components.h"
#include "hellstorm.h"
#include <memory.h>

namespace hs 
{
	namespace comp
	{
#pragma mark -
#pragma mark IDs
		
		
		//0 reserved
		family::id mark_of_death::family_id = family::mark_of_death;
		family::id position::family_id = family::position;

		family::id renderable::family_id = family::renderable;
		family::id sprite::family_id = renderable::family_id;
		family::id atlas_sprite::family_id = renderable::family_id;
		family::id text_label::family_id = renderable::family_id;
		family::id particle_emitter::family_id = renderable::family_id;

		family::id action_container::family_id = family::action_container;


#pragma mark -
#pragma mark action container
		action_container::action_container()
		{
			memset(actions,0x00,NUM_OF_ACTIONS_PER_CONTAINER*sizeof(action*));
		}
		
		action_container::~action_container()
		{
			for (int i = 0; i < NUM_OF_ACTIONS_PER_CONTAINER; i++)
			{
				if (actions[i])
				{
					action *a = actions[i];
					delete a;
				}
			}
		}
	}
}