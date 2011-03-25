//
//  startup_scene.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "startup_scene.h"
#include "menu_scene.h"

namespace game 
{
	startup_scene::~startup_scene()
	{
		
	}
	
	void startup_scene::init(void)
	{
	init_counter = 1;
		init_done = false;
		
		printf("startup scene init ...\n");
		start_screen = hs::g_renderable_manager.acquire_resource<hs::quad>("startup.png");
		hs::quad *q = hs::g_renderable_manager.get_resource<hs::quad>(&start_screen);
		q->position = hs::vec3d_screen_center();
	
		
		bool sound = true;
		hs::settings::get_value_for_key(sound, "sound_on");
		
		if (!sound)
			hs::audio_system::set_sound_volume(0.0);
		else
			hs::audio_system::set_sound_volume(0.8);
		
		bool music = true;
		hs::settings::get_value_for_key(music, "music_on");
		
		if (!music)
			hs::audio_system::set_music_volume(0.0);
		else
			hs::audio_system::set_music_volume(0.6);

	}
	
	void startup_scene::shutdown(void)
	{
		
	}
	
	void startup_scene::update(double dt)
	{
		printf("STARTUP UPDATE LOL?\n");

		//wait 2 frames before doing heavy loading - so we can at least get a welcome screen out there
		if (!init_done && (init_counter-- <= 0))
		{
			init_done = true;
			printf("PENIS?\n");
			hs::audio_system::preload_sound("click.mp3");
			hs::audio_system::preload_sound("pill_land.m4a");
			hs::audio_system::preload_sound("pill_move.m4a");
			hs::audio_system::preload_sound("pill_weg.m4a");
			
			hs::audio_system::preload_music("Menu.mp3");

			hs::g_texture_manager.acquire_texture("rahmen.png");
			hs::g_texture_manager.acquire_texture("upper.png");
			hs::g_texture_manager.acquire_texture("lower.png");
			hs::g_texture_manager.acquire_texture("sunburst_1.png");
			hs::g_texture_manager.acquire_texture("game_sheet.png");
			hs::g_texture_manager.acquire_texture("background_noraster2.png");
			
			hs::g_game->set_scene(new menu_scene());	
			//load user settings
			//scores
			//etc pp
		}
	}
	
	void startup_scene::render(void)
	{
		hs::quad *q = hs::g_renderable_manager.get_resource<hs::quad>(&start_screen);
		hs::g_renderer.push_renderable(q);
	}
	
	int startup_scene::scene_type(void)
	{
		return 12;
	}
}