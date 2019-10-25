//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBSlidingView.h>

@protocol RBSlidingViewControllerDelegate;

/**
 *  A container view controller that manages pages with tabs.
 */
@interface RBSlidingViewController : UIViewController<RBSlidingViewDelegate>

/**
 *  The underlying `RBSlidingView` object.
 */
@property (nonatomic, nonnull) RBSlidingView *view;

/**
 *  A delegate to receive tab page selection events.
 */
@property (nonatomic, weak, nullable) id<RBSlidingViewControllerDelegate> delegate;

/**
 *  The number of tab pages currently in the container.
 */
@property (nonatomic, readonly) NSInteger pages;

/**
 *  The index of the current page.
 */
@property (nonatomic, readonly) NSInteger currentPageControllerIndex;

/**
 *  The current page `UIViewController` object.
 */
@property (nonatomic, readonly, nullable) UIViewController *currentPageViewController;

/**
 *  Gets the page view controller at the given index.
 *
 *  @param index The index of the page.
 *
 *  @return The `UIViewController` object at the given index.
 */
- (nonnull UIViewController *)pageControllerAtIndex:(NSInteger)index;

/**
 *  Add a new page to the controller.
 *
 *  @param pageController The page `UIViewController` object.
 */
- (void)addPageController:(nonnull UIViewController *)pageController;

/**
 *  Insert a new page to the controller at the given index.
 *
 *  @param pageController The page `UIViewController` object.
 *  @param index          The index at which to insert the page.
 */
- (void)insertPageController:(nonnull UIViewController *)pageController atIndex:(NSInteger)index;

/**
 *  Remove the given page from the container.
 *
 *  @param pageController The page `UIViewController` object.
 */
- (void)removePageController:(nonnull UIViewController *)pageController;

/**
 *  Remove the page at the given index.
 *
 *  @param index The index of the page to remove.
 */
- (void)removePageControllerAtIndex:(NSInteger)index;

/**
 *  Remove all pages from the container.
 */
- (void)removeAllPageControllers;

/**
 *  Moves to the given page view controller.
 *
 *  @param pageController The page `UIViewController` object to move to.
 *  @param animated       Whether or not the transition should be animated.
 *  @param completion     An optional block to be called when the transition is complete.
 */
- (void)moveToPageController:(nonnull UIViewController *)pageController animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Moves to the given page view controller.
 *
 *  @param index      The index of the page to move to.
 *  @param animated   Whether or not the transition should be animated.
 *  @param completion An optional block to be called when the transition is complete.
 */
- (void)moveToPageControllerAtIndex:(NSInteger)index animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

@end

/**
 *  A delegate to receive tab page selection events for an `RBSlidingViewController`.
 */
@protocol RBSlidingViewControllerDelegate <NSObject>

@optional

/**
 *  Called when a page will be moved to.
 *
 *  @param slidingPageViewController The `RBSlidingViewController` object.
 *  @param fromIndex                 The index of the page being moved away from.
 *  @param toIndex                   The index of the page being moved to.
 *  @param animated                  Whether or not the transition is animated.
 */
- (void)slidingPageViewController:(nonnull RBSlidingViewController *)slidingPageViewController
                willMoveFromIndex:(NSInteger)fromIndex
                          toIndex:(NSInteger)toIndex
                         animated:(BOOL)animated;

/**
 *  Called when a page was moved to.
 *
 *  @param slidingPageViewController The `RBSlidingViewController` object.
 *  @param fromIndex                 The index of the page being moved away from.
 *  @param toIndex                   The index of the page being moved to.
 *  @param animated                  Whether or not the transition is animated.
 */
- (void)slidingPageViewController:(nonnull RBSlidingViewController *)slidingPageViewController
                 didMoveFromIndex:(NSInteger)fromIndex
                          toIndex:(NSInteger)toIndex
                         animated:(BOOL)animated;

/**
 *  Called when a swipe gesture will reveal the page at the given index (but not select it).
 *
 *  @param slidingPageViewController    The `RBSlidingViewController` object.
 *  @param index                        The page index.
 */
- (void)slidingPageViewController:(nonnull RBSlidingViewController *)slidingPageViewController willPeakAtIndex:(NSInteger)index;

/**
 *  Called when a swipe gesture did reveal the page at the given index (but not select it).
 *
 *  @param slidingPageViewController    The `RBSlidingViewController` object.
 *  @param index                        The page index.
 *  @param didBecomeCurrentPage         Whether or not the page did become the current page.
 */
- (void)slidingPageViewController:(nonnull RBSlidingViewController *)slidingPageViewController didPeakAtIndex:(NSInteger)index didBecomeCurrentPage:(BOOL)didBecomeCurrentPage;

@end
