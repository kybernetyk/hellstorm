//
//  hellstorm_config.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "hellstorm_config.h"
#include "hellstorm.h"

#include "ConfigFile.h"

namespace hs
{
	namespace cfg
	{
		_screen_info screen;
		_audio_info audio;
		_entity_system_info entity_system;
		
		void set_defaults(void)
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
		}
		
		bool read_config_from_file(std::string filename)
		{
			set_defaults();
			
			std::string fn = path_for_file(filename.c_str());
			
			try
			{
				ConfigFile config(fn);

				//screen
				config.readInto(screen.size.w, "screen.w");
				config.readInto(screen.size.h, "screen.h");
				config.readInto(screen.scale, "screen.scale");
				config.readInto(screen.desired_fps, "screen.desired_fps");
				
				std::string tmp;
				config.readInto(tmp, "screen.orientation");
				
				if (tmp == "portrait")
					screen.orientation = portrait;
				if (tmp == "landscape")
					screen.orientation = landscape;
	
				//audio
				config.readInto(audio.sfx_volume, "audio.sfx_volume");
				config.readInto(audio.music_volume, "audio.music_volume");

				//entity system
				config.readInto(entity_system.entity_pool_size, "entity_system.entity_pool_size");
				config.readInto(entity_system.components_per_entity, "entity_system.components_per_entity");
				
				

			}
			catch (ConfigFile::file_not_found) 
			{
				return false;
			}
			
			
			
			return true;
		}
	}
}