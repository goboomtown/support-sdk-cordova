//
//  TVIPcmaCodec.h
//  TwilioVideo
//
//  Copyright © 2018 Twilio, Inc. All rights reserved.
//

#import "TVIAudioCodec.h"

/**
 * @brief ITU-T standard for audio companding.
 *
 * @see [PCMA](https://en.wikipedia.org/wiki/G.711)
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_NAME(PcmaCodec)
@interface TVIPcmaCodec : TVIAudioCodec

/**
 * Initialzes an instance of the `TVIPcmaCodec` codec.
 */
- (null_unspecified instancetype)init;

@end
