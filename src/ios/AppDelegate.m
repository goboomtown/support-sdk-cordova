//
//  AppDelegate.m
//
//
//  Created by Larry Borsato on 2020-09-20.
//

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window, viewController;


/**
 * This is main kick off after the app inits, the views and Settings are setup here. (preferred - iOS4 and up)
 */
- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];

    self.window = [[UIWindow alloc] initWithFrame:screenBounds];
    self.window.autoresizesSubviews = YES;

    // only set if not already set in subclass
    if (self.btViewController == nil) {
        self.btViewController = [[ViewController alloc] init];
    }

    // Set your app's start page by setting the <content src='foo.html' /> tag in config.xml.
    // If necessary, uncomment the line below to override it.
    // self.viewController.startPage = @"index.html";

    // NOTE: To customize the view's frame size (which defaults to full screen), override
    // [self.viewController viewWillAppear:] in your view controller.

    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:self.btViewController];
    navigationController.navigationBarHidden = YES;
    self.window.rootViewController = navigationController;
    [self.window makeKeyAndVisible];

    return YES;
}

@end
