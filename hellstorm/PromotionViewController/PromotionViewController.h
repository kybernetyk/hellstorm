//
//  PromotionViewController.h
//  PromotionTest
//
//  Created by Brandon Trebitowski on 11/25/10.
//  Copyright 2010 brandontreb.com. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface PromotionViewController : UIViewController<UIWebViewDelegate> {
	UIActivityIndicatorView *spinner;
	UIWebView *webView;
	
	NSString *promotionAddress;
}

@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *spinner;
@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) NSString *promotionAddress;

- (IBAction) doneButtonTouched:(id) sender;

@end
