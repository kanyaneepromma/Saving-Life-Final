//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBNavigationAnimator.h>

/** The animation to use in the default navigation animator. */
typedef NS_ENUM(NSInteger, RBNavigationDefaultAnimationType)
{
    /** The default sliding animation. */
    RBNavigationDefaultAnimationTypeSlide = 0,
    
    /** The flip from left animation. */
    RBNavigationDefaultAnimationTypeFlipFromLeft,

    /** The flip from right animation. */
    RBNavigationDefaultAnimationTypeFlipFromRight,

    /** The curl up animation. */
    RBNavigationDefaultAnimationTypeCurlUp,

    /** The curl down animation. */
    RBNavigationDefaultAnimationTypeCurlDown,

    /** The cross dissolve animation. */
    RBNavigationDefaultAnimationTypeCrossDissolve,

    /** The flip from top animation. */
    RBNavigationDefaultAnimationTypeFlipFromTop,

    /** The flip from bottom animation. */
    RBNavigationDefaultAnimationTypeFlipFromBottom
};

/**
 *  Provides a default animation for `RBNavigationController` transitions.
 */
@interface RBNavigationDefaultAnimator : RBNavigationAnimator

/**
 *  The type of animation to use for push transitions.
 */
@property (nonatomic) RBNavigationDefaultAnimationType pushTransition;

/**
 *  The type of animation to use for pop transitions.
 */
@property (nonatomic) RBNavigationDefaultAnimationType popTransition;

@end
