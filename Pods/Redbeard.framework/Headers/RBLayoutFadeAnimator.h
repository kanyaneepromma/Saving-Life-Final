//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBLayoutAnimator.h>

/**
 *  Fades cells in and out of view.
 */
@interface RBLayoutFadeAnimator : RBLayoutAnimator

/**
 *  The alpha value of cells before they appear and after they disappear.  Default = 0.5.
 */
@property (nonatomic) CGFloat alphaFactor;

@end
