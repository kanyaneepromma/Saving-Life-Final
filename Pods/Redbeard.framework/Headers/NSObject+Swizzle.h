//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Convenience methods to swizzle instance and class selectors on `NSObject` types.
 */
@interface NSObject (Swizzle)

/**
 *  Determines whether the class method exists with the given selector.
 *
 *  @param selector The selector of the method.
 *
 *  @return Whether or not the method exists.
 */
+ (BOOL)classMethodExistsWithSelector:(SEL)selector;

/**
 *  Whether or not the instance method exists with the given selector.
 *
 *  @param selector The selector of the method.
 *
 *  @return Whether or not the method exists.
 */
+ (BOOL)methodExistsWithSelector:(SEL)selector;

/**
 *  Swizzle an instance method with another.
 *
 *  @param selectorA A selector to describe the first method.
 *  @param selectorB A selector to describe the second method.
 *
 *  @return Whether or not the operation was completed successfully.
 */
+ (BOOL)swizzleMethod:(SEL)selectorA withMethod:(SEL)selectorB;

/**
 *  Swizzle a class method with another.
 *
 *  @param selectorA A selector to describe the first method.
 *  @param selectorB A selector to describe the second method.
 *
 *  @return Whether or not the operation was completed successfully.
 */
+ (BOOL)swizzleClassMethod:(SEL)selectorA withClassMethod:(SEL)selectorB;

/**
 *  Copy an instance method to another.
 *
 *  @param selectorA A selector to describe the first method.
 *  @param selectorB A selector to describe the second method.
 *
 *  @return Whether or not the operation was completed successfully.
 */
+ (BOOL)copyMethodWithSelector:(SEL)selectorA toSelector:(SEL)selectorB;

/**
 *  Copy an class method to another.
 *
 *  @param selectorA A selector to describe the first method.
 *  @param selectorB A selector to describe the second method.
 *
 *  @return Whether or not the operation was completed successfully.
 */
+ (BOOL)copyClassMethodWithSelector:(SEL)selectorA toSelector:(SEL)selectorB;

/**
 *  Swizzle an instance method with another.
 *
 *  @param selectorA A selector to describe the first method.
 *  @param selectorB A selector to describe the second method.
 *  @param error     The error if one occurs.
 *
 *  @return Whether or not the operation was completed successfully.
 */
+ (BOOL)swizzleMethod:(SEL)selectorA withMethod:(SEL)selectorB error:(NSError **)error;

@end
