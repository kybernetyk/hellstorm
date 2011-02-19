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
	
	enum e_actiontype
	{
		ACTIONTYPE_NONE = 0,
		ACTIONTYPE_MOVE_TO,
		ACTIONTYPE_MOVE_BY,
		ACTIONTYPE_ADD_COMPONENT,
		ACTIONTYPE_CREATE_ENTITY,
		ACTIONTYPE_SCALE_BY,
		ACTIONTYPE_FADE_TO
	};

	struct action
	{
		static action_system *as;
		
		action();
		virtual ~action();
		
		e_actiontype action_type;
		action *on_complete_action;
		
		double duration;
		double timestamp;
		
		bool is_finished;
		bool may_be_aborted;
		bool is_initialized;
	};
	
	struct move_to_action : public action
	{
		vec2d destination;
		vec2d _velocity;
		
		move_to_action();
		move_to_action(double dur, vec2d dest);
	};
}