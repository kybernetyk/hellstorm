//
//  texture_manager.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "texture_manager.h"
#include "hellstorm.h"

namespace hs 
{
	texture_manager g_texture_manager;
	
	texture2d *texture_manager::acquire_texture(std::string filename)
	{
		if (reference_counts[filename] > 0)
		{
			reference_counts[filename]++;
			return textures[filename];
		}
	//	printf("loading tex %s\n", filename.c_str());
		
		texture2d *ret = new texture2d(filename);
		if (!ret)
			return NULL;
		
		textures[filename] = ret;
		reference_counts[filename] = 1;
		
		return ret;
	}
	
	texture2d *texture_manager::get_texture(std::string &filename)
	{
		if (reference_counts[filename] > 0)
			return textures[filename];
		
		return acquire_texture(filename);
	}
	
	void texture_manager::release_texture(std::string &filename)
	{
		reference_counts[filename]--;
		if (reference_counts[filename] <= 0)
		{
			texture2d *p = textures[filename];
			
			textures[filename] = NULL;
			reference_counts[filename] = 0;

			delete p;
		}
	}
	
	void texture_manager::purge_cache(void)
	{
		std::tr1::unordered_map <std::string, texture2d *>::iterator it = textures.begin();
		
		while (it != textures.end())
		{
			texture2d *p = it->second;
			delete p;
			++it;
		}
		
		textures.clear();
		reference_counts.clear();
	}

}