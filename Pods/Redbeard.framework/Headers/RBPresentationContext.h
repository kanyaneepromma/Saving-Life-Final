//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RBPresentationAnimator;

/** The state that a presentation is currently in. */
typedef NS_ENUM(NSInteger, RBPresentationState)
{
    /** No state - not Presented. */
    RBPresentationStateNone = 0,
    
    /** The view is currently being presented (animated). */
    RBPresentationStatePresenting,

    /** The view is currently presented. */
    RBPresentationStatePresented,
    
    /** The view is currently being dismissed (animated). */
    RBPresentationStateDismissing
};

/**
 *  A block that is called to request that the frame is calculated for a presented view.
 *
 *  @return The new `CGRect` frame value for the presented view.
 */
typedef CGRect(^PresentationLayoutBlock)(void);

@protocol RBPresentationContextDelegate;

/**
 *  A presentation context, containing the settings and state data for a presentation.
 */
@interface RBPresentationContext : NSObject

/**
 *  A delegate that is issued dismissal requests from the context.
 */
@property (nonatomic, weak, nullable) id<RBPresentationContextDelegate> delegate;

/**
 *  The `RBPresentationAnimator` object that is responsible for presentation and dismissal transitions.
 */
@property (nonatomic, readonly, nullable) RBPresentationAnimator *animator;

/**
 *  The current state of the presentation context.
 */
@property (nonatomic, readonly) RBPresentationState state;

/**
 *  The `UIViewController` being presented.
 */
@property (nonatomic, readonly, nonnull) UIViewController *viewController;

/**
 *  The presenting `UIViewController` in which the presentation occurs.
 */
@property (nonatomic, readonly, nonnull) UIViewController *containerViewController;

/**
 *  Whether or not the presentation requires that the UI orientation is locked.
 */
@property (nonatomic, readonly) BOOL doesRequireOrientationLock;

/**
 *  Logistical presentation data storage.
 */
@property (nonatomic, readonly, nullable) NSDictionary *data;

/**
 *  Creates a new presentation context.
 *
 *  @param viewController          The `UIViewController` to present.
 *  @param containerViewController The containing `UIViewController` to present within.
 *  @param layoutBlock             The block that is called to determine the frame to position the presented view controller in.
 *  @param animator                The `RBPresentationAnimator` object to use in transitions.
 *
 *  @return The configured presentation context.
 */
- (nonnull instancetype)initWithView:(nonnull UIViewController *)viewController
               containerView:(nonnull UIViewController *)containerViewController
                 layoutBlock:(nonnull PresentationLayoutBlock)layoutBlock
               usingAnimator:(nonnull RBPresentationAnimator *)animator;

/**
 *  Brings all of views that constitute the presentation to the front.
 */
- (void)bringViewsToFront;

@end

/**
 *  A delegate that is issued dismissal requests from a `RBPresentationContext`.
 */
@protocol RBPresentationContextDelegate <NSObject>

@required

/**
 *  Requests that the presentation context is dismissed.
 *
 *  @param presentationContext The presentation context to dismiss.
 */
- (void)presentationContextDoesRequestDismissal:(nonnull RBPresentationContext *)presentationContext;

@end
