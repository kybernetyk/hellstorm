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
	
	bool rect_intersect_rect(rect *r1, rect *r2)
	{
		return  !(r1->x > r2->x + r2->w ||
				  r1->x + r1->w < r2->x ||
				  r1->y + r1->h > r2->y ||
				  r1->y < r2->y + r2->h);
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
	
	bool entities_collide(entity *e1, entity *e2)
	{
		if (!e1 || !e2)
			return false;
		
		comp::position *pos1 = e1->ent_mgr->get_component<comp::position>(e1);
		if (!pos1)
			return false;

		comp::position *pos2 = e2->ent_mgr->get_component<comp::position>(e2);
		if (!pos2)
			return false;

		comp::renderable *ren1 = e1->ent_mgr->get_component<comp::renderable>(e1);
		if (!ren1)
			return false;

		comp::renderable *ren2 = e2->ent_mgr->get_component<comp::renderable>(e2);
		if (!ren2)
			return false;

		
		rect r1;
		r1.x = pos1->origin.x;
		r1.y = pos1->origin.y;
		
		rect r2;
		r2.x = pos2->origin.x;
		r2.y = pos2->origin.y;

		quad *q = 0;
		atlas_quad *aq = 0;

		switch (ren1->ren_type) 
		{
			case comp::RENDERABLETYPE_SPRITE:
				q = g_renderable_manager.get_resource<quad>(&ren1->res_handle);
				r1.w = q->size.w * fabs(pos1->scale.x);
				r1.h = q->size.h * fabs(pos1->scale.y);
				r1.x -= r1.w * (1.0 - ren1->anchor_point.x);
				r1.y -= r1.h * (1.0 - ren1->anchor_point.y);
				break;
			case comp::RENDERABLETYPE_ATLASSPRITE:
				aq = g_renderable_manager.get_resource<atlas_quad>(&ren1->res_handle);
				r1.w = aq->src_rect.w;
				r1.h = aq->src_rect.h;
				r1.x -= r1.w * (1.0 - ren1->anchor_point.x);
				r1.y -= r1.h * (1.0 - ren1->anchor_point.y);
				break;
			default:
				printf("not implemented!\n");
				abort();
				return false;
				break;
		}

		switch (ren2->ren_type) 
		{
			case comp::RENDERABLETYPE_SPRITE:
				q = g_renderable_manager.get_resource<quad>(&ren2->res_handle);
				r2.w = q->size.w * fabs(pos2->scale.x);
				r2.h = q->size.h * fabs(pos2->scale.y);
				r2.x -= r2.w * (1.0 - ren2->anchor_point.x);
				r2.y -= r2.h * (1.0 - ren2->anchor_point.y);
				break;
			case comp::RENDERABLETYPE_ATLASSPRITE:
				aq = g_renderable_manager.get_resource<atlas_quad>(&ren2->res_handle);
				r2.w = aq->src_rect.w;
				r2.h = aq->src_rect.h;
				r2.x -= r2.w * (1.0 - ren2->anchor_point.x);
				r2.y -= r2.h * (1.0 - ren2->anchor_point.y);
				break;
			default:
				printf("not implemented!\n");
				abort();
				return false;
				break;
		}

		return rect_intersect_rect(&r1, &r2);
	}

	
	bool entity_intersect_rect(entity *e1, rect *r2)
	{
		if (!e1)
			return false;
		
		comp::position *pos1 = e1->ent_mgr->get_component<comp::position>(e1);
		if (!pos1)
			return false;
		
		comp::renderable *ren1 = e1->ent_mgr->get_component<comp::renderable>(e1);
		if (!ren1)
			return false;
		
		
		rect r1;
		r1.x = pos1->origin.x;
		r1.y = pos1->origin.y;
		
		
		quad *q = 0;
		atlas_quad *aq = 0;
		
		switch (ren1->ren_type) 
		{
			case comp::RENDERABLETYPE_SPRITE:
				q = g_renderable_manager.get_resource<quad>(&ren1->res_handle);
				r1.w = q->size.w * fabs(pos1->scale.x);
				r1.h = q->size.h * fabs(pos1->scale.y);
				r1.x -= r1.w * (1.0 - ren1->anchor_point.x);
				r1.y -= r1.h * (1.0 - ren1->anchor_point.y);
				break;
			case comp::RENDERABLETYPE_ATLASSPRITE:
				aq = g_renderable_manager.get_resource<atlas_quad>(&ren1->res_handle);
				r1.w = aq->src_rect.w;
				r1.h = aq->src_rect.h;
				r1.x -= r1.w * (1.0 - ren1->anchor_point.x);
				r1.y -= r1.h * (1.0 - ren1->anchor_point.y);
				break;
			default:
				printf("not implemented!\n");
				abort();
				return false;
				break;
		}
		return rect_intersect_rect(&r1, r2);
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