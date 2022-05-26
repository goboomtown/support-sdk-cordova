//
//  SupportButton.h
//  SupportSDK
//
//  Created by Larry Borsato on 2019-09-17.
//  Copyright © 2019 Boomtown. All rights reserved.
//

@import UIKit;


@class SupportButton;
@class Support;
@class EventManager;
@protocol SupportDelegate;

typedef enum MenuStyle : NSInteger {
    NoMenu          = 0,
    Menu            = 1,
    Button          = 2,
    IconList        = 3,
    IconListExit    = 4
} MenuStyle;


extern NSString  *const _Nonnull SupportSDKErrorDomain;

/**
 These methods allow the Support Button to communicate with the delegate calling application
 */
@protocol SupportButtonDelegate <NSObject>

@required

/**
 Called when a view is ready to be displayed.
 This will display the support menu or rating screen
 */
- (void) supportButton:(nonnull SupportButton *)supportButton  displayView:(nonnull UIView *)view;


/**
 Called when a view controller is ready to be displayed.
 This will display tracking and chat related to an issue, or a knowledge base article
 */
- (void) supportButton:(nonnull SupportButton *)supportButton  displayViewController:(nonnull UIViewController *)viewController;

/**
 Called when the generated support action sheet is ready to be displayed. This will display the available support options
 */
- (void) supportButton:(nonnull SupportButton *)supportButton  displaySupportMenu:(nonnull UIAlertController *)alertController;

/**
 Called to provide alerts for the user. The message will explain the situation (which is really a failure description)
 */
- (void)supportButton:(nonnull SupportButton *)supportButton didFailWithError:(nonnull NSError *)error;

@optional


- (void) supportButtonDidGetCustomer:(nonnull SupportButton *)supportButton;
- (void) supportButton:(nonnull SupportButton *)supportButton didFailToGetCustomerWithError:(nonnull NSError *)error;

- (void) supportButtonDidGetSettings:(nonnull SupportButton *)supportButton;
- (void) supportButton:(nonnull SupportButton *)supportButton didFailToGetSettingsWithError:(nonnull NSError *)error;

- (void) supportButtonDidCreateIssue:(nonnull SupportButton *)supportButton;
- (void) supportButton:(nonnull SupportButton *)supportButton didFailToCreateIssueWithError:(nonnull NSError *)error;

- (void) supportButtonDidCancelIssue:(nonnull SupportButton *)supportButton;
- (void) supportButton:(nonnull SupportButton *)supportButton didFailToCancelIssueWithError:(nonnull NSError *)error;

/**
 Called when user requests exit from main menu
 */
- (void) supportButtonDidRequestExit:(nonnull SupportButton *)supportButton;


/**
 Called when settings were sucessfully retrieved
 */
//- (void)supportButtonDidGetSettings:(nonnull SupportSDKButton *)supportButton;

/**
 Called when settings retrieval fails
 */
- (void)supportButton:(nonnull SupportButton *)supportButton didFailRetrievingSettingsWithError:(nonnull NSError *)error;

/**
 Called when the mDNS service has been successfully advertised
 */
- (void)supportButton:(nonnull SupportButton *)supportButton didAdvertiseService:(nonnull NSNetService *)netService;

/**
 Called when the mDNS service failed to successfully advertise
 */
- (void)supportButton:(nonnull SupportButton *)supportButton didFailToAdvertiseService:(nonnull NSDictionary<NSString *,NSNumber *> *)errorDict;


@end


IB_DESIGNABLE
@interface SupportButton : UIView <NSNetServiceDelegate, SupportDelegate>


/**
 The delegate for responses
 */
@property (nullable, strong, nonatomic)	id			<SupportButtonDelegate> delegate;


@property                               MenuStyle  menuStyle;

@property                               BOOL        showLoginPrompt;

@property                               BOOL        isUndecorated;

@property                               BOOL        isSideBySideForms;

/**
 Use support view rather than popup for menu selection
 */
@property                               BOOL        useSupportView;


/**
 Determine if video components are unavailable
 
 @return    YES if no, otherwise no
 */

- (BOOL) isVideoUnavailable;


/**
 Force a click of Support button, typically without displaying it
 */
- (void) click;


/**
 Configure the Support SDK button with new appearance parameters
 
 @param     appearanceJSON
 */
