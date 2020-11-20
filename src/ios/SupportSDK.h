#import <Cordova/CDV.h>

@import SupportSDK;

@interface SupportSDK : CDVPlugin <SupportButtonDelegate>

- (void)  displayMenu:(CDVInvokedUrlCommand*)command;
- (void)  initiateBoomtown:(CDVInvokedUrlCommand*)command;
- (void)  loadConfiguration:(CDVInvokedUrlCommand*)command;
- (void)  loadConfigurationFromFile:(CDVInvokedUrlCommand*)command;
- (void)  loadConfigurationFromJSON:(CDVInvokedUrlCommand*)command;

@end
