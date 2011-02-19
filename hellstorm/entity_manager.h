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
		
		//uid family_id;
	};

	class entity
	{
	public:
		template <typename Type> 
		Type *get()
		{
			return (Type*)get_by_id(Type::family_id);
		}
		
		component *get_by_id (uid family_id);
				
		static entity_manager *ent_mgr;
		uid guid;
		uid manager_id;
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
		
		void get_entities_posessing_component(std::vector<entity*> &result, uid family_id);
		void get_entities_possesing_components(std::vector<entity*> &result, ...);

		template <typename T>
		T *add_component(entity *e)
		{
			is_dirty = true;
			
			if (T::family_id >= cfg::entity_system.components_per_entity ||
				T::family_id == 0)
				abort();
			
			T *comp = new T();
//			comp->family_id = T::FAMILY_ID;
			
			if (components[e->manager_id][T::family_id])
				remove_component <T> (e);
			components[e->manager_id][T::family_id] = comp;
			return comp;
		}
		
		template <typename COMP_TYPE>
		COMP_TYPE *add_component(entity *e, COMP_TYPE *c)
		{
			is_dirty = true;
		//	c->family_id = T::FAMILY_ID;
			
			if (COMP_TYPE::family_id >= cfg::entity_system.components_per_entity || 
				COMP_TYPE::family_id == 0)
				abort();
			
			if (components[e->manager_id][COMP_TYPE::family_id])
				remove_component(e, components[e->manager_id][COMP_TYPE::family_id]);
			
			
			components[e->manager_id][COMP_TYPE::family_id] = c;
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
			is_dirty = true;
		}

		template<typename COMP_TYPE>
		void remove_component(entity *e, COMP_TYPE *c)
		{
			components[e->manager_id][COMP_TYPE::family_id] = NULL;
			delete c;
			is_dirty = true;
		}

		
		void remove_component (entity *e, uid family_id)
		{
			component *c = components[e->manager_id][family_id];
			components[e->manager_id][family_id] = NULL;
			delete c;
			is_dirty = true;
		}
		
		void remove_all_components(entity *e);
		
		void dump_entity(entity *e);
		void dump_entity_count(void);
		void dump_entities(void);
		void dump_component(entity *e, component *c);
		void dump_components(entity *e);


		bool is_dirty;

		protected:
		uid get_next_available_manager_id(void);
		uid get_next_available_guid(void);
		
		uid current_guid;
		
		entity **entities;
		component ***components;
	};
}