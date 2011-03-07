//
//  hud_system.h
//  hellstorm
//
//  Created by jrk on 7/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "hellstorm.h"

namespace game 
{	
	class hud_system
	{
	public:
		hud_system(hs::entity_manager *manager);
		~hud_system();
		void update(double dt);
		
	protected:
		hs::entity_manager *em;
		hs::entity **ent_cache;
		size_t cache_size;
		
		hs::comp::text_label *score_label;
		hs::comp::atlas_sprite *next_left, *next_right;
		
		void update_next_display();
		void update_score_display();
	};
}