//
//  EventManager.h
//  SupportSDK
//
//  Created by Larry Borsato on 2021-02-12.
//  Copyright © 2021 Boomtown. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

static NSString * const kSupportSDKEvent                = @"com.goboomtown.supportsdk.event";

static NSString * const kSupportSDKEventName            = @"event.name";
static NSString * const kSupportSDKEventType            = @"event.type";
static NSString * const kSupportSDKEventData            = @"event.data";

static NSString * const kEventSDKStarted                = @"com.goboomtown.event.sdk.started";
static NSString * const kEventSDKEnded                  = @"com.goboomtown.event.sdk.ended";

static NSString * const kEventMenuStarted               = @"com.goboomtown.event.menu.started";
static NSString * const kEventMenuEnded                 = @"com.goboomtown.event.menu.ended";

static NSString * const kEventChatStarted               = @"com.goboomtown.event.chat.started";
static NSString * const kEventChatIssueCreated          = @"com.goboomtown.event.chat.issue_created";
static NSString * const kEventChatIssueContinued        = @"com.goboomtown.event.chat.issue_continued";
static NSString * const kEventChatIssueResolved         = @"com.goboomtown.event.chat.issue_resolved";
static NSString * const kEventChatEnded                 = @"com.goboomtown.event.chat.ended";

static NSString * const kEventHistoryStarted            = @"com.goboomtown.event.history.started";
static NSString * const kEventHistoryEnded              = @"com.goboomtown.event.history.ended";

static NSString * const kEventKnowledgeStarted          = @"com.goboomtown.event.knowledge.started";
static NSString * const kEventKnowledgeEnded            = @"com.goboomtown.event.knowledge.ended";

static NSString * const kEventFormStarted               = @"com.goboomtown.event.form.started";
static NSString * const kEventFormSubmitted             = @"com.goboomtown.event.form.submitted";
static NSString * const kEventFormEnded                 = @"com.goboomtown.event.form.ended";

static NSString * const kEventAlertPresented            = @"com.goboomtown.event.alert.presented";
static NSString * const kEventAlertDismissed            = @"com.goboomtown.event.alert.dismissed";
static NSString * const kEventAlertDefaultClicked       = @"com.goboomtown.event.alert.default";
static NSString * const kEventAlertPositiveClicked      = @"com.goboomtown.event.alert.positive";
static NSString * const kEventAlertNegativeClicked      = @"com.goboomtown.event.alert.negative";

static NSString * const kRequestSupportSDKExit          = @"com.goboomtown.request.supportsdk.exit";

static NSString * const kRequestToast                   = @"com.goboomtown.request.toast";
static NSString * const kRequestAlert                   = @"com.goboomtown.request.alert";
static NSString * const kRequestAlertTitle              = @"alert.title";
static NSString * const kRequestAlertMessage            = @"alert.message";
static NSString * const kRequestAlertPositiveButtonTitle = @"alert.positive";
static NSString * const kRequestAlertNegativeButtonTitle = @"alert.negative";

static NSString * const kRequestChatExit                = @"com.goboomtown.request.chat.exit";
static NSString * const kRequestChatExitResolveIssue    = @"com.goboomtown.request.chat.exit_resolve_issue";


@interface EventManager : NSObject

+ (void) notify:(nonnull NSString *)eventOrRequest userInfo:(nullable NSDictionary *)userInfo;

+ (void) addObserver:(nonnull id)observer selector:(nonnull SEL)selector;
+ (void) removeObserver:(nonnull id)observer;

@end

NS_ASSUME_NONNULL_END
