//
//  action_system.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "vec_2d.h"
#include "hs_types.h"

namespace hs 
{
	class action_system;
	class component;
	
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
		
		ACTIONTYPE_ADD_COMPONENT
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
	
#pragma mark -
#pragma mark move
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
		vec2d _step;
		
		move_by_action();
		move_by_action(double dur, vec2d dist);
	};

#pragma mark -
#pragma mark scale
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
	
#pragma mark -
#pragma mark fade
	struct fade_to_action : public action
	{
		double destination_alpha;
		double _step;
		
		fade_to_action();
		fade_to_action(double dur, double dest_alpha);
	};

	struct fade_by_action : public action
	{
		double fade_by;
		double _step;
		
		fade_by_action();
		fade_by_action(double dur, double by);
	};
	
#pragma mark -
#pragma mark rotate
	struct rotate_to_action : public action
	{
		double rotate_to;
		double _step;
		
		rotate_to_action();
		rotate_to_action(double dur, double rot_to);
	};
	
	struct rotate_by_action : public action
	{
		double rotate_by;
		double _step;
		
		rotate_by_action();
		rotate_by_action(double dur, double rot_by);
	};
	
#pragma mark -
#pragma mark comp/ent
	struct add_component_action : public action
	{
		uid family_id;
		component *component_to_add;
		
		template <typename T>
		add_component_action(double dur, T *comp)
		{
			action_type = ACTIONTYPE_ADD_COMPONENT;
			
			family_id = T::family_id;
			component_to_add = comp;
			
			duration = dur;
		}

	};

}