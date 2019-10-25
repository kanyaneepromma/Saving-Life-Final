//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Describes a toast alert. Corresponds to setting up a `RBToastAlertView`.
 */
@interface RBToastAlertSchema : NSObject

/**
 *  The message text to display.
 */
@property (nonatomic, nullable) NSString *message;

/**
 *  The attributed message text to display.  This overrides `message`.
 */
@property (nonatomic, nullable) NSAttributedString *attributedMessage;

/**
 *  The image to be displayed above the text.
 */
@property (nonatomic, nullable) UIImage *image;

/**
 *  The identifier of the theme to apply to the alert prior to presenting it.
 */
@property (nonatomic, nullable) NSString *themeIdentifier;

/**
 *  Theme values to apply after any other prior theming has been applied.
 */
@property (nonatomic, nullable) NSDictionary<NSString *, id> *themeOverrides;

@end
