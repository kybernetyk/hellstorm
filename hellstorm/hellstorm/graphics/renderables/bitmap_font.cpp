//
//  bitmap_font.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "bitmap_font.h"
#include "hellstorm.h"
#include "file_util.h"

namespace hs
{
	bitmap_font::bitmap_font(std::string fnt_filename)
	{
		init();
		load_from_file(fnt_filename);
		text_ptr = 0;
	}
	
	bitmap_font::~bitmap_font()
	{
		g_texture_manager.release_texture(texture_filename);
	}
	
	bool bitmap_font::load_from_file(std::string fnt_filename)
	{
		const char *fn = path_for_file(fnt_filename.c_str()).c_str();
		if (!bm_loadfont(fn, &font))
		{
			abort();
			return false;
		}
		
		texture2d *tex = g_texture_manager.acquire_texture(font.tex_filename);
		if (!tex)
		{
			abort();
			return false;
		}
		
		texture_filename = font.tex_filename;
		filename = fnt_filename;
		
		return true;
	}
	
	void bitmap_font::transform(void)
	{
		int w = bm_width(&font, text_ptr);
		float h = font.line_h*.75; //bm_height(&font, text);
		glTranslatef(position.x, position.y, position.z);
		
		if (rotation != 0.0f )
			glRotatef( rotation, 0.0f, 0.0f, 1.0f );
		
		if (scale.x != 1.0 || scale.y != 1.0)
			glScalef( scale.x, scale.y, 1.0f );
		
		glTranslatef(- (anchor_point.x * w),h - (anchor_point.y * h), 0);
	}
	
	void bitmap_font::render_content()
	{
		texture2d *texture = g_texture_manager.get_texture(texture_filename);
		if (texture)
		{
			
			glPushMatrix();
			transform();
			int l = strlen(text_ptr);
			
			texture->bind();
			
			GLfloat colors[] = 
			{
				color.r, color.g, color.b, alpha,
				color.r, color.g, color.b, alpha,
				color.r, color.g, color.b, alpha,
				color.r, color.g, color.b, alpha
			};
			glColorPointer(4, GL_FLOAT, 0, colors);
			
			//IF RENDER ERRORS OCCUR
			//EXCHANGE FLOAT FOR DOUBLE!
			float tx,ty,tw,th;
			
			
			bm_char *pchar = NULL;
			for (int i = 0; i < l; i++)
			{
				pchar = &font.chars[ text_ptr[i] ];
				
				tx = (float)pchar->x / (float)texture->size.w;
				ty = (float)pchar->y / (float)texture->size.h;
				tw = (float)pchar->w / (float)texture->size.w;
				th = (float)pchar->h / (float)texture->size.h;
				GLfloat		vertices[] = 
				{	
					0,			0,			0,
					pchar->w,	0,			0,
					0,			pchar->h,	0,
					pchar->w,	pchar->h,	0
				};
				
				GLfloat		coordinates[] = { tx,	ty + th,
					tx + tw,	ty + th,
					tx,	ty,
					tx + tw,	ty };
				
				glTranslatef(0, -pchar->h, 0.0);
				glTranslatef(pchar->x_offset, -pchar->y_offset, 0.0);			
				
				glVertexPointer(3, GL_FLOAT, 0, vertices);
				glTexCoordPointer(2, GL_FLOAT, 0, coordinates);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				
				glTranslatef(-pchar->x_offset, pchar->y_offset, 0.0);			
				glTranslatef(0, pchar->h, 0.0);
				
				
				glTranslatef(pchar->x_advance-pchar->x_offset, 0, 0.0);			
			}
			glPopMatrix();
		}
	}
}