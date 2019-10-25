//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  `UIViewController` child view controller appearance management.
 */
@interface UIViewController (AppearanceEvents)

/**
 *  Whether or not the view controller should automatically notify
 *  its children when it appears and disappears.
 *
 *  Whenever you enable this, you must override shouldAutomaticallyForwardAppearanceMethods to false
 */
@property (nonatomic, readonly) BOOL shouldAutomaticallyManageAppearanceTransitions;

#pragma mark -
#pragma mark Subclassing

// When enabled, use the methods below to notify the appearance/disappearance of children
// and the relevant notifications will be passed to the children dependant on this view controllers
// appearance state.

/**
 *  Call when a child view controller will appear.
 *
 *  @param viewController The view controller.
 *  @param animated       Whether the transition is animated.
 */
- (void)viewControllerWillAppear:(nonnull UIViewController *)viewController animated:(BOOL)animated;

/**
 *  Call when a child view controller did appear.
 *
 *  @param viewController The view controller.
 *  @param animated       Whether the transition is animated.
 */
- (void)viewControllerDidAppear:(nonnull UIViewController *)viewController animated:(BOOL)animated;

/**
 *  Call when a child view controller will disappear.
 *
 *  @param viewController The view controller.
 *  @param animated       Whether the transition is animated.
 */
- (void)viewControllerWillDisappear:(nonnull UIViewController *)viewController animated:(BOOL)animated;

/**
 *  Call when a child view controller did disappear.
 *
 *  @param viewController The view controller.
 *  @param animated       Whether the transition is animated.
 */
- (void)viewControllerDidDisappear:(nonnull UIViewController *)viewController animated:(BOOL)animated;

@end
