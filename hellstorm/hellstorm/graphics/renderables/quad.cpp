//
//  quad.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "quad.h"
#include "hellstorm.h"

namespace hs
{
	quad::quad()
	{
		init();
	}
	
	quad::quad(std::string fn)
	{
		init();
		filename = fn;
		load_from_file(fn);
	}
	
	quad::~quad()
	{
		g_texture_manager.release_texture(filename);
	}
	
	bool quad::load_from_file(std::string fn)
	{
		texture2d *tex = g_texture_manager.acquire_texture(filename);
		if (!tex)
		{
			abort();
			return false;
		}
		
		filename = fn;
		size = tex->size;
		
		return true;
	}
	
	void quad::render_content(void)
	{
		texture2d *texture = g_texture_manager.get_texture(filename);
		if (texture)
		{
			glPushMatrix();
			transform();
			
			GLfloat		coordinates[] = { 0.0f,	1.0,
				1.0,	1.0,
				0.0f,	0.0f,
				1.0,	0.0f };
			
			GLfloat		vertices[] = 
			{	
				0,						0,							0,
				size.w,					0,							0,
				0,						size.h,						0,
				size.w,					size.h,						0
			};
			
			GLfloat colors[] = 
			{
				color.r, color.g, color.b, alpha,
				color.r, color.g, color.b, alpha,
				color.r, color.g, color.b, alpha,
				color.r, color.g, color.b, alpha
			};
			glColorPointer(4, GL_FLOAT, 0, colors);
			
			texture->bind();
			//glColor4f(1.0, 1.0,1.0, alpha);
			
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glTexCoordPointer(2, GL_FLOAT, 0, coordinates);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			
			glPopMatrix();
		}
	}
}
