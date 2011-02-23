//
//  renderer.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "renderer.h"
#include "hellstorm.h"
#include "hs_ogl.h"
#include <cstdio>

namespace hs 
{
	renderer g_renderer;
	
	renderer::renderer()
	{
		
	}
	
	renderer::~renderer()
	{
		
	}
	
	void renderer::init(void)
	{
		scale_factor = cfg::screen.scale;
		
//		current_rendertarget = e_rendertarget_screen;
		
		double screen_size_x = cfg::screen.size.w;
		double screen_size_y = cfg::screen.size.h;	//change to 280 for a 40px high empty strip [eg for an ad banner]
		
		double viewport_size_x = cfg::screen.size.w / scale_factor;// / pixeltometerratio;//viewport_size_x / xyratio;
		double viewport_size_y = cfg::screen.size.h / scale_factor;	
		
		std::printf("RenderDevice init:\n{\n\tscreen_size_x: %f\n\tscreen_size_y: %f\n}\n", screen_size_x, screen_size_y);
		
		//current_rendertarget = e_rendertarget_screen;
		cam_rot = 0.0;		
		cam_pos = vec2d_make(screen_size_x/2.0, screen_size_y/2.0);
		setup_viewport_and_projection(screen_size_x,screen_size_y,viewport_size_x,viewport_size_y);
		
		create_render_texture();
		
		set_rendertarget_screen();
	}
	
	void renderer::shutdown(void)
	{

	}

	void renderer::apply_camera_transform(void)
	{
		glTranslatef( viewport_size_units.w/2.0,  viewport_size_units.h/2.0, 0);
		
		if (cam_rot != 0.0)
			glRotatef(cam_rot, 0.0, 0.0, 1.0);
		
		glTranslatef( -cam_pos.x , -cam_pos.y, 0.0);
	}
	
	void renderer::clear(void)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void renderer::push_renderable(renderable *ren)
	{
		renderables.push_back(ren);
	}

	void renderer::push_renderables(std::vector <renderable *> &rens)
	{
		renderables.insert(renderables.end(), rens.begin(), rens.end());
	}

	void renderer::begin_render(void)
	{
		glLoadIdentity();
	}
	
	bool comp_rens(renderable *r1, renderable *r2)
	{
		if (r1->position.z == r2->position.z)
			return (r1->guid < r2->guid);
		
		return (r1->position.z < r2->position.z);
	}

	
	void renderer::flush(void)
	{
		std::sort (renderables.begin(), renderables.end(), comp_rens);
		
		std::vector<renderable *>::const_iterator it = renderables.begin();
		while (it != renderables.end())
		{
			(*it)->render_content();
			++it;
		}
		renderables.clear();
	}
	
	void renderer::end_render(void)
	{
		
		glLoadIdentity();
	}
	
	vec2d renderer::conv_screen_to_world(vec2d vec)
	{
#ifdef HS_TARGET_IPHONE
#else
		vec.y = SCREEN_H*scale_factor - (float)vec.y;
#endif
		vec2d ret;
		ret.x = vec.x * x_conv + cam_pos.x - viewport_size_units.w/2.0; //+ camera offset etc
		ret.y = vec.y * y_conv + cam_pos.y - viewport_size_units.h/2.0;
	
//		printf("%f,%f --> %f,%f\n",vec.x, vec.y, ret.x, ret.y);
		
		return  ret;
	}
	
	void renderer::setup_viewport_and_projection(int viewport_width_in_pixels,
												 int viewport_height_in_pixels,
												 double viewport_width_in_units,
												 double viewport_height_in_units)
	{
		viewport_size_pixels = size2d_make(viewport_width_in_pixels, viewport_height_in_pixels);
		viewport_size_units = size2d_make(viewport_width_in_units, viewport_height_in_units);
		
		x_conv = (double)viewport_width_in_units / (double)viewport_width_in_pixels;
		y_conv = (double)viewport_height_in_units / (double)viewport_height_in_pixels;
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glViewport(0,0,viewport_width_in_pixels, viewport_height_in_pixels);
		
		glEnable(GL_TEXTURE_2D); //enable texture mapping
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Black Background
		
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_ALPHA_TEST);
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//GL_ONE_MINUS_SRC_ALPHA);      // Enable Alpha Blending (disable alpha testing)
		glEnable(GL_BLEND);
		
