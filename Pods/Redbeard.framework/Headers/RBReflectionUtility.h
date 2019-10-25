//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Reflection utility methods.
 */
@interface RBReflectionUtility : NSObject

/**
 *  Finds the subclasses of the given type.
 *
 *  @param type The type to find subclasses for.
 *
 *  @return An array of the subclasses that were found.
 */
+ (nullable NSArray<Class> *)subclassesOf:(nonnull Class)type;

/**
 *  Finds all of the classes that match the given block.
 *
 *  @param classMatchBlock The block to determine whether a given type is acceptable.
 *
 *  @return An array of the matching classes.
 */
+ (nullable NSArray<Class> *)classesThatMatch:(nonnull BOOL(^)(Class __nonnull typeClass))classMatchBlock;

/**
 *  Creates an instance of a class (NSObject based) using the given Class type.
 *
 *  @param type The class type to create an instance of.
 *
 *  @return An instance of the class or `nil`.
 */
+ (nullable id)createInstanceOf:(nonnull Class)type;

@end
