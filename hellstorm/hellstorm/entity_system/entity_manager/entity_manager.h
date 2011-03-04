//
//  entity_manager.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <vector>
#include "hs_types.h"
#include "hellstorm_config.h"

namespace hs 
{
	class entity_manager;
	struct component
	{
	public:
		component();
		virtual ~component();
	};

	class entity
	{
	public:
		template <typename Type> 
		Type *get()
		{
			return (Type*)get_by_id(Type::family_id);
		}
		
		template <typename Type>
		Type *add()
		{
			Type *c = new Type();
			return (Type*)add_component(c, Type::family_id);
		}
		
		entity_manager *ent_mgr;
		uid guid;
		uid manager_id;

	protected:
		component *get_by_id(uid family_id);
		component *add_component(component *comp, uid family_id);
				
	};
	
	class entity_manager
	{
		public:
		entity_manager();
		~entity_manager();
		
		entity *new_entity(void);
		void register_entity(entity *e);
		void remove_entity(uid entity_manager_id);
		void remove_all_entities(void);
		
		entity *get_entity(uid entity_manager_id);
		entity *get_entity_by_guid(uid entity_guid);
		
//		void get_entities_posessing_component(std::vector<entity*> &result, uid family_id);
//		void get_entities_possesing_components(std::vector<entity*> &result, ...);

		size_t get_entities_posessing_component(uid fam_id, entity **outarr, size_t outarr_size);
		size_t get_entities_possesing_components(uid query[], size_t query_size, entity **outarr, size_t outarr_size);

		
		template <typename T>
		T *add_component(entity *e)
		{
			T *comp = new T();
			if (T::family_id >= cfg::entity_system.components_per_entity ||
				T::family_id == 0)
			{	
				printf("family id of component out of bounds. component probably not registered!\n");
				dump_component(e, comp);
				abort();
			}
			
			if (components[e->manager_id][T::family_id])
				remove_component <T> (e);
			components[e->manager_id][T::family_id] = comp;
			return comp;
		}
		
		template <typename COMP_TYPE>
		COMP_TYPE *add_component(entity *e, COMP_TYPE *c)
		{
			
			if (COMP_TYPE::family_id >= cfg::entity_system.components_per_entity || 
				COMP_TYPE::family_id == 0)
			{	
				printf("family id of component out of bounds. component probably not registered!\n");
				dump_component(e, c);
				abort();
			}
			
			if (components[e->manager_id][COMP_TYPE::family_id])
				remove_component(e, (COMP_TYPE *)components[e->manager_id][COMP_TYPE::family_id]);
			
			
			components[e->manager_id][COMP_TYPE::family_id] = c;
			return c;
		}

		//fucking hack with explicit family_id because component baseclass doesn't have a static family_id
		//and if it had it would be shared (and the same) for every component subclass
		//you should almost never have to use this method!
		template <typename COMP_TYPE>
		COMP_TYPE *add_component(entity *e, COMP_TYPE *c, uid fam_id)
		{
			
			if (fam_id >= cfg::entity_system.components_per_entity || 
				fam_id == 0)
			{	
				printf("family id of component out of bounds. component probably not registered!\n");
				dump_component(e, c);
				abort();
			}
			
			if (components[e->manager_id][fam_id])
				remove_component(e, components[e->manager_id][fam_id], fam_id);
			
			
			components[e->manager_id][fam_id] = c;
			return c;
		}

		
		template <typename T> 
		T *get_component(entity *e)
		{
			return (T*)components[e->manager_id][T::family_id];
		}
		
		component *get_component(entity *e, uid family_id)
		{
			return components[e->manager_id][family_id];
		}
		
		template<typename T>
		void remove_component(entity *e)
		{
			component *c = components[e->manager_id][T::family_id];
			delete c;
			components[e->manager_id][T::family_id] = NULL;
		}

		template<typename COMP_TYPE>
		void remove_component(entity *e, COMP_TYPE *c)
		{
			components[e->manager_id][COMP_TYPE::family_id] = NULL;
			delete c;
		}

		template<typename COMP_TYPE>
		void remove_component(entity *e, COMP_TYPE *c, uid family_id)
		{
			components[e->manager_id][family_id] = NULL;
			delete c;
		}

		
		void remove_component (entity *e, uid family_id)
		{
			component *c = components[e->manager_id][family_id];
			components[e->manager_id][family_id] = NULL;
			delete c;
		}
		
		void remove_all_components(entity *e);
		
		void dump_entity(entity *e);
		void dump_entity_count(void);
		void dump_entities(void);
		void dump_component(entity *e, component *c);
		void dump_components(entity *e);

		protected:
		uid get_next_available_manager_id(void);
		uid get_next_available_guid(void);
		
		
		uid current_guid;
		static uid current_component_family_id;
		
		entity **entities;
		component ***components;
	};
}