//
//  Support.h
//  Boomtown
//
//  Created by Larry Borsato on 2019-09-17.
//  Copyright (c) 2016 BOOMTOWN. All rights reserved.
//

#ifndef _BOOMTOWN_DEBUG_NSLOG_
// call NSLog when DEBUG=1 Preprocessor flag is set (project settings Preprocessor macros for debug config)
#if DEBUG
#   define DLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#   define DLog(...)
#endif
#define ALog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BTConnectIssue.h"

@class CLLocationManager;
@class SupportButton;
@class KBViewModel;
@class BTFormModel;
@class HistoryEntryModel;
@class HistoryViewModel;

extern NSString *_Nonnull const kSDKV1Endpoint;

extern NSString *_Nonnull const kStartingBoomtownVideoTitle;

extern NSString *_Nonnull const BTConnectAPIBaseURL;

extern NSString *_Nonnull const kBroadcastExtensionSetupUIBundleId;
extern NSString *_Nonnull const kBroadcastExtensionBundleId;

/**
 Customer information keys
 */
extern NSString  *const _Nonnull kCustomerId;
extern NSString  *const _Nonnull kCustomerExternalId;
extern NSString  *const _Nonnull kCustomerLocationId;
extern NSString  *const _Nonnull kCustomerLocationExternalId;
extern NSString  *const _Nonnull kCustomerLocationMid;
extern NSString  *const _Nonnull kUserId;
extern NSString  *const _Nonnull kUserExternalId;
extern NSString  *const _Nonnull kUserEmail;
extern NSString  *const _Nonnull kUserPhone;


@protocol SupportDelegate <NSObject>

@required

@optional

- (void) supportUpdateKBWithModel:(nonnull KBViewModel *)kbViewModel;
- (void) supportSearchKBWithModel:(nonnull KBViewModel *)kbViewModel;
- (void) supportUpdateFormWithModel:(nonnull BTFormModel *)formModel;
- (void) supportUpdateForms;
- (void) supportSearchKBFailed;

@end

@protocol HistoryDelegate <NSObject>

@required

@optional

- (void) supportUpdateHistory:(nonnull HistoryViewModel *)historyViewModel;

@end




@interface Support : NSObject

@property (strong, nonatomic, nullable) NSString    *sdkName;
@property (strong, nonatomic, nullable) NSString    *endpoint;
@property (strong, nonatomic, nullable) NSString    *supportSDKVersion;
@property (strong, nonatomic, nullable) NSString    *osVersion;
@property (strong, nonatomic, nullable) NSString    *providerId;
@property (strong, nonatomic, nullable)	NSString	*membersId;
@property (strong, nonatomic, nullable)	NSString	*membersUsersId;
@property (strong, nonatomic, nullable)	NSString	*membersLocationsId;
@property (strong, nonatomic, nullable) NSString    *membersDevicesId;
@property                               BOOL        isScreenCapture;
@property                               BOOL        isCloudConfigComplete;

@property (strong, nonatomic, nullable) id<SupportDelegate> formsDelegate;
@property (strong, nonatomic, nullable) id<HistoryDelegate> historyDelegate;

@property (strong, nonatomic, nullable) BTConnectIssue  *currentIssue;
@property (strong, nonatomic, nullable) NSString        *currentIssueId;
@property (strong, nonatomic, nullable) BTConnectIssue  *rateableIssue;
@property (strong, nonatomic, nullable) NSString        *rateableIssueId;

@property (strong, nonatomic, nullable) NSDictionary    *settings;
@property (strong, nonatomic, nullable) NSString        *supportEmailAddress;
@property (strong, nonatomic, nullable) NSString        *supportPhoneNumber;
@property (strong, nonatomic, nullable) NSString        *supportWebsite;
@property (strong, nonatomic, nullable) NSURL           *supportWebsiteURL;
@property                               BOOL            showSupportEmail;
@property                               BOOL            showSupportPhone;
@property                               BOOL            showSupportWebsite;
@property                               BOOL            showSupportKnowledgeBase;
@property                               BOOL            showSupportCallMe;
@property                               BOOL            showSupportForms;
@property                               BOOL            showSupportHistory;
@property (strong, nonatomic, nullable) NSArray         *supportForms;
@property (strong, nonatomic, nullable) NSString        *callMeButtonText;
@property (strong, nonatomic, nullable) NSString        *callMeButtonConfirmation;
@property                               BOOL            supportProactiveEnabled;
@property                               BOOL            supportScreenShareEnabled;
@property                               BOOL            supportUnavailable;
@property (strong, nonatomic, nullable) NSString        *supportUnavailableSummary;

@property (strong, nonatomic, nullable) NSString        *downloadSessionToken;

@property (strong, nonatomic, nullable) NSString            *xmppdata;
@property (strong, nonatomic, nullable) KBViewModel         *kbViewModel;
@property (strong, nonatomic, nullable) KBViewModel         *kbSearchViewModel;
@property (strong, nonatomic, nullable) HistoryViewModel    *historyViewModel;

