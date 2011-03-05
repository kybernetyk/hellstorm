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
	
		bool components_registered = false;
		
		//0 reserved
		uid mark_of_death::family_id;
		uid position::family_id;

		uid renderable::family_id;
		/*uid sprite::family_id;
		uid atlas_sprite::family_id;
		uid text_label::family_id;
		uid particle_emitter::family_id;*/
		uid action_container::family_id;
		uid seq_animation::family_id;
		uid name::family_id;

		uid get_next_component_family_id(void)
		{
			static uid current_component_family_id = 1;
			return current_component_family_id++;
		}

		void register_components(void)
		{
			if (components_registered)
				return;
			
			register_component_class<mark_of_death>();
			register_component_class<position>();
			register_component_class<renderable>();
			register_component_class<action_container>();
			register_component_class<seq_animation>();
			register_component_class<name>();
			
			components_registered = true;
		}

#pragma mark -
#pragma mark action container
		action_container::action_container()
		{
//			printf("%i\n",action_container::family_id);
//			register_component_class<action_container>();
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