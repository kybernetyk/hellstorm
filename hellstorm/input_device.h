//
//  input_device.h
//  hellstorm
//
//  Created by jrk on 21/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "vec_2d.h"

namespace hs
{
	enum e_inputstate
	{
		inputstate_no_input,
		inputstate_touch_down,
		inputstate_touch_up	
	};
	
	enum e_inputevent
	{
		inputevent_none,
		inputevent_touch_down,
		inputevent_touch_up
	};
	
	class input_device
	{
	public:
		input_device();	
		
		void update(void);

		e_inputstate get_inputstate(void);
		vec2d get_initial_touch_location(void);
		vec2d get_current_touch_location(void);
	
		//to be called from external
		void input_touch_down(vec2d location);
		void input_touch_move(vec2d location);
		void input_touch_up(vec2d location);
		
		e_inputevent get_last_event(void);
		
	protected:
		e_inputstate input_state;
		e_inputevent last_event;
		vec2d initial_touch_location;
		vec2d current_touch_location;
		bool reset_event;
	};
	
	extern input_device g_input;
}