//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  `UIView` wriggle animation.
 */
@interface UIView (Wriggle)

/**
 *  The distance that the view should move during a wriggle animation.
 */
@property (nonatomic) CGFloat wriggleDistance;

/**
 *  The duration of the wriggle animation.
 */
@property (nonatomic) NSTimeInterval wriggleDuration;

/**
 *  Performs a wriggle left and right animation.
 *
 *  @param completion An optional block to be called when the animation is complete.
 */
- (void)wriggleWithCompletion:(dispatch_block_t)completion;

/**
 *  Performs a wriggle left animation.
 *
 *  @param completion An optional block to be called when the animation is complete.
 */
- (void)wriggleLeftWithCompletion:(dispatch_block_t)completion;

/**
 *  Performs a wriggle right animation.
 *
 *  @param completion An optional block to be called when the animation is complete.
 */
- (void)wriggleRightWithCompletion:(dispatch_block_t)completion;

@end
