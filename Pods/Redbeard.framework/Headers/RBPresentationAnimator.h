//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBThemeTracker.h>
#import <Redbeard/RBPresentationContext.h>

@class RBAnimator;

/**
 *  Performs the animated transitions presenting and dismissing view controllers.
 */
@interface RBPresentationAnimator : NSObject<RBThemeTrackerDelegate>

/**
 *  The theming tracker object for the view.
 */
@property (nonatomic, readonly, nonnull) RBThemeTracker *theme;

/**
 *  The `RBAnimator` object to use when animating.
 */
@property (nonatomic, readonly, nonnull) RBAnimator *animator;

/**
 *  Whether or not the animator is allowed to dismiss view controllers.
 *  For example, when the background is tapped.
 */
@property (nonatomic) BOOL animatorCanDismiss;

/**
 *  Presents a view controller with the given context.
 *
 *  @param presentationContext The configured presentation context.
 *  @param animated            Whether or not the presentation should be animated.
 *  @param completion          A block that is called when the presentation is complete.
 *
 *  @return Whether or not the operation was successful.
 */
- (BOOL)presentWithContext:(nonnull RBPresentationContext *)presentationContext animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Causes the given presentation context, if presented, to reposition the view.
 *  This is typically called when the presenting view bounds change.
 *
 *  @param presentationContext The presentation context to reposition.
 *
 *  @return Whether or not the operation was successful.
 */
- (BOOL)repositionWithContext:(nonnull RBPresentationContext *)presentationContext;

/**
 *  Dismisses a presented presentation context.
 *
 *  @param presentationContext The presentation context to dismiss.
 *  @param animated            Whether or not the dismissal should be animated.
 *  @param completion          A block that is called when the dismissal is complete.
 *
 *  @return Whether or not the operation was successful.
 */
- (BOOL)dismissWithContext:(nonnull RBPresentationContext *)presentationContext animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

#pragma mark -
#pragma mark Subclassing

/**
 *  Performs a presentation with the given context and frame.
 *
 *  @param presentationContext The presentation context to present.
 *  @param frame               The frame to present the view to.
 *  @param animated            Whether or not the presentation should be animated.
 *  @param completion          A block that is called when the presentation is complete.
 */
- (void)performPresentationWithContext:(nonnull RBPresentationContext *)presentationContext
                               toFrame:(CGRect)frame
                              animated:(BOOL)animated
                            completion:(nullable dispatch_block_t)completion;

/**
 *  Performs a repositioning with the given context and frame.
 *
 *  @param presentationContext The presentation context to reposition.
 *  @param frame               The frame to reposition the view to.
 */
- (void)performRepositionWithContext:(nonnull RBPresentationContext *)presentationContext
                             toFrame:(CGRect)frame;

/**
 *  Performs a dismissal of the given context.
 *
 *  @param presentationContext The presentation context to dismiss.
 *  @param animated            Whether or not the dismissal should be animated.
 *  @param completion          A block that is called when the dismissal is complete.
 */
- (void)performDismissalWithContext:(nonnull RBPresentationContext *)presentationContext
                           animated:(BOOL)animated
                         completion:(nullable dispatch_block_t)completion;

/**
 *  Updates the state of the context.
 *
 *  @param presentationContext        The context to update.
 *  @param viewStack                  The stack of views that constitute it's presentation.
 *  @param doesRequireOrientationLock Whether or not the presentation of this context requires that the device orientation does not change.
 *  @param data                       Additional data associated with the presentation.
 */
- (void)updateContext:(nonnull RBPresentationContext *)presentationContext
        withViewStack:(nonnull NSArray *)viewStack
doesRequireOrientationLock:(BOOL)doesRequireOrientationLock
                 data:(nullable NSDictionary *)data;

/**
 *  Called when the animator requests that the presentation context is dismissed.
 *
 *  @param presentationContext The presentation context to dismiss.
 */
- (void)requestDismissalWithPresentationContext:(nonnull RBPresentationContext *)presentationContext;

@end
