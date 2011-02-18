//
//  atlas_quad.h
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
	class atlas_quad : public renderable
	{
	public:
		atlas_quad();
		atlas_quad(std::string fn);
		~atlas_quad();
		
		void init(void);
		bool load_from_file(std::string fn);
		
		void render_content(void);
		
		size2d tex_size;
		rect src_rect;
	};
}