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

	bitmap_font *fnt = 0;
	char s[32];
	
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
		cfg::read_config_from_file("hellstorm.cfg");
		
		ticks_per_second = cfg::screen.desired_fps;
		skip_ticks = (1000.0 / (double)ticks_per_second);
		max_frame_skip = 5;
		fixed_delta = (1.0/ticks_per_second);
		max_timer_delta = fixed_delta*2.0;
		
		
		g_renderer.init(cfg::screen.scale);

		fnt = new bitmap_font("impact20.fnt");
		
		fnt->position = vec3d_make(0.0, cfg::screen.size.h, 9.0);
		fnt->anchor_point = vec2d_make(0.0, 1.0);
		
        current_scene = scene;
		current_scene->init();
		tmr.update();
		tmr.update();

		next_game_tick = get_tick_count();
        tmr.delta = 0.0;
		return true;
    }
    
    void game::shutdown()
    {
		delete fnt;
    	g_renderer.shutdown();
    }
	
	void game::tick(void)
	{
		tmr.update();
		
		if (tmr.delta > max_timer_delta)
		{
			unsigned int t = get_tick_count();
			loops = 0;
			while (t > next_game_tick) // && loops < MAX_FRAMESKIP)
			{
				current_scene->update(fixed_delta);
				next_game_tick += skip_ticks;
				loops++;
			}
		}
		else
		{
			next_game_tick = get_tick_count();
			current_scene->update(tmr.delta);
		}
	
		sprintf(s, "%.2f", tmr.fps);
	}
	
	void game::render(void)
	{
		g_renderer.begin_render();
		current_scene->render();
		fnt->render_content(s);
		g_renderer.end_render();
	}
}