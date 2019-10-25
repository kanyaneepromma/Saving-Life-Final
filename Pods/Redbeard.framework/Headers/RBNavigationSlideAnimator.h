//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBNavigationAnimator.h>

/**
 *  Provides a parallex slide animation for `RBNavigationController` transitions.
 */
@interface RBNavigationSlideAnimator : RBNavigationAnimator

/**
 *  The size of the shadow to cast between the view controllers.
 */
@property (nonatomic) CGFloat shadowRadius;

/**
 *  The color of the shadow to cast between the view controllers.
 */
@property (nonatomic, nonnull) UIColor *shadowColor;

@end
