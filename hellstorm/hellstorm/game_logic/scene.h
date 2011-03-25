//
//  scene.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

namespace hs
{
    class scene
    {
		public:
        virtual void init(void) = 0;
		virtual void shutdown(void) = 0;
		
		virtual void update(double dt) = 0;
		virtual void render(void) = 0;
		
		virtual int scene_type(void) = 0;
		
		virtual void game_did_become_inactive(void);
		virtual void game_did_become_active(void);
		
		virtual ~scene();
    };
};