//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `NSNumber` extensions.
 */
@interface NSNumber (Extensions)

/**
 * Determines if this `NSNumber` is closer to the first `NSNumber`
 * than the second.
 *
 * @param closeTo The first `NSNumber`.
 * @param farFrom The second `NSNumber`.
 * @return `true` if the first `NSNumber` is closer to the second `NSNumber`.
 */
- (BOOL)isCloserTo:(double)closeTo than:(double)farFrom;

@end
