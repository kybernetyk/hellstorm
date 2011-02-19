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
		uid mark_of_death::family_id = 1;
		uid position::family_id = 2;

		uid renderable::family_id = 4;
		uid sprite::family_id = renderable::family_id;
		uid atlas_sprite::family_id = renderable::family_id;
		uid text_label::family_id = renderable::family_id;
		uid particle_emitter::family_id = renderable::family_id;

		uid action_container::family_id = 5;


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