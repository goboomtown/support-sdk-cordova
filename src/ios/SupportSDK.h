#import <Cordova/CDV.h>
#import "ViewController.h"

@import SupportSDK;

@interface SupportSDK : CDVPlugin <SupportButtonDelegate>

@property   ViewController *btViewController;

- (void)  displayMenu:(CDVInvokedUrlCommand*)command;
- (void)  initiateBoomtown:(CDVInvokedUrlCommand*)command;
- (void)  loadConfigurationFromJSON:(CDVInvokedUrlCommand*)command;

@end
