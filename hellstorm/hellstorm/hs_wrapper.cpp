//
//  hs_wrapper.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "hs_wrapper.h"
#include "hellstorm.h"
#include "menu_scene.h"

static hs::game *the_game;

void hs_game_init(hs::scene *scene)
{
    the_game = new hs::game();
	//the_game->init_wih_scene(scene);
	
	the_game->init_with_scene(scene);
}

void hs_game_shutdown(void)
{
    delete the_game;
}

void hs_game_tick(void)
{
	the_game->tick();
}

void hs_game_render(void)
{
    the_game->render();
}

void hs_game_did_become_active(void)
{
	the_game->long_delta_occured();
}

void hs_game_did_enter_background(void)
{
	
}



void hs_input_touch_down(double x, double y)
{
	hs::g_input.input_touch_down(hs::vec2d_make(x, y));
}

void hs_input_touch_move(double x, double y)
{
	hs::g_input.input_touch_move(hs::vec2d_make(x, y));	
}

void hs_input_touch_up(double x, double y)
{
	hs::g_input.input_touch_up(hs::vec2d_make(x, y));
}