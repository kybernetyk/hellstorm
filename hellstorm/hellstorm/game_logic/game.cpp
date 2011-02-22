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
	
	void game::set_next_scene(hs::scene *scene)
	{
		if (next_scene)
		{
			printf("can't set next scene in same frame more than once!\n");
			abort();
		}
		
		next_scene = scene;
		scene_queue_state = e_sqs_set;
	}
	
	void game::push_scene(hs::scene *scene)
	{
		scene_stack_pointer++;
		if (scene_stack_pointer >= scene_stack_size)
		{
			printf("scene stack fuck'd up!\n");
			abort();
		}
		scene_stack[scene_stack_pointer] = scene;
		scene->init();
		
		scene_queue_state = e_sqs_pushed;
	}
	
	void game::pop_scene(void)
	{
		printf("popping scene ...\n");
		
		scene_queue_state = e_sqs_popped;
		pop_counter++;
	}
	
    bool game::init_with_scene(hs::scene *scene)
    {
		srand(time(0));
		
		scene_queue_state = e_sqs_none;
		pop_counter = 0;
		scene_stack_pointer = 0;
		next_scene = 0;
		scene_stack[scene_stack_pointer] = scene;
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
		if (scene_queue_state != e_sqs_none)
		{
			switch (scene_queue_state) 
			{
				case e_sqs_set:
					current_scene->shutdown();
					delete current_scene;
					scene_stack[scene_stack_pointer] = next_scene;
					current_scene = next_scene;
					current_scene->init();
					next_scene = 0;
					break;
				case e_sqs_pushed:
					current_scene = scene_stack[scene_stack_pointer];
					break;
				case e_sqs_popped:
					for (int i = 0; i < pop_counter; i++)
					{
						scene_stack_pointer--;
						if (scene_stack_pointer < 0)
						{
							printf("scene stack is fuck'd up!\n");
							abort();
							return;
						}
						current_scene->shutdown();
						delete current_scene;
						current_scene = scene_stack[scene_stack_pointer];
					}
					pop_counter = 0;
					break;
					
				default:
					abort();
					break;
			}
			scene_queue_state = e_sqs_none;
			next_game_tick = get_tick_count();
			tmr.update();
			tmr.update();
		}
		
		
		tmr.update();
		
		if (tmr.delta > max_timer_delta)
		{
			unsigned int t = get_tick_count();
			loops = 0;
			while (t > next_game_tick) // && loops < MAX_FRAMESKIP)
			{
				audio_system::update(fixed_delta);
				current_scene->update(fixed_delta);
				next_game_tick += skip_ticks;
				loops++;
				
				g_input.update();

			}
			if (loops > 0)
			{
				printf("had to do %i loops in one frame!\n", loops);
			}
		}
		else
		{
			next_game_tick = get_tick_count();
			audio_system::update(tmr.delta);
			current_scene->update(tmr.delta);
			
			g_input.update();
		}
	
		sprintf(s, "%.2f", tmr.fps);
	}
	
	void game::render(void)
	{
//#define TEX_RENDER_TEST

#ifdef TEX_RENDER_TEST
		static double xx = 0;
		//xx += 100.0 * tmr.delta;
		if (xx >= 320)
			xx = 0;
		
		g_renderer.set_rendertarget(e_rendertarget_texture);
		g_renderer.clear();

		g_renderer.begin_render();
		g_renderer.apply_camera_transform();
		current_scene->render();
		g_renderer.end_render();
		
		g_renderer.set_rendertarget(e_rendertarget_screen);
		g_renderer.clear();
		g_renderer.begin_render();
		
		//glDisable(GL_BLEND);
		
		glTranslatef(-xx, 0.0, 0.0);
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.0);
			g_renderer.render_backing_texture_to_screen();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(320.0, 0.0, 0.0);
		
			g_renderer.render_backing_texture_to_screen();
		glPopMatrix();

		glPushMatrix();
		glLoadIdentity();
		fnt->render_content(s);
		glPopMatrix();
		//glEnable(GL_BLEND);
		g_renderer.end_render();
#else
		g_renderer.clear();
		g_renderer.begin_render();
		g_renderer.apply_camera_transform();
	 	current_scene->render();
		fnt->render_content(s);
		g_renderer.end_render();
#endif
	}
}