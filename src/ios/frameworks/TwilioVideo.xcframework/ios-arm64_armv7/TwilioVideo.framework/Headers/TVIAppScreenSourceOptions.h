//
//  TVIAppScreenSourceOptions.h
//  TwilioVideo
//
//  Copyright © 2020 Twilio, Inc. All rights reserved.
//

#import "TVIScreenContent.h"

/**
 *  `TVIAppScreenSourceOptionsBuilder` is a builder class for `TVIAppScreenSourceOptions`.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_NAME(AppScreenSourceOptionsBuilder)
@interface TVIAppScreenSourceOptionsBuilder : NSObject

/**
 *  @brief How `TVIAppScreenSource` should optimize the video format.
 *
 *  @see TVIScreenContent
 */
@property (nonatomic) TVIScreenContent screenContent;

/**
 *  @brief You should not initialize `TVIAppScreenSourceOptionsBuilder` directly, use a `TVIAppScreenSourceOptionsBuilderBlock` instead.
 */
- (nonnull instancetype)init __attribute__((unavailable("Use a TVIAppScreenSourceOptionsBuilderBlock instead.")));

@end

/**
 *  `TVIAppScreenSourceOptionsBuilderBlock` allows you to construct `TVIAppScreenSourceOptions` using the builder pattern.
 *
 *  @param builder The builder.
 */
API_AVAILABLE(ios(11.0))
typedef void (^TVIAppScreenSourceOptionsBuilderBlock)(TVIAppScreenSourceOptionsBuilder * _Nonnull builder)
NS_SWIFT_NAME(AppScreenSourceOptionsBuilder.Block);

/**
 *  Represents immutable configuration options for a `TVIAppScreenSource`.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_NAME(AppScreenSourceOptions)
@interface TVIAppScreenSourceOptions : NSObject

/**
 *  @brief How `TVIAppScreenSource` should optimize the video format. Defaults to `TVIScreenContentDefault`.
 *
 *  @see TVIScreenContent
 */
@property (nonatomic, readonly) TVIScreenContent screenContent;

/**
 *  @brief Creates default options.
 *
 *  @return An instance of `TVIAppScreenSourceOptions`.
*/
+ (nonnull instancetype)options;

/**
 *  @brief Creates an instance of `TVIAppScreenSourceOptions` using a builder block.
 *
 *  @param block The builder block which will be used to configure the `TVIAppScreenSourceOptions` instance.
 *
 *  @return An instance of `TVIAppScreenSourceOptions`.
 */
+ (nonnull instancetype)optionsWithBlock:(nonnull TVIAppScreenSourceOptionsBuilderBlock)block;

@end
