//
//  BTConnectIssue.h
//  BTConnectAPI
//
//  Created by Larry Borsato on 2016-03-10.
//  Copyright © 2016 Boomtown. All rights reserved.
//

#import <Foundation/Foundation.h>

enum {
    kBoomtownIssueTypeSales        = 1,
    kBoomtownIssueTypeSupport     = 2,
    kBoomtownIssueTypeWorkOrder = 3,
    kBoomtownIssueTypeTraining    = 4
};

enum {
    kIssueStatusPreparing       = 1,
    kIssueStatusRemote          = 2,
    kIssueStatusDispatching     = 3,
    kIssueStatusDispatched      = 4,
    kIssueStatusEnRoute         = 5,
    kIssueStatusOnSite          = 6,
    kIssueStatusResolved        = 7,
    kIssueStatusClosed          = 8,
    kIssueStatusPendingClosed   = 9,
    kIssueStatusClosedAlso      = 10,
    kIssueStatusCanceled        = 89,
    kIssueStatusDeleted         = 99
};

enum {
    kJobStatusAvailable     = 0,
    kJobStatusAccepted      = 1,
    kJobStatusEnRoute         = 2,
    kJobStatusCheckedIn     = 3,
    kJobStatusStarted       = 4,
    kJobStatusPaused        = 5,
    kJobStatusCompleted     = 6
};

enum {
    kIssueJobStatusNotStarted   = 0,
    kIssueJobStatusInProgress   = 1,
    kIssueJobStatusPaused       = 2,
    kIssueJobStatusCompleted    = 3
};

enum {
    kPayableStatusNotSet        = 0,
    kPayableStatusPayable       = 3,
    kPayableStatusInvoiced      = 4,
    kPayableStatusProcessing    = 6,
    kPayableStatusPaid          = 9,
    kPayableStatusWrittenOff    = 12
};


enum {
    kIssueResolutionNotSet         = 0,
    kIssueResolutionCompleted     = 1,
    kIssueResolutionChanged     = 2,
    kIssueResolutionCanceled     = 3,
    kIssueResolutionUnresolved     = 4
};

enum {
    kIssueTypeSales = 1,
    kIssueTypeSupport = 2
};


enum {
    kIssueCategoryOther             = 0,
    kIssueCategoryNetwork             = 1,
    kIssueCategoryHardware             = 2,
    kIssueCategorySoftware             = 3,
    kIssueCategoryPrinter             = 4,
    kIssueCategoryPc                 = 5,
    kIssueCategoryAccountPartner     = 6,
    kIssueCategoryAccount             = 7,
    kIssueCategoryConsultation         = 8,
    kIssueCategoryPosInstall         = 10
};


@interface BTConnectIssue : NSObject

@property (nonatomic, strong)	NSString	*arrival_time;
@property (nonatomic, strong)	NSString	*category;
@property (nonatomic, strong)	NSString	*created;
@property (nonatomic, strong)   NSString    *resolved;
@property (nonatomic, strong)	NSString	*departure_time;
@property (nonatomic, strong)	NSString	*details;
@property (nonatomic, strong)	NSString	*enroute_time;
@property (nonatomic, strong)	NSString	*id;
@property (nonatomic, strong)	NSString	*job;
@property (nonatomic, strong)	NSString	*members_email;
@property (nonatomic, strong)	NSString	*members_id;
@property (nonatomic, strong)	NSString	*members_locations_id;
@property (nonatomic, strong)	NSString	*members_locations_name;
@property (nonatomic, strong)	NSString	*members_name;
@property (nonatomic, strong)	NSString	*members_users_email;
@property (nonatomic, strong)	NSString	*members_users_id;
@property (nonatomic, strong)	NSString	*members_users_name;
@property (nonatomic, strong)	NSString	*reference_num;
@property (nonatomic, strong)	NSString	*remote_id;
@property (nonatomic, strong)	NSString	*resolution;
@property (nonatomic, strong)	NSString	*scheduled_time;
@property (nonatomic, strong)   NSString    *owner_user_avatar;
@property (nonatomic, strong)	NSNumber	*status;
@property (nonatomic, strong)   NSNumber    *rating;
@property (nonatomic, strong)	NSString	*type;
@property (nonatomic, strong)	NSString	*updated;
@property (nonatomic, strong)	NSString	*xmpp_data;
@property (nonatomic, strong)   NSString    *comm_id;
@property (nonatomic, strong)   NSDictionary    *transcripts;
@property                       BOOL        isRated;
@property                       BOOL        isTemporary;


- (NSDictionary *)  dict;
- (NSString *)      displayStatus;
- (id)              initWithDictionary:(NSDictionary *)dict;
- (BOOL)            isClosed;
- (BOOL)            isOpen;
- (BOOL)            isResolved;


@end

