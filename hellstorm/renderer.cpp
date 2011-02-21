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
	
	void renderer::init(double scale)
	{
		scale_factor = scale;
		double screen_size_x = cfg::screen.size.w * scale_factor;
		double screen_size_y = cfg::screen.size.h * scale_factor;	//change to 280 for a 40px high empty strip [eg for an ad banner]
		
		double viewport_size_x = cfg::screen.size.w;// / pixeltometerratio;//viewport_size_x / xyratio;
		double viewport_size_y = cfg::screen.size.h;	
		
		std::printf("RenderDevice init:\n{\n\tscreen_size_x: %f\n\tscreen_size_y: %f\n}\n", screen_size_x, screen_size_y);
		
//		current_render_target = RENDERTARGET_SCREEN;
		cam_rot = 0.0;		
//		camera = vector2D_make(viewport_size_x/2, viewport_size_y/2);
		cam_pos = vec2d_make(viewport_size_x/2.0, viewport_size_y/2.0);
		
		//camera = vector2D_make(0, 0);
		setup_viewport_and_projection(screen_size_x,screen_size_y,viewport_size_x,viewport_size_y);
	}
	
	void renderer::shutdown(void)
	{

	}
	
	void renderer::begin_render(void)
	{
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glLoadIdentity();
		
		
		glTranslatef( viewport_size_units.w/2.0,  viewport_size_units.h/2.0, 0);
		
		if (cam_rot != 0.0)
			glRotatef(cam_rot, 0.0, 0.0, 1.0);
		
		glTranslatef( -cam_pos.x , -cam_pos.y, 0.0);

	}
	
	void renderer::end_render(void)
	{
		
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
		
		return  ret;
	}
	
	void renderer::setup_viewport_and_projection(int viewport_width_in_pixels,
												 int viewport_height_in_pixels,
												 double viewport_width_in_units,
												 double viewport_height_in_units)
	{
		viewport_size_pixels = size2d_make(viewport_width_in_pixels, viewport_height_in_pixels);
		viewport_size_units = size2d_make(viewport_width_in_units, viewport_height_in_units);
		
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
}