//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBSidebarContainerView.h>

@class RBAnimator;
@protocol RBSidebarContainerViewControllerDelegate;

/**
 *  Manages sidebars and a content view that can be swiped to reveal the sidebar(s).
 */
@interface RBSidebarContainerViewController : UIViewController

/**
 *  The underlying `RBSidebarContainerView` object.
 */
@property (nonatomic, retain, nonnull) RBSidebarContainerView *view;

/**
 *  A delegate to receive `RBSidebarContainerViewController` events.
 */
@property (nonatomic, weak, nullable) id<RBSidebarContainerViewControllerDelegate> delegate;


/**
 *  The mode describing the availability of the sidebars.
 */
@property (nonatomic) RBSidebarContainerViewMode mode;

/**
 *  The body content view controller.
 */
@property (nonatomic, nullable) UIViewController *bodyViewController;

/**
 *  The left sidebar view controller.
 */
@property (nonatomic, nullable) UIViewController *leftSidebarViewController;

/**
 *  The right sidebar view controller.
 */
@property (nonatomic, nullable) UIViewController *rightSidebarViewController;

#pragma mark -
#pragma mark Tweaking

/**
 *  Whether or not the sidebars can be opened with a swipe/pan gesture.
 */
@property (nonatomic) BOOL swipeEnabled;

/**
 *  The amount of swipe that is required so that on release the sidebar will open/close.
 */
@property (nonatomic) CGFloat swipeMargin;

/**
 *  The `RBAnimator` object to use when animating.
 */
@property (nonatomic, readonly, nonnull) RBAnimator *animator;

#pragma mark -
#pragma mark Sidebar States

/**
 *  The current state of the left sidebar.
 */
@property (nonatomic, readonly) RBSidebarViewState leftSidebarState;

/**
 *  Whether or not the left sidebar is currently visible.
 */
@property (nonatomic, readonly) BOOL leftSidebarIsVisible;

/**
 *  Whether or not the left sidebar is currently enabled.
 */
@property (nonatomic, readonly) BOOL leftSidebarIsEnabled;

/**
 *  Whether or not the left sidebar is currently expanded.
 */
@property (nonatomic, readonly) BOOL leftSidebarIsExpanded;

/**
 *  The current state of the right sidebar.
 */
@property (nonatomic, readonly) RBSidebarViewState rightSidebarState;

/**
 *  Whether or not the right sidebar is currently visible.
 */
@property (nonatomic, readonly) BOOL rightSidebarIsVisible;

/**
 *  Whether or not the right sidebar is currently enabled.
 */
@property (nonatomic, readonly) BOOL rightSidebarIsEnabled;

/**
 *  Whether or not the right sidebar is currently expanded.
 */
@property (nonatomic, readonly) BOOL rightSidebarIsExpanded;

#pragma mark -
#pragma mark Opening & Closing

/**
 *  Opens the left sidebar.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)openLeftSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Opens the right sidebar.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)openRightSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Closes the sidebars.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)closeSidebarsWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Expanding

/**
 *  Expands the left sidebar to occupy the full width.  This will do nothing if
 *  the sidebar is not open or pinned.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)expandLeftSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Expands the right sidebar to occupy the full width.  This will do nothing if
 *  the sidebar is not open or pinned.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)expandRightSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Collapse the currently extended sidebar.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)collapseSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Pinning

/**
 *  Pins the left sidebar so that it remains open.  The body content view is adjusted.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)pinLeftSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Unpins the left sidebar.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)unpinLeftSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Pins the right sidebar so that it remains open.  The body content view is adjusted.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)pinRightSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Unpins the right sidebar.
 *
 *  @param animated   Whether or not the animation should be animated.
 *  @param completion An optional block to be called on completion.
 */
- (void)unpinRightSidebarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Automatic Pinning

/**
 *  Whether or not to automatically pin the left sidebar if there would be sufficient body width.
 */
@property (nonatomic) BOOL pinLeftSidebarIfSufficientWidth;

/**
 *  Whether or not to automatically pin the right sidebar if there would be sufficient body width.
 */
@property (nonatomic) BOOL pinRightSidebarIfSufficientWidth;

/**
 *  Whether or not the left sidebar should be pinned before the right sidebar when there is sufficient body width.
 */
@property (nonatomic) BOOL pinLeftSidebarBeforeRightSidebar;

/**
 *  The body width that is required with a bar open in order for it to be automatically pinned.
 */
@property (nonatomic) CGFloat desiredMinimumBodyWidth;

@end

/**
 *  A delegate to receive `RBSidebarContainerView` events.
 */
@protocol RBSidebarContainerViewControllerDelegate <NSObject>

@optional

/**
 *  Determines whether or not the left sidebar should be permitted to open.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to open.
 */
- (BOOL)leftSidebarShouldOpenWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar began opening.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarBeganOpeningWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar did open.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarDidOpenWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Determines whether or not the left sidebar should be permitted to close.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to close.
 */
- (BOOL)leftSidebarShouldCloseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar began closing.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarBeganClosingWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar did close.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarDidCloseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Determines whether or not the left sidebar should be permitted to expand.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to expand.
 */
- (BOOL)leftSidebarShouldExpandWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar will expand.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarWillExpandWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar did expand.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarDidExpandWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Determines whether or not the left sidebar should be permitted to collapse.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to collapse.
 */
- (BOOL)leftSidebarShouldCollapseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar will collapse.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarWillCollapseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar did collapse.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarDidCollapseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar was pinned.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarDidPinWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the left sidebar was unpinned.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)leftSidebarDidUnpinWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Determines whether or not the right sidebar should be permitted to open.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to open.
 */
- (BOOL)rightSidebarShouldOpenWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar began opening.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarBeganOpeningWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar did open.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarDidOpenWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Determines whether or not the right sidebar should be permitted to close.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to close.
 */
- (BOOL)rightSidebarShouldCloseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar began closing.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarBeganClosingWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar did close.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarDidCloseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Determines whether or not the right sidebar should be permitted to expand.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to expand.
 */
- (BOOL)rightSidebarShouldExpandWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar will expand.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarWillExpandWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar did expand.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarDidExpandWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Determines whether or not the right sidebar should be permitted to collapse.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 *
 *  @return Whether or not the sidebar should be permitted to collapse.
 */
- (BOOL)rightSidebarShouldCollapseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar will collapse.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarWillCollapseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar did collapse.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarDidCollapseWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar was pinned.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarDidPinWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

/**
 *  Called to notify that the right sidebar was unpinned.
 *
 *  @param sidebarContainerViewController The `RBSidebarContainerViewController` object.
 */
- (void)rightSidebarDidUnpinWithSidebarContainerViewController:(nonnull RBSidebarContainerViewController *)sidebarContainerViewController;

@end
