//
//  components.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "entity_manager.h"
#include "hs_types.h"
#include "vec_2d.h"
#include "renderable_manager.h"
#include "particle_emitter.h"

namespace hs 
{
	namespace comp
	{
		struct mark_of_death : public component
		{
			static uid FAMILY_ID;
			
			mark_of_death()
			{
				family_id = FAMILY_ID;
			}
		};

	
		struct position : public component
		{
			static uid FAMILY_ID;
			
			vec2d origin;
			vec2d scale;
			double rot;
			
			position()
			{
				family_id = FAMILY_ID;
				
				origin = vec2d_make(0.0, 0.0);
				scale = vec2d_make(1.0, 1.0);
				rot = 0.0;
			}
		};
		
#pragma mark -
#pragma mark renderable
		
#define RENDERABLETYPE_BASE 0
#define RENDERABLETYPE_SPRITE 1
#define RENDERABLETYPE_ATLASSPRITE 2
#define RENDERABLETYPE_TEXT 3
#define RENDERABLETYPE_PARTICLE_EMITTER 4
		
		struct renderable : public component
		{
			static uid FAMILY_ID;
			unsigned int ren_type;
			
			resource_handle res_handle;
			vec2d anchor_point;
			double alpha;
			double z;
			
			renderable()
			{
				family_id = FAMILY_ID;
				
				anchor_point = vec2d_make(0.5, 0.5);
				z = 0.0;
				alpha = 1.0;
				res_handle = 0;
			}

			virtual ~renderable()
			{
				if (res_handle)
					g_renderable_manager.release_resource(&res_handle);
			}
			
			//WARNING: Don't forget to set the entity manager to dirty when you change the z value of an existing component! (Which shouldn't happen too often anyways)

		};
		
		struct sprite : public renderable
		{
			static uid FAMILY_ID;

			sprite()
			{
				family_id = FAMILY_ID;
				ren_type = RENDERABLETYPE_SPRITE;
			}
		};
		
		struct atlas_sprite : public renderable
		{
			static uid FAMILY_ID;
			rect src_rect;
			
			atlas_sprite()
			{
				family_id = FAMILY_ID;
				ren_type = RENDERABLETYPE_ATLASSPRITE;
			
				src_rect = rect_make(0.0, 0.0, 0.0, 0.0);
			}
		};
		
		struct text_label : public renderable
		{
			static uid FAMILY_ID;
			std::string text;
			
			text_label()
			{
				family_id = FAMILY_ID;
				ren_type = RENDERABLETYPE_TEXT;
			}
		};

		struct particle_emitter : public renderable
		{
			static uid FAMILY_ID;
			
			hs::particle_emitter *pe;
			
			particle_emitter()
			{
				family_id = FAMILY_ID;
				ren_type = RENDERABLETYPE_PARTICLE_EMITTER;
				pe = NULL;
			}
			~particle_emitter()
			{
				if (!pe->do_not_delete)
					delete pe;
			}
		};
	}
}