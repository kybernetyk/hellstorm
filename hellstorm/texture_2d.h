//
//  texture_2d.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "hs_ogl.h"
#include "vec_2d.h"
#include <string>

namespace hs
{
	struct tex_params
	{
		GLuint	minFilter;
		GLuint	magFilter;
		GLuint	wrapS;
		GLuint	wrapT;
	};
	
	
	class texture2d
	{
	public:
		texture2d()
		{
			size = size2d_make(0.0, 0.0);
		}
		
		texture2d(std::string filename);
		virtual ~texture2d();
		
		virtual bool load_from_file(std::string filename);
		void bind();
		
		void set_tex_params(tex_params *t_params);
		
		void set_alias_tex_params();
		void set_anti_alias_tex_params();

		size2d size;
		GLuint name;
		std::string filename;
		
		static GLuint bound_texture;
	};

}