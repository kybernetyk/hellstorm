//
//  entity_manager.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "entity_manager.h"
#include "hellstorm.h"

namespace hs 
{
#pragma mark -
#pragma mark component
	component::component()
	{
	}
	
	component::~component()
	{
	}
#pragma mark -
#pragma mark entity
//	entity_manager *entity::ent_mgr = NULL;
	component *entity::get_by_id(uid family_id)
	{
		return ent_mgr->get_component(this, family_id);
	}
	
	component *entity::add_component(component *comp, uid family_id)
	{
		return ent_mgr->add_component(this, comp, family_id);
	}
	
#pragma mark -
#pragma mark entity manager
	entity_manager::entity_manager()
	{
		printf("EntityManager startup:\n{\n");
		printf("\t[*] Entity Slots: %i\n", cfg::entity_system.entity_pool_size);
		printf("\t[*] Component Slots per Entity: %i\n", cfg::entity_system.components_per_entity);
		printf("\t[!] don't exceed these limits without adjusting the #defines!\n");
		printf("\t[!] no checks/asserts will be made for this! you will crash and burn!\n}\n");
		
		if (!comp::components_registered)
			comp::register_components();
		
		current_guid = 1;
		
		entities = new entity*[cfg::entity_system.entity_pool_size];
		if (!entities)
			abort();
		
		components = new component**[cfg::entity_system.entity_pool_size];
		if (!components)
			abort();
		
		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
			components[i] = new component*[cfg::entity_system.components_per_entity];
		
		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
		{
			entities[i] = NULL;
			for (int j = 0; j < cfg::entity_system.components_per_entity; j++)
			{
				components[i][j] = NULL;
			}
		}
		
	//	entity::ent_mgr = this;
	}
	
	entity_manager::~entity_manager()
	{
		remove_all_entities();
		
		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
			delete [] components[i];
		delete [] components;
		
		delete entities;
	}
	
	uid entity_manager::get_next_available_manager_id(void)
	{
		for (uid i = 1; i < cfg::entity_system.entity_pool_size; i++)
			if (entities[i] == NULL)
				return i;
		
		printf("no entity slots left!\n");
		abort();
		return -1;
	}
	
	uid entity_manager::get_next_available_guid(void)
	{
		return current_guid++;
	}
	
	void entity_manager::register_entity(entity *e)
	{
		e->ent_mgr = this;
		e->manager_id = get_next_available_manager_id();
		e->guid = get_next_available_guid();
		entities[e->manager_id] = e;
	}
	
	entity *entity_manager::new_entity(void)
	{
		entity *e = new entity();
		register_entity(e);
		return e; 
	}
	
	entity *entity_manager::get_entity(uid entity_manager_id)
	{
		return entities[entity_manager_id];
	}

#pragma mark -
#pragma mark remove
	void entity_manager::remove_entity(uid entity_manager_id)
	{
		entity *e = entities[entity_manager_id];
		remove_all_components(e);
		entities[entity_manager_id] = NULL;
		delete e;
	}
	
	void entity_manager::remove_all_entities(void)
	{
		entity *e = NULL;
		
		for (uid i = 0; i < cfg::entity_system.entity_pool_size; i++)
		{
			e = entities[i];
			if (e)
				remove_entity(e->manager_id);
		}
	}
	
	void entity_manager::remove_all_components(entity *e)
	{
		component *c = NULL;
		for (uid i = 0; i < cfg::entity_system.components_per_entity; i++)
		{
			c = components[e->manager_id][i];
			delete c;
			components[e->manager_id][i] = NULL;
		}
	}
	
#pragma mark -
#pragma mark query
	
	size_t entity_manager::get_entities_posessing_component(uid fam_id, entity **outarr, size_t outarr_size)
	{
		size_t out_counter = 0;
		
		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
		{
			if (components[i][fam_id])
				outarr[out_counter++] = entities[i];
			
			if (out_counter >= outarr_size)
				break;
		}
		
		return out_counter;

	}

