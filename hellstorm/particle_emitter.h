//
//  particle_emitter.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "renderable.h"
#include <string>

namespace hs 
{
	class particle_emitter : public renderable
	{
	public:
		particle_emitter();
		particle_emitter(std::string fn);
		~particle_emitter();
		
		void init(void);
		bool load_from_file(std::string fn);
		
		//loop stuff
		void update(double dt);
		void render_content(void);
		
		//state
		bool is_active(void);
		bool should_handle(void);
		
		//control
		void start(void);
		void stop(void);
		void reset(void);

		//properties
		double duration(void);
		void set_duration(double dur);
		
		bool do_not_delete;
	
		void *objc_pe_ptr;
	};
}