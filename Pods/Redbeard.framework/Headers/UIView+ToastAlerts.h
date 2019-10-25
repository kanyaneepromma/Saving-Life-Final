//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBToastAlertView.h>

/**
 *  `UIView` toast alerts
 */
@interface UIView (ToastAlerts) <RBToastAlertViewDelegate>

/**
 *  The toast alert view.
 */
@property (nonatomic, readonly, nullable) RBToastAlertView *toastAlertView;

/**
 *  Presents a `RBToastAlertView` toast alert with the given schema.
 *
 *  @param schema     The schema describing the toast alert to present.
 *  @param completion An optional block to be called when the toast alert has been presented.
 */
- (void)toastAlert:(nonnull RBToastAlertSchema *)schema completion:(nullable dispatch_block_t)completion;

@end
