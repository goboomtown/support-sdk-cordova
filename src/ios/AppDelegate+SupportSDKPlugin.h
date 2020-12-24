//
//  AppDelegate.h
//
//
//  Created by Larry Borsato on 2020-09-20.
//

#import "AppDelegate.h"
#import <UIKit/UIKit.h>
#import <Cordova/CDV.h>
#import "ViewController.h"


NS_ASSUME_NONNULL_BEGIN

@interface AppDelegate (SupportSDKPlugin)


// @property (strong, nonatomic, nullable) ViewController *btViewController;

- (BOOL)application:(UIApplication *)application
didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions;

@end

NS_ASSUME_NONNULL_END
