//
//  components.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "components.h"

namespace hs 
{
	namespace comp
	{
		//0 reserved
		uid mark_of_death::family_id = 1;
		uid position::family_id = 2;

		uid renderable::family_id = 4;
		uid sprite::family_id = renderable::family_id;
		uid atlas_sprite::family_id = renderable::family_id;
		uid text_label::family_id = renderable::family_id;
		uid particle_emitter::family_id = renderable::family_id;
		
	}
}