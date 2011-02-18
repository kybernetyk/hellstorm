//
//  vec_2d.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "vec_2d.h"
#include <cmath>

namespace hs
{
	vec2d vec2d_make(double x, double y)
	{
		vec2d vc = {x,y};
		return vc;
	}
	
	vec2d vec2d_normalize(vec2d vec)
	{
		float len = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
		vec.x = vec.x/len;
		vec.y = vec.y/len;
		
		return vec;
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