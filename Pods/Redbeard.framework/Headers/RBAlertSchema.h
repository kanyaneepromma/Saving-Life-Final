//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  A message alert schema. Corresponds to setting up a `RBAlertViewController`. If you provide no buttons by default a button with title 'Ok' is set.
 */
@interface RBAlertSchema : NSObject

/**
 *  The message text to display.
 */
@property (nonatomic, nullable) NSString *message;

/**
 *  The attributed text to display.
 */
@property (nonatomic, nullable) NSAttributedString *attributedMessage;

/**
 *  The image to display above the text.
 */
@property (nonatomic, nullable) UIImage *image;

/**
 *  Whether or not the alignment specified in this schema should be used
 *  rather than the default value on the presenting view controller.
 */
@property (nonatomic) BOOL shouldUseSchemaAlignment;

/**
 *  The vertical alignment to use when positioning the alert.
 */
@property (nonatomic) RBVerticalAlignment alignment;

/**
 *  Whether or not the margin specified in this schema should be used
 *  rather than the default value on the presenting view controller.
 */
@property (nonatomic) BOOL shouldUseSchemaMargin;

/**
 *  The margin to use around the outside of the alert view when
 *  positioning it within the presenting view controller.
 */
@property (nonatomic) UIEdgeInsets margin;

/**
 *  The animator to use when animating the presentation and dismissal transitions.
 */
@property (nonatomic, nullable) RBPresentationAnimator *animator;

/**
 *  The index of the primary button. Default is `0`, set `-1` to exclude setting a primary button.
 */
@property (nonatomic) NSInteger primaryButtonIndex;

/**
 *  An array of button titles that define the buttons that will be provided.
 */
@property (nonatomic, nonnull) NSArray<NSString *> *buttonTitles;

/**
 *  The identifier of the theme to apply to the alert prior to presenting it.
 */
@property (nonatomic, nullable) NSString *themeIdentifier;

/**
 *  Theme values to apply after any other prior theming has been applied.
 */
@property (nonatomic, nullable) NSDictionary<NSString *, id> *themeOverrides;

@end
