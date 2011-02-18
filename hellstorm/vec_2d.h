//
//  vec_2d.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

namespace hs
{
	struct vec2d
	{
		double x;
		double y;
	};
	
	vec2d vec2d_make(double x, double y);
	vec2d vec2d_normalize(vec2d vec);
	
	struct vec3d
	{
		double x;
		double y;
		double z;
	};
	
	vec3d vec3d_make(double x, double y, double z);
	
	
	struct size2d
	{
		double w;
		double h;
	};
	
	size2d size2d_make(double w, double h);
	
	struct rect
	{
		double x;
		double y;
		double w;
		double h;
	};
	
	rect rect_make(double x, double y, double w, double h);
	bool rect_is_equal_to_rect(rect *r1, rect *r2);
}