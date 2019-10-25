//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBLayoutAnimator.h>

/**
 *  Scales cells in and out of view.
 */
@interface RBLayoutScaleAnimator : RBLayoutAnimator

/**
 *  The scale of the cell before it appears and after it disappears.  Default = 0.7
 */
@property (nonatomic) CGFloat scaleFactor;

@end
