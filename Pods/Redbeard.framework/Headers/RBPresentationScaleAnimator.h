//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBPresentationAnimator.h>

/**
 *  Provides a scale animation for the presentation of view controllers.
 */
@interface RBPresentationScaleAnimator : RBPresentationAnimator

/**
 *  The beginning scale factor.
 *  Animated to 1.0.
 */
@property (nonatomic) CGFloat scaleFactor;

/**
 *  The beginning alpha channel of the presenting view.
 *  Animated to 1.0.
 */
@property (nonatomic) CGFloat beginningFadeAlpha;

/**
 *  The alpha channel of the black background around the presenting view.
 */
@property (nonatomic) CGFloat darknessFactor;

@end
