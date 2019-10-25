//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBThemeTracker.h>

@class RBAnimator;
@class RBNavigationController;

/**
 *  Provides animation functionality for an `RBNavigationController` object.
 */
@interface RBNavigationAnimator : NSObject<RBThemeTrackerDelegate>

/**
 *  The theming tracker object for the view.
 */
@property (nonatomic, readonly, nonnull) RBThemeTracker *theme;

/**
 *  The `RBAnimator` object to use when animating.
 */
@property (nonatomic, readonly, nonnull) RBAnimator *animator;

#pragma mark -
#pragma mark Navigation Controller

/**
 *  The underlying `RBNavigationController` object that the animator belongs to.
 */
@property (nonatomic, readonly, nullable) RBNavigationController *navigationController;

/**
 *  Notifies the animator that it was added to an `RBNavigationController`.
 *
 *  @param navigationController The `RBNavigationController` object.
 */
- (void)wasAddedToController:(nonnull RBNavigationController *)navigationController;

/**
 *  Notifies the animator that it was removed from an `RBNavigationController`.
 *
 *  @param navigationController The `RBNavigationController` object.
 */
- (void)wasRemovedFromController:(nonnull RBNavigationController *)navigationController;

#pragma mark -
#pragma mark Transitions

/**
 *  Animate a pop transition.
 *
 *  @param container            The containing view of the view that is being popped.
 *  @param back                 The previous view that will be revealed by the pop operation.
 *  @param front                The view that is being popped from the container.
 *  @param completion           The completion block to be called to notify that the operation is complete.
 */
- (void)animatePopWithContainer:(nonnull UIView *)container
                       withBack:(nonnull UIView *)back
                      withFront:(nonnull UIView *)front
                     completion:(nullable dispatch_block_t)completion;

/**
 *  Animate a push transition.
 *
 *  @param container            The containing view of the view that is being pushed.
 *  @param back                 The previous view that will be hidden by the push operation.
 *  @param front                The view that is being pushed to the container.
 *  @param completion           The completion block to be called to notify that the operation is complete.
 */
- (void)animatePushWithContainer:(nonnull UIView *)container
                        withBack:(nonnull UIView *)back
                       withFront:(nonnull UIView *)front
                      completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Swipe Pop

/**
 *  Whether or not the animator supports swipe-to-pop.
 */
@property (nonatomic, readonly) BOOL doesSupportSwipePop;

/**
 *  Whether or not the swipe to pop a view controller is from the left (YES) or right (NO).
 */
@property (nonatomic, readonly) BOOL swipePopIsFromLeft;

/**
 *  Notifies the animator that a swipe-to-pop operation has begun.
 *
 *  @param container            The containing view.
 *  @param back                 The back view that is being revealed by the pop.
 *  @param front                The front view that is being popped.
 *  @param vector               The current vector of the swipe.
 */
- (void)swipePopBeganWithContainer:(nonnull UIView *)container
                              back:(nonnull UIView *)back
                             front:(nonnull UIView *)front
                            vector:(CGPoint)vector;

/**
 *  Notifies the animator that a swipe-to-pop operation has updated.
 *
 *  @param container            The containing view.
 *  @param back                 The back view that is being revealed by the pop.
 *  @param front                The front view that is being popped.
 *  @param vector               The current vector of the swipe.
 */
- (void)swipePopUpdatedWithContainer:(nonnull UIView *)container
                                back:(nonnull UIView *)back
                               front:(nonnull UIView *)front
                              vector:(CGPoint)vector;

/**
 *  Notifies the animator that a swipe-to-pop operation has ended.
 *
 *  @param container            The containing view.
 *  @param back                 The back view that is being revealed by the pop.
 *  @param front                The front view that is being popped.
 *  @param vector               The current vector of the swipe.
 *  @param completion           An optional completion block to be called when the operation is complete, indicating whether the view controller should be popped or not.
 */
- (void)swipePopEndedWithContainer:(nonnull UIView *)container
                              back:(nonnull UIView *)back
                             front:(nonnull UIView *)front
                            vector:(CGPoint)vector
                        completion:(nullable void(^)(BOOL pop))completion;

@end
