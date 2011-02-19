//
//  render_system.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "render_system.h"
#include "hellstorm.h"

namespace hs 
{
	bool comp_ents(entity *e1, entity *e2)
	{
//		comp::renderable *ren1 = e1->ent_mgr->get_component<comp::renderable>(e1);
//		comp::renderable *ren2 = e1->ent_mgr->get_component<comp::renderable>(e2);
//		
//		if (ren1->z == ren2->z)
//			return (e1->guid < e2->guid);
//		
//		return (ren1->z < ren2->z);
		
		comp::position *pos1 = entity::ent_mgr->get_component<comp::position>(e1);
		comp::position *pos2 = entity::ent_mgr->get_component<comp::position>(e2);
		
		if (pos1->origin.z == pos2->origin.z)
			return (e1->guid < e2->guid);
		
		return (pos1->origin.z < pos2->origin.z);
	}
	
	render_system::render_system(entity_manager *manager)
	{
		em = manager;
	}
	
	void render_system::render(void)
	{
		if (em->is_dirty)
		{
			gl_data.clear();
			ent_cache.clear();
			em->get_entities_possesing_components(ent_cache, comp::position::family_id, comp::renderable::family_id, ARGLIST_END);
			std::sort(ent_cache.begin(), ent_cache.end(), comp_ents);
		}
		
		entity *current_entity = NULL;
		
		comp::position *pos = NULL;
		comp::renderable *ren = NULL;

		quad *qd = NULL;
		atlas_quad *aq = NULL;
		bitmap_font *bf = NULL;
		particle_emitter *pe = NULL;
		
		std::vector<entity*>::const_iterator it = ent_cache.begin();
		while (it != ent_cache.end())
		{
			current_entity = *it;
			
			pos = em->get_component<comp::position>(current_entity);
			ren = em->get_component<comp::renderable>(current_entity);
		
			switch (ren->ren_type)
			{
				case RENDERABLETYPE_SPRITE:
					qd = g_renderable_manager.get_resource<quad>(&ren->res_handle);
					
					qd->position = pos->origin;
					
					qd->scale = pos->scale;
					qd->rotation = pos->rot;
					qd->alpha = ren->alpha;
					qd->anchor_point = ren->anchor_point;
					
					qd->render_content();
					break;
					
				case RENDERABLETYPE_ATLASSPRITE:
					aq = g_renderable_manager.get_resource<atlas_quad>(&ren->res_handle);
					
					aq->position = pos->origin;
					
					aq->scale = pos->scale;
					aq->rotation = pos->rot;
					aq->alpha = ren->alpha;
					aq->anchor_point = ren->anchor_point;
					
					aq->src_rect = ((comp::atlas_sprite *)ren)->src_rect;
					
					aq->render_content();
					break;
					
				case RENDERABLETYPE_TEXT:
					bf = g_renderable_manager.get_resource<bitmap_font>(&ren->res_handle);

					bf->position = pos->origin;
					
					bf->scale = pos->scale;
					bf->rotation = pos->rot;
					bf->alpha = ren->alpha;
					bf->anchor_point = ren->anchor_point;
	
					//the fuck?
					comp::text_label *tl;
					tl = (comp::text_label*)ren;
					bf->render_content(tl->text.c_str());
					break;
					
				case RENDERABLETYPE_PARTICLE_EMITTER:
					comp::particle_emitter *pem;
					pem = (comp::particle_emitter *)ren;
					pe = pem->pe;
					pe->position.z = pos->origin.z;
					pe->render_content();
					break;
				default:
					abort();
					break;
			}
			++it;
		}

	}
}