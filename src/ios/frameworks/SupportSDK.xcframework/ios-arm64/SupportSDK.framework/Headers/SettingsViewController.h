//
//  SettingsViewController.h
//  SupportSDK
//
//  Created by Larry Borsato on 2021-06-25.
//  Copyright © 2021 Boomtown. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SupportSDK/Support.h>


@class BarcodeViewController;
@protocol BarcodeViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

@interface SettingsViewController : UITableViewController <UITableViewDelegate, UIPickerViewDataSource, UIPickerViewDelegate, BarcodeViewControllerDelegate>

@property Support *support;

- (void) changeDeveloperMode;
- (BOOL) isDeveloperMode;

@end

NS_ASSUME_NONNULL_END
