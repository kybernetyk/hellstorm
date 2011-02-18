//
//  renderable.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "renderable.h"
#include "hellstorm.h"

namespace hs 
{
	unsigned int renderable::last_guid = 0;
	
	renderable::renderable()
	{
		guid = ++last_guid;
		init();
	}
	
	renderable::~renderable()
	{
		
	}
	
	void renderable::init(void)
	{
		position = vec3d_make(0.0, 0.0, 0.0);
		size = size2d_make(0.0, 0.0);
		
		alpha = 1.0;
		rotation = 0.0;
		
		scale = vec2d_make(1.0, 1.0);
		anchor_point = vec2d_make(0.5, 0.5);
	}
	
	void renderable::transform(void)
	{
		glTranslatef(position.x, position.y, position.z);
		
		if (rotation != 0.0f )
			glRotatef( -rotation, 0.0f, 0.0f, 1.0f );
		
		if (scale.x != 1.0 || scale.y != 1.0)
			glScalef( scale.x, scale.y, 1.0f );
		
		glTranslatef(- (anchor_point.x * size.w), - (anchor_point.y * size.h), 0);

	}
	
	void renderable::render_content(void)
	{

	}
}