- (NSError * _Nullable) configureWithJSON:(NSString *_Nullable) appearanceJSON;


/**
 Reset support button
 */

- (void) reset;


/**
 Send request to SDK
 
 @param request     the event request
 */
- (void) sendRequest:(nonnull NSString *)request;


/*
 Display settings
 */
- (void) settings;


/**
 Intialize the support button
 
 @param frame   the desired frame for the button
 
 @return    the new button instance
 */
- (nullable instancetype) initWithFile:(nullable NSString *)filename customerInfo:(nullable NSDictionary *)customerInfo;


/**
 Load the Support SDK configuration from the provided JSON file in the app bundle

 @param     configFileName      the file name of the configuration file (i.e support_sdk.json)
 @param     customerId          an NSDictionary containing key/value id pairs (emai, MID, etc) to identify a customer

 @return    YES if configuration was successfully loaded, NO if not
 */
- (BOOL) loadConfigurationFile:(nonnull NSString *)configFileName customerInfo:(nullable NSDictionary *)customerInfo;


/**
 Load the Support SDK configuration from the provided JSON string

 @param     json                the configuration information JSON as a string
 @param     customerId          an NSDictionary containing key/value id pairs (emai, MID, etc) to identify a customer

 @return    YES if configuration was successfully loaded, NO if not
 */
- (BOOL) loadConfigurationJSON:(NSString *_Nonnull)json customerInfo:(NSDictionary * _Nullable)customerInfo;


/**
 Load the Support SDK configuration from the provided JSON string

 @param     json                the configuration information JSON
 @param     customerInfoJson    an id (emai, MID, etc) to identify a customer

 @return    YES if configuration was successfully loaded, NO if not
 */

- (BOOL) loadConfigurationJSON:(NSString * _Nonnull)jsonString customerInfoJSON:(NSString * _Nullable)customerInfoJSON;


/**
 Load SDK configuration from a JSON dictionary, and specify customer if information is provided

 @param json                a string containing the configuration JSON
 @param customerInfo        the dictionary containing key/value informaion identifying the customer

 @return    YES if configuration was valid, NO is not
 */
- (BOOL) loadConfiguration:(NSDictionary *)json customerInfo:(NSDictionary *)customerInfo;

/**
Retrieve and load the desired customer into the Support SDK. This must me done after the settings have been retrieved

@param     customerInformationJSON       a JSON string of possible keys (i.e. customer_email) and values (i.e. an email address)
*/
- (void) getCustomerWithJSON:(NSString * _Nullable)customerInfoJSON;


/**
Retrieve and load the desired customer into the Support SDK. This must me done after the settings have been retrieved

@param     customerInformation       a dictionary of possible keys (i.e. customer_email) and values (i.e. an email address)
*/
- (void) getCustomerWithInformation:(NSDictionary * _Nullable)customerInformation;

/**
 Customer information keys
 
 These are the possible keys that can be searched for when attempting to retrieve a customer

 NSString  *const _Nonnull kCustomerId                   = @"members_id";
 NSString  *const _Nonnull kCustomerExternalId           = @"members_external_id";
 NSString  *const _Nonnull kCustomerLocationId           = @"members_locations_id";
 NSString  *const _Nonnull kCustomerLocationExternalId   = @"members_locations_external_id";
 NSString  *const _Nonnull kCustomerLocationMid          = @"members_locations_mid";
 NSString  *const _Nonnull kUserId                       = @"members_users_id";
 NSString  *const _Nonnull kUserExternalId               = @"members_users_external_id";
 NSString  *const _Nonnull kUserEmail                    = @"members_users_email";
 NSString  *const _Nonnull kUserPhone                    = @"members_users_phone";
 */



/**
 Advertise the Support SDK service via mDNS

 The contents of publicData will be available in the TXT record in clear text. The contents of dataToEncrypt will be available
 as an encrypted string under the key "private".

 @param     publicData      key-value pairs that will be available in the TXT record in clear text
 @param     dataToEncrypt   key-value pairs that will be available in the TXT record as an encrypted string under the "private" key

 @return    YES if mDNS service is created, NO if creation fails
 */
- (BOOL) advertiseServiceWithPublicData:(nullable NSDictionary<NSString*, NSString*> *)publicData
                            privateData:(nullable NSDictionary<NSString*, NSString*> *)privateData;


@end
