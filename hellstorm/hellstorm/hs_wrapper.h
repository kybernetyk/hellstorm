//
//  hs_wrapper.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
namespace hs
{
	class scene;
}

extern void hs_game_init(hs::scene *scene);
extern void hs_game_shutdown(void);

extern void hs_game_tick(void);
extern void hs_game_render(void);

extern void hs_game_did_become_active(void);
extern void hs_game_did_enter_background(void);

extern void hs_input_touch_down(double x, double y);
extern void hs_input_touch_move(double x, double y);
extern void hs_input_touch_up(double x, double y);