//
//  game.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "game.h"
#include "hellstorm.h"
#include "scene.h"

namespace hs 
{
	game::game()
	{
		current_scene = 0;
	}

	game::~game()
	{
		current_scene = 0;
	}
	
    bool game::init_with_scene(hs::scene *scene)
    {
		g_renderer.init(1.0);
		
        current_scene = scene;
        return true;
    }
    
    void game::shutdown()
    {
    	g_renderer.shutdown();
		delete rdev;
    }
	
	void game::tick(void)
	{
		current_scene->update(0.167);
	}
	
	void game::render(void)
	{
		g_renderer.begin_render();
		current_scene->render();
		g_renderer.end_render();
	}
}