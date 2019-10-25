//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `NSNull` extensions.
 */
@interface NSNull (Extensions)

/**
 * Determines whether a given object is `nil` or `NSNull`.
 *
 * @param object The object to check.
 * @return Whether the object is `nil` or `NSNull`.
 */
+ (BOOL)objectIsNull:(nullable id)object;

@end