		glShadeModel(GL_SMOOTH); //enables smooth color shading
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity(); //Reset projection matrix
		
		//glOrthof(-viewport_width_in_meters/2.0 , viewport_width_in_meters/2.0 , -viewport_height_in_meters/2.0, viewport_height_in_meters/2.0 , -10.0 , 10.0 );
		
		glOrthof(0, viewport_width_in_units, 0, viewport_height_in_units, -10.0 , 10.0 );
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		
		glEnableClientState( GL_VERTEX_ARRAY);
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY);
		
		glEnable( GL_TEXTURE_2D);
	}
	
#pragma mark -
#pragma mark render backing tex
	void renderer::render_backing_texture_to_screen(void)
	{
		GLfloat		coordinates[] = { 0.0f,	0.0,
			1.0,	0.0,
			0.0f,	1.0f,
			1.0,	1.0f };

		GLfloat		vertices[] = 
		{	
			0,			0,			0,
			viewport_size_pixels.w*x_conv,	0,			0,
			0,			viewport_size_pixels.h*y_conv,	0,
			viewport_size_pixels.w*x_conv,			viewport_size_pixels.h*y_conv,	0
		};

		float alpha = 1.0;
		GLfloat colors[] = 
		{
			1.0,1.0,1.0,alpha,
			1.0,1.0,1.0,alpha,
			1.0,1.0,1.0,alpha,
			1.0,1.0,1.0,alpha,
		};
		glColorPointer(4, GL_FLOAT, 0, colors);

		if (texture2d::bound_texture != render_texture)
		{
			texture2d::bound_texture = render_texture;
			glBindTexture( GL_TEXTURE_2D, render_texture );
		}
		glDisable(GL_BLEND);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, coordinates);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glEnable(GL_BLEND);
		
	}
	
#pragma mark -
#pragma mark render texture helpers
	GLuint renderer::make_empty_texture(int w, int h)
	{
		GLuint ret;
		
		glGenTextures(1, &ret);
		
		glBindTexture(GL_TEXTURE_2D, ret);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glBindTexture(GL_TEXTURE_2D, ret);
		
//		tex_params t_params = { GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t_params.minFilter );
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t_params.magFilter );
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, t_params.wrapS );
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_params.wrapT );

		
		texture2d::bound_texture = ret;
		return ret;
	}
	
#pragma mark -
#pragma mark render targets
	void renderer::create_render_texture(void)
	{
		render_texture = make_empty_texture(512,512);
		
		screen_frame_buffer = 100;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, &screen_frame_buffer);
		
		glGenFramebuffersOES(1, &texture_frame_buffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, texture_frame_buffer);
		glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_TEXTURE_2D, render_texture, 0);
		
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, screen_frame_buffer);
	}
	
	void renderer::set_rendertarget(e_rendertarget t)
	{
		if (current_rendertarget == t)
			return;
		
		if (t == e_rendertarget_screen)
			set_rendertarget_screen();
		else
			set_rendertarget_texture();
	}

	void renderer::set_rendertarget_screen(void)
	{
		current_rendertarget = e_rendertarget_screen;
		
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, screen_frame_buffer);
		glViewport(0,0,viewport_size_pixels.w, viewport_size_pixels.h);
	}

	void renderer::set_rendertarget_texture(void)
	{
		current_rendertarget = e_rendertarget_texture;
		
		glViewport(0, 0, 512, 512);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, texture_frame_buffer);
	}

	
}