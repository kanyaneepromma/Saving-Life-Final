//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  `NSAttributedString` extensions.
 */
@interface NSAttributedString (Extensions)

/**
 * Creates a new `NSAttributedString`.
 *
 * @param string The character string.
 * @return The `NSAttributedString` object.
 */
+ (nonnull NSAttributedString *)attributedStringWithString:(nonnull NSString *)string;

/**
 * Creates a new `NSAttributedString`.
 *
 * @param string The character string.
 * @param attributes The attributes to be applied to the string.
 * @return The `NSAttributedString` object.
 */
+ (nonnull NSAttributedString *)attributedStringWithString:(nonnull NSString *)string attributes:(nullable NSDictionary<NSString *, id> *)attributes;

/**
 * Calculates the `CGSize` that would be required to render this `NSAttributedString` given the container `CGSize`.
 *
 * @param container The size in which attempt to fit the text.
 * @return The `CGSize` required to render.
 */
- (CGSize)sizeWithContainer:(CGSize)container;

/**
 * Calculates the `CGSize` that would be required to render this `NSAttributedString` given the container `CGSize`.
 *
 * @param container The size in which attempt to fit the text.
 * @param lineBreakMode The `NSLineBreakMode` to use when laying out the text.
 * @return The `CGSize` required to render.
 */
- (CGSize)sizeWithContainer:(CGSize)container lineBreakMode:(NSLineBreakMode)lineBreakMode;

/**
 * Calculates the `CGSize` that would be required to render this `NSAttributedString` given the container `CGSize`.
 *
 * @param container The size in which attempt to fit the text.
 * @param lineBreakMode The `NSLineBreakMode` to use when laying out the text.
 * @param padding The padding to apply to the container before calculating.
 * @return The `CGSize` required to render.
 */
- (CGSize)sizeWithContainer:(CGSize)container lineBreakMode:(NSLineBreakMode)lineBreakMode padding:(UIEdgeInsets)padding;

@end

//
// Quick Reference:
//
// NSFontAttributeName                  UIFont*
// NSParagraphStyleAttributeName        NSParagraphStyle
// NSForegroundColorAttributeName       UIColor*
// NSBackgroundColorAttributeName       UIColor*
// NSLigatureAttributeName              NSNumber (int)
// NSKernAttributeName                  NSNumber (float)
// NSStrikethroughStyleAttributeName    NSNumber (int) (0 = None, 1 = Single line)
// NSUnderlineStyleAttributeName        NSNumber (int) (0 = None, 1 = Single Line)
// NSStrokeColorAttributeName           UIColor*
// NSStrokeWidthAttributeName           NSNumber (float)
// NSShadowAttributeName                NSShadow
// NSVerticalGlyphFormAttributeName     NSNumber (int) (0 = Horizontal, 1 = Vertical - Not supported in iOS)
//
