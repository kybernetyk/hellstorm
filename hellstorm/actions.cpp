//
//  action_system.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "actions.h"
#include "hellstorm.h"
#include "action_system.h"

namespace hs 
{
	action_system *action::as = NULL;
	
	action::action()
	{
		action_type = ACTIONTYPE_NONE;
		on_complete_action = NULL;
		timestamp = duration = 0.0;
		may_be_aborted = true;
		is_finished = false;
		is_initialized = false;
	}
	
	action::~action()
	{
		
	}
	
	void action::append_action(action *next_action)
	{
		action *last = this;

		while (1)
		{
			if (last->on_complete_action)
				last = last->on_complete_action;
			else
				break;
		}
		
		last->on_complete_action = next_action;
	//	return last->on_complete_action;
	}


	move_to_action::move_to_action()
	{
		action_type = ACTIONTYPE_MOVE_TO;
		
		destination = vec2d_make(0.0, 0.0);
		_velocity = vec2d_make(0.0, 0.0);
	}
	
	move_to_action::move_to_action(double dur, vec2d dest)
	{
		action_type = ACTIONTYPE_MOVE_TO;
		
		destination = dest;
		duration = dur;
		
		_velocity = vec2d_zero;
	}
	
	move_by_action::move_by_action()
	{
		action_type = ACTIONTYPE_MOVE_BY;
		
		distance = vec2d_zero;
		duration = 0.0;
		_step = vec2d_zero;
	}

	move_by_action::move_by_action(double dur, vec2d dist)
	{
		action_type = ACTIONTYPE_MOVE_BY;
		
		duration = dur;
		distance = dist;
		_step = vec2d_zero;
	}

	scale_to_action::scale_to_action()
	{
		action_type = ACTIONTYPE_SCALE_BY;
		
		duration = 0.0;
		scale_to = vec2d_zero;
		_step = vec2d_zero;
	}
	
	scale_to_action::scale_to_action(double dur, vec2d to)
	{
		action_type = ACTIONTYPE_SCALE_BY;
		
		duration = dur;
		scale_to = to;
		_step = vec2d_zero;
	}

	scale_by_action::scale_by_action()
	{
		action_type = ACTIONTYPE_SCALE_BY;
		
		duration = 0.0;
		scale_by = vec2d_zero;
		_step = vec2d_zero;
	}
	
	scale_by_action::scale_by_action(double dur, vec2d by)
	{
		action_type = ACTIONTYPE_SCALE_BY;
		
		duration = dur;
		scale_by = by;
		_step = vec2d_zero;
	}
	
	fade_to_action::fade_to_action()
	{
		action_type = ACTIONTYPE_FADE_TO;
		destination_alpha = 0.0;
		_step = 0.0;
		duration = 0.0;
	}
	
	fade_to_action::fade_to_action(double dur, double dest_alpha)
	{
		action_type = ACTIONTYPE_FADE_TO;
		destination_alpha = dest_alpha;
		_step = 0.0;
		duration = dur;
	}

	fade_by_action::fade_by_action()
	{
		action_type = ACTIONTYPE_FADE_BY;
		fade_by = 0.0;
		_step = 0.0;
		duration = 0.0;
	}
	
	fade_by_action::fade_by_action(double dur, double by)
	{
		action_type = ACTIONTYPE_FADE_BY;
		fade_by = by;
		_step = 0.0;
		duration = dur;
	}

	rotate_to_action::rotate_to_action()
	{
		action_type = ACTIONTYPE_ROTATE_TO;
		_step = 0.0;
		
		rotate_to = 0.0;
		duration = 0.0;
	}
	
	rotate_to_action::rotate_to_action(double dur, double rot_to)
	{
		action_type = ACTIONTYPE_ROTATE_TO;
		_step = 0.0;
		
		rotate_to = rot_to;
		duration = dur;
	}
	
	rotate_by_action::rotate_by_action()
	{
		action_type = ACTIONTYPE_ROTATE_BY;
		_step = 0.0;
		
		rotate_by = 0.0;
		duration = 0.0;
	}
	
	rotate_by_action::rotate_by_action(double dur, double rot_by)
	{
		action_type = ACTIONTYPE_ROTATE_BY;
		_step = 0.0;
		
		rotate_by = rot_by;
		duration = dur;
	}

	
//	add_component_action::add_component_action(double dur, component *comp)
//	{
//		action_type = ACTIONTYPE_ADD_COMPONENT;
//		duration = dur;
//		family_id = comp->family_id;
//		component_to_add = comp;
//	}
	
}