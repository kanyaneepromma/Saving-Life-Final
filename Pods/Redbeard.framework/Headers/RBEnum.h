//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * A static class that provides enumeration string mapping.
 */
@interface RBEnum : NSObject

/**
 * Register the string mappings to an enumeration type.
 *
 * @param enumerationTypeName The name of the enumeration type.
 * @param mapping             The string to value mapping for the enumeration. Note mapping keys are lowercased.
 * @param combinations        Indicates that the mapping values maybe combined e.g. "top | left" which will be converted to UIRectEdgeTop | UIRectEdgeLeft.
 */
+ (void)registerEnumerationType:(nonnull NSString *)enumerationTypeName withMapping:(nonnull NSDictionary<NSString *, NSNumber *> *)mapping allowCombinations:(BOOL)combinations;

/**
 * Retrieve the string of the given enumeration value.
 *
 * @param value               The enumeration value to get the string for.
 * @param enumerationTypeName The name of the enumeration type.
 * @return                    The string value.
 */
+ (nullable NSString *)stringWithValue:(NSInteger)value forEnumerationType:(nonnull NSString *)enumerationTypeName;

/**
 * Retrieve the value of the given enumeration string.
 *
 * @param string              The enumeration string to get the value for.
 * @param enumerationTypeName The name of the enumeration type.
 * @return                    The value.
 */
+ (NSInteger)valueWithString:(nonnull NSString *)string forEnumerationType:(nonnull NSString *)enumerationTypeName;

/**
 * Retrieves the set of mapped enumeration strings for the given type name.
 *
 * @param enumerationTypeName The name of the enumeration type.
 * @return                    The `NSSet` of strings.
 */
+ (nullable NSSet *)stringsForEnumerationType:(nonnull NSString *)enumerationTypeName;

/**
 * Retrieves the flag determining that this enumeration can be combined.
 *
 * @param enumerationTypeName The name of the enumeration type.
 * @return                    `YES` if the enumaration allows combinations.
 */
+ (BOOL)enumerationTypeAllowsCombinations:(nonnull NSString *)enumerationTypeName;

@end
