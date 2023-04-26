#import "SupportSDK.h"
#import <Cordova/CDV.h>

@interface SupportSDK ()

@property (strong, nonatomic, nonnull)  SupportButton   *supportButton;
@property (strong, nonatomic, nullable) UIView          *displayedView;
@property (strong)                      NSString*       delegateCallbackId;
@property                               BOOL            isConfigured;
@property                               BOOL            isViewConfigured;
@property                               BOOL            isButtonVisible;
@property                               NSInteger       desiredMenuType;
@property (strong, nonatomic, nullable) NSString        *supportJSON;
@property (strong, nonatomic, nullable) NSString        *customerJSON;
@property (strong, nonatomic, nullable) NSDictionary    *customerInfo;
@property (strong, nonatomic, nullable) NSString        *appearanceJSON;
@property (strong, nonatomic, nullable) NSError         *lastError;
@property (strong, nonatomic, nullable) UINavigationController  *localNavigationController;
@property                               BOOL            isViewControllerOnly;

@end

@implementation SupportSDK


# pragma mark CDVPlugin

- (void)pluginInitialize
{
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(finishLaunching:) name:UIApplicationDidFinishLaunchingNotification object:nil];
  [self initSupportButton];
}

- (void)finishLaunching:(NSNotification *)notification
{
// Put here the code that should be on the AppDelegate.m
}

- (void) initSupportButton
{
  self.isViewControllerOnly = YES;
    self.supportButton = [[SupportButton alloc] initWithFrame:CGRectMake(0,0,50,50)];
    self.supportButton.delegate = self;
    [EventManager addObserver:self selector:@selector(handleEvents:)];
  }


-(void) handleEvents:(NSNotification*)notification
{
    NSString *eventRequest = [notification object];
    NSDictionary *userInfo = [notification userInfo];
    if ( [eventRequest isEqualToString:kRequestToast] ) {
      [self toast:userInfo[kRequestAlertTitle] withDelayInSeconds:5];
    } else if ( [eventRequest isEqualToString:kRequestAlert] ) {
      [self alertWithTitle:userInfo[kRequestAlertTitle]
                      message:userInfo[kRequestAlertMessage]
          positiveButtonTitle:userInfo[kRequestAlertPositiveButtonTitle]
          negativeButtonTitle:userInfo[kRequestAlertNegativeButtonTitle]];
    }
    NSDictionary *payload;
    if ( userInfo ) {
      payload = @{ kSupportSDKEventName: kSupportSDKEvent, kSupportSDKEventType: eventRequest, @"userInfo": userInfo};
    } else {
      payload = @{ kSupportSDKEventName: kSupportSDKEvent, kSupportSDKEventType: eventRequest};
    }
    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:payload];
    [result setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:result callbackId:self.delegateCallbackId];
}



- (NSString *) getContentsOfFile:(NSString *)file
{
    NSString *contents;
    NSURL* fileURL = [NSURL URLWithString:file];
    NSString* filePath = [self.commandDelegate pathForResource:[fileURL path]];
    if ( filePath ) {
        NSURL* url = [NSURL fileURLWithPath:filePath];
        NSError *error;

        contents = [NSString stringWithContentsOfURL:url encoding:NSUTF8StringEncoding error:&error];
    }
    return contents;
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
    self.supportJSON = [self jsonForArgument:[command.arguments objectAtIndex:0]];
    if ( !self.supportJSON ) {
        msg = [NSString stringWithFormat:@"Unable to read configuration: %@", self.lastError.userInfo[@"NSDebugDescription"]];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                       messageAsString:msg];
    } else {
      // self.desiredMenuType = -1;
      // if ( command.arguments.count > 1 ) {
      //     NSString* menuTypeString = [command.arguments objectAtIndex:1];
      //     [self getMenuType:menuTypeString];
      // }
      [self.supportButton reset];
      BOOL loaded = [self.supportButton loadConfigurationJSON:self.supportJSON customerInfo:nil];
      if ( loaded ) {
          msg = @"Configuration read successfully.";
      } else {
          msg = @"Unable to read configuration.";
      }
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                       messageAsString:msg];
    }

    [pluginResult setKeepCallbackAsBool:true];
    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
  }];
}

