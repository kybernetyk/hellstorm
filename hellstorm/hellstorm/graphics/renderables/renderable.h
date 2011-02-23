//
//  renderable.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "hs_ogl.h"
#include "vec_2d.h"
#include <string>


namespace hs 
{
	
	class renderable
	{
		public:
		renderable();
		virtual ~renderable();
		
		virtual void init(void);
		virtual void transform(void);
			
		vec3d position;
		size2d size;
		
		color3f color;
		double alpha;
		double rotation;

		vec2d scale;
		vec2d anchor_point;
		
		unsigned int guid;
		std::string filename;
		
		static unsigned int last_guid;
	};
}