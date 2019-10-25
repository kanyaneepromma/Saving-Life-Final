//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBNavigationAnimator.h>

@protocol RBNavigationControllerDelegate;

/**
 *  A customisable navigation controller.
 */
@interface RBNavigationController : UIViewController<UIGestureRecognizerDelegate>

/**
 *  An array of the view controllers currently on the navigation stack.
 */
@property (nonatomic, readonly, nonnull) NSArray *viewControllers;

/**
 *  The view controller behind the currently displayed view controller.
 */
@property (nonatomic, readonly, nullable) UIViewController *previousViewController;

/**
 *  The animator that is used to provide animated push and pop transitions.
 */
@property (nonatomic, nonnull) RBNavigationAnimator *animator;

/**
 *  Whether or not the user can swipe from the edge to pop a view controller.
 */
@property (nonatomic) BOOL swipePopEnabled;

/**
 *  An optional delegate to be informed of navigation events.
 */
@property (nonatomic, weak, nullable) id<RBNavigationControllerDelegate> delegate;

/**
 *  Retrieves the view controller at the given index from the top.
 *  The visible view controller has an index of 0.
 *
 *  @param index The index from the top of the view controller desired.
 *
 *  @return The retrieved view controller.
 */
- (nullable UIViewController *)viewControllerFromTop:(NSUInteger)index; // 0 = top, 1 = below top, 2 = ...

/**
 *  Pushes a view controller to the navigation stack.
 *
 *  @param viewController The view controller to push to the navigation stack.
 *  @param animated       Whether or not the operation should be animated.
 *  @param completion     An optional block to be called when the operation is complete.
 */
- (void)pushViewController:(nonnull UIViewController *)viewController
                  animated:(BOOL)animated
                completion:(nullable dispatch_block_t)completion;

/**
 *  Pushes a view controller to the navigation stack.
 *
 *  @param viewController The view controller to push to the navigation stack.
 *  @param animator       An Optional `RBNavigationAnimator` to use for animating.
 *  @param completion     An optional block to be called when the operation is complete.
 */
- (void)pushViewController:(nonnull UIViewController *)viewController
                  animator:(nullable RBNavigationAnimator *)animator
                completion:(nullable dispatch_block_t)completion;

/**
 *  Pops all view controllers above the given view controller from the navigation stack.
 *  When the operation is complete, the given view controller will be the visible view controller.
 *
 *  @param viewController The view controller to pop to.
 *  @param animated       Whether or not the operation should be animated.
 *  @param completion     An optional block to be called when the operation is complete.
 *
 *  @return An array of the view controllers that were popped.
 */
- (nonnull NSArray *)popToViewController:(nonnull UIViewController *)viewController
                                animated:(BOOL)animated
                              completion:(nullable dispatch_block_t)completion;

/**
 *  Pops all view controllers above the given view controller from the navigation stack.
 *  When the operation is complete, the given view controller will be the visible view controller.
 *
 *  @param viewController The view controller to pop to.
 *  @param animator       An Optional `RBNavigationAnimator` to use for animating.
 *  @param completion     An optional block to be called when the operation is complete.
 *
 *  @return An array of the view controllers that were popped.
 */
- (nonnull NSArray *)popToViewController:(nonnull UIViewController *)viewController
                                animator:(nullable RBNavigationAnimator *)animator
                              completion:(nullable dispatch_block_t)completion;

/**
 *  Pops the top view controller from the navigation stack.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 *
 *  @return The view controller that was popped.
 */
- (nullable UIViewController *)popViewControllerAnimated:(BOOL)animated
                                              completion:(nullable dispatch_block_t)completion;

/**
 *  Pops the top view controller from the navigation stack using a specific optional animator.
 *
 *  @param animator   An Optional `RBNavigationAnimator` to use for animating.
 *  @param completion An optional block to be called when the operation is complete.
 *
 *  @return The view controller that was popped.
 */
- (nullable UIViewController *)popViewControllerWithAnimator:(nullable RBNavigationAnimator *)animator
                                                  completion:(nullable dispatch_block_t)completion;
/**
 *  Pops all view controllers except the first view controller.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 *
 *  @return An array of the view controllers that were popped.
 */
- (nonnull NSArray *)popToRootViewControllerAnimated:(BOOL)animated
                                          completion:(nullable dispatch_block_t)completion;

/**
 *  Pops all view controllers except the first view controller using a specific optional animator.
 *
 *  @param animator   An Optional `RBNavigationAnimator` to use for animating.
 *  @param completion An optional block to be called when the operation is complete.
 *
 *  @return An array of the view controllers that were popped.
 */
- (nonnull NSArray *)popToRootViewControllerWithAnimator:(nullable RBNavigationAnimator *)animator
                                              completion:(nullable dispatch_block_t)completion;

/**
 *  Removes the view controllers in the given range.  There is no animation for this operation.
 *
 *  @param range The `NSRange` of the view controllers to remove.
 */
- (void)removeViewControllersInRange:(NSRange)range;

/**
 *  Removes all view controllers between the ones given.
 *
 *  @param viewControllerA The first view controller.
 *  @param viewControllerB The second view controller.
 */
- (void)removeViewControllersBetween:(nonnull UIViewController *)viewControllerA
                   andViewController:(nonnull UIViewController *)viewControllerB;

@end

/**
 *  A delegate that is informed of `RBNavigationController` events.
 */
@protocol RBNavigationControllerDelegate <NSObject>

@optional

/**
 *  The navigation controller will push a view controller to the navigation stack.
 *
 *  @param navigationController The navigation controller object.
 *  @param viewController       The view controller that will be pushed to the navigation stack.
 *  @param animated             Whether or not the operation is animated.
 */
- (void)navigationController:(nonnull RBNavigationController *)navigationController
      willPushViewController:(nonnull UIViewController *)viewController
                    animated:(BOOL)animated;

/**
 *  The navigation controller did push a view controller to the navigation stack.
 *
 *  @param navigationController The navigation controller object.
 *  @param viewController       The view controller that was pushed to the navigation stack.
 *  @param animated             Whether or not the operation is animated.
 */
- (void)navigationController:(nonnull RBNavigationController *)navigationController
       didPushViewController:(nonnull UIViewController *)viewController
                    animated:(BOOL)animated;

/**
 *  The navigation controller will pop a view controller from the navigation stack.
 *
 *  @param navigationController The navigation controller object.
 *  @param viewControllers      An array of the view controllers that will be popped from the navigation stack.
 *  @param viewController       The view controller that will be revealed when the operation is complete.
 *  @param animated             Whether or not the operation is animated.
 */
- (void)navigationController:(nonnull RBNavigationController *)navigationController
      willPopViewControllers:(nonnull NSArray *)viewControllers
            toViewController:(nonnull UIViewController *)viewController
                    animated:(BOOL)animated;

/**
 *  The navigation controller did pop a view controller from the navigation stack.
 *
 *  @param navigationController The navigation controller object.
 *  @param viewControllers      An array of the view controllers that were popped from the navigation stack.
 *  @param viewController       The view controller that was revealed when the operation finished.
 *  @param animated             Whether or not the operation is animated.
 */
- (void)navigationController:(nonnull RBNavigationController *)navigationController
       didPopViewControllers:(nonnull NSArray *)viewControllers
            toViewController:(nonnull UIViewController *)viewController
                    animated:(BOOL)animated;

@end
