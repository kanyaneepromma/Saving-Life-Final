//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  `UIImage` image effects methods.
 */
@interface UIImage (ImageEffects)

/**
 *  Applies a lightening effect to the `UIImage`.
 *
 *  @return The new `UIImage` object with the effect applied.
 */
- (nonnull UIImage *)applyLightEffect;

/**
 *  Applies an extra-strong lightening effect to the `UIImage`.
 *
 *  @return The new `UIImage` object with the effect applied.
 */
- (nonnull UIImage *)applyExtraLightEffect;

/**
 *  Applies a darkening effect to the `UIImage`.
 *
 *  @return The new `UIImage` object with the effect applied.
 */
- (nonnull UIImage *)applyDarkEffect;

/**
 *  Applies a color tint effect to the `UIImage`.
 *
 *  @param tintColor The tint color to apply.
 *
 *  @return The new `UIImage` object with the effect applied.
 */
- (nonnull UIImage *)applyTintEffectWithColor:(nonnull UIColor *)tintColor;

/**
 *  Applies a blur effect to the image with a tint.
 *
 *  @param blurRadius            The radius of the blur.
 *  @param tintColor             The optional tint color to use.
 *  @param saturationDeltaFactor The saturation delta factor value to use.
 *  @param maskImage             The optional mask to apply the blur effect to.
 *
 *  @return The new `UIImage` object with the effect applied.
 */
- (nonnull UIImage *)applyBlurWithRadius:(CGFloat)blurRadius
                       tintColor:(nullable UIColor *)tintColor
           saturationDeltaFactor:(CGFloat)saturationDeltaFactor
                       maskImage:(nullable UIImage *)maskImage;

@end
