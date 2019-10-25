//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `NSObject` extensions.
 */
@interface NSObject (Extensions)

/**
 *  Determines whether or not the receiver has a value that is not `NSNull`.
 *
 *  @return Whether or not the object has a non-`NSNull` value.
 */
- (BOOL)isNotNil;

/**
 * Determines whether the selector given belongs to the protocol given.
 *
 * @param selector The selector to check.
 * @param protocol The protocol to check the existance of the selector in.
 * @return `true` if the selector is a member of the protocol.
 */
+ (BOOL)selectorBelongsToProtocol:(nonnull SEL)selector protocol:(nonnull Protocol *)protocol;

/**
 * Determines whether two objects are equal to each other.  Both the
 * pointer equivalence and object equality are checked.  `nil` values
 * for either or both objects are fully supported.
 *
 * @param objectA The first object to compare.
 * @param objectB The second object to compare.
 * @return `true` if the two objects are equal, `false` if not.
 */
+ (BOOL)object:(nullable id)objectA isEqualToObject:(nullable id)objectB;

/**
 * Sets the meta value of the object for the specified key.
 *
 * @param value The value to set. If a `nil` value is passed the key-value pair is removed.
 * @param key The key to set the value for.
 */
- (void)setMetaValue:(nullable id)value withKey:(nonnull NSString *)key;

/**
 * Gets the meta value of the object for the specified key.  Returns
 * `nil` if a value does not exist for the key.
 *
 * @param key The key to retrieve the value for.
 * @return The retrieved value, or `nil` if it does not exist.
 */
- (nullable id)metaValueForKey:(nonnull NSString *)key;

@end
