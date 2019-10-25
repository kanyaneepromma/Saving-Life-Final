//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBAlertViewController.h>
#import <Redbeard/RBAlertSchema.h>

/**
 *  A block that is called when a managed alert button is tapped by the user.
 *
 *  @param buttonIndex The index of the button that was tapped.
 */
typedef void (^AlertCompletionBlock)(NSUInteger buttonIndex);

/**
 *  `UIViewController` managed alert.
 */
@interface UIViewController (Alert) <RBAlertViewControllerDelegate>

/**
 *  The default animator to use when presenting the alert.
 */
@property (nonatomic, nonnull) RBPresentationAnimator *defaultAlertAnimator;

/**
 *  The default vertical alignment to use when positioning the alert.
 */
@property (nonatomic) RBVerticalAlignment defaultAlertAlignment;

/**
 *  The default margin to use when positioning the alert.
 */
@property (nonatomic) UIEdgeInsets defaultAlertMargin;

/**
 *  Presents a managed `RBAlertViewController` alert with the given schema.
 *
 *  @param schema     The schema of the alert.
 *  @param animated   Whether the presentation should be animated.
 *  @param completion An optional block to be called when the presentation has completed.
 */
- (void)alertWithSchema:(nonnull RBAlertSchema *)schema
               animated:(BOOL)animated
             completion:(nullable AlertCompletionBlock)completion;

/**
 *  Dismisses the top-most open alert.
 *
 *  @param animated   Whether the dismissal should be animated.
 *  @param completion An optional block to be called when the dismissal has completed.
 *
 *  @return Whether or not there was an open alert to dismiss.
 */
- (BOOL)dismissAlertWithAnimation:(BOOL)animated
                       completion:(nullable dispatch_block_t)completion;

@end
