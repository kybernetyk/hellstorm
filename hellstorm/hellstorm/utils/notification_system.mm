//
//  notification_system.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "notification_system.h"
#include <string>
#import <Foundation/Foundation.h>

namespace hs 
{
	void post_notification(std::string &notification_name, void *object)
	{
		//NSString *nn = [NSString stringWithFormat: @"%s",notification_name.c_str()];
		
		NSString *nn = [[[NSString alloc] initWithCString: notification_name.c_str() encoding: NSASCIIStringEncoding] autorelease];
		
		NSNotificationCenter *dc = [NSNotificationCenter defaultCenter];
		[dc postNotificationName: nn object: (id)object];
	}
}