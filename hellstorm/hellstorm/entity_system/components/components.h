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
		uid get_next_component_family_id(void);
		
		template <typename T>
		void register_component_class(void)
		{
			if (T::family_id != 0) //already registered
				return;
			
			T::family_id = get_next_component_family_id();
			
			if (T::family_id >= cfg::entity_system.components_per_entity)
			{
				printf("The family id %i exceeds 'entity_system.components_per_entity'. Please update your config file!\n",
					   T::family_id);
				abort();
			}
			
		}

		void register_components(void);
		extern bool components_registered;
		
#pragma mark -
#pragma mark mark of death
		struct mark_of_death : public component
		{
			static uid family_id;
			
			COMP_DEBUGINFO("[%i] mark_of_death", family_id);
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
			
			COMP_DEBUGINFO("[%i] Position: (origin: %.2f,%.2f,%.2f), (rot: %.2f)", 
						   family_id,
						   origin.x,
						   origin.y,
						   origin.z,
						   rot);
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
			color3f color;
			double alpha;

			renderable()
			{
				anchor_point = vec2d_make(0.5, 0.5);
				alpha = 1.0;
				color.r = color.g = color.b = 1.0;
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
			sprite()
			{
				ren_type = RENDERABLETYPE_SPRITE;
			}
			
			COMP_DEBUGINFO("[%i] renderable::sprite", family_id);
		};
		
		struct atlas_sprite : public renderable
		{
			rect src_rect;
			
			atlas_sprite()
			{
				ren_type = RENDERABLETYPE_ATLASSPRITE;
			
				src_rect = rect_make(0.0, 0.0, 0.0, 0.0);
			}

			COMP_DEBUGINFO("[%i] renderable::atlas_sprite", family_id);
		};
		
		struct text_label : public renderable
		{
			std::string text;
			
			text_label()
			{
				ren_type = RENDERABLETYPE_TEXT;
			}

			COMP_DEBUGINFO("[%i] renderable::text_label", family_id);
		};

		struct particle_emitter : public renderable
		{
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

			COMP_DEBUGINFO("[%i] renderable::particle_emitter", family_id);
		};
		
#pragma mark -
#pragma mark action container
		
#define NUM_OF_ACTIONS_PER_CONTAINER 32
	
		struct action_container : public component
		{
			static uid family_id;
			action *actions[NUM_OF_ACTIONS_PER_CONTAINER];
			
			action_container();
			~action_container();

			COMP_DEBUGINFO("[%i] action_container", family_id);
		};

#pragma mark -
#pragma mark animation
		
		enum e_animationtype
		{
			SEQ_ANIMATION = 0
		};
		
		enum e_animationstate
		{
			ANIM_STATE_PAUSE = 0,
			ANIM_STATE_PLAY
		};
		
		struct seq_animation : public component
		{
			static uid family_id;
			e_animationtype animation_type;
			
			size2d frame_size;
			
			double current_frame;
			double frames_per_second;
			double speed_scale;
			
			e_animationstate state;
			double start_frame;
			double end_frame;
			
			bool loop;
			bool destroy_on_finish;
			
			seq_animation *next_animation;
			action *on_complete_action;
			
			double _cached_frame;
			
			seq_animation()
			{
				current_frame = 0.0;
				speed_scale = 1.0;
				frames_per_second = 0.0;
				loop = false;
				destroy_on_finish = true;
				frame_size = size2d_make(0.0, 0.0);
				state = ANIM_STATE_PAUSE;
				start_frame = 0.0;
				_cached_frame = -8.0;
				end_frame = 0.0;
				next_animation = NULL;
				on_complete_action = NULL;
			}
			
			COMP_DEBUGINFO("[%i] seq_animation: (current frame: %.2f, fps: %.2f, start: %.2f, end: %.2f, loop: %i)", 
						   family_id,
						   current_frame,
						   frames_per_second,
						   start_frame,
						   end_frame,
						   loop);
		};
		
#pragma mark -
#pragma mark name
		struct name : public component
		{
			static uid family_id;
			
			std::string text;
			
			name()
			{
				text = "no name yet!";
			}
			
			COMP_DEBUGINFO("[%i] name: %s", family_id, text.c_str())
		};
	
	}
}