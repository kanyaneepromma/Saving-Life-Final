//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  The base class for storing and processing a theme set.
 */
@interface RBBaseThemeSet : NSObject

/**
 *  An array of the postfix strings that serve as overrides for this platform.
 *  For example, the postfix '_iPad' will result in all keys ending with that string
 *  being chosen over those that do not.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *platformOverridePostfixes;

/**
 *  Initializes the theme set object using the given override postfixes.
 *
 *  @param platformOverridePostfixes The array of override postfix strings.
 *
 *  @return The initialized object.
 */
- (nonnull instancetype)initWithPlatformOverridePostfixes:(nullable NSArray<NSString *> *)platformOverridePostfixes;

#pragma mark -
#pragma mark Platform Overrides

/**
 *  Resolves platform overrides in the given property list.
 *
 *  @param propertyList The property list to resolve the overrides in.
 *
 *  @return The resulting property list.
 */
- (nonnull id)resolvePlatformOverridesInPropertyList:(nonnull id)propertyList;

#pragma mark -
#pragma mark Reference Strings

/**
 *  Determines whether a given string is a valid constant reference.
 *  It also checks the type of the given value, and thus anything can be passed to it.
 *
 *  @param value The value to check.
 *
 *  @return Whether or not the given value is a valid constant reference string.
 */
+ (BOOL)isReferenceString:(nonnull id)value;

/**
 *  Extracts the name that is referred to by the given
 *  reference string e.g. 'ref://color-background' > 'color-background'.
 *
 *  @param referenceString The reference string.
 *
 *  @return The extracted name.
 */
+ (nonnull NSString *)nameFromReferenceString:(nonnull NSString *)referenceString;

#pragma mark -
#pragma mark Reference Inheritance

/**
 *  Extracts the name of the reference that the dictionary should inherit from.
 *  Provides an error where one is specified but is invalid.
 *
 *  @param dictionary The dictionary to check.
 *  @param error      A pointer to an `NSError*` that will be assigned in the case of an error.
 *
 *  @return The extracted reference name, or `nil`.
 */
+ (nullable NSString *)inheritanceReferenceNameWithDictionary:(nonnull NSDictionary<NSString *, NSString *> *)dictionary error:(NSError * _Nullable * _Nullable)error;

/**
 *  Removes the inheritance key from the given dictionary.
 *
 *  @param dictionary The dictionary to remove the inheritance key from.
 *
 *  @return The resulting dictionary with the inheritance key removed.
 */
+ (nonnull NSDictionary<NSString *, NSString *> *)dictionaryByRemovingReferenceInheritanceKey:(nonnull NSDictionary<NSString *, NSString *> *)dictionary;

/**
 *  Resolves the inheritance reference of a given dictionary.
 *
 *  @param dictionary     The dictionary to resolve the inheritance reference of.
 *  @param lookup         A block that will be used to retrieve the resolved value for the given name.
 *  @param error          A pointer to an `NSError*` that will be assigned in the case of an error.
 */
+ (void)resolveInheritanceReferenceInDictionary:(nonnull NSMutableDictionary<NSString *, NSString *> *)dictionary
                                 lookup:(nonnull id __nullable (^)(NSString * __nonnull name, NSError * _Nullable * _Nullable blockError))lookup
                                          error:(NSError * _Nullable * _Nullable)error;

@end
