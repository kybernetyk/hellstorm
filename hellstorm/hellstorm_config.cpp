//
//  hellstorm_config.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "hellstorm_config.h"
#include "hellstorm.h"

namespace hs
{
	namespace cfg
	{
		_screen_info screen;
		_audio_info audio;
		_entity_system_info entity_system;
		
		bool read_config_from_file(std::string filename)
		{
			screen.size.w = 320;
			screen.size.h = 480;
			screen.scale = 1.0;
			screen.desired_fps = 60;
			screen.orientation = portrait;
			
			audio.sfx_volume = 0.8;
			audio.music_volume = 0.5;
			
			entity_system.entity_pool_size = 128;
			entity_system.components_per_entity = 32;
			
			return true;
		}
	}
}