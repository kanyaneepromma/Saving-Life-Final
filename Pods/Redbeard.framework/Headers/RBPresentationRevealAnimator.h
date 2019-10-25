//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBPresentationAnimator.h>

/** The orientation and position of the reveal view animation. */
typedef NS_ENUM(NSInteger, RBPresentationRevealMode)
{
    /** The view is revealed vertically at the top. */
    RBPresentationRevealModeVerticalFromTop,

    /** The view is revealed vertically at the middle. */
    RBPresentationRevealModeVerticalFromMiddle,
    
    /** The view is revealed vertically at the bottom. */
    RBPresentationRevealModeVerticalFromBottom,
    
    /** The view is revealed horizontally at the left. */
    RBPresentationRevealModeHorizontalFromLeft,
    
    /** The view is revealed horizontally at the middle. */
    RBPresentationRevealModeHorizontalFromMiddle,
    
    /** The view is revealed horizontally at the right. */
    RBPresentationRevealModeHorizontalFromRight
};

/**
 *  Provides a reveal animation for the presentation of view controller.
 *
 *  The reveal animation consists of the view splitting and opening to reveal
 *  the view being presented.
 */
@interface RBPresentationRevealAnimator : RBPresentationAnimator

/**
 *  The reveal mode to use.
 */
@property (nonatomic) RBPresentationRevealMode mode;

@end
