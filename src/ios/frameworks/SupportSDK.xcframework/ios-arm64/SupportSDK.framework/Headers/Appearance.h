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


@interface Appearance : NSObject

@property                                 BOOL       darkMode;
@property                                   BOOL       transparentMode;
@property (strong, nonatomic, nullable)          UIColor    *labelColor;
@property (strong, nonatomic, nullable)            UIColor    *placeholderTextColor;
@property (strong, nonatomic, nullable)            UIColor    *systemBackgroundColor;
@property (strong, nonatomic, nullable)            UIColor    *secondarySystemBackgroundColor;
@property ( nonatomic, assign)            UIColor    *separatorColor;
@property ( nonatomic, assign)            UIColor    *linkColor;
@property ( nonatomic, assign)            UIColor    *darkTextColor;
@property ( nonatomic, assign)            UIColor    *lightTextColor;
@property ( nonatomic, assign)            UIColor    *badgeBackgroundColor;
//@property (strong, nonatomic, nullable)            UIColor    *navigationBarBackgroundColor;


@property (strong, nonatomic, nullable)            UIColor    *homeBackgroundColor;
@property (strong, nonatomic, nullable)            UIColor    *linkAndButtonTintColor;

@property (strong, nonatomic, nullable) UIColor    *redRatingControlColor;
@property (strong, nonatomic, nullable) UIColor    *yellowRatingControlColor;
@property (strong, nonatomic, nullable) UIColor    *greenRatingControlColor;

@property ( nonatomic, assign, readonly)  UIColor    *canceledServiceHistoryFooterColor;
@property ( nonatomic, assign, readonly)  UIColor    *completedServiceHistoryFooterColor;
@property ( nonatomic, assign, readonly)  UIColor    *inProgressServiceHistoryFooterColor;

@property ( nonatomic, assign, readonly)  UIImage    *canceledServiceHistoryFooterIcon;
@property ( nonatomic, assign, readonly)  UIImage    *completedServiceHistoryFooterIcon;
@property ( nonatomic, assign, readonly)  UIImage    *inProgressServiceHistoryFooterIcon;
@property ( nonatomic, assign, readonly)  UIImage    *starOffIcon;
@property ( nonatomic, assign, readonly)  UIImage    *starOnIcon;

@property ( nonatomic, assign)            UIImage    *logo;

@property ( nonatomic, assign, readonly)  UIColor    *sliderOnColor;
@property ( nonatomic, assign, readonly)  UIColor    *sliderOffColor;
@property ( nonatomic, assign, readonly)  UIColor    *sliderTextColor;
@property ( nonatomic, assign, readonly)  UIColor    *sliderBorderColor;
@property ( nonatomic, assign, readonly)  UIColor    *sliderHandleBackgroundColor;
@property ( nonatomic, assign, readonly)  UIColor    *sliderHandleTextColor;

@property ( nonatomic, assign, readonly)  UIFont     *sliderTextIPadFont;
@property ( nonatomic, assign, readonly)  UIFont     *sliderTextIPhoneFont;

//  Branding colors
@property ( readonly)                     UIColor     *iconColor;
@property ( readonly)                     UIColor     *buttonColor;
@property ( readonly)                     UIColor     *lineColor;
@property ( readonly)                     UIColor     *textColor;
@property (strong, nonatomic, nullable, readonly)                     UIColor     *loginBackgroundColor;
@property ( readonly)                     UIColor     *loginFieldBorderColor;
@property ( readonly)                     UIColor     *loginFieldBackgroundColor;
@property ( readonly)                     UIColor     *loginFieldTextColor;
@property ( readonly)                     UIColor     *loginButtonColor;
@property ( readonly)                     CGFloat     loginFieldTextFontSize;
@property ( readonly)                     UIColor     *homeIconColor;
@property ( readonly)                     UIColor     *homeLineColor;
@property ( readonly)                     NSString    *homeFontName;
@property ( readonly)                     UIColor     *homeTextColor;
@property ( readonly)                     UIColor     *homeSelectedColor;
@property ( readonly)                     UIColor     *callMeHeaderTextColor;
@property ( readonly)                     UIColor     *callMeLabelTextColor;
@property ( readonly)                     NSString    *callMeFontName;
@property ( readonly)                     UIColor     *callMeHintTextColor;
@property ( readonly)                     UIColor     *callMeButtonTextColor;
@property ( readonly)                     UIColor     *callMeButtonBackgroundColor;
@property ( readonly)                     UIColor     *ratingHeaderTextColor;
@property ( readonly)                     UIColor     *ratingLabelTextColor;
@property ( readonly)                     NSString    *ratingFontName;
@property ( readonly)                     UIColor     *ratingHintTextColor;
@property ( readonly)                     UIColor     *ratingButtonTextColor;
@property ( readonly)                     UIColor     *ratingButtonBackgroundColor;
@property ( readonly)                     UIColor     *chatRefidTextColor;
@property ( readonly)                     NSString    *chatFontName;
@property ( readonly)                     UIColor     *chatNavBarColor;
@property ( readonly)                     UIColor     *chatSendButtonEnabledColor;
@property ( readonly)                     UIColor     *chatSendButtonDisabledColor;
@property ( readonly)                     UIColor     *chatTimeStampColor;
@property ( readonly)                     UIColor     *chatActionButtonTextColor;
@property ( readonly)                     UIColor     *chatActionButtonSelectedTextColor;
@property ( readonly)                     UIColor     *chatActionButtonBorderColor;
@property ( readonly)                     UIColor     *chatIconColor;
@property ( readonly)                     CGFloat     chatAttachmentIconHeight;
@property ( readonly)                     UIColor     *kbFolderNameTextColor;
@property ( readonly)                     UIColor     *kbFolderL0BackgroundColor;
@property ( readonly)                     NSString    *kbFontName;
@property ( readonly)                     UIColor     *kbTextColor;

