//
//  vec_2d.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "vec_2d.h"
#include "hellstorm.h"
#include <cmath>

namespace hs
{
	vec2d anchor_bottom_left = {0.0,0.0};
	vec2d anchor_bottom_right = {1.0,0.0};
	vec2d anchor_center = {0.5,0.5};
	vec2d anchor_top_left = {0.0,1.0};
	vec2d anchor_top_right = {1.0,1.0};

	
	vec2d vec2d_make(double x, double y)
	{
		vec2d vc = {x,y};
		return vc;
	}
		
	vec2d vec2d_screen_center(void)
	{
		vec2d vc = {cfg::screen.size.w/2, cfg::screen.size.h/2};
		return vc;
	}
	
	vec2d vec2d_normalize(vec2d vec)
	{
		float len = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
		vec.x = vec.x/len;
		vec.y = vec.y/len;
		
		return vec;
	}

	vec3d vec3d_make(double x, double y, double z)
	{
		vec3d vc = {x,y,z};
		return vc;
	}
	
	vec3d vec3d_screen_center(double z)
	{
		vec3d vc = {cfg::screen.size.w/2, cfg::screen.size.h/2, z};
		return vc;
	}
	
	size2d size2d_make(double w, double h)
	{
		size2d s = {w,h};
		return s;
	}
	
	rect rect_make(double x, double y, double w, double h)
	{
		rect rc = {x,y,w,h};
		return rc;
	}
	
	bool rect_is_equal_to_rect(rect *r1, rect *r2)
	{
		if ((int)r1->x == (int)r2->x &&
			(int)r1->y == (int)r2->y &&
			(int)r1->w == (int)r2->w &&
			(int)r1->h == (int)r2->h)
			return true;
		
		return false;
	}
}