//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBThemeTracker.h>

@class RBBaseLayoutView;

/**
 *  A base animator class that provides animations on cells as they appear
 *  and disappear.
 */
@interface RBLayoutAnimator : NSObject<RBThemeTrackerDelegate>

/**
 *  The theming tracker object for the view.
 */
@property (nonatomic, readonly, nonnull) RBThemeTracker *theme;

/**
 *  The `RBAnimator` object used to control transition animations.
 */
@property (nonatomic, readonly, nonnull) RBAnimator *animator;

/**
 *  Whether or not the cells animate when scrolling in the positive direction (down or right).
 */
@property (nonatomic) BOOL animatePositiveDirection;

/**
 *  Whether or not the cells animate when scrolling in the negative direction (up or left).
 */
@property (nonatomic) BOOL animateNegativeDirection;

/**
 *  Animate a cell that is appearing.
 *
 *  @param cell              The cell that is appearing.
 *  @param positiveDirection Whether or not scrolling is in the positive direction.
 *  @param completion        The completion block to be called when the animation is complete.
 */
- (void)animateAppearedCell:(nonnull UIView *)cell positiveDirection:(BOOL)positiveDirection completion:(nullable dispatch_block_t)completion;

/**
 *  Animate a cell that is disappearing.
 *
 *  @param cell              The cell that is disappearing.
 *  @param positiveDirection Whether or not scrolling is in the negative direction.
 *  @param completion        The completion block to be called when the animation is complete.
 */
- (void)animateDisappearedCell:(nonnull UIView *)cell positiveDirection:(BOOL)positiveDirection completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Subclassing

/**
 *  Perform a cell appearance animation.
 *
 *  @param cell              The cell that is appearing.
 *  @param positiveDirection Whether or not scrolling is in the positive direction.
 *  @param completion        The completion block to be called when the animation is complete.
 */
- (void)performAnimateAppearedCell:(nonnull UIView *)cell positiveDirection:(BOOL)positiveDirection completion:(nullable dispatch_block_t)completion;

/**
 *  Perform a cell disappearance animation.
 *
 *  @param cell              The cell that is disappearing.
 *  @param positiveDirection Whether or not scrolling is in the positive direction.
 *  @param completion        The completion block to be called when the animation is complete.
 */
- (void)performAnimateDisappearedCell:(nonnull UIView *)cell positiveDirection:(BOOL)positiveDirection completion:(nullable dispatch_block_t)completion;

@end
