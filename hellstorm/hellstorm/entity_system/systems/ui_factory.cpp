//
//  ui_factory.cpp
//  hellstorm
//
//  Created by jrk on 23/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ui_factory.h"

namespace hs 
{
	namespace ui
	{
		namespace factory
		{
			entity *create_button(entity_manager *em, 
								  std::string filename, 
								  std::string label_text,
								  rect rc_unpressed,
								  rect rc_pressed,
								  vec3d position,
								  vec2d anchor)
			{
				entity *ret = em->new_entity();
				button *btn = em->add_component<button>(ret);
				btn->type = e_control_button;
			
				btn->rc_idle = rc_unpressed;
				btn->rc_pressed = rc_pressed;
				
				btn->graphic = hs::factory::create_atlas_sprite(em, filename, position, rc_unpressed);
				
				if (label_text.length() > 0)
					btn->text = hs::factory::create_text_label(em, "impact20.fnt", label_text, position);
				else
					btn->text = NULL;
					
				return ret;
			}
		}
	}
}