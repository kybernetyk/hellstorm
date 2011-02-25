//
//  game.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "timer.h"

namespace hs 
{
    class scene;
	class renderer;
    
	enum e_scene_queue_state
	{
		e_sqs_none,
		e_sqs_set,
		e_sqs_pushed,
		e_sqs_popped
	};
	
	const int scene_stack_size = 32;
	
    class game 
    {
	public:
		bool init_with_scene(hs::scene *scene);
		void shutdown(void);
        
		void set_scene(hs::scene *scene);
		void push_scene(hs::scene *scene);
		void pop_scene(void);
		
		void tick(void);
		void render(void);
	
		void did_become_inactive(void);
		void did_become_active(void);
		
		void long_delta_occured(void);
	
		game();
		~game();
	protected:
		timer tmr;
	
	private:
		unsigned int ticks_per_second;
		double skip_ticks;
		unsigned int max_frame_skip;
		double fixed_delta;
		unsigned int next_game_tick;
		unsigned int loops;
		double max_timer_delta;
		
		//scene management
		e_scene_queue_state scene_queue_state;
		scene *scene_stack[scene_stack_size];
		scene *current_scene;
		scene *next_scene;
		int scene_stack_pointer;
		int push_counter;
		int pop_counter;
    };
    
	extern game *g_game;
};