//
//  hellstorm_config.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "vec_2d.h"
#include <string>

namespace hs
{
	namespace cfg
	{
		const int portrait = 0;
		const int landscape = 1;
		
		extern struct _screen_info
		{
			size2d size;
			double scale;
			int desired_fps;
			int orientation;
		} screen;
		
		extern struct _audio_info
		{
			double sfx_volume;
			double music_volume;
		} audio;
		
		extern struct _entity_system_info
		{
			int entity_pool_size;
			int components_per_entity;
		} entity_system;
				
		
		extern bool read_config_from_file(std::string filename);
		extern void read_user_settings(void);
		extern void save_user_settings(void);
	}
}