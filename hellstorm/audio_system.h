//
//  audio_system.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <string>

namespace hs
{
	class audio_system
	{
	public:
		audio_system();
		~audio_system();
		
		static void preload_sound(std::string filename);
		static void unload_sound(std::string filename);
		
		static void play_sound(std::string filename);
		
		static void play_music(std::string filename);
		static void stop_music(void);
		
		static void pause_music(void);
		static void rewind_music(void);
		static void resume_music(void);
		
		static void set_music_volume(double vol);
		static double get_music_volume(void);
		
		static void set_sound_volume(double vol);
		static double get_sound_volume(void);

	protected:
		static double music_volume;
		static double sound_volume;
		static std::string last_music_played;
	};
	
}