//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  `UIView` rotation animation.
 */
@interface UIView (RotationAnimator)

/**
 *  The duration of a single rotation during a rotation animation.
 */
@property (nonatomic) CGFloat rotationAnimationDuration;

/**
 *  Starts the rotation animation.
 */
- (void)startRotationAnimation;

/**
 *  Stops the rotation animation.
 */
- (void)stopRotationAnimation;

// TODO: Add support for performing a given number of rotations.

@end