@property ( readonly)                     NSString    *chatMenuText;
@property ( readonly)                     UIImage     *chatMenuIcon;
@property ( readonly)                     NSString     *callMeMenuText;
@property ( readonly)                     UIImage     *callMeMenuIcon;
@property ( readonly)                     NSString     *knowledgeMenuText;
@property ( readonly)                     UIImage     *knowledgeMenuIcon;
@property ( readonly)                     NSString     *webMenuText;
@property ( readonly)                     UIImage     *webMenuIcon;
@property ( readonly)                     NSString     *emailMenuText;
@property ( readonly)                     UIImage     *emailMenuIcon;
@property ( readonly)                     NSString     *phoneMenuText;
@property ( readonly)                     UIImage     *phoneMenuIcon;
@property ( readonly)                     NSString     *formsMenuText;
@property ( readonly)                     UIImage     *formsMenuIcon;
@property ( readonly)                     NSString     *historyMenuText;
@property ( readonly)                     UIImage     *historyMenuIcon;
@property ( readonly)                     NSString     *exitMenuText;
@property ( readonly)                     UIImage     *exitMenuIcon;


@property ( readonly)                     UIColor *navigationBarTextColor;
@property ( readonly)                     UIColor *navigationBarBackgroundColor;
@property ( readonly)                     UIColor *navigationBarIconColor;

@property ( readonly)                     NSString  *menuStyle;
@property ( readonly)                     NSString  *menuHeading;
@property ( readonly)                     CGFloat   menuTextSize;
@property ( readonly)                     NSString  *menuTextStyle;
@property ( readonly)                     UIColor   *menuTextColor;
@property ( readonly)                     UIColor   *menuIconColor;
@property ( readonly)                     UIColor   *menuBorderColor;
@property ( readonly)                     CGFloat   menuBorderWidth;
@property ( readonly)                     CGFloat   menuPadding;
@property ( readonly)                     CGFloat   menuSpacing;

@property ( readonly)                     NSString  *formCancelButtonText;
@property ( readonly)                     NSString  *formSaveButtonText;
@property ( readonly)                     CGFloat   formSpacing;
@property ( readonly)                     UIColor   *formEntryBorderColor;
@property ( readonly)                     UIColor   *formEntryBorderColorDark;
@property ( readonly)                     CGFloat   formEntryBorderWidth;
@property ( readonly)                     UIColor   *formEntryTextColor;
@property ( readonly)                     UIColor   *formEntryTextColorDark;
@property ( readonly)                     CGFloat   formEntryTextSize;
@property ( readonly)                     NSString  *formEntryTextStyle;
@property ( readonly)                     UIColor   *formLabelRequiredIndicatorColor;
@property ( readonly)                     UIColor   *formLabelRequiredIndicatorColorDark;
@property ( readonly)                     UIColor   *formLabelRequiredTextColor;
@property ( readonly)                     UIColor   *formLabelRequiredTextColorDark;
@property ( readonly)                     UIColor   *formLabelTextColor;
@property ( readonly)                     UIColor   *formLabelTextColorDark;
@property ( readonly)                     CGFloat   formLabelTextSize;
@property ( readonly)                     NSString  *formLabelTextStyle;

@property ( nonatomic, assign)            UIImage     *kbFolderIcon;
@property ( nonatomic, assign)            UIImage     *chatAttachmentButtonImage;
@property ( nonatomic, assign)            UIImage     *chatSendButtonImage;


- (void)            configure;
- (NSError *)       configureWithJSON:(NSString *)jsonString;
- (UIColor *)       getColor:(NSUInteger)color;
- (NSString *)      getJSONFromFile:(NSString *)filename;
- (void)            handleTraits:(UITraitCollection *)traitCollection;
- (void)            setup;


- (BOOL) hasMenuBorder;

@end

NS_ASSUME_NONNULL_END
