//
//  action_system.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "actions.h"
#include "components.h"
#include <vector>

namespace hs
{
	class entity_manager;
	class entity;
	
	void action_append_action(action *first, action *to_append);
	
	class action_system
	{
	public:
		action_system(entity_manager *manager);
		void update(double dt);
		
		void add_action_to_entity(entity *e, action *a);
		void cancel_action(entity *e, action *a);
		
	protected:
		void step_action(action *action);
		void handle_action_container(void);
		
		
		void handle_default_action (action *action);		
		void handle_move_to_action (move_to_action *action);
//		void handle_move_by_action (MoveByAction *action);
//		void handle_create_entity_action (CreateEntityAction *action);
//		void handle_add_component_action (AddComponentAction *action);
//		
//		void handle_scale_by_action (ScaleByAction *action);
//		void handle_fade_to_action (FadeToAction *action);

		
	private:
		entity_manager *em;
		std::vector<entity *> entities;
		double current_dt;
		double tmp_dt;
		
		entity *current_entity;
		comp::action_container *current_container;
		comp::position *current_position;
		comp::renderable *current_renderable;
		
	};
}