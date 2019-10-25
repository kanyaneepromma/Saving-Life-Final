//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  `UIView` viewport transmission and events.
 *
 *  The viewport is the currently visible part of the view.
 */
@interface UIView (Viewport)

/**
 *  The current viewport of the `UIView`
 */
@property (nonatomic, readonly) CGRect viewport;

/**
 *  Whether or not updates to the viewport are disabled.
 */
@property (nonatomic) BOOL disableViewportUpdates;

/**
 *  Marks the viewport as needing an update.
 */
- (void)setNeedsUpdateViewport;

/**
 *  Updates the viewport if an update is needed.
 */
- (void)updateViewportIfNeeded;

#pragma mark -
#pragma mark Subclassing

/**
 *  Calculates the viewport of a subview.
 *
 *  @param subview The subview to calculate the viewport of.
 *
 *  @return The calculated viewport of the subview.
 */
- (CGRect)viewportForSubview:(nonnull UIView *)subview;

/**
 *  Called when the viewport will change.
 *
 *  @param previousViewport The previous and current viewport.
 *  @param viewport         The new viewport that is about to be set.
 */
- (void)viewportWillChangeFrom:(CGRect)previousViewport to:(CGRect)viewport;

/**
 *  Called when the viewport did change.
 *
 *  @param previousViewport The previous viewport.
 *  @param viewport         The new and current viewport.
 */
- (void)viewportDidChangeFrom:(CGRect)previousViewport to:(CGRect)viewport;

@end
