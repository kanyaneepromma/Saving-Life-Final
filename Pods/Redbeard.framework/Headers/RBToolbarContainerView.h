//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
@class RBScrollView;

/**
 *  The display state of a toolbar.
 */
typedef NS_ENUM(NSInteger, RBToolbarContainerBarState)
{
    /**
     *  The toolbar is hidden.
     */
    RBToolbarContainerBarStateHidden = 0,
    /**
     *  The toolbar is pinned open.
     */
    RBToolbarContainerBarStatePinned,
    /**
     *  The toolbar is floating and can open and close.
     */
    RBToolbarContainerBarStateFloating
};

/**
 *  The bar position.
 */
typedef NS_ENUM(NSInteger, RBToolbarContainerBar){
    /**
     *  A top bar.
     */
    RBToolbarContainerBarTop,
    
    /**
     *  A bottom bar.
     */
    RBToolbarContainerBarBottom,
    
    /**
     *  A left bar.
     */
    RBToolbarContainerBarLeft,
    
    /**
     *  A right bar.
     */
    RBToolbarContainerBarRight
};

// TODO: Add option to also "fade" in/out toolbars as they animate open/close.

@protocol RBToolbarContainerViewDelegate;

/**
 *  Provides toolbar management for a content view.
 */
@interface RBToolbarContainerView : UIView

/**
 *  The `RBAnimator` object to use when animating.
 */
@property (nonatomic, nullable) RBAnimator *animator;

/**
 *  A delegate to receive events.
 */
@property (nonatomic, weak, nullable) id<RBToolbarContainerViewDelegate> delegate;

/**
 *  The content view.
 */
@property (nonatomic, nonnull) UIView *view;

/**
 *  Sets the `RBScrollView` object to track, providing automatic opening and closing
 *  of floating bars. Keeps a weak reference.
 *
 *  @param trackerScrollView The scroll view to track.
 */
- (void)setScrollViewForTracking:(nonnull RBScrollView *)trackerScrollView;

#pragma mark -
#pragma mark Top Bar

/**
 *  The state of the top bar.
 */
@property (nonatomic) RBToolbarContainerBarState topBarViewState;

/**
 *  The top bar view.
 */
@property (nonatomic, nullable) UIView *topBarView;

/**
 *  Whether or not the content view's content insets should be updated
 *  when the top bar opens and closes.
 */
@property (nonatomic) BOOL topBarShouldAdjustContentInsets;

/**
 *  Whether or not the top bar is currently open.
 */
@property (nonatomic, readonly) BOOL topBarViewIsOpen;

/**
 *  Opens the top bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)openTopBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Closes the top bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)closeTopBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Bottom Bar

/**
 *  The state of the bottom bar.
 */
@property (nonatomic) RBToolbarContainerBarState bottomBarViewState;

/**
 *  The bottom bar view.
 */
@property (nonatomic, nullable) UIView *bottomBarView;

/**
 *  Whether or not the content view's content insets should be updated
 *  when the bottom bar opens and closes.
 */
@property (nonatomic) BOOL bottomBarShouldAdjustContentInsets;

/**
 *  Whether or not the bottom bar is currently open.
 */
@property (nonatomic, readonly) BOOL bottomBarViewIsOpen;

/**
 *  Opens the bottom bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)openBottomBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Closes the bottom bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)closeBottomBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Left Bar

/**
 *  The state of the left bar.
 */
@property (nonatomic) RBToolbarContainerBarState leftBarViewState;

/**
 *  The left bar view.
 */
@property (nonatomic, nullable) UIView *leftBarView;

/**
 *  Whether or not the content view's content insets should be updated
 *  when the left bar opens and closes.
 */
@property (nonatomic) BOOL leftBarShouldAdjustContentInsets;

/**
 *  Whether or not the left bar is currently open.
 */
@property (nonatomic, readonly) BOOL leftBarViewIsOpen;

/**
 *  Opens the left bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)openLeftBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Closes the left bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)closeLeftBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Right Bar

/**
 *  The state of the right bar.
 */
@property (nonatomic) RBToolbarContainerBarState rightBarViewState;

/**
 *  The right bar view.
 */
@property (nonatomic, nullable) UIView *rightBarView;

/**
 *  Whether or not the content view's content insets should be updated
 *  when the right bar opens and closes.
 */
@property (nonatomic) BOOL rightBarShouldAdjustContentInsets;

/**
 *  Whether or not the right bar is currently open.
 */
@property (nonatomic, readonly) BOOL rightBarViewIsOpen;

/**
 *  Opens the right bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)openRightBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Closes the right bar.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)closeRightBarWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

@end

/**
 *  A delegate that receives `RBToolbarContainerView` events.
 */
@protocol RBToolbarContainerViewDelegate <NSObject>

@optional

/**
 *  Notifies that the top bar of a toolbar container view will open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)topBarWillOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the top bar of a toolbar container view did open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)topBarDidOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the top bar of a toolbar container view will close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)topBarWillCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the top bar of a toolbar container view did close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)topBarDidCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the bottom bar of a toolbar container view will open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)bottomBarWillOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the bottom bar of a toolbar container view did open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)bottomBarDidOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the bottom bar of a toolbar container view will close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)bottomBarWillCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the bottom bar of a toolbar container view did close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)bottomBarDidCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the left bar of a toolbar container view will open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)leftBarWillOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the left bar of a toolbar container view did open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)leftBarDidOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the left bar of a toolbar container view will close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)leftBarWillCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the left bar of a toolbar container view did close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)leftBarDidCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the right bar of a toolbar container view will open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)rightBarWillOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the right bar of a toolbar container view did open.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)rightBarDidOpenWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the right bar of a toolbar container view will close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)rightBarWillCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

/**
 *  Notifies that the right bar of a toolbar container view did close.
 *
 *  @param toolbarContainerView The `RBToolbarContainerView` object.
 */
- (void)rightBarDidCloseWithContainerView:(nonnull RBToolbarContainerView *)toolbarContainerView;

@end
