//
//  quad.h
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
	class quad : public renderable
	{
	public:
		quad();
		quad(std::string fn);
		~quad();
		
		bool load_from_file(std::string fn);

		void render_content(void);
	};
}