- (NSString *) jsonForArgument:(NSString *)arg
{
  NSError *error;
  if (arg && ![arg isKindOfClass:[NSNull class]] && [arg length]>0) {
      NSData *data = [arg dataUsingEncoding:NSUTF8StringEncoding];
      NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];
      self.lastError = error;
      if ( !error ) {
        return arg;
      }
  }
  return nil;
}

// - (void) getMenuType:(id)menuType
// {
//     if ( [menuType isKindOfClass:[NSNumber class]] ) {
//         NSNumber *number = (NSNumber *) menuType;
//         self.desiredMenuType = [menuType intValue];
//     } else if ( [menuType isKindOfClass:[NSString class]] ) {
//         NSString *string = (NSString *) menuType;
//         self.desiredMenuType = [string integerValue];
//     } else {
//         self.desiredMenuType = Menu;
//     }
// }

- (void) loadConfigurationWithAppearance:(CDVInvokedUrlCommand*)command
{
  // [self fixViewController];
  [self.commandDelegate runInBackground:^{
    NSString *msg = @"";
    self.delegateCallbackId = command.callbackId;
    CDVPluginResult* pluginResult = nil;
    NSString* json = [command.arguments objectAtIndex:0];
    if (json == nil || [json length] == 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    } else {
      self.supportJSON = json;
      // self.desiredMenuType = -1;
      if ( command.arguments.count > 1 ) {
          NSString* uiJSON = [command.arguments objectAtIndex:1];
          if ( [uiJSON isKindOfClass:[NSString class]] ) {
              self.appearanceJSON = uiJSON;
              if ( self.appearanceJSON && [self.appearanceJSON length]>0 ) {
                  [self.supportButton configureWithJSON:self.appearanceJSON];
              }
          }
      }

      // if ( command.arguments.count > 2 ) {
      //     NSString* menuTypeString = [command.arguments objectAtIndex:2];
      //     // self.desiredMenuType = [menuTypeString integerValue];
      //     [self getMenuType:menuTypeString];
      // }

        NSError *error;
        NSData *data = [self.supportJSON dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];
        if ( jsonDict ) {
            // if ( self.isConfigured ) {
            //     dispatch_async(dispatch_get_main_queue(), ^{
            //         [self supportButtonDidGetSettings:self.supportButton];
            //     });
            // } else {
            [self.supportButton reset];
                BOOL loaded = [self.supportButton loadConfigurationJSON:self.supportJSON customerInfo:nil];

                if ( loaded ) {
                    msg = @"Configuration read successfully.";
                } else {
                    msg = @"Unable to read configuration.";
                }
            // }

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

- (void) loadConfigurationWithCustomerAndAppearance:(CDVInvokedUrlCommand*)command
{
  // [self fixViewController];
  [self.commandDelegate runInBackground:^{
    NSString *msg = @"";
    self.delegateCallbackId = command.callbackId;
    CDVPluginResult* pluginResult = nil;
    self.supportJSON = [command.arguments objectAtIndex:0];
    self.supportJSON = [self jsonForArgument:[command.arguments objectAtIndex:0]];
    if ( !self.supportJSON ) {
        msg = [NSString stringWithFormat:@"Unable to read configuration: %@", self.lastError.userInfo[@"NSDebugDescription"]];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                       messageAsString:msg];
    } else {
      if ( command.arguments.count > 1 ) {
        self.customerInfo = nil;
        self.customerJSON = [self jsonForArgument:[command.arguments objectAtIndex:1]];
        if ( self.customerJSON ) {
            NSError *error;
            NSData *data = [self.customerJSON dataUsingEncoding:NSUTF8StringEncoding];
            self.customerInfo = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];
            if ( error ) {
                self.customerInfo = nil;
            }
        }
      }

      if ( command.arguments.count > 2 ) {
        self.appearanceJSON = [self jsonForArgument:[command.arguments objectAtIndex:2]];
       }

      // self.desiredMenuType = -1;
      // if ( command.arguments.count > 3 ) {
      //     NSString* menuTypeString = [command.arguments objectAtIndex:3];
      //     // self.desiredMenuType = [menuTypeString integerValue];
      //     [self getMenuType:menuTypeString];
      // }
      [self.supportButton reset];
      BOOL loaded = [self.supportButton loadConfigurationJSON:self.supportJSON customerInfo:self.customerInfo];

      if ( loaded ) {
        msg = @"Configuration read successfully.";
      } else {
        msg = @"Unable to read configuration.";
      }
      if ( self.appearanceJSON ) {
        [self.supportButton configureWithJSON:self.appearanceJSON];
      }

      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                             messageAsString:msg];
    }

    [pluginResult setKeepCallbackAsBool:true];
    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
  }];
}


- (void) settings:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult;
    if ( self.isConfigured ) {
        [self.supportButton settings];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:@""];
    } else {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult
                            callbackId:command.callbackId];
}


