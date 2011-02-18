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
		uid mark_of_death::FAMILY_ID = 1;
		uid position::FAMILY_ID = 2;

		uid renderable::FAMILY_ID = 4;
		uid sprite::FAMILY_ID = renderable::FAMILY_ID;
		uid atlas_sprite::FAMILY_ID = renderable::FAMILY_ID;
		uid text_label::FAMILY_ID = renderable::FAMILY_ID;
		uid particle_emitter::FAMILY_ID = renderable::FAMILY_ID;
		
	}
}