	size_t entity_manager::get_entities_possesing_components(uid query[], size_t query_size, entity **outarr, size_t outarr_size)
	{
		size_t out_counter = 0;
		
		bool add_ent = true;	
		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
		{
			add_ent = true;
			for (int qi = 0; qi < query_size; qi++)
			{
				if (!components[i][query[qi]])
				{	
					add_ent = false;
					break;
				}
			}
			
			if (add_ent)
			{	
				outarr[out_counter++] = entities[i];
				if (out_counter >= outarr_size)
					break;
			}
		}
		
		return out_counter;
	}

	
	
//	
//#define NUM_FAMILY_IDS 32
//	void entity_manager::get_entities_possesing_components(std::vector<entity*> &result, ...)
//	{
//		va_list listPointer;
//		va_start( listPointer, result );
//		
//		uid family_ids[NUM_FAMILY_IDS+1];
//		uid arg;
//		int count = 0;
//		while (1)
//		{
//			arg = va_arg( listPointer, int );
//			if (arg == ARGLIST_END || count >= NUM_FAMILY_IDS)
//				break;
//			family_ids[count] = arg;
//			++count;
//		}
//		va_end(listPointer);
//		
//		entity *current_entity = NULL;
//		bool is_entity_valid = true;
//		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
//		{
//			current_entity = entities[i];
//			is_entity_valid = true;
//			
//			if (current_entity)
//			{
//				for (int j = 0; j < count; j++)
//				{
//					if (!components[current_entity->manager_id][family_ids[j]])
//					{
//						is_entity_valid = false;
//						break;
//					}
//				}
//				
//				if (is_entity_valid)
//				{
//					result.push_back (current_entity);
//				}
//			}
//		}
//	}
//	
//	void entity_manager::get_entities_posessing_component(std::vector<entity*> &result, uid family_id)
//	{
//		entity *current_entity = NULL;
//		bool is_entity_valid = true;
//		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
//		{
//			current_entity = entities[i];
//			is_entity_valid = true;
//			
//			if (current_entity)
//			{
//				if (components[current_entity->manager_id][family_id])
//				{
//					result.push_back (current_entity);
//				}
//			}
//		}
//	}
//
#pragma mark -
#pragma mark dump
	void entity_manager::dump_entity_count(void)
	{
		int count = 0;
		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
		{
			if (entities[i])
				count ++;
		}
		printf("** EntityManager entity count: %i\n", count);
		
		if ((cfg::entity_system.entity_pool_size-count) < 20)
		{
			printf("\t[!] MAX_ENTITES is %i - you are reaching the limit!\n", cfg::entity_system.entity_pool_size);
		}
	}

	void entity_manager::dump_entity(entity *e)
	{
		printf("\n\n************** DUMP *************\n");
		printf("entity ID: %i, checksum: %i, address: %p (%s)\n{\n", e->manager_id,e->guid, e, typeid(e).name());
		dump_components(e);	
		printf("}\n************** DUMP END *************\n");

	}

	void entity_manager::dump_entities(void)
	{
		entity *e = NULL;
		printf("\n\n************** DUMP *************\n");
		for (int i = 0; i < cfg::entity_system.entity_pool_size; i++)
		{
			e = entities[i];
			if (e)
			{		
				printf("entity ID: %i, checksum: %i, address: %p (%s)\n{\n", e->manager_id,e->guid, e, typeid(e).name());			
				dump_components(e);
				printf("}\n");
			}
		}
		printf("************** DUMP END *************\n");	

	}
	
	void entity_manager::dump_component(entity *e, component *c)
	{
#ifdef __RUNTIME_INFORMATION__
		printf("\t+[%i] %p (%s)\n",c->_id,c,c->toString().c_str() );
#else
		printf("\t+ %p\n",c);
#endif
	}
	
	void entity_manager::dump_components(entity *e)
	{
		component *c = NULL;
		for (int i = 0; i < cfg::entity_system.components_per_entity; i++)
		{
			c = components[e->manager_id][i];
			if (c)
			{
#ifdef __RUNTIME_INFORMATION__
				printf("\t+[%i] %p (%s)\n",c->_id,c,c->toString().c_str() );
#else
				printf("\t+ %p\n",c);
#endif
				
			}
		}

	}
	

}