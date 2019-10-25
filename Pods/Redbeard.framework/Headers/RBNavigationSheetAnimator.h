//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import "RBNavigationAnimator.h"

/**
 *  Provides a parallex sheet animation (slides in from bottom) for `RBNavigationController` transitions.
 */
@interface RBNavigationSheetAnimator : RBNavigationAnimator

/**
 *  The size of the shadow to cast between the view controllers.
 */
@property (nonatomic) CGFloat shadowRadius;

/**
 *  The color of the shadow to cast between the view controllers.
 */
@property (nonatomic, nonnull) UIColor *shadowColor;

@end
