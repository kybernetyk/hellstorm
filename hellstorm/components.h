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
#include "actions.h"

namespace hs 
{
	namespace comp
	{
		
#pragma mark -
#pragma mark mark of death
		struct mark_of_death : public component
		{
			static uid family_id;
		};

#pragma mark -
#pragma mark position
		struct position : public component
		{
			static uid family_id;
			
			vec3d origin;
			vec2d scale;
			double rot;
			
			position()
			{
				origin = vec3d_make(0.0, 0.0, 0.0);
				scale = vec2d_make(1.0, 1.0);
				rot = 0.0;
			}
		};
		
#pragma mark -
#pragma mark renderable
		enum e_renderabletype
		{
			RENDERABLETYPE_BASE = 0,
			RENDERABLETYPE_SPRITE,
			RENDERABLETYPE_ATLASSPRITE,
			RENDERABLETYPE_TEXT,
			RENDERABLETYPE_PARTICLE_EMITTER
		};
		
		struct renderable : public component
		{
			static uid family_id;
			e_renderabletype ren_type;
			
			resource_handle res_handle;
			vec2d anchor_point;
			double alpha;
			
			renderable()
			{
				anchor_point = vec2d_make(0.5, 0.5);
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
			static uid family_id;

			sprite()
			{
				ren_type = RENDERABLETYPE_SPRITE;
			}
		};
		
		struct atlas_sprite : public renderable
		{
			static uid family_id;
			rect src_rect;
			
			atlas_sprite()
			{
				ren_type = RENDERABLETYPE_ATLASSPRITE;
			
				src_rect = rect_make(0.0, 0.0, 0.0, 0.0);
			}
		};
		
		struct text_label : public renderable
		{
			static uid family_id;
			std::string text;
			
			text_label()
			{
				ren_type = RENDERABLETYPE_TEXT;
			}
		};

		struct particle_emitter : public renderable
		{
			static uid family_id;
			
			hs::particle_emitter *pe;
			
			particle_emitter()
			{
				ren_type = RENDERABLETYPE_PARTICLE_EMITTER;
				pe = NULL;
			}
			~particle_emitter()
			{
				if (!pe->do_not_delete)
					delete pe;
			}
		};
		
#pragma mark -
#pragma mark action container
		
#define NUM_OF_ACTIONS_PER_CONTAINER 256
	
		struct action_container : public component
		{
			static uid family_id;
			action *actions[NUM_OF_ACTIONS_PER_CONTAINER];
			
			action_container();
			~action_container();
		};
	}
}