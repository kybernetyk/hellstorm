//
//  sprite_factory.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <string>
#include "vec_2d.h"


namespace hs 
{
	class entity;
	class particle_emitter;
	class entity_manager;
	
	namespace factory
	{
		entity *create_sprite(entity_manager *em, std::string filename, vec3d position, vec2d anchor = anchor_center);
		entity *create_atlas_sprite(entity_manager *em, std::string filename, vec3d position, rect src_rect, vec2d anchor = anchor_center);
		entity *create_text_label(entity_manager *em, std::string fontname, std::string text, vec3d position, vec2d anchor = anchor_center);
		
		entity *create_particle_emitter(entity_manager *em, std::string filename, double duration, vec3d position, bool autostart = false);
		entity *create_particle_emitter(entity_manager *em, particle_emitter *existing_em, double duration, vec3d position, bool autostart = false);

	}
}