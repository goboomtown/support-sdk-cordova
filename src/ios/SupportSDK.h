#import <Cordova/CDV.h>

@import SupportSDK;

@interface SupportSDK : CDVPlugin <SupportButtonDelegate>

- (void)loadConfiguration:(CDVInvokedUrlCommand*)command;
- (void)loadConfigurationFromFile:(CDVInvokedUrlCommand*)command;
- (void) loadConfigurationFromJSON:(CDVInvokedUrlCommand*)command;

@end
