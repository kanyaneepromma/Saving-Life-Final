//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  A regular expression to match a valid e-mail address.
 */
extern NSString * __nonnull const RBRegexEmailAddress;

/**
 *  A validation rule for a managed form field.
 */
@interface RBFormValidationRule : NSObject

/**
 *  The validation rule context data.
 */
@property (nonatomic, readonly, nullable) id data;

/**
 *  The failure message to be used when the field is invalid.
 */
@property (nonatomic, readonly, nullable) NSString *failureMessage;

/**
 *  Creates a new validation rule that uses a custom block.
 *
 *  @param validationBlock The custom block to call on the value to determine whether it's valid.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithValidationBlock:(nonnull BOOL(^)(id __nullable value))validationBlock
                         failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that the field cannot be empty.
 *
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)nonEmptyRuleWithFailureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that applies a regular expression to the field value.
 *
 *  @param regularExpression The regular expression to match on the field value.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithRegularExpression:(nonnull NSString *)regularExpression
                           failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that ensures a numeric field has a value in the given range.
 *
 *  @param minimumValue    The minimum value.
 *  @param maximumValue    The maximum value.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithNumericRangeFrom:(double)minimumValue
                                      to:(double)maximumValue
                          failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that ensures a numeric field has a minimum value.
 *
 *  @param minimumValue   The minimum value.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithNumericMinimumValue:(double)minimumValue
                             failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that ensures a numeric field has a maximum value.
 *
 *  @param maximumValue    The maximum value.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithNumericMaximumValue:(double)maximumValue
                             failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces an image size range.
 *
 *  @param minimumSize    The minimum image size.
 *  @param maximumSize    The maximum image size.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithImageSizeRangeFrom:(CGSize)minimumSize
                                        to:(CGSize)maximumSize
                            failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces a minimum image size.
 *
 *  @param minimumSize    The minimum image size.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithImageMinimumSize:(CGSize)minimumSize
                          failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces a maximum image size.
 *
 *  @param maximumSize    The maximum image size.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithImageMaximumSize:(CGSize)maximumSize
                          failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces an image aspect ratio.
 *
 *  @param aspectRatio    The aspect ratio required of the image.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithImageAspectRatio:(double)aspectRatio
                          failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces a string length range.
 *
 *  @param minimumLength  The minimum string length.
 *  @param maximumLength  The maximum string length.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithStringLengthRangeFrom:(NSUInteger)minimumLength
                                           to:(NSUInteger)maximumLength
                               failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces a minimum string length
 *
 *  @param minimumLength  The minimum string length.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithStringLengthMinimumLength:(NSUInteger)minimumLength
                                   failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces a maximum string length
 *
 *  @param maximumLength  The maximum string length.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithStringLengthMaximumLength:(NSUInteger)maximumLength
                                   failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces an array count range.
 *
 *  @param minimumCount   The minimum number of elements.
 *  @param maximumCount   The maximum number of elements.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithArrayCountRangeFrom:(NSUInteger)minimumCount
                                         to:(NSUInteger)maximumCount
                             failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces a minimum array count.
 *
 *  @param minimumCount   The minimum number of elements.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithArrayCountMinimum:(NSUInteger)minimumCount
                           failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule that enforces a maximum array count.
 *
 *  @param maximumCount   The maximum number of elements.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithArrayCountMaximum:(NSUInteger)maximumCount
                           failureMessage:(nonnull NSString *)failureMessage;


/**
 *  Runs the validation checks on the given value.
 *
 *  @param value The value to validate.
 *
 *  @return Whether or not the value was found to be valid.
 */
- (BOOL)valueIsValid:(nullable id)value;

@end

