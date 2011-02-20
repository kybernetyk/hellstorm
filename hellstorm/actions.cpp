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
	}

	move_by_action::move_by_action(double dur, vec2d dist)
	{
		action_type = ACTIONTYPE_MOVE_BY;
		
		duration = dur;
		distance = dist;
	}

	
	
	action_system *action::as = NULL;
}