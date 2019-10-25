//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class RBGridPositioner;

@protocol RBAlertViewControllerDelegate;

/**
 * A view controller that displays an alert message with buttons. Used by UIViewController+Alert.h.
 */
@interface RBAlertViewController : UIViewController

/**
 * The delegate to be informed of button selections by the user.
 */
@property (nonatomic, weak, nullable) id<RBAlertViewControllerDelegate> delegate;

/**
 * The message string to display on the alert.
 */
@property (nonatomic, nullable) NSString *message;

/**
 *  The attributed message to display on the alert.
 */
@property (nonatomic, nullable) NSAttributedString *attributedMessage;

/**
 *  The image to display above the text.
 */
@property (nonatomic, nullable) UIImage *image;

/**
 * The index of the primary button. Default is `0`, set `-1` to exclude setting a primary button.
 */
@property (nonatomic) NSInteger primaryButtonIndex;

/**
 * An array of button titles that define the buttons that will be provided.
 */
@property (nonatomic, nullable) NSArray<NSString *> *buttonTitles;

/**
 *  The overall layout positioner used. You may theme this positioner. Default values =
 *  spacing = 10,
 *  dimensions = 1,
 *  margin = [10, 10, 10, 10],
 *  orientation = `RBOrientationVertical`,
 *  sizing = `RBGridPositionerSizeEvenly`.
 */
@property (nonatomic, nonnull, readonly) RBGridPositioner *positioner;

/**
 *  The layout positioner used for the buttons. You may theme this positioner. Default values =
 *  spacing = 10,
 *  dimensions = 1,
 *  margin = [10, 10, 10, 10],
 *  orientation = `RBOrientationVertical`,
 *  sizing = `RBGridPositionerSizeEvenly`.
 */
@property (nonatomic, nonnull, readonly) RBGridPositioner *buttonPositioner;

/**
 *  Calculates the size that would be required to display the alert in the given available container size.
 *
 *  @param size The available container size.
 *
 *  @return The size that would be required to present the alert view.
 */
- (CGSize)sizeWithContainerSize:(CGSize)size;

@end

/**
 * The `RBAlertViewController` delegate.
 */
@protocol RBAlertViewControllerDelegate <NSObject>

@required

/**
 *  Called when a user button has been tapped on the alert view controller.
 *
 *  @param alertViewController The `RBAlertViewController` object.
 *  @param buttonIndex         The index of the button that has been tapped.
 */
- (void)alertViewController:(nonnull RBAlertViewController *)alertViewController
   didSubmitWithButtonIndex:(NSInteger)buttonIndex;

@end
