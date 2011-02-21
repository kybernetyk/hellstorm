//
//  renderer.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "vec_2d.h"

namespace hs 
{
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
		
	protected:
		void setup_viewport_and_projection(int viewport_width_in_pixels,
										   int viewport_height_in_pixels,
										   double viewport_width_in_units,
										   double viewport_height_in_units);
		private:
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