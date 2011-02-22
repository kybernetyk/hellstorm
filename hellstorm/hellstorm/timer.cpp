//
//  timer.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "timer.h"
#include <sys/time.h>
#include <time.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

namespace hs 
{
	double get_double_time(void)
	{
		mach_timebase_info_data_t base;
		mach_timebase_info(&base);
		
		uint64_t nanos = (mach_absolute_time()*base.numer)/base.denom;
		return (double)nanos*1.0e-9;
	}

	unsigned int get_tick_count(void)
	{
		timeval v;
		gettimeofday(&v, 0);
		return (v.tv_sec * 1000) + (v.tv_usec / 1000);
	}

	
	timer::timer()
	{
		fps = 0.0;
		delta = 0.0;
		
		tick_count = 0.0;
		last_tick_count = 0.0;
		
		temp = 0.0;
		frames = 0.0;
	}
	
	void timer::update(void)
	{
		last_tick_count = tick_count;
		tick_count = get_double_time();
		
		delta = (tick_count - last_tick_count);
		
		//fps
		frames++;
		temp += delta;
		if (temp >= 1.0)
		{
			fps = frames / temp;
			temp = 0.0;
			frames = 0.0;
		}
	}
}