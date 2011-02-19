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
	
	namespace factory
	{
		entity *create_sprite(std::string filename, vec3d position, vec2d anchor = anchor_center);
		entity *create_atlas_sprite(std::string filename, vec3d position, rect src_rect, vec2d anchor = anchor_center);
		entity *create_text_label(std::string fontname, std::string text, vec3d position, vec2d anchor = anchor_center);
		
		entity *create_particle_emitter(std::string filename, double duration, vec2d position, bool autostart = false);
		entity *create_particle_emitter(particle_emitter *existing_em, double duration, vec2d position, bool autostart = false);

	}
}