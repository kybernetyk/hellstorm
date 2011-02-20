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

		ACTIONTYPE_SCALE_TO,
		ACTIONTYPE_SCALE_BY,

		ACTIONTYPE_FADE_TO,
		ACTIONTYPE_FADE_BY,
		
		ACTIONTYPE_ROTATE_TO,
		ACTIONTYPE_ROTATE_BY,
		
		ACTIONTYPE_ADD_COMPONENT,
		ACTIONTYPE_CREATE_ENTITY

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
		
		void append_action(action *next_action);
	};
	
//
	struct move_to_action : public action
	{
		vec2d destination;
		vec2d _velocity;
		
		move_to_action();
		move_to_action(double dur, vec2d dest);
	};
	
	struct move_by_action : public action
	{
		vec2d distance;
		vec2d _destination;
		
		move_by_action();
		move_by_action(double dur, vec2d dist);
	};

//
	struct scale_to_action : public action
	{
		vec2d scale_to;
		vec2d _step;
		
		scale_to_action();
		scale_to_action(double dur, vec2d to);
	};

	struct scale_by_action : public action
	{
		vec2d scale_by;
		vec2d _step;
		
		scale_by_action();
		scale_by_action(double dur, vec2d by);
	};
	

//
	struct fade_to_action : public action
	{
		double destination_alpha;
		double _step;
		
		fade_to_action();
		fade_to_action(double dur, double dest_alpha);
	};
}