//
//  user_settings.h
//  hellstorm
//
//  Created by jrk on 25/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <string>

namespace hs 
{
	namespace settings
	{
		void set_value_for_key(const char *val, std::string key);
		void set_value_for_key(char *val, std::string key);
		void set_value_for_key(bool val, std::string key);
		void set_value_for_key(int val, std::string key);
		void set_value_for_key(double val, std::string key);
		void set_value_for_key(std::string val, std::string key);
		
		bool get_value_for_key(bool &val, std::string key);
		bool get_value_for_key(int &val, std::string key);
		bool get_value_for_key(double &val, std::string key);
		bool get_value_for_key(std::string &val, std::string key);
		
		void sync(void);
	}
}