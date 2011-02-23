//
//  ui_factory.h
//  hellstorm
//
//  Created by jrk on 23/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "hellstorm.h"

namespace hs 
{
	namespace ui
	{
		namespace factory
		{
//			entity *create_sprite(entity_manager *em, std::string filename, vec3d position, vec2d anchor = anchor_center);
			entity *create_button(entity_manager *em, 
								  std::string filename, 
								  std::string label_text,
								  rect rc_unpressed,
								  rect rc_pressed,
								  vec3d position,
								  vec2d anchor = anchor_center
								  );
		}
	}
}