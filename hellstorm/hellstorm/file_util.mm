//
//  file_util.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "file_util.h"

namespace hs
{
	std::string path_for_file (const char *filename)
	{
		NSString *relPath = [NSString stringWithFormat: @"%s",filename];
		NSMutableArray *imagePathComponents = [NSMutableArray arrayWithArray:[relPath pathComponents]];
		NSString *file = [imagePathComponents lastObject];
		
		[imagePathComponents removeLastObject];
		NSString *imageDirectory = [NSString pathWithComponents:imagePathComponents];
		
		NSString *ret = [[NSBundle mainBundle] pathForResource:file ofType:nil inDirectory:imageDirectory];	
		if (!ret)
		{
			NSLog(@"%s wurde nicht gefunden! pathForFile()",filename);
			abort();
		}
		const char *c = [ret cStringUsingEncoding: NSASCIIStringEncoding];
		
		return std::string (c);
	}
}