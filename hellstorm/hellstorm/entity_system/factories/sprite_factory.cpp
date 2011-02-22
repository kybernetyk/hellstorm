//
//  sprite_factory.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "sprite_factory.h"
#include "hellstorm.h"

namespace hs 
{
	class entity;
	namespace factory
	{
		entity *create_sprite(std::string filename, vec3d position, vec2d anchor)
		{
			entity_manager *em = entity::ent_mgr;
			entity *ent = em->new_entity();
			comp::position *pos = em->add_component<hs::comp::position>(ent);
			pos->origin = position;
						
			comp::sprite *sprite = em->add_component<hs::comp::sprite>(ent);
			sprite->res_handle = hs::g_renderable_manager.acquire_resource<hs::quad>(filename);
			sprite->anchor_point = anchor;
			
			return ent;
		}
		
		entity *create_atlas_sprite(std::string filename, vec3d position, rect src_rect, vec2d anchor)
		{
			entity_manager *em = entity::ent_mgr;
			entity *ent = em->new_entity();
			comp::position *pos = em->add_component<hs::comp::position>(ent);
			pos->origin = position;
			
			comp::atlas_sprite *sprite = em->add_component<hs::comp::atlas_sprite>(ent);
			sprite->res_handle = hs::g_renderable_manager.acquire_resource<hs::atlas_quad>(filename);
			sprite->src_rect = src_rect;
			sprite->anchor_point = anchor;

			return ent;
		}
		
		entity *create_text_label(std::string fontname, std::string text, vec3d position, vec2d anchor)
		{
			entity_manager *em = entity::ent_mgr;
			entity *ent = em->new_entity();
			comp::position *pos = em->add_component<hs::comp::position>(ent);
			pos->origin = position;
			
			
			hs::comp::text_label *label = em->add_component<hs::comp::text_label>(ent);
			label->res_handle = hs::g_renderable_manager.acquire_resource<hs::bitmap_font>(fontname);
			label->text = text;
			label->anchor_point = anchor;

			return ent;
		}
		
		entity *create_particle_emitter(std::string filename, double duration, vec3d position, bool autostart)
		{
			entity_manager *em = entity::ent_mgr;
			
			entity *e = em->new_entity();
			
			comp::position *pos = em->add_component<comp::position>(e);
			pos->origin = position;
			
			comp::particle_emitter *pe = em->add_component<comp::particle_emitter>(e);
			pe->pe = g_renderable_manager.acquire_particle_emitter(filename);
			
			if (duration != 0.0)
				pe->pe->set_duration(duration);
			
			if (autostart)
			{
				pe->pe->reset();
				pe->pe->start();
			}
			
			return e;
		}
		
		entity *create_particle_emitter(particle_emitter *existing_em, double duration, vec3d position, bool autostart)
		{
			entity_manager *em = entity::ent_mgr;
			
			entity *e = em->new_entity();
			
			comp::position *pos = em->add_component<comp::position>(e);
			pos->origin = position;
			
			comp::particle_emitter *pe = em->add_component<comp::particle_emitter>(e);
			pe->pe = existing_em;
			
			if (duration != 0.0)
				pe->pe->set_duration(duration);
			
			if (autostart)
			{
				pe->pe->reset();
				pe->pe->start();
			}
			
			return e;
		}


	}
}