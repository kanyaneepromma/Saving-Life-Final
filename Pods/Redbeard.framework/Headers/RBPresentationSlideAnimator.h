//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBPresentationAnimator.h>

/** The direction in which the view slides into view during presentation and dismissal. */
typedef NS_ENUM(NSInteger, RBPresentationSlideDirection)
{
    /** The view slides in to view from the top. */
    RBPresentationSlideFromTop,
    
    /** The view slides in to view from the left. */
    RBPresentationSlideFromLeft,
    
    /** The view slides in to view from the bottom. */
    RBPresentationSlideFromBottom,

    /** The view slides in to view from the right. */
    RBPresentationSlideFromRight
};

/**
 *  Provides a slide animation for the presentation of view controller.
 */
@interface RBPresentationSlideAnimator : RBPresentationAnimator

/**
 *  The direction from which the view should slide into it's frame.
 */
@property (nonatomic) RBPresentationSlideDirection fromDirection;

/**
 *  The alpha channel of the black background around the presenting view.
 */
@property (nonatomic) CGFloat darknessFactor;

@end
