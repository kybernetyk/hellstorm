//
//  psycho_bg_system.h
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <stddef.h>

#include "hellstorm.h"

namespace game
{
	enum e_psycho_type
	{
		e_psycho_type_static,
		e_psycho_type_sunburst,
		e_psycho_type_raster
	};
	
	struct comp_psycho_marker : public hs::component
	{
		static hs::uid family_id;
		
		e_psycho_type type;
		hs::vec2d velocity;
		double rot_speed;
		
		comp_psycho_marker()
		{
			type = e_psycho_type_static;
			rot_speed = 40.0;
			velocity = hs::vec2d_zero;
		}
	};
	
	class psycho_bg_system
	{
	public:
		psycho_bg_system(hs::entity_manager *manager);
		~ psycho_bg_system();
		
		void update(double dt);
		
	protected:
		hs::entity_manager *em;
		
		hs::entity **ent_cache;
		size_t cache_size;
	};
}