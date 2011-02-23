//
//  animation_system.cpp
//  hellstorm
//
//  Created by jrk on 20/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "animation_system.h"
#include "hellstorm.h"

namespace hs 
{
	animation_system::animation_system(entity_manager *manager, action_system *asystem)
	{
		em = manager;
		as = asystem;
		
		ent_cache = new entity*[cfg::entity_system.entity_pool_size];
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = 0;
	}
	
	animation_system::~animation_system()
	{
		delete [] ent_cache;	
	}
	
	void animation_system::setup_next_animation_or_stop(entity *e, comp::seq_animation *current_animation)
	{
		if (current_animation->on_complete_action)
		{
			as->add_action_to_entity(e, current_animation->on_complete_action);
		}
		
		if (current_animation->next_animation)
		{
			em->remove_component<comp::seq_animation>(e);
			em->add_component(e, current_animation->next_animation);
		}
		else
		{
			em->remove_component<comp::seq_animation>(e);
		}
	}
	
	void animation_system::update(double dt)
	{
//		entities.clear();
//		em->get_entities_possesing_components(entities, comp::seq_animation::family_id, comp::atlas_sprite::family_id, ARGLIST_END);

		uid qry[] =
		{
			comp::seq_animation::family_id, 
			comp::atlas_sprite::family_id
		};
		
//		cache_size = em->get_entities_posessing_components(qry, ent_cache, cfg::entity_system.entity_pool_size);
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = em->get_entities_possesing_components(qry, 2, ent_cache, cfg::entity_system.entity_pool_size);

		
		entity *current_entity;
		comp::seq_animation *current_animation;
		comp::atlas_sprite *current_sprite;
		atlas_quad *aq;
		
//		std::vector<entity *>::const_iterator it = entities.begin();
//		while (it != entities.end()) 
//		{
//			current_entity = *it;
//			++it;
//			
		for (uid i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];
			
			current_animation = em->get_component<comp::seq_animation>(current_entity);
			current_sprite = em->get_component<comp::atlas_sprite>(current_entity);

		
			if (current_animation->state == comp::ANIM_STATE_PLAY)
			{
				//forward advance
				if (current_animation->start_frame <= current_animation->end_frame)
				{
					current_animation->current_frame += (dt * current_animation->frames_per_second * current_animation->speed_scale);
				}
				else //backwards advance
				{
					current_animation->current_frame -= (dt * current_animation->frames_per_second * current_animation->speed_scale);
				}

				//forward update
				if (current_animation->start_frame <= current_animation->end_frame)
				{
					//animation finished?
					if ( current_animation->current_frame >= current_animation->end_frame+1.0 )
					{
						//on loop rewind
						if (current_animation->loop)
						{
							current_animation->current_frame = current_animation->start_frame;
						}
						else	//destroy animation + start next
						{
							//shall we kill this anim and start next?
							if (current_animation->destroy_on_finish)
							{
								setup_next_animation_or_stop(current_entity, current_animation);
								continue;
							}
							else //ok, we don't kill it. just rewind and pause
							{
								current_animation->current_frame = current_animation->end_frame;
								current_animation->state = comp::ANIM_STATE_PAUSE;
							}
						}
					}
				}
				else //backwars update
				{
					//anim finished?
					if ( current_animation->current_frame <= current_animation->end_frame )
					{
						if (current_animation->loop)
						{
							current_animation->current_frame = current_animation->start_frame;
						}
						else
						{
							if (current_animation->destroy_on_finish)
							{
								setup_next_animation_or_stop(current_entity, current_animation);
								continue;
							}
							else
							{
								current_animation->current_frame = current_animation->end_frame;
								current_animation->state = comp::ANIM_STATE_PAUSE;
							}
						}
					}
				}
			}
			
			//update the sprite related data only once each frame
			if ( fabs(current_animation->current_frame - current_animation->_cached_frame) >= 1.0 )
			{
				aq = g_renderable_manager.get_resource<atlas_quad>(&current_sprite->res_handle);
				
				//size2d framesize = current_animation->frame_size;
				int sx = aq->tex_size.w / current_animation->frame_size.w;
				//	int sy = current_sprite->atlas_quad->tex_h / fs.h;
				
				int fn = (int)(current_animation->current_frame);
				
				int fx = fn % sx;
				int fy = fn / sx; // (/ sy is for quadratische texutren! ansonsten muessen wir durch x beficken, damit wir indexiert tun koennen)
				
				current_sprite->src_rect.x = fx * current_animation->frame_size.w;
				current_sprite->src_rect.y = fy * current_animation->frame_size.h;
				current_sprite->src_rect.w = current_animation->frame_size.w;
				current_sprite->src_rect.h = current_animation->frame_size.h;
				
				current_animation->_cached_frame = current_animation->current_frame;
			}


		}
		
	}
}