//
//  timer.h
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

namespace hs 
{
	extern double get_double_time(void);
	extern unsigned int get_tick_count(void);
	
	class timer
	{
	public:
		timer();
		void update(void);

		double delta;
		double fps;
		
	protected:
		double tick_count;
		double last_tick_count;
		
		double temp;
		double frames;
	};
}