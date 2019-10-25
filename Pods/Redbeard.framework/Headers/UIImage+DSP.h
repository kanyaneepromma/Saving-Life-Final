//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `UIImage` Digital Sign Processing (DSP) methods.
 */
@interface UIImage (DSP)

/**
 *  Applies a 3x3 gaussian blur effect to the image.
 *
 *  @return The new `UIImage` with the effect applied.
 */
- (UIImage *)imageByApplyingGaussianBlur3x3;

/**
 *  Applies a 5x5 gaussian blur effect to the image.
 *
 *  @return The new `UIImage` with the effect applied.
 */
- (UIImage *)imageByApplyingGaussianBlur5x5;

/**
 *  Applies a gaussian blur effect to the image.
 *
 *  @param kernelSize The kernel size to use in the blur.
 *  @param sigmaSq    The sigma squared value to use in the blur.
 *
 *  @return The new `UIImage` with the effect applied.
 */
- (UIImage *)imageByApplyingGaussianBlurOfSize:(int)kernelSize withSigmaSquared:(float)sigmaSq;

/**
 *  Applies a 3x3 sharpen effect to the image.
 *
 *  @return The new `UIImage` with the effect applied.
 */
- (UIImage *)imageByApplyingSharpen3x3;

/**
 *  Applies a 3x3 box blur effect to the image.
 *
 *  @return The new `UIImage` with the effect applied.
 */
- (UIImage *)imageByApplyingBoxBlur3x3;

/**
 *  Applies a 3x3 emboss effect to the image.
 *
 *  @return The new `UIImage` with the effect applied.
 */
- (UIImage *)imageByApplyingEmboss3x3;

/**
 *  Applies a 3x3 diagonal motion blur effect to the image.
 *
 *  @return The new `UIImage` with the effect applied.
 */
- (UIImage *)imageByApplyingDiagonalMotionBlur5x5;

@end

