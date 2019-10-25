//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBFormValidationRule.h>

/**
 *  The type of a validation rule.
 */
typedef NS_ENUM(NSInteger, RBFormValidationRuleType) {
    /**
     *  Performs no validation.
     */
    RBFormValidationRuleTypeNone,
    
    /**
     *  Ensures that the field value is not empty. For strings this will check length > 0.
     */
    RBFormValidationRuleTypeNotEmpty,
    
    /**
     *  Ensures that the field value matches a regular expression.
     */
    RBFormValidationRuleTypeRegex,
    
    /**
     *  Ensures that the field value is within a range.
     */
    RBFormValidationRuleTypeNumericRange,
    
    /**
     *  Ensures that the field value is not below a minimum value.
     */
    RBFormValidationRuleTypeNumericMin,
    
    /**
     *  Ensures that the field value is not above a maximum value.
     */
    RBFormValidationRuleTypeNumericMax,
    
    /**
     *  Ensures that the field value image size is within a range.
     */
    RBFormValidationRuleTypeImageSizeRange,
    
    /**
     *  Ensures that the field value image size is not below a minimum size.
     */
    RBFormValidationRuleTypeImageSizeMin,
    
    /**
     *  Ensures that the field value image size is not above a maximum size.
     */
    RBFormValidationRuleTypeImageSizeMax,
    
    /**
     *  Ensures that the field value image size has a given aspect ratio.
     */
    RBFormValidationRuleTypeImageRatio,
    
    /**
     *  Ensures that the field value string length is within a range.
     */
    RBFormValidationRuleTypeStringLengthRange,
    
    /**
     *  Ensures that the field value string length is not below a given minimum.
     */
    RBFormValidationRuleTypeStringLengthMin,
    
    /**
     *  Ensures that the field value string length is not above a given maximum.
     */
    RBFormValidationRuleTypeStringLengthMax,
    
    /**
     *  Ensures that the field value array size is within a range.
     */
    RBFormValidationRuleTypeArraySizeRange,
    
    /**
     *  Ensures that the field value array size is not below a minimum size.
     */
    RBFormValidationRuleTypeArraySizeMin,
    
    /**
     *  Ensures that the field value array size is not above a maximum size.
     */
    RBFormValidationRuleTypeArraySizeMax
};

/**
 *  A managed form field validation rule schema.
 */
@interface RBFormValidationRuleSchema : NSObject <NSCopying>

/**
 *  The type of validation rule.
 */
@property (nonatomic) RBFormValidationRuleType type;

/**
 *  The failure message to use when the field is invalid.
 */
@property (nonatomic, nullable) NSString *failureMessage;

/**
 *  The validation context data.
 */
@property (nonatomic, nullable) id data;

/**
 *  Initializes a new managed form field validation rule schema with the given
 *  serialised dictionary schema.
 *
 *  @param schemaDictionary The serialised dictionary schema.
 *
 *  @return The initialized schema object.
 */
- (nonnull instancetype)initWithSchemaDictionary:(nonnull NSDictionary *)schemaDictionary;

/**
 *  Serialises the managed form field validation rule schema to a dictionary.
 *
 *  @return The serialised schema dictionary.
 */
- (nonnull NSDictionary *)schemaDictionary;

/**
 *  Creates a new `RBFormValidationRuleTypeNone` object from the schema.
 *
 *  @return The new `RBFormValidationRuleTypeNone` object.
 */
- (nullable RBFormValidationRule *)newValidationRule;

#pragma mark -
#pragma mark Factory

/**
 *  Creates a new validation rule schema that the field cannot be empty.
 *
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)nonEmptyRuleWithFailureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that applies a regular expression to the field value.
 *
 *  @param regularExpression The regular expression to match on the field value.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithRegularExpression:(nonnull NSString *)regularExpression
                           failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that ensures a numeric field has a value in the given range.
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
 *  Creates a new validation rule schema that ensures a numeric field has a minimum value.
 *
 *  @param minimumValue   The minimum value.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithNumericMinimumValue:(double)minimumValue
                             failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that ensures a numeric field has a maximum value.
 *
 *  @param maximumValue    The maximum value.
 *  @param failureMessage  The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithNumericMaximumValue:(double)maximumValue
                             failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that enforces an image size range.
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
 *  Creates a new validation rule schema that enforces a minimum image size.
 *
 *  @param minimumSize    The minimum image size.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithImageMinimumSize:(CGSize)minimumSize
                          failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that enforces a maximum image size.
 *
 *  @param maximumSize    The maximum image size.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithImageMaximumSize:(CGSize)maximumSize
                          failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that enforces an image aspect ratio.
 *
 *  @param aspectRatio    The aspect ratio required of the image.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithImageAspectRatio:(double)aspectRatio
                          failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that enforces a string length range.
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
 *  Creates a new validation rule schema that enforces a minimum string length
 *
 *  @param minimumLength  The minimum string length.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithStringLengthMinimumLength:(NSUInteger)minimumLength
                                   failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that enforces a maximum string length
 *
 *  @param maximumLength  The maximum string length.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithStringLengthMaximumLength:(NSUInteger)maximumLength
                                   failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that enforces an array count range.
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
 *  Creates a new validation rule schema that enforces a minimum array count.
 *
 *  @param minimumCount   The minimum number of elements.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithArrayCountMinimum:(NSUInteger)minimumCount
                           failureMessage:(nonnull NSString *)failureMessage;

/**
 *  Creates a new validation rule schema that enforces a maximum array count.
 *
 *  @param maximumCount   The maximum number of elements.
 *  @param failureMessage The failure message to use when the field is invalid.
 *
 *  @return The new validation rule.
 */
+ (nonnull instancetype)ruleWithArrayCountMaximum:(NSUInteger)maximumCount
                           failureMessage:(nonnull NSString *)failureMessage;

@end
