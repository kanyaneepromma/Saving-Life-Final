//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBPresentationController.h>

/**
 *  `UIViewController` presentation controller.
 */
@interface UIViewController (PresentationController)

/**
 *  The presentation controller for the view controller.
 */
@property (nonatomic, readonly, nonnull) RBPresentationController *redbeardPresentationController;

#pragma mark -
#pragma mark Subclassing

/**
 *  Called when a view controller is about to be presented.
 *
 *  @param viewController The view controller that will be presented.
 *  @param animated       Whether or not the presentation will be animated.
 */
- (void)willPresentViewController:(nonnull UIViewController *)viewController animated:(BOOL)animated;

/**
 *  Called when a view controller has just been presented.
 *
 *  @param viewController The view controller that has just been presented.
 *  @param animated       Whether or not the presentation was animated.
 */
- (void)didPresentViewController:(nonnull UIViewController *)viewController animated:(BOOL)animated;

/**
 *  Called when a view controller is about to be dismissed.
 *
 *  @param viewController The view controller that will be dismissed.
 *  @param animated       Whether or not the dismissal will be animated.
 */
- (void)willDismissViewController:(nonnull UIViewController *)viewController animated:(BOOL)animated;

/**
 *  Called when a view controller has just been dismissed.
 *
 *  @param viewController The view controller that has just been dismissed.
 *  @param animated       Whether or not the dismissal was animated.
 */
- (void)didDismissViewController:(nonnull UIViewController *)viewController animated:(BOOL)animated;

@end
