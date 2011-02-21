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
	//for std::sort
	bool comp_ents(entity *e1, entity *e2)
	{
		comp::position *pos1 = entity::ent_mgr->get_component<comp::position>(e1);
		comp::position *pos2 = entity::ent_mgr->get_component<comp::position>(e2);
		
		if (pos1->origin.z == pos2->origin.z)
			return (e1->guid < e2->guid);
		
		return (pos1->origin.z < pos2->origin.z);
	}
	
	//for qsort
	static int z_comp(const void *ep1, const void *ep2)
	{
		entity *e1 = *(entity**)ep1;
		entity *e2 = *(entity**)ep2;
		
		comp::position *p1 = entity::ent_mgr->get_component<comp::position>(e1);
		comp::position *p2 = entity::ent_mgr->get_component<comp::position>(e2);
		
		if (p1->origin.z < p2->origin.z)
			return -1;
		if (p1->origin.z > p2->origin.z)
			return 1;
		
		if (e1->guid < e2->guid)
			return -1;
		if (e1->guid > e2->guid)
			return 1;
		
		return 0;
	}

	
	render_system::render_system(entity_manager *manager)
	{
		em = manager;

		ent_cache = new entity*[cfg::entity_system.entity_pool_size];
		memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
		cache_size = 0;

	}

	render_system::~render_system()
	{
		delete [] ent_cache;
		ent_cache = 0;
	}
	
	void render_system::render(void)
	{
		if (em->is_dirty)
		{
			uid qry[] =
			{
				comp::position::family_id,
				comp::renderable::family_id
			};
			memset(ent_cache, 0x00, sizeof(entity *)*cfg::entity_system.entity_pool_size);
			cache_size = em->get_entities_possesing_components(qry, 2, ent_cache, cfg::entity_system.entity_pool_size);

			for (int i = 0; i < cache_size; i++)
				printf("%p = z: %f\n", 
					   ent_cache[i], 
					   ent_cache[i]->get<comp::position>()->origin.z);

			printf("\n\n");
			
			qsort(ent_cache, cache_size, sizeof(entity *),z_comp);
			
			for (int i = 0; i < cache_size; i++)
				printf("%p = z: %f\n", 
					   ent_cache[i], 
					   ent_cache[i]->get<comp::position>()->origin.z);
		}
		
		entity *current_entity = NULL;
		
		comp::position *pos = NULL;
		comp::renderable *ren = NULL;

		quad *qd = NULL;
		atlas_quad *aq = NULL;
		bitmap_font *bf = NULL;
		particle_emitter *pe = NULL;
		
//		std::vector<entity*>::const_iterator it = ent_cache.begin();
//		while (it != ent_cache.end())
//		{
//			current_entity = *it;

		for (uid i = 0; i < cache_size; i++)
		{
			current_entity = ent_cache[i];

			pos = em->get_component<comp::position>(current_entity);
			ren = em->get_component<comp::renderable>(current_entity);
		
			switch (ren->ren_type)
			{
				case comp::RENDERABLETYPE_SPRITE:
					qd = g_renderable_manager.get_resource<quad>(&ren->res_handle);
					
					qd->position = pos->origin;
					
					qd->scale = pos->scale;
					qd->rotation = pos->rot;
					qd->alpha = ren->alpha;
					qd->anchor_point = ren->anchor_point;
					
					qd->render_content();
					break;
					
				case comp::RENDERABLETYPE_ATLASSPRITE:
					aq = g_renderable_manager.get_resource<atlas_quad>(&ren->res_handle);
					
					aq->position = pos->origin;
					
					aq->scale = pos->scale;
					aq->rotation = pos->rot;
					aq->alpha = ren->alpha;
					aq->anchor_point = ren->anchor_point;
					
					aq->src_rect = ((comp::atlas_sprite *)ren)->src_rect;
					
					aq->render_content();
					break;
					
				case comp::RENDERABLETYPE_TEXT:
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
					
				case comp::RENDERABLETYPE_PARTICLE_EMITTER:
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
//			++it;
		}

	}
}