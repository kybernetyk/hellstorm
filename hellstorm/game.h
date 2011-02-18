//
//  game.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

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
		
			renderer *rdev;
    };
    
};