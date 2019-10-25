//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  `UIImage` extension methods. Note the image 'scale' property is used to correctly scale/crop etc images with regards to retina screens.
 */
@interface UIImage (Extensions)

/**
 *  Creates a `UIImage` mask of the given size and individual corner radiuses.
 *
 *  @param size The size of the mask.
 *  @param tl   The corner radius of the top left corner.
 *  @param tr   The corner radius of the top right corner.
 *  @param bl   The corner radius of the bottom left corner.
 *  @param br   The corner radius of the bottom right corner.
 *
 *  @return The `UIImage` mask object.
 */
+ (UIImage *)maskWithSize:(CGSize)size
            topLeftRadius:(CGFloat)tl
           topRightRadius:(CGFloat)tr
         bottomLeftRadius:(CGFloat)bl
        bottomRightRadius:(CGFloat)br;

/**
 *  Fills all non-transparent parts of the image with the given fill color.
 *
 *  @param fillColor The color to use when filling.
 *
 *  @return The `UIImage` mask object filled with the given color.
 */
- (UIImage *)imageByFillingMaskWithColor:(UIColor *)fillColor;

/**
 *  Tints the image with the given color.
 *
 *  @param tintColor The color to tint the image with.
 *
 *  @return The tinted `UIImage` object.
 */
- (UIImage *)tintedImageWithColor:(UIColor *)tintColor;

/**
 *  Scales the `UIImage` to the given size.
 *
 *  @param newSize The size to scale the `UIImage` to.
 *
 *  @return The scaled `UIImage` object.
 */
- (UIImage *)scaledImageWithSize:(CGSize)newSize;

/**
 *  Zooms the image by the given zoom factor and then crops to maintain the original size.
 *
 *  @param zoom The zoom factor (1.0 = no change).
 *
 *  @return The zoomed and cropped `UIImage` object.
 */
- (UIImage *)croppedImageWithZoom:(CGFloat)zoom;

/**
 *  Scales the `UIImage` to fit the given bounds maintaining the aspect ratio.
 *
 *  @param bounds The bounds of the new `UIImage`.
 *
 *  @return The scaled `UIImage` object.
 */
- (UIImage *)aspectRatioImageWithBounds:(CGSize)bounds;

/**
 *  Crops the `UIImage` to the given frame.
 *
 *  @param rect The frame to crop the image to.
 *
 *  @return The cropped `UIImage` object.
 */
- (UIImage *)croppedImageWithRect:(CGRect)rect;

/**
 *  Crops the `UIImage` to a circle using the smallest dimension as the diameter.
 *
 *  @return The cropped `UIImage` object.
 */
- (UIImage *)circularCroppedImage;

/**
 *  Orientates the `UIImage` to the given orienation.
 *
 *  @param orientation  The orientation to apply.
 *
 *  @return The orientated `UIImage` object.
 */
- (UIImage *)imageWithOrientation:(UIImageOrientation)orientation;

// This decompresses/decodes the UIImage explicitly, otherwise it's done automatically
// when rendered by a control (i.e. UIImageView).  Use this method to do this yourself
// ahead of time, to prevent UI lag.

/**
 *  Decompresses and decodes the `UIImage` so that it is ready for fast use.
 *
 *  This is normally done automatically when it needs to be rendered for the first time,
 *  but it can be more efficient to do this ahead of time in a thread by using this method.
 *
 *  @param image The `UIImage` to decompress and decode.
 *
 *  @return The decompressed and decoded `UIImage` object.
 */
+ (UIImage *)decodedImageWithImage:(UIImage *)image;

@end
