//
//  menu_scene.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "menu_scene.h"
#include <cstdio>

namespace test_game 
{
	menu_scene::~menu_scene()
	{
		std::printf("menu scene dtor\n");
	}
	
	void menu_scene::init(void)
	{
		
	}
	
	void menu_scene::shutdown(void)
	{
		
	}
	
	void menu_scene::update(double dt)
	{
		std::printf("update\n");		
	}
	
	void menu_scene::render()
	{
		
	}
	
	int menu_scene::scene_type()
	{
		return 1;
	}
}