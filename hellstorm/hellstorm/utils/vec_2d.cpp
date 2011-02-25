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

	vec3d vec3d_make(vec2d v, double z)
	{
		vec3d vc = {v.x,v.y,z};
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
	
	bool point_in_rect(vec2d point, rect r1)
	{
		if ( ( (point.x > r1.x) && (point.x < (r1.x + r1.w)) ) &&
			 ( (point.y > r1.y) && (point.y < (r1.x + r1.h)) ))
			return true;
		return false;
	}
	 
	
	color3f color3f_make(double r, double g, double b)
	{
		color3f col = {r, g, b};
		return  col;
	}

	bool point_in_entity(vec2d point, entity *e)
	{
		if (!e)
			return false;

		comp::position *pos = e->ent_mgr->get_component<comp::position>(e);
		if (!pos)
			return false;
		
		comp::renderable *ren = e->ent_mgr->get_component<comp::renderable>(e);
		if (!ren)
			return false;
		
		double x = pos->origin.x;
		double y = pos->origin.y;
		float w;
		float h;
		

		quad *q = 0;
		atlas_quad *aq = 0;
		switch (ren->ren_type) 
		{
			case comp::RENDERABLETYPE_SPRITE:
				q = g_renderable_manager.get_resource<quad>(&ren->res_handle);
				w = q->size.w * fabs(pos->scale.x);
				h = q->size.h * fabs(pos->scale.y);
				x -= w * (1.0 - ren->anchor_point.x);
				y -= h * (1.0 - ren->anchor_point.y);
				break;
			case comp::RENDERABLETYPE_ATLASSPRITE:
				aq = g_renderable_manager.get_resource<atlas_quad>(&ren->res_handle);
				w = aq->src_rect.w;
				h = aq->src_rect.h;
				x -= w * (1.0 - ren->anchor_point.x);
				y -= h * (1.0 - ren->anchor_point.y);
				break;
			default:
				printf("not implemented!\n");
				abort();
				return false;
				break;
		}
		
		
//		TexturedQuad *tq = 0;
//		switch (ren->_renderable_type) 
//		{
//			case RENDERABLETYPE_SPRITE:
//				tq = (TexturedQuad*)g_RenderableManager.getResource <TexturedQuad> (&ren->res_handle);
//				w = tq->w * fabs(pos->scale_x);
//				h = tq->h * fabs(pos->scale_y);
//				x -= w * (1.0 - ren->anchorPoint.x);
//				y -= h * (1.0 - ren->anchorPoint.y);
//				break;
//			default:
//				NSLog(@"not implemented yet!")
//				return false;
//				break;
//		};
		//printf("is %f,%f in (%f,%f <-> %f,%f)?\n",vec.x,vec.y, x,y,x+w,x+h);
		if (point.x >= x && point.x <= x + w &&
			point.y >= y && point.y <= y + h)
			return true;
		
		return false;
	}


}