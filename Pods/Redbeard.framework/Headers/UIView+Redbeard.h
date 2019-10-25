//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  `UIView` extension methods.
 */
@interface UIView (Redbeard)

/**
 *  Initializes the view.
 *
 *  Never call this directly, it should be implemented to set up the view.
 *  It is called directly by initWithFrame: and initWithCoder:.
 */
- (void)initializeView;

/**
 *  Whether or not setNeedsLayout was called and layoutSubviews has not yet been called.
 */
@property (nonatomic, readonly) BOOL needsLayout;

#pragma mark -
#pragma mark Frame Invalidation

/**
 *  Notifies the super views in the heirarchy that this view needs its frame
 *  recalculating.  For example, it requires a different size.
 */
- (void)invalidateFrame;

/**
 *  Notifies the super views in the heirarchy that this view needs its frame
 *  recalculating with an immediate layout.
 */
- (void)invalidateFrameWithImmediateLayout;

#pragma mark -
#pragma mark Subclassing

/**
 *  Called when the view's bounds are changed.
 *
 *  @param previousBounds The previous bounds.
 *  @param bounds         The new and current bounds.
 */
- (void)boundsDidChangeFrom:(CGRect)previousBounds toBounds:(CGRect)bounds;

/**
 *  Called when the frame of a child view has been invalidated.
 *
 *  @param childView               The child view who's frame is now invalidated.
 *  @param requiresImmediateLayout Whether or not an immediate layout is required.
 */
- (void)childViewFrameDidInvalidate:(nonnull UIView *)childView requiresImmediateLayout:(BOOL)requiresImmediateLayout;

@end

