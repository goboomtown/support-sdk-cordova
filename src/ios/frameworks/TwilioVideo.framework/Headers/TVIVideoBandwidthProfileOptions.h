//
//  TVIVideoBandwidthProfileOptions.h
//  TwilioVideo
//
//  Copyright © 2020 Twilio, Inc. All rights reserved.
//

#import "TVITrackPriority.h"

#pragma mark - TVIBandwidthProfileMode
/**
 *  TVIBandwidthProfileMode specifies how `TVIRemoteVideoTrack`(s) TrackPriority values
 *  are mapped to bandwidth allocation in Group Rooms.
 */
typedef NSString * TVIBandwidthProfileMode NS_STRING_ENUM
NS_SWIFT_NAME(BandwidthProfileMode);
/**
 *  This mode is for use cases where some `TVIRemoteVideoTrack`(s) are more prioritized over others. However,
 *  the lower priority `TVIRemoteVideoTrack`s still need to be visible. The bandwidth allocation algorithm will
 *  distribute the available downlink bandwidth proportional to the requested VideoRenderDimensions. In case of low
 *  downlink bandwidth, the quality of higher priority `TVIRemoteVideoTrack`s may be degraded to avoid switching off
 *  lower priority `TVIRemoteVideoTrack`(s).
 */
FOUNDATION_EXPORT _Nonnull TVIBandwidthProfileMode const TVIBandwidthProfileModeCollaboration;
/**
 *  This mode is for use cases where all the subscribed `TVIRemoteVideoTrack`s are equally important. The bandwidth
 *  allocation algorithm will share the available downlink bandwidth equally among the subscribed `TVIRemoteVideoTrack`(s).
 */
FOUNDATION_EXPORT _Nonnull TVIBandwidthProfileMode const TVIBandwidthProfileModeGrid;
/**
 *  This mode is for use cases where some `TVIRemoteVideoTrack`s are deemed critical and must be preserved at any cost
 *  over the other `TVIRemoteVideoTrack`s. The bandwidth allocation algorithm will allocate as big a share of the
 *  available downlink bandwidth as it possibly can to the higher priority `TVIRemoteVideoTrack`s, and only then consider
 *  the lower priority `TVIRemoteVideoTrack`s. In case of low downlink bandwidth, the lower priority `TVIRemoteVideoTrack`s
 *  are switched off in order to preserve the quality of the higher priority `TVIRemoteVideoTrack`(s).
 */
FOUNDATION_EXPORT _Nonnull TVIBandwidthProfileMode const TVIBandwidthProfileModePresentation;


#pragma mark - TVITrackSwitchOffMode

/**
 *  TVITrackSwitchOffMode represents the possible modes of behavior of the Track switch-off mechanism.
 */
typedef NSString * TVITrackSwitchOffMode NS_STRING_ENUM
NS_SWIFT_NAME(Track.SwitchOffMode);
/**
 *  In this mode, Tracks are never switched off.
 */
FOUNDATION_EXPORT _Nonnull TVITrackSwitchOffMode const TVITrackSwitchOffModeDisabled;
/**
 *  In this mode, Tracks are pro-actively switched off when network congestion is predicted by the bandwidth
 *  estimation mechanism.
 */
FOUNDATION_EXPORT _Nonnull TVITrackSwitchOffMode const TVITrackSwitchOffModePredicted;
/**
 *  In this mode, Tracks are switched off only when network congestion is detected.
 */
FOUNDATION_EXPORT _Nonnull TVITrackSwitchOffMode const TVITrackSwitchOffModeDetected;


#pragma mark - TVIVideoDimensions

/**
 *  TVIVideoDimensions represents dimensions for a VideoTrack.
 */
NS_SWIFT_NAME(VideoDimensions)
@interface TVIVideoDimensions : NSObject

/**
 *  @brief The video width.
 */
@property (nonatomic, assign) NSUInteger width;

/**
 *  @brief The video height.
 */
@property (nonatomic, assign) NSUInteger height;

