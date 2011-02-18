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

void hs_game_init(void)
{
    the_game = new hs::game();
	the_game->init_with_scene(new test_game::menu_scene());
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
