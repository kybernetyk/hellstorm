//
//  startup_scene.h
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "hellstorm.h"

namespace game 
{
	class startup_scene : public hs::scene
	{
	public:
		void init(void);
		void shutdown(void);
		
		void update(double dt);
		void render(void);
		
		int scene_type(void);
		
		~startup_scene();
	protected:
		int init_counter;
		bool init_done;
		
		hs::resource_handle start_screen;
	};
	
}