/**
 *  @brief Creates an instance of `TVIVideoDimensions`.
 *
 *  @param width The video width.
 *  @param height The video height.
 *
 *  @return An instance of `TVIVideoDimensions`.
 */
+ (nonnull instancetype)dimensionsWithWidth:(NSUInteger)width height:(NSUInteger)height;

/**
 *  @brief Developers shouldn't initialize this class directly.
 *
 *  @discussion Use the class methods `dimensionsWithWidth:height:` instead.
 */
- (null_unspecified instancetype)init __attribute__((unavailable("Use `dimensionsWithWidth:height` instead.")));

@end


#pragma mark - TVIVideoRenderDimensions

/**
 *  TVIVideoRenderDimensions represents dimensions for a VideoTrack.
 *
 *  @discussion TVIVideoRenderDimensions allows you to specify the desired render dimensions
 *  of `TVIRemoteVideoTrack`s based on TrackPriority and the `TVIRemoteVideoTrack`s of the Dominant Speaker. The bandwidth
 *  allocation algorithm will distribute the available downlink bandwidth proportional to the requested render dimensions.
 */
NS_SWIFT_NAME(VideoRenderDimensions)
@interface TVIVideoRenderDimensions : NSObject

/**
 *  @brief VideoDimensions for low priority Tracks.
 */
@property (nonatomic, strong, nullable) TVIVideoDimensions *low;

/**
 *  @brief VideoDimensions for track priority standard.
 */
@property (nonatomic, strong, nullable) TVIVideoDimensions *standard;

/**
 *  @brief VideoDimensions for track priority high.
 */
@property (nonatomic, strong, nullable) TVIVideoDimensions *high;

@end


#pragma mark - TVIVideoBandwidthProfileOptionsBuilder

/**
 *  `TVIVideoBandwidthProfileOptionsBuilder` is a builder for `TVIVideoBandwidthProfileOptions`.
 */
NS_SWIFT_NAME(VideoBandwidthProfileOptionsBuilder)
@interface TVIVideoBandwidthProfileOptionsBuilder : NSObject

/**
 *  @brief Optional property to specify the default TrackPriority of the Dominant Speaker's `TVIRemoteVideoTrack`(s).
 */
@property (nonatomic, copy, nullable) TVITrackPriority dominantSpeakerPriority;

/**
 *  @brief Optional property to specify the maximum downlink video bandwidth in Kilobits per second (Kbps).
 *
 *  @discussion The maximum bitrate for subscribed `TVIRemoteVideoTrack`s, or none to allow
 *  the maximum possible in the Room. The default is 2,400 Kbps.
 */
@property (nonatomic, strong, nullable) NSNumber *maxSubscriptionBitrate;

/**
 *  @brief Optional property to specify the maximum number of visible `TVIRemoteVideoTrack`s selected
 *  first using TrackPriority and second using an N-Loudest policy.
 *
 *  @discussion The maximum number of video tracks. By default there are no limits on the number of
 *  visible `TVIRemoteVideoTrack`s.
 */
@property (nonatomic, strong, nullable) NSNumber *maxTracks;

/**
 *  @brief Optional property to specify how `TVIRemoteVideoTrack`s TrackPriority values are mapped to bandwidth
 *  allocation in Group Rooms.
 */
@property (nonatomic, copy, nullable) TVIBandwidthProfileMode mode;

/**
 *  @brief VideoRenderDimensions allows you to specify the desired render dimensions of `TVIRemoteVideoTrack`s
 *  based on TrackPriority and the `TVIRemoteVideoTrack`s of the Dominant Speaker. The bandwidth allocation algorithm
 *  will distribute the available downlink bandwidth proportional to the requested render dimensions.
 */
@property (nonatomic, strong, nullable) TVIVideoRenderDimensions *renderDimensions;

/**
 *  @brief Optional property to configure how `TVIRemoteVideoTrack`(s) are switched off.
 */
@property (nonatomic, copy, nullable) TVITrackSwitchOffMode trackSwitchOffMode;

