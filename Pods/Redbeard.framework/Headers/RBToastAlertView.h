//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBToastAlertSchema.h>

@class UIInline;

@protocol RBToastAlertViewDelegate;

/**
 *  A view presenting a toast notification message.
 */
@interface RBToastAlertView : UIView

/**
 *  A delegate to receive toast presentation events.
 */
@property (nonatomic, weak, nullable) id<RBToastAlertViewDelegate> delegate;

/**
 *  The margin to provide around the content of the alert.
 */
@property (nonatomic) UIEdgeInsets margin;

/**
 *  The margin to provide around the toast alert itself within it's parent view.
 */
@property (nonatomic) UIEdgeInsets presentationMargin;

/**
 *  The vertical alignment of the toast notification in it's parent view. Default = `RBVerticalAlignmentMiddle`.
 */
@property (nonatomic) RBVerticalAlignment presentationVerticalAlignment;

/**
 *  The horizontal alignment of the toast notification in it's parent view. Default = `RBHorizontalAlignmentCenter`.
 */
@property (nonatomic) RBHorizontalAlignment presentationHorizontalAlignment;

/**
 *  The animation duration in seconds of the fade-in transition. Default = 1.
 */
@property (nonatomic) CGFloat presentationFadeInDuration;

/**
 *  The animation duration in seconds of the fade-out transition. Default = 2.5
 */
@property (nonatomic) CGFloat presentationFadeOutDuration;

/**
 *  Whether or not the toast notification is currently visible in it's parent view.
 */
@property (nonatomic, readonly) BOOL isVisible;

/**
 *  Presents the toast notification with the given schema.
 *
 *  @param schema     The schema describing the toast notification content.
 *  @param completion An optional block to be called when the presentation transition is complete.
 */
- (void)presentWithSchema:(nonnull RBToastAlertSchema *)schema completion:(nullable dispatch_block_t)completion;

/**
 *  Positions the toast notification within it's parent view.
 */
- (void)positionInParent;

@end

/**
 *  A delegate to receive toast presentation events for an `RBToastAlertView`.
 */
@protocol RBToastAlertViewDelegate <NSObject>

@optional

/**
 *  Called when the toast alert view will become active.
 *
 *  @param toastAlertView The `RBToastAlertView` object.
 */
- (void)toastAlertViewWillBecomeActive:(nonnull RBToastAlertView *)toastAlertView;

/**
 *  Called when the toast alert view will become inactive.
 *
 *  @param toastAlertView The `RBToastAlertView` object.
 */
- (void)toastAlertViewDidBecomeInactive:(nonnull RBToastAlertView *)toastAlertView;

/**
 *  Called when the toast alert view will present in it's parent view.
 *
 *  @param toastAlertView The `RBToastAlertView` object.
 *  @param schema         The schema that describes the toast alert content that will be presented.
 */
- (void)toastAlertView:(nonnull RBToastAlertView *)toastAlertView willPresentWithSchema:(nonnull RBToastAlertSchema *)schema;

@end
