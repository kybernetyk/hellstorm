//
//  game_factory.h
//  hellstorm
//
//  Created by jrk on 22/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "hellstorm.h"
namespace game 
{
	namespace factory
	{
		void create_psycho_back(hs::entity_manager *em);
		void create_borders_and_raster(hs::entity_manager *em);
	}
}