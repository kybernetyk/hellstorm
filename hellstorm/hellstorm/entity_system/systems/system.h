//
//  system.h
//  hellstorm
//
//  Created by jrk on 8/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <stddef.h>

namespace hs 
{
	class entity;
	class entity_manager;
	
	class system
	{
	public:
		system();
		virtual ~system();
		
	//	virtual void init() = 0;
	//	virtual void update(double dt) = 0;
	//	virtual void shutdown() = 0;
		
		void set_manager(entity_manager *manager);
		
	protected:
		void sys_init();
		void sys_destroy();
		
		entity_manager *em;
		int skiptimer;
		
		entity **ent_cache;
		size_t cache_size;
	};
	
//	template <typename T> T *create_system(entity_manager *manager)
//	{
//		T *ret = new T();
//		ret->set_manager(manager);
//		ret->init();
//		return ret;
//	}
//	
//	template <typename T> void destroy_system(T *sys)
//	{
//		sys->shutdown();
//		delete sys;
//	}
}

