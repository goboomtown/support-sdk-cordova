#import "SupportSDK.h"
#import <Cordova/CDV.h>

@interface SupportSDK ()

@property (strong, nonatomic, nonnull)  SupportButton   *supportButton;
@property (strong, nonatomic, nullable) UIView          *displayedView;
@property (strong)                      NSString*       delegateCallbackId;
@property                               BOOL            isConfigured;
@property                               BOOL            isButtonVisible;

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
        NSError *error;
        NSData *data = [json dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];
        if ( jsonDict ) {
            BOOL loaded = [self.supportButton loadConfigurationJSON:json customerInfo:nil];

            if ( loaded ) {
                msg = @"Configuration read successfully.";
            } else {
                msg = @"Unable to read configuration.";
            }
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                             messageAsString:msg];
        } else {
            msg = [NSString stringWithFormat:@"Unable to read configuration: %@", error.userInfo[@"NSDebugDescription"]];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                             messageAsString:msg];
        }
    }

    [pluginResult setKeepCallbackAsBool:true];
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
  self.displayedView = view;
  dispatch_async(dispatch_get_main_queue(), ^{
    view.backgroundColor = [UIColor whiteColor];
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


- (void) supportButtonDidRequestExit:(nonnull SupportButton *)supportButton;
{
    NSLog(@"supportButtonDidRequestExit");
    if ( self.displayedView ) {
        [self.displayedView removeFromSuperview];
        self.displayedView = nil;
    }
}


- (void) supportButton:(SupportButton *)supportButton didFailWithError:(nonnull NSError *)error
{
    [self toast:[error localizedDescription]];
}

- (void)supportButtonDidGetSettings:(SupportButton *)supportButton
{
  CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                   messageAsString:@"didGetSettings"];
  [pluginResult setKeepCallbackAsBool:false];
  if ( self.delegateCallbackId ) {
    [self.commandDelegate sendPluginResult:pluginResult
                              callbackId:self.delegateCallbackId];
  }

  self.isConfigured = YES;
  self.isButtonVisible = NO;
  if ( self.isButtonVisible) {
      supportButton.menuStyle = Menu; //IconList;
      CGFloat buttonSize = 75;
      CGRect buttonFrame = CGRectMake((self.viewController.view.frame.size.width-buttonSize)/2,
                                  (self.viewController.view.frame.size.height-buttonSize)/2,
                                  buttonSize,
                                  buttonSize);
      supportButton.frame = buttonFrame;
      [self.viewController.view addSubview:supportButton];
  } else {
      supportButton.menuStyle = IconList;
      // [supportButton click];
  }
}


- (void) displayMenu:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult;
    if ( self.isConfigured ) {
        self.supportButton.menuStyle = IconListExit; //Menu;
        [self.supportButton click];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:@""];
    } else {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult
                            callbackId:command.callbackId];
}


- (void)supportButton:(SupportButton *)supportButton didFailToGetSettingsWithError:(NSError *)error
{
  CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                   messageAsString:@"didFailToGetSettingsWithError"];
  [pluginResult setKeepCallbackAsBool:false];
  if ( self.delegateCallbackId ) {
    [self.commandDelegate sendPluginResult:pluginResult
                              callbackId:self.delegateCallbackId];
  }
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
