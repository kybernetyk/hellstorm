//
//  action_system.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "action_system.h"
#include "hellstorm.h"

namespace hs 
{
//	action *action_append_action(action *first, action *next_action)
//	{
//		action *last = first;
//		while (1)
//		{
//			if (last->on_complete_action)
//				last = last->on_complete_action;
//			else
//				break;
//		}
//		
//		last->on_complete_action = next_action;
//		
//		return last->on_complete_action;
//	}
	
	action_system::action_system(entity_manager *manager)
	{
		action::as = this;
		em = manager;
		current_dt = 0.0;
	}
	
	void action_system::add_action_to_entity(entity *e, action *a)
	{
		comp::action_container *cont = em->get_component<comp::action_container>(e);
		if (!cont)
			cont = em->add_component<comp::action_container>(e);
		
		bool did_insert = false;
		for (int i = 0; i < NUM_OF_ACTIONS_PER_CONTAINER; i++)
		{
			if (!cont->actions[i])
			{
				cont->actions[i] = a;
				did_insert = true;
				break;
			}
		}
		
		if (!did_insert)
			abort();
	}
	
	void action_system::cancel_action(entity *e, action *a)
	{
		comp::action_container *cont = em->get_component<comp::action_container>(e);
		if (!cont)
			return;
		
		for (int i = 0; i < NUM_OF_ACTIONS_PER_CONTAINER; i++)
		{
			if (cont->actions[i] == a)
			{
				action *child = a->on_complete_action;
				
				while (child) 
				{
					action *t = child;
					child = child->on_complete_action;
					delete t;
				}
				cont->actions[i] = NULL;
			}
		}
	}
	
	
	
	void action_system::handle_action_container(void)
	{
		action **actions = current_container->actions;
		
		action *current_action = NULL;
		for (int i = 0; i < NUM_OF_ACTIONS_PER_CONTAINER; i++)
		{
			current_action = actions[i];
			if (!current_action)
				continue;
			
			step_action(current_action);
			
			switch (current_action->action_type) 
			{
				case ACTIONTYPE_MOVE_TO:
					handle_move_to_action((move_to_action *)current_action);
					break;
				case ACTIONTYPE_MOVE_BY:
					handle_move_by_action((move_by_action *)current_action);
					break;
				case ACTIONTYPE_SCALE_TO:
					handle_scale_to_action((scale_to_action *)current_action);
				case ACTIONTYPE_SCALE_BY:
					handle_scale_by_action((scale_by_action *)current_action);
					break;
				case ACTIONTYPE_FADE_TO:
					handle_fade_to_action((fade_to_action *)current_action);
					break;
				case ACTIONTYPE_NONE:
				default:
					//handle_default_action(current_action);
					break;
			}

			if (current_action->is_finished)
			{
				action *on_complete_action = current_action->on_complete_action;
				
				//run another action
				if (on_complete_action)
				{
					delete current_action;
					current_action = NULL;
					current_container->actions[i] = on_complete_action;
				}
				else //do nothing - just delete current action
				{
					delete current_action;
					current_action = NULL;
					current_container->actions[i] = NULL;
				}
			}
		}
	}
	
	void action_system::update(double dt)
	{
		tmp_dt = dt;
		
		entities.clear();
		em->get_entities_posessing_component(entities, comp::action_container::family_id);
		
		std::vector<entity *>::const_iterator it = entities.begin();
		while (it != entities.end())
		{
			current_entity = *it;
			++it;
			
			current_container = em->get_component<comp::action_container>(current_entity);
			current_position = em->get_component<comp::position>(current_entity);
			current_renderable = em->get_component<comp::renderable>(current_entity);

			handle_action_container();
		}
		
	}
	
	void action_system::step_action(action *action)
	{
		action->timestamp += tmp_dt;
		current_dt = tmp_dt;
		
		if ( (action->duration - action->timestamp) <= 0.0)
		{
			action->is_finished = true;
			current_dt -= (action->timestamp - action->duration);
		}
	}

#pragma -
#pragma actions handler
	void action_system::handle_move_to_action(move_to_action *action)
	{
		if (action->duration == 0.0)
		{
			current_position->origin.x = action->destination.x;
			current_position->origin.y = action->destination.y;
		}
		
		if (!action->is_initialized)
		{
			action->is_initialized = true;
			double dx = action->destination.x - current_position->origin.x;
			double dy = action->destination.y - current_position->origin.y;
			
			action->_velocity = vec2d_make(dx / action->duration, dy / action->duration);
		}
		
		current_position->origin.x += action->_velocity.x * current_dt;
		current_position->origin.y += action->_velocity.y * current_dt;		
	}
	
	void action_system::handle_move_by_action(move_by_action *action)
	{
		if (action->duration == 0.0)
		{
			current_position->origin.x += action->distance.x;
			current_position->origin.y += action->distance.y;
			return;
		}
		
		if (!action->is_initialized)
		{
			action->is_initialized = true;
			
			action->_destination.x = current_position->origin.x + action->distance.x;
			action->_destination.y = current_position->origin.y + action->distance.y;
		}
		
		current_position->origin.x += (action->distance.x/action->duration) * current_dt;
		current_position->origin.y += (action->distance.y/action->duration) * current_dt;
	}
	
	void action_system::handle_scale_to_action(scale_to_action *action)
	{
		if (action->duration == 0.0)
		{
			current_position->scale.x = action->scale_to.x;
			current_position->scale.y = action->scale_to.y;
			return;
		}
		
		if (!action->is_initialized)
		{
			action->is_initialized = true;
			double dx = action->scale_to.x - current_position->scale.x;
			double dy = action->scale_to.y - current_position->scale.y;
			
			action->_step = vec2d_make(dx / action->duration, dy / action->duration);
		}
		
		current_position->scale.x += action->_step.x * current_dt;
		current_position->scale.y += action->_step.y * current_dt;
	}
	
	void action_system::handle_scale_by_action(scale_by_action *action)
	{
		if (action->duration == 0.0)
		{
			current_position->scale.x *= action->scale_by.x;
			current_position->scale.y *= action->scale_by.y;
			return;
		}
		
		if (!action->is_initialized)
		{
			action->is_initialized = true;
			
			action->_step.x = ((current_position->scale.x * action->scale_by.x) - current_position->scale.x) / action->duration;
			action->_step.y = ((current_position->scale.y * action->scale_by.y) - current_position->scale.y) / action->duration;
		}
		
		current_position->scale.x += action->_step.x * current_dt;
		current_position->scale.y += action->_step.y * current_dt;
	}
	
	void action_system::handle_fade_to_action(fade_to_action *action)
	{
		if (action->duration == 0.0)
		{
			current_renderable->alpha = action->destination_alpha;
			return;
		}
		
		if (!action->is_initialized)
		{
			action->is_initialized = true;
			action->_step = (action->destination_alpha - current_renderable->alpha) / action->duration;
		}
		
		current_renderable->alpha += action->_step * current_dt;
	}
}
















