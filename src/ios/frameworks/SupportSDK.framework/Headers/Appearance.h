//
//  Appearance.h
//  BoomtownConnect
//
//  Created by Larry Borsato on 2019-08-08.
//  Copyright © 2019 BOOMTOWN. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

static NSString * const kMenuTextChat       = @"com.goboomtown.supportsdk.menu.text.chat";
static NSString * const kMenuIconChat       = @"com.goboomtown.supportsdk.menu.icon.chat";
static NSString * const kMenuTextCallMe     = @"com.goboomtown.supportsdk.menu.text.callme";
static NSString * const kMenuIconCallMe     = @"com.goboomtown.supportsdk.menu.icon.callme";
static NSString * const kMenuTextKnowledge  = @"com.goboomtown.supportsdk.menu.text.knowledge";
static NSString * const kMenuIconKnowledge  = @"com.goboomtown.supportsdk.menu.icon.knowledge";
static NSString * const kMenuTextWeb        = @"com.goboomtown.supportsdk.menu.text.web";
static NSString * const kMenuIconWeb        = @"com.goboomtown.supportsdk.menu.icon.web";
static NSString * const kMenuTextEmail      = @"com.goboomtown.supportsdk.menu.text.email";
static NSString * const kMenuIconEmail      = @"com.goboomtown.supportsdk.menu.icon.email";
static NSString * const kMenuTextPhone      = @"com.goboomtown.supportsdk.menu.text.phone";
static NSString * const kMenuIconPhone      = @"com.goboomtown.supportsdk.menu.icon.phone";
static NSString * const kMenuTextForms      = @"com.goboomtown.supportsdk.menu.text.forms";
static NSString * const kMenuIconForms      = @"com.goboomtown.supportsdk.menu.icon.forms";
static NSString * const kMenuTextHistory    = @"com.goboomtown.supportsdk.menu.text.history";
static NSString * const kMenuIconHistory    = @"com.goboomtown.supportsdk.menu.icon.history";
static NSString * const kMenuTextExit       = @"com.goboomtown.supportsdk.menu.text.exit";
static NSString * const kMenuIconExit       = @"com.goboomtown.supportsdk.menu.icon.exit";
static NSString * const kMenuBorderColor    = @"com.goboomtown.supportsdk.menu.border.color";


@interface Appearance : NSObject

@property (class, assign)                       BOOL       darkMode;
@property (class, assign)                       BOOL       transparentMode;
@property (class, assign)                       NSDictionary    *menuConfiguration;
@property (class, nonatomic, assign)            UIColor    *labelColor;
@property (class, nonatomic, assign)            UIColor    *placeholderTextColor;
@property (class, nonatomic, assign)            UIColor    *systemBackgroundColor;
@property (class, nonatomic, assign)            UIColor    *secondarySystemBackgroundColor;
@property (class, nonatomic, assign)            UIColor    *separatorColor;
@property (class, nonatomic, assign)            UIColor    *linkColor;
@property (class, nonatomic, assign)            UIColor    *darkTextColor;
@property (class, nonatomic, assign)            UIColor    *lightTextColor;
@property (class, nonatomic, assign)            UIColor    *badgeBackgroundColor;
@property (class, nonatomic, assign)            UIColor    *navigationBarBackgroundColor;


@property (class, nonatomic, assign)            UIColor    *homeBackgroundColor;
@property (class, nonatomic, assign)            UIColor    *linkAndButtonTintColor;

@property (class, nonatomic, assign, readonly)  UIColor    *redRatingControlColor;
@property (class, nonatomic, assign, readonly)  UIColor    *yellowRatingControlColor;
@property (class, nonatomic, assign, readonly)  UIColor    *greenRatingControlColor;

@property (class, nonatomic, assign, readonly)  UIColor    *canceledServiceHistoryFooterColor;
@property (class, nonatomic, assign, readonly)  UIColor    *completedServiceHistoryFooterColor;
@property (class, nonatomic, assign, readonly)  UIColor    *inProgressServiceHistoryFooterColor;

@property (class, nonatomic, assign, readonly)  UIImage    *canceledServiceHistoryFooterIcon;
@property (class, nonatomic, assign, readonly)  UIImage    *completedServiceHistoryFooterIcon;
@property (class, nonatomic, assign, readonly)  UIImage    *inProgressServiceHistoryFooterIcon;
@property (class, nonatomic, assign, readonly)  UIImage    *starOffIcon;
@property (class, nonatomic, assign, readonly)  UIImage    *starOnIcon;

