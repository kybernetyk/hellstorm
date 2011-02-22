//
//  renderer.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "vec_2d.h"
#include "hs_ogl.h"

namespace hs 
{
	enum e_rendertarget
	{
		e_rendertarget_screen,
		e_rendertarget_texture
	};
	
	class renderer
	{
	public:
		void init(void);
		void shutdown(void);
		
		void begin_render(void);
		void end_render(void);
		
		vec2d conv_screen_to_world(vec2d vec);
		
		renderer();
		~renderer();
		
		void set_rendertarget(e_rendertarget t);
		
		void render_backing_texture_to_screen(void);
		
		void apply_camera_transform(void);
		
	protected:
		void setup_viewport_and_projection(int viewport_width_in_pixels,
										   int viewport_height_in_pixels,
										   double viewport_width_in_units,
										   double viewport_height_in_units);
		
		void set_rendertarget_screen(void);
		void set_rendertarget_texture(void);
		void create_render_texture(void);
		
		GLuint make_empty_texture(int w, int h);
		
	private:
		e_rendertarget current_rendertarget;
		
		GLint screen_frame_buffer;
		GLuint render_texture;
		GLuint texture_frame_buffer;
		
		double scale_factor;
		
		double x_conv;
		double y_conv;
		
		double cam_rot;
		vec2d cam_pos;
		
		size2d viewport_size_pixels;
		size2d viewport_size_units;
	};
	extern renderer g_renderer;
}