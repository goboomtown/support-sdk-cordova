//
//  AppDelegate.h
//
//
//  Created by Larry Borsato on 2020-09-20.
//

#import <UIKit/UIKit.h>
#import <Cordova/CDV.h>
#import "ViewController.h"


NS_ASSUME_NONNULL_BEGIN

@interface AppDelegate : CDVAppDelegate

@property (strong, nonatomic, nullable) ViewController *btViewController;

@end

NS_ASSUME_NONNULL_END
