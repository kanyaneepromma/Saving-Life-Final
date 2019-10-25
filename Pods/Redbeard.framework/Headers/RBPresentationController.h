//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBPresentationAnimator.h>

// Note: You usually will not need to create this, they exist on all UIViewController under the presentationController
//       property.  They're lazy-loaded.

/**
 *  Manages the presentation of view controllers within a parent view controller.
 *
 *  For normal use, you do not need to create one of these, but can use them using
 *  the presentationController property on any UIViewController.
 */
@interface RBPresentationController : NSObject

/**
 *  Whether or not the controller is currently presenting a view controller.
 */
@property (nonatomic, readonly) BOOL isPresenting;

/**
 *  Whether or not the controller is currently dismissing a view controller.
 */
@property (nonatomic, readonly) BOOL isDismissing;

/**
 *  Whether or not the controller currently has a view controller presented.
 */
@property (nonatomic, readonly) BOOL isPresented;

/**
 *  Whether or not the controller requires that the UI orientation is locked.
 */
@property (nonatomic, readonly) BOOL requiresOrientationLock;

/**
 *  The default animator to use when one isn't provided in a presentation context.
 */
@property (nonatomic, nonnull) RBPresentationAnimator *defaultAnimator;

/**
 *  The number of view controllers that are currently presented.
 */
@property (nonatomic, readonly) NSUInteger presentedViewControllerCount;

/**
 *  Initializes a new presentation controller.
 *
 *  @param viewController The `UIViewController` that the presentation controller will belong to.
 *
 *  @return The initialized presentation controller.
 */
- (nullable id)initWithViewController:(nonnull UIViewController *)viewController;

/**
 *  Gets the presented view controller at the given index from the top.
 *
 *  @param indexFromTop The zero-based index from the top.
 *
 *  @return The presented `UIViewController` object.
 */
- (nonnull UIViewController *)presentedViewControllerFromTop:(NSUInteger)indexFromTop;

/**
 *  Presents a view controller.
 *
 *  @param viewController The `UIViewController` object to present.
 *  @param positionBlock  The block that is called to determine the frame that the presented view should occupy.
 *  @param animated       Whether or not the presentation transition should be animated.
 *  @param completion     An optional block to be called when the presentation is complete.
 *
 *  @return Whether or not the operation was successful.
 */
- (BOOL)presentViewController:(nonnull UIViewController *)viewController
            withPositionBlock:(nullable CGRect(^)(void))positionBlock
                     animated:(BOOL)animated
                   completion:(nullable dispatch_block_t)completion;

/**
 *  Presents a view controller.
 *
 *  @param viewController The `UIViewController` object to present.
 *  @param animator       The animator to use when presenting and dismissing the view controller.
 *  @param positionBlock  The block that is called to determine the frame that the presented view should occupy.
 *  @param animated       Whether or not the presentation transition should be animated.
 *  @param completion     An optional block to be called when the presentation is complete.
 *
 *  @return Whether or not the operation was successful.
 */
- (BOOL)presentViewController:(nonnull UIViewController *)viewController
                usingAnimator:(nonnull RBPresentationAnimator *)animator
            withPositionBlock:(nullable CGRect(^)(void))positionBlock
                     animated:(BOOL)animated
                   completion:(nullable dispatch_block_t)completion;

/**
 *  Dismisses the top-most presented view controller.
 *
 *  @param animated   Whether or not the dismissal should be animated.
 *  @param completion An optional block to be called when the dismissal is complete.
 */
- (void)dismissViewControllerAnimated:(BOOL)animated
                           completion:(nullable dispatch_block_t)completion;

/**
 *  Brings all presentation views to the front.
 */
- (void)bringSubviewsToFront;

/**
 *  Repositions all presentation views.
 */
- (void)setNeedsLayout;

@end