@property (strong, nonatomic, nullable) NSMutableArray<BTFormModel *>       *forms;
@property (strong, nonatomic, nonnull)  NSMutableArray<HistoryEntryModel *> *historyEntries;

@property                               BOOL                isUndecorated;


+ (Support *_Nonnull)sharedInstance;

- (void)    chatEnter:(nonnull NSString *)commId
              success:(void (^_Nonnull)(NSDictionary *_Nonnull))success
              failure:(void (^_Nonnull)(NSDictionary *_Nonnull))failure;
- (void)    chatExit:(NSString *_Nonnull)commId
       durationStart:(NSNumber *_Nonnull)durationStart
         durationAdd:(NSNumber *_Nonnull)durationAdd
             success:(void (^_Nonnull)(NSDictionary *_Nonnull))success
             failure:(void (^_Nonnull)(NSDictionary *_Nonnull))failure;
- (void)    chatFilePut:(NSString *_Nonnull)commId
                  image:(UIImage *_Nonnull)image
                success:(void (^_Nonnull)(NSDictionary *_Nonnull))success
                failure:(void (^_Nonnull)(NSDictionary *_Nonnull))failure;
- (void)    chatGet:(NSString *_Nonnull)commId
            success:(void (^_Nonnull)(NSDictionary *_Nonnull))success
            failure:(void (^_Nonnull)(NSDictionary *_Nonnull))failure;

- (nullable BTFormModel *) currentForm;

- (BTConnectIssue *_Nullable)   loadCurrentIssue;
- (void)                        saveCurrentIssue:(BTConnectIssue *_Nonnull)issue;
- (void)                        clearCurrentIssue;

- (void)                cancelIssue:(NSString *_Nonnull)issueId
                            success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                            failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;
- (NSString *_Nullable)      clientAppIdentifier;
- (void) createIssueWithCallbackNumber:(NSString *_Nullable)callbackNumber
                          description:(NSString *_Nullable)description
                              success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                              failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;

- (void) displayRatingScreenFromButton:(nonnull SupportButton *)supportButton;

- (NSString *_Nullable)      encodeString:(NSString *_Nonnull)data;
- (NSDictionary *_Nullable)	extractXmppInformation:(NSString *_Nonnull)xmppData;
- (void) getCallbackNumberWithSuccess:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                              failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;
- (void)            getCustomer:(NSDictionary *_Nonnull)customerInformation
                        success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                        failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;
- (void)            getForm:(nullable NSString *)id
success:(void (^_Nullable)(NSDictionary *_Nullable))success
failure:(void (^_Nullable)(NSDictionary *_Nullable))failure;

- (void) getForms:(nullable id<SupportDelegate>)sender;

- (void) getHistory;

- (void) getKB:(nullable id<SupportDelegate>)sender;
- (void) getIssue:(NSString *_Nonnull)issueId
          success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
          failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;
//- (NSDictionary *)  getServerFailureResponseForOperation:(NSURLSessionTask *)operation;
- (NSString *_Nonnull)      getServerFailureMessageForOperation:(NSURLSessionTask *_Nonnull)operation;
- (void)            getSettingsWithSuccess:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                                   failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;
- (BOOL) isProactiveEnabled;
- (void) postChecks:(NSArray *_Nonnull)checks
            success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
            failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;

- (void)            putForm:(BTFormModel * _Nonnull)formModel
                    success:(void (^ _Nonnull)(NSDictionary*_Nonnull))success
                    failure:(void (^ _Nonnull)(NSDictionary*_Nonnull))failure;


- (void)            rateIssue:(nonnull NSString *)issueId
                       rating:(NSUInteger)rating
                  description:(nullable NSString *)desc
                      success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                      failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;

- (void)            refreshIssue:(nullable NSString *)issueId;

- (void)            resolveIssue:(nonnull NSString *)issueId
                         success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                         failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;

- (void)            retrieveKB:(nullable NSString *)id
                       success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
                       failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;

- (void) searchKB:(nullable id<SupportDelegate>)sender query:(nullable NSString *)query;

- (void)            startVideoSessionWithId:(NSString *_Nonnull)id token:(NSString *_Nonnull)token;
+ (NSString *_Nullable) 		stringFromDictionary:(NSDictionary *_Nonnull)dict withKey:(NSString *_Nonnull)key;
- (void)            stopVideoSession;
+ (NSNumber *_Nullable) 		numberFromDictionary:(NSDictionary *_Nonnull)dict withKey:(NSString *_Nonnull)key;
+ (UIViewController *_Nullable)  topViewController;
- (void)    upload:(NSFileHandle *_Nullable)file
           success:(void (^_Nonnull)(NSDictionary*_Nonnull))success
           failure:(void (^_Nonnull)(NSDictionary*_Nonnull))failure;
- (NSArray *_Nullable)       validateInfoPlistKeys;

@end
