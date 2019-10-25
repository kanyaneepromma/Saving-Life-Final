//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBTooltipSchema.h>
#import <Redbeard/RBTooltipView.h>

/**
 *  Provides managed tooltips for a UIView and it's children.
 */
@interface UIView (Tooltip) <RBTooltipViewDelegate>

/**
 *  Whether or not a tooltip is being presented at the descendent view.
 *
 *  @param view The view, which must be a descendent in the heirarchy.
 *
 *  @return Whether or not a tooltip is presented at the given view.
 */
- (BOOL)isPresentingTooltipForView:(nonnull UIView *)view;

/**
 *  Presents a tooltip with the given message at the given descendent view.
 *
 *  @param schema        The schema that describes the tooltip to present.
 *  @param view          The view to point the tooltip at.
 *  @param completion    An optional block to be called when the tooltip has been presented.
 */
- (void)presentTooltipWithSchema:(nonnull RBTooltipSchema *)schema
                         forView:(nonnull UIView *)view
                      completion:(nullable dispatch_block_t)completion;

/**
 *  Retrieves the `RBTooltipView` that is currently presented pointing at the given view.
 *
 *  @param view The view.
 *
 *  @return The `RBTooltipView` object, or `nil` if none is presented.
 */
- (nullable RBTooltipView *)presentedTooltipViewForView:(nonnull UIView *)view;

/**
 *  Dismisses the tooltip currently presented at the given view.
 *
 *  @param view       The view.
 *  @param completion An optional block to be called when the tooltip has been dismissed.
 */
- (void)dismissTooltipForView:(nonnull UIView *)view completion:(nullable dispatch_block_t)completion;

/**
 *  Dismisses all tooltips currently presented at views.
 *
 *  @param completion An optional block to be called when the tooltips have been dismissed.
 */
- (void)dismissAllTooltipsWithCompletion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Subclassing

/**
 *  Called when a tooltip has been presented for the given view.
 *
 *  @param view The view for which the tooltip has been presented.
 */
- (void)tooltipDidPresentForView:(nonnull UIView *)view;

/**
 *  Called when a tooltip has been dismissed for the given view.
 *
 *  @param view The view for which the tooltip has been dismissed.
 */
- (void)tooltipDidDismissForView:(nonnull UIView *)view;

@end
