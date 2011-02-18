//
//  texture_2d.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "texture_2d.h"
#include "file_util.h"
#include <cstdio>
#include "SOIL.h"

namespace hs 
{
	GLuint texture2d::bound_texture = 0;
	
	texture2d::texture2d(std::string filename)
	{
		size = size2d_make(0.0, 0.0);
		if (!load_from_file(filename))
		{
			std::printf("couldn't load texture: %s!\n", filename.c_str());
			abort();
		}
	}
	
	texture2d::~texture2d()
	{
		if (bound_texture == name)
			bound_texture = 0;
		glDeleteTextures(1, &name);
		name = 0;
	}
	
	bool texture2d::load_from_file(std::string fn)
	{
		filename = fn;
		
		fn = path_for_file(fn.c_str());
		
		unsigned int w,h;
		
		 GLuint tex_2d = SOIL_load_OGL_texture2
		 (
		 fn.c_str(),
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 0,//SOIL_FLAG_COMPRESS_TO_DXT,
		 // SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		 //SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT
		 //	 SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		 &w,&h
		 );

		
		if(tex_2d == 0)
		{
			std::printf( "SOIL loading error: '%s' - %s\n", SOIL_last_result(),filename.c_str());
			abort();
			return false;
		}
		
		name = tex_2d;
		size = size2d_make(w, h);		
		set_alias_tex_params();
		return true;
	}
	
	void texture2d::bind(void)
	{
		if (bound_texture == name)
			return;
		
		bound_texture = name;
		glBindTexture(GL_TEXTURE_2D, name);
	}

	void texture2d::set_tex_params(tex_params *t_params)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t_params->minFilter );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t_params->magFilter );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, t_params->wrapS );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_params->wrapT );
	}
	
	void texture2d::set_alias_tex_params(void)
	{
		tex_params params = { GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
		set_tex_params(&params);
	}
	
	void texture2d::set_anti_alias_tex_params(void)
	{
		tex_params params = { GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
		set_tex_params(&params);
	}
	
}