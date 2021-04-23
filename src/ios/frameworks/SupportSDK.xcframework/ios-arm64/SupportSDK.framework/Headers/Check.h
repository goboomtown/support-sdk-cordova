//
//  Check.h
//  SupportSDK
//
//  Created by Larry Borsato on 2020-01-14.
//  Copyright © 2020 Boomtown. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
  * Represents the types of checks supported by the SDK.  {@link this#UNKNOWN} checks are not processed by the SDK = effectively ignored.
  */
 typedef enum  {
     UNKNOWNTYPE = -1,
     APP_HEALTH = 1,
     APP_HARDWARE = 2,
     APP_CLOUD = 3,
     APP_DUMP = 4
 } CheckType;


/**
  * Represents a check status understood by the Boomtown Cloud.
  */
//typedef enum {
//    NOT_SET = -1,
//    OK = 0,
//    UNKNOWN = 1,
//    WARNING = 2,
//    CRITICAL = 3
//} CheckStatus;

typedef NS_ENUM(unsigned long, CheckStatus) {
    NOT_SET = -1,
    OK = 0,
    UNKNOWN = 1,
    WARNING = 2,
    CRITICAL = 3
};


@interface Check : NSObject

@property                               CheckType   type;
@property (strong, nonatomic, nullable) NSString    *name;
@property                               CheckStatus checkStatus;
@property (strong, nonatomic, nullable) NSString    *checkStatusDetail;
@property (strong, nonatomic, nullable) NSMutableArray<NSFileHandle *> *files;


- (NSDictionary *) dict;
- (instancetype) initWithCheckType:(CheckType)type
             name:(NSString *)name
      checkStatus:(CheckStatus)checkStatus
                 checkStatusDetail:(NSString *)checkStatusDetail;

@end

NS_ASSUME_NONNULL_END
