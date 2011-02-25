//
//  user_settings.cpp
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "user_settings.h"
#import <Foundation/Foundation.h>

namespace hs 
{
	namespace settings
	{
		void sync(void)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			[defs synchronize];
		}
		
		void set_value_for_key(bool val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];

			NSNumber *nval = [NSNumber numberWithBool: val];
			[defs setValue: nval forKey: nkey];
		}
		
		void set_value_for_key(int val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];

			NSNumber *nval = [NSNumber numberWithInt: val];
			[defs setValue: nval forKey: nkey];
		}
		
		void set_value_for_key(double val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];
			
			NSNumber *nval = [NSNumber numberWithDouble: val];
			[defs setValue: nval forKey: nkey];
		}
		
		void set_value_for_key(std::string val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];
			NSString *nval = [[[NSString alloc] initWithCString: val.c_str() encoding: NSASCIIStringEncoding] autorelease];
			
			[defs setValue: nval forKey: nkey];
		}
		
		//guard against c++ interpreting a const char * argument as bool, int, etc instead of calling the
		//std::string version
		void set_value_for_key(const char *val, std::string key)
		{
			set_value_for_key(std::string(val), key);
		}
		void set_value_for_key(char *val, std::string key)
		{
			set_value_for_key(std::string(val), key);
		}
		
		
		bool get_value_for_key(bool &val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];

			NSNumber *nval = [defs valueForKey: nkey];
			if (!nval)
				return false;
			
			if (![nval isKindOfClass: [NSNumber class]])
			{
				NSLog(@"%s isn't a string! It's a: %@", key.c_str(), [nval class]);
				abort();
				return false;
			}

			val = [nval boolValue];

			return true;
		}

		bool get_value_for_key(int &val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];
			
			NSNumber *nval = [defs valueForKey: nkey];
			if (!nval)
				return false;

			if (![nval isKindOfClass: [NSNumber class]])
			{
				NSLog(@"%s isn't a string! It's a: %@", key.c_str(), [nval class]);
				abort();
				return false;
			}

			val = [nval intValue];
			
			return true;
		}
		
		bool get_value_for_key(double &val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];
			
			NSNumber *nval = [defs valueForKey: nkey];
			if (!nval)
				return false;
			
			if (![nval isKindOfClass: [NSNumber class]])
			{
				NSLog(@"%s isn't a string! It's a: %@", key.c_str(), [nval class]);
				abort();
				return false;
			}

			val = [nval doubleValue];
			
			return true;
		}
		
		bool get_value_for_key(std::string &val, std::string key)
		{
			NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
			NSString *nkey = [[[NSString alloc] initWithCString: key.c_str() encoding: NSASCIIStringEncoding] autorelease];
						
			NSString *nval = [defs valueForKey: nkey];
			if (!nval)
				return false;

			if (![nval isKindOfClass: [NSString class]])
			{
				NSLog(@"%s isn't a string! It's a: %@", key.c_str(), [nval class]);
				abort();
				return false;
			}

			val = std::string([nval cStringUsingEncoding: NSASCIIStringEncoding]);
			return true;
		}
	}
}