//
//  ui_system.h
//  hellstorm
//
//  Created by jrk on 23/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "entity_manager.h"

namespace hs
{
	namespace ui
	{
		enum e_control_type
		{
			e_control_button
		};
		
		enum e_control_state
		{
			e_state_idle,
			e_state_pressed
		};
		
		struct control : public component
		{
			static uid family_id;
			e_control_type type;
		};
		
		struct button : public control
		{
			e_control_state prev_state;
			e_control_state state;
			entity *text;
			entity *graphic;
			
			vec2d pressin;
			
			rect rc_pressed;
			rect rc_idle;
			int tag;
			
			int *tag_ptr;
			
			button()
			{
				type = e_control_button;
				state = e_state_idle;
				prev_state = state;
				tag = 0;
				
				tag_ptr = 0;
				rc_idle = rect_make(0.0, 0.0, 0.0, 0.0);
				rc_pressed = rect_make(0.0, 0.0, 0.0, 0.0);
				pressin = vec2d_zero;
			}
		};
	}
	
	class ui_system
	{
	public:
		ui_system(entity_manager *manager);
		~ui_system();
		
		void update(double dt);
		
	protected:
		void handle_button(void);
		
		entity *current_entity;
		ui::control *current_control;
		entity_manager *em;
		
		entity **ent_cache;
		size_t cache_size;
	};
}