/**
 *  @brief You should not initialize `TVIVideoBandwidthProfileOptionsBuilder` directly, use a `TVIVideoBandwidthProfileOptionsBuilderBlock` instead.
 */
- (null_unspecified instancetype)init __attribute__((unavailable("Use a `TVIVideoBandwidthProfileOptionsBuilderBlock` instead.")));

@end

#pragma mark - TVIVideoBandwidthProfileOptionsBuilderBlock

/**
 *  `TVIVideoBandwidthProfileOptionsBuilderBlock` allows you to construct `TVIVideoBandwidthProfileOptions` using the builder pattern.
 *
 *  @param builder The builder.
 */
typedef void (^TVIVideoBandwidthProfileOptionsBuilderBlock)(TVIVideoBandwidthProfileOptionsBuilder * _Nonnull builder)
NS_SWIFT_NAME(VideoBandwidthProfileOptions.BuilderBlock);

# pragma mark - TVIVideoBandwidthProfileOptions

/**
 *  VideoBandwidthProfileOptions enables you to configure how available bandwidth is shared among the
 *  `TVIRemoteVideoTrack`(s) in a Group Room.
*/
NS_SWIFT_NAME(VideoBandwidthProfileOptions)
@interface TVIVideoBandwidthProfileOptions : NSObject

/**
 *  @brief Optional property to specify the default TrackPriority of the Dominant Speaker's `TVIRemoteVideoTrack`(s).
 */
@property (nonatomic, copy, readonly, nullable) TVITrackPriority dominantSpeakerPriority;

/**
 *  @brief Optional property to specify the maximum downlink video bandwidth in Kilobits per second (Kbps).
 *
 *  @discussion The maximum bitrate for subscribed `TVIRemoteVideoTrack`s, or none to allow
 *  the maximum possible in the Room. The default is 2,400 Kbps.
 */
@property (nonatomic, strong, readonly, nullable) NSNumber *maxSubscriptionBitrate;

/**
 *  @brief Optional property to specify the maximum number of visible `TVIRemoteVideoTrack`s selected
 *  first using TrackPriority and second using an N-Loudest policy.
 *
 *  @discussion The maximum number of video tracks. By default there are no limits on the number of
 *  visible `TVIRemoteVideoTrack`s.
 */
@property (nonatomic, strong, readonly, nullable) NSNumber *maxTracks;

/**
 *  @brief Optional property to specify how `TVIRemoteVideoTrack`s TrackPriority values are mapped to bandwidth
 *  allocation in Group Rooms.
 */
@property (nonatomic, copy, readonly, nullable) TVIBandwidthProfileMode mode;

/**
 *  @brief VideoRenderDimensions allows you to specify the desired render dimensions of `TVIRemoteVideoTrack`s
 *  based on TrackPriority and the `TVIRemoteVideoTrack`s of the Dominant Speaker. The bandwidth allocation algorithm
 *  will distribute the available downlink bandwidth proportional to the requested render dimensions.
 */
@property (nonatomic, strong, readonly, nullable) TVIVideoRenderDimensions *renderDimensions;

/**
 *  @brief Optional property to configure how `TVIRemoteVideoTrack`(s) are switched off.
 */
@property (nonatomic, copy, readonly, nullable) TVITrackSwitchOffMode trackSwitchOffMode;

/**
 *  @brief Creates an instance of `TVIVideoBandwidthProfileOptions` using a builder block.
 *
 *  @param block The builder block which will be used to configure the `TVIVideoBandwidthProfileOptions` instance.
 *
 *  @return An instance of `TVIVideoBandwidthProfileOptions`.
 */
+ (nonnull instancetype)optionsWithBlock:(nonnull TVIVideoBandwidthProfileOptionsBuilderBlock)block;

/**
 *  @brief Developers shouldn't initialize this class directly.
 *
 *  @discussion Use the class methods `optionsWithBlock:` instead.
 */
- (null_unspecified instancetype)init __attribute__((unavailable("Use optionsWithBlock: to create a TVIVideoBandwidthProfileOptions instance.")));

@end
