//
//  PromotionViewController.m
//  PromotionTest
//
//  Created by Brandon Trebitowski on 11/25/10.
//  Copyright 2010 brandontreb.com. All rights reserved.
//

#import "PromotionViewController.h"
#import "hellstorm.h"

@implementation PromotionViewController

@synthesize webView;
@synthesize spinner;
@synthesize promotionAddress;

- (void) viewWillAppear:(BOOL)animated {	
	
	// Create a URL from the address
	NSURL *url = [NSURL URLWithString:promotionAddress];
	
	// Creates the URL request to load in the webview
	NSURLRequest *request = [NSURLRequest requestWithURL:url];
	[self.webView setHidden: YES];
	// Load the request in our webview
	[self.webView loadRequest:request];
	
	NSLog(@"will appear");
	
}

#pragma mark -
#pragma mark webView delegate
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request 
 navigationType:(UIWebViewNavigationType)navigationType 
{
	NSLog(@"%@", [[request URL] scheme]);
	
	//if ([[[request URL] scheme] isEqualToString: @"itms"])
	if (navigationType == UIWebViewNavigationTypeLinkClicked)
	{
		hs::audio_system::play_sound("click.mp3");
		[[UIApplication sharedApplication] openURL: [request URL]];
		return NO;
	}
	
	
	[spinner startAnimating];
	return YES;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {
	[self.webView setHidden: NO];
	[spinner stopAnimating];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
//	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" 
//													message:@"Unable to load, please try again later." 
//												   delegate:nil 
//										  cancelButtonTitle:@"OK" 
//										  otherButtonTitles:nil];
//	[alert show];
//	[alert release];
//	[self.parentViewController dismissModalViewControllerAnimated:YES];

}


- (IBAction) doneButtonTouched:(id) sender 
{
	hs::audio_system::play_sound("click.mp3");

	[self.parentViewController dismissModalViewControllerAnimated:YES];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation 
{
#ifdef ORIENTATION_LANDSCAPE
    return (interfaceOrientation == UIInterfaceOrientationLandscapeRight ||
			interfaceOrientation == UIInterfaceOrientationLandscapeLeft);
#endif
	
#ifdef ORIENTATION_PORTRAIT
	return (interfaceOrientation == UIInterfaceOrientationPortrait ||
			interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
#endif
	
	return NO;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload 
{
    [super viewDidUnload];
    self.spinner = nil;
	self.webView = nil;
}


- (void)dealloc 
{
	[self setWebView: nil];
	[self setSpinner: nil];
	[self setPromotionAddress: nil];
    [super dealloc];
}


@end
