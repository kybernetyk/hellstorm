//
//  popup_system.h
//  hellstorm
//
//  Created by jrk on 8/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "hellstorm.h"

namespace game 
{
	class popup_system : public hs::system
	{
	public:
		popup_system(hs::entity_manager *manager);
		~popup_system();
		
		void update(double dt);
	};
}