- (void) initiateBoomtown:(CDVInvokedUrlCommand*)command
{
    [self loadConfigurationFromJSON:command];
}


- (void) initiateBoomtownWithAppearance:(CDVInvokedUrlCommand*)command
{
    [self loadConfigurationWithAppearance:command];
}


- (void) initiateBoomtownWithCustomerAndAppearance:(CDVInvokedUrlCommand*)command
{
    [self loadConfigurationWithCustomerAndAppearance:command];
}


- (void) sendRequest:(CDVInvokedUrlCommand*)command
{
  if ( command.arguments.count == 0 ) {
      return;
  }
  NSString *request = [command.arguments objectAtIndex:0];
  id userInfo = command.arguments.count>1 ? [command.arguments objectAtIndex:1] : nil;
    CDVPluginResult* pluginResult;
    if ( self.isConfigured ) {
        [EventManager notify:request userInfo:userInfo];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:@""];
    } else {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult
                            callbackId:command.callbackId];
}

- (void) displayMenu:(CDVInvokedUrlCommand*)command
{
    if ( command.arguments.count > 0 ) {
        // NSString* menuTypeString = [command.arguments objectAtIndex:0];
        // // self.desiredMenuType = [menuTypeString integerValue];
        // [self getMenuType:menuTypeString];
    }
    CDVPluginResult* pluginResult;
    if ( self.isConfigured ) {
        // self.supportButton.menuStyle = self.desiredMenuType == -1 ? IconListExit : self.desiredMenuType; //Menu;
        [self.supportButton click];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:@""];
    } else {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult
                            callbackId:command.callbackId];
}


- (void) configureAppearance:(CDVInvokedUrlCommand*)command
{
    if ( command.arguments.count > 0 ) {
        self.appearanceJSON = [command.arguments objectAtIndex:0];
    }
    CDVPluginResult* pluginResult;
    if ( self.appearanceJSON ) {
        [self.supportButton configureWithJSON:self.appearanceJSON];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:@""];
    } else {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult
                            callbackId:command.callbackId];
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


#pragma mark - Message display

- (void) toast:(NSString *)msg
{
    [self toast:msg withDelayInSeconds:5];
}


- (void) toast:(NSString *)msg withDelayInSeconds:(NSInteger)delayInSeconds
{
    UIAlertView *toast = [[UIAlertView alloc] initWithTitle:@""
                                                    message:msg
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:nil, nil];

    [toast show];

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC),
                   dispatch_get_main_queue(), ^{
        [toast dismissWithClickedButtonIndex:0 animated:YES];
      }
    );
}


