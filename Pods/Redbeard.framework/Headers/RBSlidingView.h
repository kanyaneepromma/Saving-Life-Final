//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol RBSlidingViewDelegate;

/**
 *  A sliding container of pages.
 */
@interface RBSlidingView : UIView

/**
 *  Whether or not the user can swipe between pages.  Default = true.
 */
@property (nonatomic) BOOL panningEnabled;

/**
 *  The minimum size of the sliding page container view.
 */
@property (nonatomic) CGSize minimumSize;

/**
 *  Whether or not the container view sizes to fit the current page only (true)
 *  or to fit all of the pages (false).  Default = false.
 */
@property (nonatomic) BOOL sizeToCurrentPageOnly;

/**
 *  The `RBAnimator` to use when sliding between pages.
 */
@property (nonatomic, readonly, nonnull) RBAnimator *animator;

/**
 *  The delegate to be informed of page transition events.
 */
@property (nonatomic, weak, nullable) id<RBSlidingViewDelegate> delegate;

/**
 *  The number of pages in the container.
 */
@property (nonatomic, readonly) NSInteger pages;

/**
 *  Retrieves the page view at the given index.
 *
 *  @param index The page index.
 *
 *  @return The retrieved page view.
 */
- (nonnull UIView *)pageViewAtIndex:(NSInteger)index;

/**
 *  Adds a new page with the given title.
 *
 *  @param pageView The page view.
 */
- (void)addPage:(nonnull UIView *)pageView;

/**
 *  Inserts a new page with the given title at the given index.
 *
 *  @param pageView The page view.
 *  @param index    The page index at which to insert.
 */
- (void)insertPage:(nonnull UIView *)pageView atIndex:(NSInteger)index;

/**
 *  Removes the page with the given view.
 *
 *  @param pageView The page view.
 */
- (void)removePage:(nonnull UIView *)pageView;

/**
 *  Removes the page at the given index.
 *
 *  @param index The page index.
 */
- (void)removePageAtIndex:(NSInteger)index;

/**
 *  Removes all pages.
 */
- (void)removeAllPages;

/**
 *  The index of the current page.
 */
@property (nonatomic, readonly) NSInteger currentPageIndex;

/**
 *  Moves to the page with the given view.
 *
 *  @param pageView   The page view.
 *  @param animated   Whether or not the transition should be animated.
 *  @param completion An optional block to be called when the transition is complete.
 */
- (void)moveToPage:(nonnull UIView *)pageView animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Moves to the page at the given index.
 *
 *  @param index      The page index.
 *  @param animated   Whether or not the transition should be animated.
 *  @param completion An optional block to be called when the transition is complete.
 */
- (void)moveToPageAtIndex:(NSInteger)index animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Subclassing

/**
 *  Called when a swipe gesture will reveal the page at the given index (but not select it).
 *
 *  @param index The page index.
 */
- (void)willPeakAtIndex:(NSInteger)index;

/**
 *  Called when a swipe gesture did reveal the page at the given index (but not select it).
 *
 *  @param index                The page index.
 *  @param didBecomeCurrentPage Whether or not the page did become the current page.
 */
- (void)didPeakAtIndex:(NSInteger)index didBecomeCurrentPage:(BOOL)didBecomeCurrentPage;

/**
 *  Called when the container will move from one page to another.
 *
 *  @param fromIndex The index of the page being moved away from.
 *  @param toIndex   The index of the page being moved to.
 *  @param animated  Whether or not the transition is animated.
 */
- (void)willMoveFromIndex:(NSInteger)fromIndex toIndex:(NSInteger)toIndex animated:(BOOL)animated;

/**
 *  Called when the container did move from one page to another.
 *
 *  @param fromIndex The index of the page being moved away from.
 *  @param toIndex   The index of the page being moved to.
 *  @param animated  Whether or not the transition is animated.
 */
- (void)didMoveFromIndex:(NSInteger)fromIndex toIndex:(NSInteger)toIndex animated:(BOOL)animated;

@end

/**
 *  An `RBSlidingView` delegate that receives events related to the sliding between pages.
 */
@protocol RBSlidingViewDelegate <NSObject>

@optional

/**
 *  Called when a swipe gesture will reveal the page at the given index (but not select it).
 *
 *  @param slidingView              The sliding view.
 *  @param index                    The page index.
 */
- (void)slidingView:(nonnull RBSlidingView *)slidingView willPeakAtIndex:(NSInteger)index;

/**
 *  Called when a swipe gesture did reveal the page at the given index (but not select it).
 *
 *  @param slidingView              The sliding view.
 *  @param index                    The page index.
 *  @param didBecomeCurrentPage     Whether or not the page did become the current page.
 */
- (void)slidingView:(nonnull RBSlidingView *)slidingView didPeakAtIndex:(NSInteger)index didBecomeCurrentPage:(BOOL)didBecomeCurrentPage;

/**
 *  The sliding page container view will slide from one page to another.
 *
 *  @param slidingView              The sliding view.
 *  @param fromIndex                The index of the page being moved away from.
 *  @param toIndex                  The index of the page being moved to.
 *  @param animated                 Whether or not the operation is animated.
 */
- (void)slidingView:(nonnull RBSlidingView *)slidingView willMoveFromIndex:(NSInteger)fromIndex toIndex:(NSInteger)toIndex animated:(BOOL)animated;

/**
 *  The sliding page container view did slide from one page to another.
 *
 *  @param slidingView              The sliding view.
 *  @param fromIndex                The index of the page being moved away from.
 *  @param toIndex                  The index of the page being moved to.
 *  @param animated                 Whether or not the operation is animated.
 */
- (void)slidingView:(nonnull RBSlidingView *)slidingView didMoveFromIndex:(NSInteger)fromIndex toIndex:(NSInteger)toIndex animated:(BOOL)animated;

@end
