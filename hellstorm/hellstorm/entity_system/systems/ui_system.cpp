//
//  ui_system.cpp
//  hellstorm
//
//  Created by jrk on 23/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ui_system.h"
#include "hellstorm.h"

namespace hs 
{
	namespace ui
	{
		uid control::family_id = 0;
	}
	
	ui_system::ui_system(entity_manager *manager)
	{
		em = manager;
		comp::register_component_class<ui::control>();

		ent_cache = new entity*[cfg::entity_system.entity_pool_size];
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = 0;
	}
	
	ui_system::~ui_system()
	{
		
	}
	
	void ui_system::handle_button(void)
	{
		ui::button *btn = (ui::button *)current_control;
		comp::atlas_sprite *graphic = btn->graphic->get<comp::atlas_sprite>();
		
		if (btn->state == ui::e_state_pressed)
		{
			if (g_input.has_touched_up())
			{
				if (btn->tag_ptr && point_in_entity(g_input.get_current_touch_location(), btn->graphic))
					*(btn->tag_ptr) = btn->tag;
					
				btn->state = ui::e_state_idle;
			}
		}
		else if (btn->state == ui::e_state_idle)
		{
			if (g_input.has_touched_down())
				if (point_in_entity(g_input.get_current_touch_location(), btn->graphic))
					btn->state = ui::e_state_pressed;
		}

		
		if (btn->state != btn->prev_state)
		{
			comp::position *pos = btn->graphic->get<comp::position>();

			if (btn->state == ui::e_state_pressed)
			{
				graphic->src_rect = btn->rc_pressed;
				pos->origin.x += btn->pressin.x;
				pos->origin.y += btn->pressin.y;
				
				printf("pressin: %f,%f\n", btn->pressin.x, btn->pressin.y);
			}
			else if (btn->state == ui::e_state_idle)
			{
				graphic->src_rect = btn->rc_idle;
				pos->origin.x -= btn->pressin.x;
				pos->origin.y -= btn->pressin.y;
			}
			
			btn->prev_state = btn->state;
		}
		
	}
	
	void ui_system::update(double dt)
	{
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = em->get_entities_posessing_component(ui::control::family_id, ent_cache, cfg::entity_system.entity_pool_size);

		
		for (uid i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			current_control = em->get_component<ui::control>(current_entity);
			
			switch (current_control->type)
			{
				case ui::e_control_button:
					handle_button();
					break;
					
				default:
					break;
			}
		}

	}
}