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
		

	protected:
		entity_manager *em;
		int skiptimer;
	};
}