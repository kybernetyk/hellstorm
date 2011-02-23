//
//  bitmap_font.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "renderable.h"
#include <string>

extern "C"
{
	#include "bm_font.h"
};


namespace hs 
{
	class bitmap_font : public renderable
	{
	public:
		bitmap_font(std::string fnt_filename);
		~bitmap_font();

		bool load_from_file(std::string fnt_filename);
		void transform(void);
		void render_content();
				
		std::string texture_filename;
		bm_font font;
		const char *text_ptr;
	};
}
