//
//  game_scene.h
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "hellstorm.h"
#include "psycho_bg_system.h"

namespace game 
{
	namespace defs
	{
		const double board_x_offset = 64.0;
		const double board_y_offset = 32.0;
		const double board_z = 0.0;
	}
	
	class game_scene : public hs::scene
	{
	public:
		void init(void);
		void shutdown(void);
		
		void update(double dt);
		void render(void);
		
		int scene_type(void);
		
		~game_scene();

	protected:
		hs::entity *create_pill (int col, int row, int type);
		hs::entity *create_virus (int col, int row, int type);
		
		
		hs::entity_manager *em;
		hs::corpse_retrieval_system *cs;
		hs::render_system *rs;
		hs::particle_system *ps;
		hs::action_system *as;
		hs::animation_system *ans;
		psycho_bg_system *bg_system;
	};

}