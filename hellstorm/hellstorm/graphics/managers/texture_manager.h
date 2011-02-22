//
//  texture_manager.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <tr1/unordered_map>
#include <string>

namespace hs 
{
	class texture2d;
	
	class texture_manager
	{
		public:
		texture2d *acquire_texture(std::string filename);
		texture2d *get_texture(std::string &filename);
		
		void release_texture(std::string &filename);
		
		void purge_cache(void);
		
	protected:
		std::tr1::unordered_map <std::string, int> reference_counts;
		std::tr1::unordered_map <std::string, texture2d *> textures;
	};
	
	extern texture_manager g_texture_manager;
}