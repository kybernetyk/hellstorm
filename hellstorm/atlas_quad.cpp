//
//  atlas_quad.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "atlas_quad.h"
#include "hellstorm.h"

namespace hs 
{
	atlas_quad::atlas_quad()
	{
		init();
	}
	
	atlas_quad::atlas_quad(std::string fn)
	{
		init();
		filename = fn;
		load_from_file(fn);
	}
	
	atlas_quad::~atlas_quad()
	{
		g_texture_manager.release_texture(filename);
	}
	
	void atlas_quad::init(void)
	{
		renderable::init();
		
		src_rect = rect_make(0.0, 0.0, 0.0, 0.0);
		tex_size = size2d_make(0.0, 0.0);
	}
	
	bool atlas_quad::load_from_file(std::string fn)
	{
		texture2d *tex = g_texture_manager.acquire_texture(fn);
		if (!tex)
		{
			abort();
			return false;
		}
		
		filename = fn;
		tex_size = tex->size;

		return true;
	}
	
	void atlas_quad::render_content(void)
	{
		texture2d *texture = g_texture_manager.get_texture(filename);
		if (texture)
		{
			glPushMatrix();
			
			size.w = src_rect.w;
			size.h = src_rect.h;
			
			transform();
			
			rect atlas_info;
			atlas_info.x = src_rect.x / texture->size.w;
			atlas_info.y = src_rect.y / texture->size.h;
			
			atlas_info.w = src_rect.w / texture->size.w;
			atlas_info.h = src_rect.h / texture->size.h;
		
			GLfloat		coordinates[] = { 
				atlas_info.x,	atlas_info.y + atlas_info.h,
				atlas_info.x + atlas_info.w,	atlas_info.y + atlas_info.h,
				atlas_info.x,	atlas_info.y,
				atlas_info.x + atlas_info.w,	atlas_info.y };

			GLfloat		vertices[] = 
			{	
				0,			0,			0,
				size.w,	0,			0,
				0,			size.h,	0,
				size.w,			size.h,	0
			};

			GLfloat colors[] = 
			{
				1.0,1.0,1.0,alpha,
				1.0,1.0,1.0,alpha,
				1.0,1.0,1.0,alpha,
				1.0,1.0,1.0,alpha,
			};
			glColorPointer(4, GL_FLOAT, 0, colors);
			
			//		glEnable( GL_TEXTURE_2D);
			texture->bind();
			//glColor4f(1.0, 1.0,1.0, alpha);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glTexCoordPointer(2, GL_FLOAT, 0, coordinates);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			
			//		glDisable( GL_TEXTURE_2D);
			//		glDisableClientState(GL_VERTEX_ARRAY );
			//		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			glPopMatrix();
		}
	}
}