@property (class, nonatomic, assign)            UIImage    *logo;

@property (class, nonatomic, assign, readonly)  UIColor    *sliderOnColor;
@property (class, nonatomic, assign, readonly)  UIColor    *sliderOffColor;
@property (class, nonatomic, assign, readonly)  UIColor    *sliderTextColor;
@property (class, nonatomic, assign, readonly)  UIColor    *sliderBorderColor;
@property (class, nonatomic, assign, readonly)  UIColor    *sliderHandleBackgroundColor;
@property (class, nonatomic, assign, readonly)  UIColor    *sliderHandleTextColor;

@property (class, nonatomic, assign, readonly)  UIFont     *sliderTextIPadFont;
@property (class, nonatomic, assign, readonly)  UIFont     *sliderTextIPhoneFont;

//  Branding colors
@property (class, readonly)                     UIColor     *loginBackgroundColor;
@property (class, readonly)                     UIColor     *loginFieldBorderColor;
@property (class, readonly)                     UIColor     *loginFieldBackgroundColor;
@property (class, readonly)                     UIColor     *loginFieldTextColor;
@property (class, readonly)                     UIColor     *loginButtonColor;
@property (class, readonly)                     CGFloat     loginFieldTextFontSize;
@property (class, readonly)                     UIColor     *homeIconColor;
@property (class, readonly)                     UIColor     *homeLineColor;
@property (class, readonly)                     UIColor     *homeFontName;
@property (class, readonly)                     UIColor     *homeTextColor;
@property (class, readonly)                     UIColor     *homeSelectedColor;
@property (class, readonly)                     UIColor     *callMeHeaderTextColor;
@property (class, readonly)                     UIColor     *callMeLabelTextColor;
@property (class, readonly)                     UIColor     *callMeFontName;
@property (class, readonly)                     UIColor     *callMeHintTextColor;
@property (class, readonly)                     UIColor     *callMeButtonTextColor;
@property (class, readonly)                     UIColor     *callMeButtonBackgroundColor;
@property (class, readonly)                     UIColor     *ratingHeaderTextColor;
@property (class, readonly)                     UIColor     *ratingLabelTextColor;
@property (class, readonly)                     UIColor     *ratingFontName;
@property (class, readonly)                     UIColor     *ratingHintTextColor;
@property (class, readonly)                     UIColor     *ratingButtonTextColor;
@property (class, readonly)                     UIColor     *ratingButtonBackgroundColor;
@property (class, readonly)                     UIColor     *chatRefidTextColor;
@property (class, readonly)                     UIColor     *chatFontName;
@property (class, readonly)                     UIColor     *chatNavBarColor;
@property (class, readonly)                     UIColor     *chatSendButtonEnabledColor;
@property (class, readonly)                     UIColor     *chatSendButtonDisabledColor;
@property (class, readonly)                     UIColor     *chatTimeStampColor;
@property (class, readonly)                     UIColor     *chatActionButtonTextColor;
@property (class, readonly)                     UIColor     *chatActionButtonSelectedTextColor;
@property (class, readonly)                     UIColor     *chatActionButtonBorderColor;
@property (class, readonly)                     UIColor     *chatIconColor;
@property (class, readonly)                     CGFloat     chatAttachmentIconHeight;
@property (class, readonly)                     UIColor     *kbFolderNameTextColor;
@property (class, readonly)                     UIColor     *kbFolderL0BackgroundColor;
@property (class, readonly)                     UIColor     *kbFontName;
@property (class, readonly)                     UIColor     *kbTextColor;

@property (class, nonatomic, assign)            UIImage     *kbFolderIcon;
@property (class, nonatomic, assign)            UIImage     *chatAttachmentButtonImage;
@property (class, nonatomic, assign)            UIImage     *chatSendButtonImage;


+ (void) configure;
+ (void) handleTraits:(UITraitCollection *)traitCollection;
+ (void) setup;

+ (void) setIconColor:(NSInteger)colorValue;
+ (void) setTextColor:(NSInteger)colorValue;
+ (void) setDisabledColor:(NSInteger)colorValue;
+ (void) setBackgroundColor:(NSInteger)colorValue;
+ (void) setBorderColor:(NSInteger)colorValue;

+ (NSDictionary *) menuConfiguration;
+ (void) setMenuConfiguration:(NSDictionary *)menuConfiguration;

@end

NS_ASSUME_NONNULL_END
