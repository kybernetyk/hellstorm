//
//  particle_system.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include <vector>
#include "vec_2d.h"
#include "components.h"
namespace hs
{
	class entity;
	class entity_manager;
	class comp::particle_emitter;
	
	class particle_system
	{
	public:
		particle_system(entity_manager *manager);
		
		void update(double dt);
		
		static entity *create_particle_emitter(std::string filename, double duration, vec2d position, bool autostart = false);
		static entity *create_particle_emitter(hs::particle_emitter *existing_em, double duration, vec2d position, bool autostart = false);

	protected:
		entity_manager *em;
		int skiptimer;
	};
}