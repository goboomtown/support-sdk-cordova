#import "SupportSDK.h"
#import <Cordova/CDV.h>

@interface SupportSDK ()

@property (strong, nonatomic, nonnull)  SupportButton   *supportButton;
@property (strong)                      NSString*       delegateCallbackId;

@end


@implementation SupportSDK


# pragma mark CDVPlugin

- (void)pluginInitialize
{
    [self initSupportButton];
}


- (void) initSupportButton
{
    self.supportButton = [[SupportButton alloc] initWithFrame:CGRectMake(0,0,50,50)];
    self.supportButton.delegate = self;
    [Appearance setIconColor:0xff0000];
    [Appearance setTextColor:0x000000];
}


- (void)onDomDelegateReady:(CDVInvokedUrlCommand*)command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:@"onDomDelegateReady"];
    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];

}


- (void) loadConfigurationFromJSON:(CDVInvokedUrlCommand*)command
{
  [self.commandDelegate runInBackground:^{
    NSString *msg = @"";
    self.delegateCallbackId = command.callbackId;
    CDVPluginResult* pluginResult = nil;
    NSString* json = [command.arguments objectAtIndex:0];
    if (json == nil || [json length] == 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    } else {
        BOOL loaded = [self.supportButton loadConfigurationJSON:json customerInfo:nil];

        if ( loaded ) {
            msg = @"Configuration read successfully.";
        } else {
            msg = @"Unable to read configuration.";
        }
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:msg];
    }

    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
  }];
}


- (void) initiateBoomtown:(CDVInvokedUrlCommand*)command
{
    [self loadConfigurationFromJSON:command];
}


- (void)registerDelegateCallbackId:(CDVInvokedUrlCommand*)command {
//    [self _handleCallSafely:^CDVPluginResult *(CDVInvokedUrlCommand* command) {
//
////        [[self getLogger] debugLog:@"Registering delegate callback ID: %@", command.callbackId];
//        self.delegateCallbackId = command.callbackId;
//
//        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
//        [result setKeepCallbackAsBool:YES];
//
//        return result;
//    } :command];
}


- (void) respond:(NSString *)msg
{
    if ( !self.delegateCallbackId ) {
        return;
    }
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:msg];
        [pluginResult setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.delegateCallbackId];
    }];
}


- (void) toast:(NSString *)msg
{
    UIAlertView *toast = [[UIAlertView alloc] initWithTitle:@""
                                                    message:msg
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:nil, nil];

    [toast show];

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 5 * NSEC_PER_SEC),
                   dispatch_get_main_queue(), ^{
        [toast dismissWithClickedButtonIndex:0 animated:YES];
      }
    );
}

#pragma mark - Support Button delegates


- (void) supportButton:(SupportButton *)supportButton didAdvertiseService:(NSNetService *)netService
{
    NSLog(@"mDNS service successfully advertised.");
}


- (void) supportButton:(SupportButton *)supportButton didFailToAdvertiseService:(NSDictionary<NSString *,NSNumber *> *)errorDict
{
    NSLog(@"mDNS service failed to advertise.");
}


- (void) supportButton:(SupportButton *)supportButton displayView:(UIView *)view
{
  dispatch_async(dispatch_get_main_queue(), ^{
    //
    // for ( UIView *subview in view.subviews ) {
    //     if ( [subview isKindOfClass:[LoginView class]] ) {
    //         subview.hidden = YES;
    //     }
    //     else if ( [subview isKindOfClass:[UICollectionView class]] ) {
    //         subview.hidden = NO;
    //     }
    // }

    view.frame = self.viewController.view.bounds;

    // NSString *viewRect = [NSString stringWithFormat:@"view %f %f %f %f\nviewController %f %f %f %f",
    // view.frame.origin.x,
    // view.frame.origin.y,
    // view.frame.size.width,
    // view.frame.size.height,
    // self.viewController.view.frame.origin.x,
    // self.viewController.view.frame.origin.y,
    // self.viewController.view.frame.size.width,
    // self.viewController.view.frame.size.height];
    // [self toast:viewRect];

    view.backgroundColor = [UIColor whiteColor];
    // view.center = self.viewController.view.center;
    [self.viewController.view addSubview:view];
  });
}


