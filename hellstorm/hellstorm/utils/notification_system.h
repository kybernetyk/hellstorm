//
//  notification_system.h
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <string>

namespace hs 
{
	void post_notification(const char *name, void *object = NULL);
	void post_notification(std::string &notification_name, void *object = NULL);
}