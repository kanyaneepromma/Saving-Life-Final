//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class RBAnimator;

/** The sidebar view mode (which sidebars should be enabled).
 */
typedef NS_ENUM(NSInteger, RBSidebarContainerViewMode)
{
    /** Both side bars are enabled. */
    RBSidebarViewModeBoth = 0,

    /** No side bars are enabled. */
    RBSidebarViewModeNone,
    
    /** The left side bar is enabled only. */
    RBSidebarViewModeLeft,
    
    /** The right side bar is enabled only. */
    RBSidebarViewModeRight
};

/** The view state of the sidebar.
 */
typedef NS_ENUM(NSInteger, RBSidebarViewState)
{
    /** The side bar is closed. */
    RBSidebarViewStateClosed = 0,
    
    /** The side bar is opening. */
    RBSidebarViewStateOpening,
    
    /** The side bar is opened. */
    RBSidebarViewStateOpened,

    /** The side bar is closing. */
    RBSidebarViewStateClosing,
    
    /** The side bar is pinned. */
    RBSidebarViewStatePinned
};

@protocol RBSidebarContainerViewDelegate;

/**
 *  Manages sidebars and a content view that can be swiped to reveal the sidebar(s).
 */
@interface RBSidebarContainerView : UIView<UIGestureRecognizerDelegate>

/**
 *  A delegate to receive `RBSidebarContainerView` events.
 */
@property (nonatomic, weak, nullable) id<RBSidebarContainerViewDelegate> delegate;

/**
 *  The mode describing the availability of the sidebars.
 */
@property (nonatomic) RBSidebarContainerViewMode mode;

/**
 *  The body content view.
 */
@property (nonatomic, nullable) UIView *bodyView;

/**
 *  The left sidebar view.
 */
@property (nonatomic, nullable) UIView *leftSidebarView;

/**
 *  The right sidebar view.
 */
@property (nonatomic, nullable) UIView *rightSidebarView;

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
@protocol RBSidebarContainerViewDelegate <NSObject>

@optional

/**
 *  Determines whether or not the left sidebar should be permitted to open.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to open.
 */
- (BOOL)leftSidebarShouldOpenWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar began opening.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarBeganOpeningWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar did open.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarDidOpenWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Determines whether or not the left sidebar should be permitted to close.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to close.
 */
- (BOOL)leftSidebarShouldCloseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar began closing.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarBeganClosingWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar did close.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarDidCloseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Determines whether or not the left sidebar should be permitted to expand.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to expand.
 */
- (BOOL)leftSidebarShouldExpandWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar will expand.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarWillExpandWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar did expand.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarDidExpandWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Determines whether or not the left sidebar should be permitted to collapse.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to collapse.
 */
- (BOOL)leftSidebarShouldCollapseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar will collapse.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarWillCollapseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar did collapse.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarDidCollapseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar was pinned.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarDidPinWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the left sidebar was unpinned.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)leftSidebarDidUnpinWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Determines whether or not the right sidebar should be permitted to open.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to open.
 */
- (BOOL)rightSidebarShouldOpenWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar began opening.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarBeganOpeningWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar did open.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarDidOpenWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Determines whether or not the right sidebar should be permitted to close.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to close.
 */
- (BOOL)rightSidebarShouldCloseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar began closing.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarBeganClosingWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar did close.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarDidCloseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Determines whether or not the right sidebar should be permitted to expand.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to expand.
 */
- (BOOL)rightSidebarShouldExpandWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar will expand.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarWillExpandWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar did expand.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarDidExpandWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Determines whether or not the right sidebar should be permitted to collapse.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 *
 *  @return Whether or not the sidebar should be permitted to collapse.
 */
- (BOOL)rightSidebarShouldCollapseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar will collapse.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarWillCollapseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar did collapse.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarDidCollapseWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar was pinned.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarDidPinWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

/**
 *  Called to notify that the right sidebar was unpinned.
 *
 *  @param sidebarContainerView The `RBSidebarContainerView` object.
 */
- (void)rightSidebarDidUnpinWithSidebarContainerView:(nonnull RBSidebarContainerView *)sidebarContainerView;

@end