- (void) supportButton:(SupportButton *)supportButton displaySupportMenu:(UIAlertController *)alertController
{
  dispatch_async(dispatch_get_main_queue(), ^{

    if ( self.viewController.view.traitCollection.horizontalSizeClass != UIUserInterfaceSizeClassCompact )
    {
        // In this case the device is an iPad.
        [self.viewController.navigationController presentViewController:alertController animated:YES completion:nil];
        UIPopoverPresentationController *popPresenter = [alertController
                                                         popoverPresentationController];
        popPresenter.sourceView = supportButton;
        popPresenter.sourceRect = supportButton.bounds;
    }
    else
    {
        // In this case the device is an iPhone/iPod Touch.
        [self.viewController.navigationController presentViewController:alertController animated:YES completion:nil];
    }
  });
}


- (void) supportButton:(SupportButton *)supportButton displayViewController:(UIViewController *)viewController
{
  dispatch_async(dispatch_get_main_queue(), ^{
    [self.viewController.navigationController pushViewController:viewController animated:NO];
  });
}


- (void) supportButton:(SupportButton *)supportButton didFailWithError:(nonnull NSError *)error
{
    [self toast:[error localizedDescription]];
}

- (void)supportButtonDidGetSettings:(SupportButton *)supportButton
{
    supportButton.menuStyle = IconList;
    [supportButton click];
}

- (void)supportButton:(SupportButton *)supportButton didFailToGetSettingsWithError:(NSError *)error
{
    [self toast:[error localizedDescription]];
}


- (void)supportButton:(SupportButton *)supportButton didFailToGetCustomerWithError:(NSError *)error
{
//    [self warnWithError:error];
}


# pragma mark Javascript Plugin API

//- (void)onDomDelegateReady:(CDVInvokedUrlCommand*)command {
//    [self _handleCallSafely:^CDVPluginResult *(CDVInvokedUrlCommand * command) {
//
//        // Starts propagating the events.
////        [self resumeEventPropagationToDom];
//
//        return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
//    } :command];
//}



#pragma mark Utilities

//- (NSError*) parseErrorWithDescription:(NSString*) description {
//    return [self errorWithCode:CDV_LOCATION_MANAGER_INPUT_PARSE_ERROR andDescription:description];
//}
//
//
//- (NSError*) errorWithCode: (int)code andDescription:(NSString*) description {
//
//    NSMutableDictionary* details;
//    if (description != nil) {
//        details = [NSMutableDictionary dictionary];
//        [details setValue:description forKey:NSLocalizedDescriptionKey];
//    }
//
//    return [[NSError alloc] initWithDomain:@"CDVLocationManager" code:code userInfo:details];
//}

//- (void) _handleCallSafely: (CDVPluginCommandHandler) unsafeHandler : (CDVInvokedUrlCommand*) command  {
//    [self _handleCallSafely:unsafeHandler :command :true];
//}
//
//- (void) _handleCallSafely: (CDVPluginCommandHandler) unsafeHandler : (CDVInvokedUrlCommand*) command : (BOOL) runInBackground :(NSString*) callbackId {
//    if (runInBackground) {
//        [self.commandDelegate runInBackground:^{
//            @try {
//                [self.commandDelegate sendPluginResult:unsafeHandler(command) callbackId:callbackId];
//            }
//            @catch (NSException * exception) {
//                [self _handleExceptionOfCommand:command :exception];
//            }
//        }];
//    } else {
//        @try {
//            [self.commandDelegate sendPluginResult:unsafeHandler(command) callbackId:callbackId];
//        }
//        @catch (NSException * exception) {
//            [self _handleExceptionOfCommand:command :exception];
//        }
//    }
//}
//
//- (void) _handleCallSafely: (CDVPluginCommandHandler) unsafeHandler : (CDVInvokedUrlCommand*) command : (BOOL) runInBackground {
//    [self _handleCallSafely:unsafeHandler :command :true :command.callbackId];
//
//}
//
//- (void) _handleExceptionOfCommand: (CDVInvokedUrlCommand*) command : (NSException*) exception {
//    NSLog(@"Uncaught exception: %@", exception.description);
//    NSLog(@"Stack trace: %@", [exception callStackSymbols]);
//
//    // When calling without a request (LocationManagerDelegate callbacks) from the client side the command can be null.
//    if (command == nil) {
//        return;
//    }
//    CDVPluginResult* pluginResult = nil;
//    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:exception.description];
//    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
//}



@end