- (void) alertWithTitle:(NSString *)title
                message:(NSString *)msg
    positiveButtonTitle:(NSString *)positiveButtonTitle
    negativeButtonTitle:(NSString *)negativeButtonTitle
{
    NSString *defaultButtonTitle;
    if ( !positiveButtonTitle || !negativeButtonTitle ) {
        defaultButtonTitle = positiveButtonTitle ? positiveButtonTitle : negativeButtonTitle;
        if ( !defaultButtonTitle ) {
          defaultButtonTitle = @"OK";
        }
    }
    UIAlertController *alertController = [UIAlertController
                                          alertControllerWithTitle:NSLocalizedString(title, nil)
                                          message:NSLocalizedString(msg, nil)
                                          preferredStyle:UIAlertControllerStyleActionSheet];
    if ( defaultButtonTitle ) {
        UIAlertAction *action = [UIAlertAction actionWithTitle:NSLocalizedString(defaultButtonTitle, nil)
                                                                style:UIAlertActionStyleDefault
                                                           handler:^(UIAlertAction *action)
                                 {
            [EventManager notify:kEventAlertDefaultClicked userInfo:nil];
                                 }];
        [alertController addAction:action];
    } else {
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:NSLocalizedString(negativeButtonTitle, nil)
                                                           style:UIAlertActionStyleCancel
                                                         handler:^(UIAlertAction *action)
                                   {
            [EventManager notify:kEventAlertNegativeClicked userInfo:nil];
                                   }];
        [alertController addAction:cancelAction];
        UIAlertAction *action = [UIAlertAction actionWithTitle:NSLocalizedString(positiveButtonTitle, nil)
                                                                style:UIAlertActionStyleDefault
                                                           handler:^(UIAlertAction *action)
                                 {
            [EventManager notify:kEventAlertPositiveClicked userInfo:nil];
                                 }];
        [alertController addAction:action];
    }
    [self.viewController presentViewController:alertController animated:YES completion:^{
        [EventManager notify:kEventMenuStarted userInfo:nil];
   }];
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

- (UIColor *) getBackgroundColor
{
    if (@available(iOS 13.0, *)) {
        return UIColor.systemBackgroundColor;
    }
    return UIColor.whiteColor;
}

- (void) supportButton:(SupportButton *)supportButton displayView:(UIView *)view
{
  self.displayedView = view;
  dispatch_async(dispatch_get_main_queue(), ^{
    view.backgroundColor = [self getBackgroundColor];
    [self.viewController.view addSubview:view];
  });
}


- (void) supportButton:(SupportButton *)supportButton displaySupportMenu:(UIAlertController *)alertController
{
  dispatch_async(dispatch_get_main_queue(), ^{

    if ( self.viewController.view.traitCollection.horizontalSizeClass != UIUserInterfaceSizeClassCompact )
    {
        // In this case the device is an iPad.
        if ( self.isViewControllerOnly ) {
          [self.viewController presentViewController:alertController animated:YES completion:nil];
        } else {
          [self.viewController.navigationController presentViewController:alertController animated:YES completion:nil];
        }
        UIPopoverPresentationController *popPresenter = [alertController
                                                         popoverPresentationController];
        popPresenter.sourceView = supportButton;
        popPresenter.sourceRect = supportButton.bounds;
    }
    else
    {
        // In this case the device is an iPhone/iPod Touch.
        if ( self.isViewControllerOnly ) {
          [self.viewController presentViewController:alertController animated:YES completion:nil];
        } else {
          [self.viewController.navigationController presentViewController:alertController animated:YES completion:nil];
        }
    }
  });
}


- (void) supportButton:(SupportButton *)supportButton displayViewController:(UIViewController *)viewController
{
  viewController.view.backgroundColor = [self getBackgroundColor];
  dispatch_async(dispatch_get_main_queue(), ^{
    if ( self.isViewControllerOnly ) {
      UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"Back", nil)
                                                               style:UIBarButtonItemStylePlain
                                                              target:self
                                                              action:@selector(back:)];
      self.localNavigationController = [[UINavigationController alloc] initWithRootViewController:viewController];
      viewController.navigationItem.backBarButtonItem = backButton;
      viewController.navigationItem.leftBarButtonItem = backButton;
      self.localNavigationController.modalPresentationStyle = UIModalPresentationOverFullScreen;
      [self.viewController presentViewController:self.localNavigationController animated:YES completion:nil];
  } else {
    [self.viewController.navigationController pushViewController:viewController animated:NO];
  }
  });

}


- (IBAction)back:(id)sender
{
    [self.localNavigationController dismissViewControllerAnimated:YES completion:nil];
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
  [pluginResult setKeepCallbackAsBool:YES];
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
      // supportButton.menuStyle = self.desiredMenuType; // IconList;
      [supportButton click];

  }
}


- (void)supportButton:(SupportButton *)supportButton didFailToGetSettingsWithError:(NSError *)error
{
  CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                   messageAsString:@"didFailToGetSettingsWithError"];
  [pluginResult setKeepCallbackAsBool:YES];
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




@end
