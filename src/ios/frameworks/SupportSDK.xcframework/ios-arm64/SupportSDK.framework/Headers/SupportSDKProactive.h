//
//  SupportSDKProactive.h
//  SupportSDK
//
//  Created by Larry Borsato on 2020-01-14.
//  Copyright © 2020 Boomtown. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SupportSDK/Support.h>
#import <SupportSDK/Check.h>
//#import "CheckAppCloud.h"
//#import "CheckAppDump.h"
//#import "CheckAppHardware.h"
//#import "CheckAppHealth.h"

NS_ASSUME_NONNULL_BEGIN

@interface SupportSDKProactive : NSObject <SupportDelegate>

- (instancetype)    initWithConfigurationFile:(NSString *)configFileName customerInfo:(nullable NSDictionary *)customerInfo;
- (BOOL)            loadConfigurationFile:(NSString *)configFileName;
- (void)            putAppHealthCheck:(NSString *)name
                          checkStatus:(CheckStatus)checkStatus
                    checkStatusDetail:(NSString *) checkStatusDetail;

- (void)            putAppHardwareCheck:(NSString *)name
                            checkStatus:(CheckStatus)checkStatus
                      checkStatusDetail:(NSString *) checkStatusDetail;

- (void)            putAppCloudCheck:(NSString *)name
                         checkStatus:(CheckStatus)checkStatus
                   checkStatusDetail:(NSString *) checkStatusDetail;

- (void)            putAppDumpCheckWithFile:(NSFileHandle *)dumpFile
                                checkStatus:(CheckStatus)checkStatus
                          checkStatusDetail:(NSString *) checkStatusDetail;

- (void)            putAppDumpCheckWithFiles:(NSArray<NSFileHandle *> *)dumpFiles
                                 checkStatus:(CheckStatus)checkStatus
                           checkStatusDetail:(NSString *) checkStatusDetail;

@end

NS_ASSUME_NONNULL_END
