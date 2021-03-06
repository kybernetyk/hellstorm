//
//  input_device.cpp
//  hellstorm
//
//  Created by jrk on 21/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "input_device.h"
#include "hellstorm.h"

namespace hs 
{
	input_device g_input;

	input_device::input_device()
	{
		last_event = inputevent_none;
		
		initial_touch_location = vec2d_zero;
		current_touch_location = vec2d_zero;
		
		reset_event = false;
	}
	
	void input_device::update(void)
	{
		if (reset_event)
			last_event = inputevent_none;
	}

	vec2d input_device::get_initial_touch_location(void)
	{
		return initial_touch_location;	
	}

	vec2d input_device::get_current_touch_location(void)
	{
		return current_touch_location;
	}
	
	e_inputevent input_device::get_last_event(void)
	{
		reset_event = true;
		return last_event;
	}
	
	bool input_device::has_touched_down(void)
	{
		return (get_last_event() == inputevent_touch_down);
	}

	bool input_device::has_moved(void)
	{
		return (get_last_event() == inputevent_touch_move);		
	}
	
	bool input_device::has_touched_up(void)
	{
		return (get_last_event() == inputevent_touch_up);
	}
	
	void input_device::input_touch_down(vec2d location)
	{
		last_event = inputevent_touch_down;
		initial_touch_location = g_renderer.conv_screen_to_world(location);
		current_touch_location = initial_touch_location;
	}
	
	void input_device::input_touch_move(vec2d location)
	{
		last_event = inputevent_touch_move;
		current_touch_location = g_renderer.conv_screen_to_world(location);
	}
	
	void input_device::input_touch_up(vec2d location)
	{
		last_event = inputevent_touch_up;
		current_touch_location = g_renderer.conv_screen_to_world(location);
	}

}