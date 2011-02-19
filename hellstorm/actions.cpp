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
	namespace actions
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
			
			_velocity = vec2d_make(0.0, 0.0);
		}

		
		action_system *action::as = NULL;
	}
}