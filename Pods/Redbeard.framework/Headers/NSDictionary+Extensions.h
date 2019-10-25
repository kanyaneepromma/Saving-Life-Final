//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/**
 *  `NSDictionary` extensions.
 */
@interface NSDictionary (Extensions)

/**
 * Creates a new dictionary by transferring values from the given dictionary using
 * the given { source key: destination key } mapping.
 *
 * @param dictionary The source dictionary to read from.
 * @param mapping The { source key: destination key } mapping.
 * @return The new dictionary.
 */
+ (nonnull instancetype)dictionaryWithDictionary:(nonnull NSDictionary *)dictionary withMapping:(nonnull NSDictionary *)mapping;

/**
 * Creates a new dictionary by using the given transformation block on each value.
 *
 * @param transformBlock The block to execute on each element of the dictionary. Returning `nil` from the block results in the key-value being removed.
 * @return The new dictionary with transformed elements.
 */
- (nonnull NSDictionary *)dictionaryByTransformingValuesWithBlock:(nonnull id __nullable (^)(NSString * __nonnull key, id __nonnull value))transformBlock;

/**
 * Gets a random key from the `NSDictionary`.
 *
 * @return The randomly chosen key.
 */
- (nullable NSString *)randomKey;

/**
 * Gets a random value from the `NSDictionary`.
 *
 * @return The randomly chosen value.
 */
- (nullable id)randomValue;

/**
 * Gets an `NSString` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (nullable NSString *)stringWithKey:(nonnull NSString *)key withDefault:(nullable NSString *)def;

/**
 * Gets an `NSString` value with the given key, or `nil` if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @return The retrieved value.
 */
- (nullable NSString *)stringWithKey:(nonnull NSString *)key;

/**
 * Gets a localized `NSString` value with the given key, or `nil` if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @return The retrieved value.
 */
- (nullable NSString *)localizedStringWithKey:(nonnull NSString *)key;

/**
 * Gets an `NSNumber` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (nullable NSNumber *)numberWithKey:(nonnull NSString *)key withDefault:(nullable NSNumber *)def;

/**
 * Gets an `NSNumber` value with the given key, or `nil` if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @return The retrieved value.
 */
- (nullable NSNumber *)numberWithKey:(nonnull NSString *)key;

/**
 * Gets an `char` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (char)charWithKey:(nonnull NSString *)key withDefault:(char)def;

/**
 * Gets an `unsigned char` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (unsigned char)unsignedCharWithKey:(nonnull NSString *)key withDefault:(unsigned char)def;

/**
 * Gets an `short` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (short)shortWithKey:(nonnull NSString *)key withDefault:(short)def;

/**
 * Gets an `unsigned short` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (unsigned short)unsignedShortWithKey:(nonnull NSString *)key withDefault:(unsigned short)def;

/**
 * Gets an `int` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (int)intWithKey:(nonnull NSString *)key withDefault:(int)def;

/**
 * Gets an `unsigned int` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (unsigned int)unsignedIntWithKey:(nonnull NSString *)key withDefault:(unsigned int)def;

/**
 * Gets an `long` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (long)longWithKey:(nonnull NSString *)key withDefault:(long)def;

/**
 * Gets an `unsigned long` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (unsigned long)unsignedLongWithKey:(nonnull NSString *)key withDefault:(unsigned long)def;

/**
 * Gets an `long long` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (long long)longLongWithKey:(nonnull NSString *)key withDefault:(long long)def;

/**
 * Gets an `unsigned long long` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (unsigned long long)unsignedLongLongWithKey:(nonnull NSString *)key withDefault:(unsigned long long)def;

/**
 * Gets an `float` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (float)floatWithKey:(nonnull NSString *)key withDefault:(float)def;

/**
 * Gets an `double` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (double)doubleWithKey:(nonnull NSString *)key withDefault:(double)def;

/**
 * Gets an `BOOL` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (BOOL)boolWithKey:(nonnull NSString *)key withDefault:(BOOL)def;

/**
 * Gets an `NSInteger` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (NSInteger)integerWithKey:(nonnull NSString *)key withDefault:(NSInteger)def;

/**
 * Gets an `NSUInteger` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (NSUInteger)unsignedIntegerWithKey:(nonnull NSString *)key withDefault:(NSUInteger)def;

/**
 * Gets an `CGSize` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (CGSize)sizeWithKey:(nonnull NSString *)key withDefault:(CGSize)def;

/**
 * Gets an `NSDate` value with the given key, or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param def The default value to return in the event of a retrieval failure.
 * @param interpretAsUniversalTime Whether the date being read is in the UTC timezone.
 * @return The retrieved value.
 */
- (nullable NSDate *)dateWithKey:(nonnull NSString *)key withDefault:(nullable NSDate *)def interpretAsUniversalTime:(BOOL)interpretAsUniversalTime;

