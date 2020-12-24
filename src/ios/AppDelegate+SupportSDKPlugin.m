//
//  AppDelegate.m
//
//
//  Created by Larry Borsato on 2020-09-20.
//

#import "AppDelegate+SupportSDKPlugin.h"
#import "ViewController.h"


@implementation AppDelegate (SupportSDKPlugin)


/**
 * This is main kick off after the app inits, the views and Settings are setup here. (preferred - iOS4 and up)
 */
- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
  CGRect screenBounds = [[UIScreen mainScreen] bounds];

  self.window = [[UIWindow alloc] initWithFrame:screenBounds];
  self.window.autoresizesSubviews = YES;

  self.viewController = [[ViewController alloc] init];

  UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:self.viewController];
  navigationController.navigationBarHidden = YES;
  self.window.rootViewController = navigationController;
  [self.window makeKeyAndVisible];

  return YES;
}

@end
