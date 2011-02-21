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
	game *g_game = 0;
	
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
	
	void game::long_delta_occured(void)
	{
		tmr.update();
		tmr.update();
		next_game_tick = get_tick_count();
	}
	
    bool game::init_with_scene(hs::scene *scene)
    {
		g_game = this;
		
		cfg::read_config_from_file("hellstorm.cfg");
		
		
		audio_system::init(cfg::audio.sfx_volume, cfg::audio.music_volume);
		
		
		ticks_per_second = cfg::screen.desired_fps;
		skip_ticks = (1000.0 / (double)ticks_per_second);
		max_frame_skip = 5;
		fixed_delta = (1.0/ticks_per_second);
		max_timer_delta = fixed_delta*2.0;
				
		g_renderer.init();

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
				audio_system::update(fixed_delta);
				g_input.update();
				current_scene->update(fixed_delta);
				next_game_tick += skip_ticks;
				loops++;
			}
			if (loops > 0)
			{
				printf("had to do %i loops in one frame!\n", loops);
			}
		}
		else
		{
			next_game_tick = get_tick_count();
			g_input.update();
			audio_system::update(tmr.delta);
			current_scene->update(tmr.delta);
		}
	
		sprintf(s, "%.2f", tmr.fps);
	}
	
	void game::render(void)
	{
#ifdef TEX_RENDER_TEST
		g_renderer.set_rendertarget(e_rendertarget_texture);
		g_renderer.begin_render();
		current_scene->render();
		fnt->render_content(s);
		g_renderer.end_render();

		
		g_renderer.set_rendertarget(e_rendertarget_screen);
		g_renderer.begin_render();
		
		glLoadIdentity();
		int _x = 320;
		int _y = 480;
		float r = 0.0;
		
		float xscale = 0.5;
		
		glTranslatef( (0.5 * _x),  (0.5 * _y), 0);
		glScalef(xscale, xscale, 1.0);
		glRotatef(r, 0, 0, 1.0);
		glTranslatef( -(0.5 * _x),  -(0.5 * _y), 0);

		glPushMatrix();
		glTranslatef(-_x, -_y, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -_y, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(_x, -_y, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-_x, 0, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, 0, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(_x, 0, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-_x, _y, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, _y, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(_x, _y, 0);
		g_renderer.render_backing_texture_to_screen();
		glPopMatrix();

		
		g_renderer.end_render();
#else
		
		g_renderer.begin_render();
		current_scene->render();
		fnt->render_content(s);
		g_renderer.end_render();
#endif
	}
}