//
//  LoginView.h
//  SupportSDK
//
//  Created by Larry Borsato on 2020-05-11.
//  Copyright © 2020 Boomtown. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Support.h"

NS_ASSUME_NONNULL_BEGIN

@interface LoginView : UIView

@property (strong, nonatomic, nullable) Support             *support;
@property (strong, nonatomic, nullable) UICollectionView    *collectionView;

@end

NS_ASSUME_NONNULL_END
