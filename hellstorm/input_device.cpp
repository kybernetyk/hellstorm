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
		input_state = inputstate_no_input;
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
	
	e_inputstate input_device::get_inputstate(void)
	{
		return input_state;
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
	
	void input_device::input_touch_down(vec2d location)
	{
		last_event = inputevent_touch_down;
		input_state = inputstate_touch_down;
		initial_touch_location = g_renderer.conv_screen_to_world(location);;
		current_touch_location = initial_touch_location;
	}
	
	void input_device::input_touch_move(vec2d location)
	{
		current_touch_location = g_renderer.conv_screen_to_world(location);;
	}
	
	void input_device::input_touch_up(vec2d location)
	{
		last_event = inputevent_touch_up;
		input_state = inputstate_no_input;
		current_touch_location = g_renderer.conv_screen_to_world(location);;
	}

}