/**
 * Gets an enumeration value for the given enumeration type with the given key,
 * or the given default value if the value could not be retrieved.
 *
 * @param key The key to lookup the value with.
 * @param enumType The name of the enumeration type to convert.
 * @param def The default value to return in the event of a retrieval failure.
 * @return The retrieved value.
 */
- (NSInteger)enumNumberWithKey:(nonnull NSString *)key enumType:(nonnull NSString *)enumType withDefault:(NSInteger)def;

/**
 * Creates a new dictionary by copying the elements from this dictionary, overriding all
 * elements with the key postfix given.
 *
 * For example, if the postfix is "iPad", { "name": "iPhone", "name_iPad": "iPad" } will be merged to
 * { "name": "iPad", "name_iPad": "iPad" }, and if `removeOverridesAfterApply` then
 * { "name": "iPad" }
 *
 * @param priorityPostfix The key postfix to denote an override.
 * @param removeOverridesAfterApply Removes the override elements (those with the postfix) after merge.
 * @return The merged dictionary.
 *
 */
- (nonnull instancetype)mergedDictionaryWithPriorityPostfix:(nonnull NSString *)priorityPostfix
                          removeOverridesAfterApply:(BOOL)removeOverridesAfterApply;

/**
 * Creates a new `NSDictionary` object by copying respectively the contents of
 * each dictionary in the array `dictionaries`.
 *
 * @param dictionaries An `NSArray` of `NSDictionary` objects.
 * @return The merged `NSDictionary`.
 */
+ (nonnull NSDictionary *)dictionaryByMergingDictionariesRespectively:(nonnull NSArray *)dictionaries;

/**
 * Creates a new `NSDictionary` object by copying respectively the contents of
 * `dictionaryA` and then `dictionaryB`.
 *
 * @param dictionaryA The first `NSDictionary` to copy.
 * @param dictionaryB The second `NSDictionary` to copy.
 * @return The merged `NSDictionary`.
 */
+ (nullable NSDictionary *)dictionaryByMergingDictionary:(nullable NSDictionary *)dictionaryA withDictionary:(nullable NSDictionary *)dictionaryB;

/**
 * Creates a new `NSDictionary` object by copying respectively the contents of
 * this `NSDictionary` and then the given `NSDictionary`.
 *
 * @param dictionary The `NSDictionary` to copy.
 * @return The merged `NSDictionary`.
 */
- (nonnull NSDictionary *)mergedDictionaryWithDictionary:(nonnull NSDictionary *)dictionary;

/**
 * Creates a new `NSDictionary` object removing all `NSNull` values.
 *
 * @param recursive Whether to recursively do the same for all child `NSDictionary` and `NSArray` values.
 * @return The new `NSDictionary` with no `NSNull` values inside.
 */
- (nonnull NSDictionary *)dictionaryWithNullsRemovedRecursive:(BOOL)recursive;

/**
 * Creates a new `NSDictionary` object by removing all keys that aren't
 * in the given array of keys.  This is done recursively to all child
 * `NSDictionary` objects too.
 *
 * @param onlyLeafKeys The keys to keep.
 * @return The new `NSDictionary`.
 */
- (nonnull NSDictionary *)prunedDictionaryWithOnlyLeafKeys:(nonnull NSArray<NSString *> *)onlyLeafKeys;

@end

/** `NSMutableDictionary` extensions. */
@interface NSMutableDictionary (Extensions)

/**
 *  Copies the value assignments from `keyedValues` to the dictionary.  If `recursive` is true
 *  this operation will also be performed on child dictionaries in the tree.
 *
 *  @param keyedValues The assignments to copy.
 *  @param recursive   Whether or not to recursively follow child dictionaries.
 */
- (void)setValuesForKeysWithDictionary:(nonnull NSDictionary *)keyedValues recursive:(BOOL)recursive;

/**
 *  Applies the given transformation block on each value.
 *  Nil values returned by `transformBlock` result in removal.
 *
 *  @param transformBlock The block to execute on each element of the dictionary. Returning `nil` from the block results in the key-value being removed.
 */
- (void)transformValuesWithBlock:(nonnull id __nullable(^)(NSString * __nonnull key, id __nonnull value))transformBlock;

/**
 *  Transfer the keys and values from the given dictionary using the given
 *  { source key: destination key } mapping.
 *
 *  @param dictionary The dictionary to transfer from.
 *  @param mapping The { source key: destination key } mapping to use.
 */
- (void)transferFromDictionary:(nonnull NSDictionary *)dictionary withMapping:(nonnull NSDictionary *)mapping;

/**
 * Removes the value for the given key from the dictionary and returns it.
 *
 * @param key The key to pop the value for.
 * @return The value that was popped with the given key.
 */
- (nullable id)popWithKey:(nonnull NSString *)key;

@end
