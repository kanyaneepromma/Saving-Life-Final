//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Serializes and deserializes glyph reference strings.
 */
@interface RBThemeGlyphReference : NSObject

/**
 *  The name of the glyph image.
 */
@property (nonatomic, nullable) NSString *imageName;

/**
 *  The reference name of the color to use for the glyph.
 */
@property (nonatomic, nullable) NSString *colorReferenceName;

/**
 *  The hexadecimal RGB/RGBA color code to use for the glyph.
 */
@property (nonatomic, nullable) NSString *colorHexCode;

/**
 *  The desired height of the glyph in pt, or `nil` to preserve the original size.
 */
@property (nonatomic, nullable) NSNumber *desiredHeight;

/**
 *  Parses the given glyph reference string, extracting the components found into
 *  the properties of the receiver.
 *
 *  @param referenceString The glyph reference string to parse.
 *  @param error           A pointer to an `NSError*` object that is assigned in the event of an error.
 */
- (void)parseReferenceString:(nonnull NSString *)referenceString error:(NSError * _Nullable * _Nullable)error;

/**
 *  The glyph reference string that describes the contents of this object.
 */
@property (nonatomic, readonly, nonnull) NSString *referenceString;

/**
 *  Whether or not the color is a reference name.
 */
@property (nonatomic, readonly) BOOL colorIsReference;

/**
 *  Whether or not this glyph reference is valid.
 */
@property (nonatomic, readonly) BOOL isValid;

/**
 *  Determines whether or not the given value is a valid glyph reference string.
 *  Also checks the object type of `value` and ignores non-strings.
 *
 *  @param value The value to check.
 *
 *  @return Whether or not the value is a valid glyph reference string.
 */
+ (BOOL)valueIsReferenceString:(nonnull id)value;

@end
