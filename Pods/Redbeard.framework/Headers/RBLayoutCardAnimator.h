//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Redbeard/RBLayoutAnimator.h>

/**
 *  Spins cells in and out of view.
 */
@interface RBLayoutCardAnimator : RBLayoutAnimator

/**
 *  The scale of the cell before it appears and after it disappears.  Default = 0.3
 */
@property (nonatomic) CGFloat scaleFactor;

@end
