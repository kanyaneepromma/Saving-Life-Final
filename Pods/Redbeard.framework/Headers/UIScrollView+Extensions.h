//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  `UIScrollView` extension methods.
 */
@interface UIScrollView (Extensions)

/**
 *  Scroll to reveal the given view and it's managed tooltip if it has one.
 *
 *  @param view       The view to reveal.
 *  @param animated   Whether or not to animate the scroll.
 *  @param completion An optional block to be called when the scroll is complete.
 */
- (void)scrollToView:(nonnull UIView *)view
            animated:(BOOL)animated
          completion:(nullable dispatch_block_t)completion;

/**
 *  Scroll to reveal the given content frame.
 *
 *  @param rect       The content frame to reveal.
 *  @param animated   Whether or not the scroll should be animated.
 *  @param completion An optional block to be called when the scroll is complete.
 */
//- (void)scrollToRect:(CGRect)rect
//            animated:(BOOL)animated
//          completion:(nullable dispatch_block_t)completion;

// Gets the content size of the top-level UIScrollView in the view heirarchy.

/**
 *  Gets the content size of the top-level `UIScrollView` in the view heirarchy.
 *
 *  @return The `CGSize` value.
 */
- (CGSize)heirarchyContentSize;

/**
 *  Gets the content offset at the top left of the content, taking into account bounds and insets.
 *
 *  @return The calculated content offset.
 */
- (CGPoint)contentOffsetAtTopLeft;

/**
 *  Gets the content offset at the bottom right of the content, taking into account bounds and insets.
 *
 *  @return The calculated content offset.
 */
- (CGPoint)contentOffsetAtBottomRight;

/**
 *  Whether or not the current scroll position is overflowing (bouncing) at the top.
 *
 *  @return The result.
 */
- (BOOL)scrollPositionIsOverflowingAtTop;

/**
 *  Whether or not the current scroll position is overflowing (bouncing) at the left.
 *
 *  @return The result.
 */
- (BOOL)scrollPositionIsOverflowingAtLeft;

/**
 *  Whether or not the current scroll position is overflowing (bouncing) at the bottom.
 *
 *  @return The result.
 */
- (BOOL)scrollPositionIsOverflowingAtBottom;

/**
 *  Whether or not the current scroll position is overflowing (bouncing) at the right.
 *
 *  @return The result.
 */
- (BOOL)scrollPositionIsOverflowingAtRight;

/**
 *  The closest ancestor scroll view in the view heirarchy that is the key (scrolling) `UIScrollView`.
 */
@property (nonatomic, readonly, nullable) UIScrollView *keyScrollView;

/**
 *  Whether or not the `UIScrollView` is currently scrolling.
 */
@property (nonatomic, readonly) BOOL isScrolling;

/**
 *  Whether or not this `UIScrollView` is scrolling or is a part of currently scrolling
 *  content in a parent `UIScrollView`.
 */
@property (nonatomic, readonly) BOOL isScrollingIncludingSuperviews;

/**
 *  Whether or not the content requires horizontal scrolling.
 */
@property (nonatomic, readonly) BOOL contentRequiresHorizontalScrolling;

/**
 *  Whether or not the content requires vertical scrolling.
 */
@property (nonatomic, readonly) BOOL contentRequiresVerticalScrolling;

/**
 *  Whether or not the content requires scrolling.
 */
@property (nonatomic, readonly) BOOL contentRequiresScrolling;

/**
 *  Stops the current scrolling operation.
 */
- (void)stopScrolling;

@end
