//
//  action_system.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "vec_2d.h"

namespace hs 
{
	class action_system;
	namespace actions
	{
		#define ACTIONTYPE_NONE 0
		#define ACTIONTYPE_MOVE_TO 1
		#define ACTIONTYPE_MOVE_BY 2
		#define ACTIONTYPE_ADD_COMPONENT 3
		#define ACTIONTYPE_CREATE_ENTITY 4
		#define ACTIONTYPE_CHANGE_INTEGER_TO 5	
		#define ACTIONTYPE_CHANGE_INTEGER_BY 6
		#define ACTIONTYPE_CHANGE_FLOAT_TO 7
		#define ACTIONTYPE_CHANGE_FLOAT_BY 8
		#define ACTIONTYPE_SCALE_BY 9
		#define ACTIONTYPE_FADE_TO 10

		struct action
		{
			static action_system *as;
			
			action();
			virtual ~action();
			
			unsigned int action_type;
			action *on_complete_action;
			
			double duration;
			double timestamp;
			
			bool is_finished;
			bool may_be_aborted;
			bool is_initialized;
		};
		
		struct move_to_action : public action
		{
			vec2d dest;
			vec2d _velocity;
			
			move_to_action()
			{
				action_type = ACTIONTYPE_MOVE_TO;
				
				dest = vec2d_make(0.0, 0.0);
				_velocity = vec2d_make(0.0, 0.0);
			}
		};
		
		
		
	}
}