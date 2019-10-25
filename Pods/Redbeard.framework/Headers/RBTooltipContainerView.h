//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/** The direction that the arrow should point at the target view. */
typedef NS_ENUM(NSInteger, RBTooltipPointDirection)
{
    /** The arrow points down to the target view. */
    RBTooltipPointDirectionDown = 0,

    /** The arrow points up to the target view. */
    RBTooltipPointDirectionUp
};

/** The type of animation to use when displaying and dismissing the tooltip. */
typedef NS_ENUM(NSInteger, RBTooltipAnimationType)
{
    /** The tooltip slides in and out. */
    RBTooltipAnimationTypeSlide = 0,

    /** The tooltip pops in and out. */
    RBTooltipAnimationTypePop
};

@protocol RBTooltipViewDelegate;

/**
 *  A tooltip container view that can be configured to display any content.
 */
@interface RBTooltipContainerView : UIView

/**
 *  A delegate to receive dismissal events.
 */
@property (nonatomic, weak, nullable) id<RBTooltipViewDelegate> delegate;

/**
 *  The content view that will be displayed within the tooltip.
 */
@property (nonatomic, nullable) UIView *contentView;

#pragma mark -
#pragma mark State

/**
 *  Whether or not the tooltip is currently presented.
 */
@property (nonatomic, readonly) BOOL isPresented;

/**
 *  Whether or not the tooltip is currently presenting.
 */
@property (nonatomic, readonly) BOOL isPresenting;

/**
 *  Whether or not the tooltip is currently dismissing.
 */
@property (nonatomic, readonly) BOOL isDismissing;

/**
 *  The view in which the tooltip is being presented.
 */
@property (nonatomic, readonly, weak, nullable) UIView *containerView;

/**
 *  The view at which the tooltip is being presented.
 */
@property (nonatomic, readonly, weak, nullable) UIView *targetView;

#pragma mark -
#pragma mark Settings

/**
 *  The corner radius of the tooltip bubble.
 */
@property (nonatomic) CGFloat cornerRadius;

/**
 *  The size of the pointer on the tooltip bubble.
 */
@property (nonatomic) CGFloat pointerSize;

/**
 *  The background color of the tooltip bubble.
 */
@property (nonatomic, nullable) UIColor *backgroundColor;

/**
 *  Whether the tooltip bubble should not be dismissed when tapped by the user.  Default = false.
 */
@property (nonatomic) BOOL disableTapToDismiss;

/**
 *  The color of the border of the tooltip bubble.
 */
@property (nonatomic, nullable) UIColor *borderColor;

/**
 *  The width of the border of the tooltip bubble in points (pt).
 */
@property (nonatomic) CGFloat borderWidth;

/**
 *  The type of animation that should be used when presenting and dismissing the tooltip.
 */
@property (nonatomic) RBTooltipAnimationType animationType;

#pragma mark -
#pragma mark Present / Dismiss

/**
 *  Presents the tooltip.
 *
 *  @param targetView    The view at which the tooltip should be presented.
 *  @param containerView The containing view in which the tooltip should be presented.
 *  @param animated      Whether or not the transition should be animated.
 *  @param completion    An optional block to be called when the presentation is complete.
 */
- (void)presentPointingAtView:(nonnull UIView *)targetView
                       inView:(nonnull UIView *)containerView
                     animated:(BOOL)animated
                   completion:(nullable dispatch_block_t)completion;

/**
 *  Dismisses the tooltip.
 *
 *  @param animated   Whether or not the transition should be animated.
 *  @param completion An optional block to be called when the dismissal is complete.
 */
- (void)dismissAnimated:(BOOL)animated
             completion:(nullable dispatch_block_t)completion;

@end

/**
 *  A delegate to receive dismissal events from a tooltip view.
 */
@protocol RBTooltipViewDelegate <NSObject>

/**
 *  Called when the tooltip view was dismissed due to a user tap.
 *
 *  @param tooltipView   The `RBTooltipContainerView` object.
 *  @param targetView    The view that the tooltip was pointed at.
 *  @param containerView The view in which the tooltip was presented.
 */
- (void)tooltipViewWasDismissedByUser:(nonnull RBTooltipContainerView *)tooltipView pointingAtView:(nonnull UIView *)targetView inView:(nonnull UIView *)containerView;

@end
