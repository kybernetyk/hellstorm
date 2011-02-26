//
//  renderable_manager.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <tr1/unordered_map>
#include <string>
#include "renderable.h"
#include "hs_types.h"
namespace hs 
{
	
#define MAX_RESOURCES 512
	class particle_emitter;
	
	class renderable_manager
	{
	public:
		renderable_manager();
		
		template <typename T> resource_handle acquire_resource(std::string filename)
		{
//			if (reference_counts[filename] > 0)
//			{
//				reference_counts[filename] ++;
//				resource_handle ret =  handles_by_filename[filename];
//				if (ret == 0)
//				{
//					printf("handle may not be 0!\n");
//					abort();
//					return 0;
//				}
//				return ret;
//			}
			
			resource_handle current_handle = get_free_handle();
			
			T *res = new T(filename);
			resources_by_handle[current_handle] = res;
			reference_counts[filename] = 1;
			handles_by_filename[filename] = current_handle;
			filenames_by_handle[current_handle] = filename;
			return current_handle;
		}

		template <typename T> T *get_resource(resource_handle *handle)
		{
			if (resources_by_handle[*handle])
				return (T *)resources_by_handle[*handle];
			
			printf("No renderable found to handle %i!\n", *handle);
			abort();
			return NULL;
		}

		void release_resource(resource_handle *handle)
		{
			std::string fn = filenames_by_handle [*handle];
			if (fn.length() <= 0)
			{
				printf("handle %i not found and not loaded before ...\n", *handle);
				
				abort();
				return;
			}
						
			reference_counts[fn]--;
			
			if (reference_counts[fn] <= 0)
			{
				reference_counts[fn] = 0;
				filenames_by_handle[*handle] = "";
				handles_by_filename[fn] = 0;
								
				renderable *p = resources_by_handle[*handle];
				if (!p)
				{
					printf("trying to delete NULL resource! handle: %i\n", *handle);
					abort ();
					return;
				}
				delete p;
				resources_by_handle[*handle] = NULL;
			}
			*handle = 0;
		}

		particle_emitter *acquire_particle_emitter(std::string fn);
		
	protected:
		resource_handle get_free_handle(void);
		
		std::tr1::unordered_map <std::string, int> reference_counts;
		std::tr1::unordered_map <std::string, resource_handle> handles_by_filename;
		std::tr1::unordered_map <resource_handle, std::string> filenames_by_handle;
		
		renderable *resources_by_handle[MAX_RESOURCES];
	};
	
	extern renderable_manager g_renderable_manager;
}