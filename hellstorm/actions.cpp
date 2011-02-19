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
	
		action_system *action::as = NULL;
	}
}