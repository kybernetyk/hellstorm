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
	
	const vec2d anchor_bottom_left = {0.0,0.0};
	const vec2d anchor_bottom_right = {1.0,0.0};
	const vec2d anchor_center = {0.5,0.5};
	const vec2d anchor_top_left = {0.0,1.0};
	const vec2d anchor_top_right = {1.0,1.0};
	
	const vec2d vec2d_zero = {0.0,0.0};
		
	vec2d vec2d_make(double x, double y);
	vec2d vec2d_screen_center(void);
	vec2d vec2d_normalize(vec2d vec);
	
	struct vec3d
	{
		double x;
		double y;
		double z;
	};
	
	vec3d vec3d_make(double x, double y, double z);
	vec3d vec3d_screen_center(double z = 0.0);
	
	const vec3d vec3d_zero = {0.0,0.0,0.0};

	
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
	bool point_in_rect(vec2d point, rect r1);

	class entity;
	bool point_in_entity(vec2d point, entity *e);
	
	struct color3f
	{
		double r, g, b;
	};

	color3f color3f_make(double r, double g, double b);
	const color3f color3f_white = {1.0, 1.0, 1.0};
	const color3f color3f_black = {0.0, 0.0, 0.0};
	const color3f color3f_red = {1.0, 0.0, 0.0};
	const color3f color3f_green = {0.0, 1.0, 0.0};
	const color3f color3f_blue = {0.0, 0.0, 1.0};
	
}