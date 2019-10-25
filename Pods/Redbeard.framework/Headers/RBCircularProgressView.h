//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * A circular view uses an arc to show progress.
 */
@interface RBCircularProgressView : UIView

/**
 * The image to display in the circle (it is automatically adjusted for display).
 */
@property (nonatomic, nullable) UIImage *circleImage;

/**
 * The background color of the circle.
 */
@property (nonatomic, nullable) UIColor *circleColor;

/**
 * Whether the arc should fill the whole circle.
 */
@property (nonatomic) BOOL barShouldFillRadius;

/**
 * The width of the arc bar.
 * This is ignored if `barShouldFillRadius` is set to true.
 */
@property (nonatomic) CGFloat barWidth;

/**
 * The color of the arc bar.
 */
@property (nonatomic, nullable) UIColor *barColor;

/**
 * The current progress from 0 to 1.
 */
@property (nonatomic) CGFloat progress; // 0.0 - 1.0

/**
 * Begins a continuous arc fill/unfill animation.
 */
- (void)startRepeatProgress;

/**
 * Stops the continuous arc fill/unfill animation.
 */
- (void)stopRepeatProgress;

@end
