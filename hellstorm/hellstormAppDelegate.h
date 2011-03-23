//
//  hellstormAppDelegate.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GameCenterManager.h"
@class hellstormViewController;

@interface hellstormAppDelegate : NSObject <UIApplicationDelegate> 
{
	GameCenterManager *gcm;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet hellstormViewController *viewController;

@end
