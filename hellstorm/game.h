//
//  game.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "timer.h"

namespace hs 
{
    class scene;
	class renderer;
    
    class game 
    {
        public:
            bool init_with_scene(hs::scene *scene);
            void shutdown(void);
        
            void tick(void);
			void render(void);
               
			game();
			~game();
        protected:
            hs::scene *current_scene;
			timer tmr;
		
		private:
			unsigned int ticks_per_second;
			double skip_ticks;
			unsigned int max_frame_skip;
			double fixed_delta;
			unsigned int next_game_tick;
			unsigned int loops;
			double max_timer_delta;
    };
    
	extern game *g_game;
};