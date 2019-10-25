//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Describes a managed tooltip to be presented.
 */
@interface RBTooltipSchema : NSObject

/**
 *  The message text to display.
 */
@property (nonatomic, nullable) NSString *message;

/**
 *  The attributed message text to display.  This overrides `message`.
 */
@property (nonatomic, nullable) NSAttributedString *attributedMessage;

/**
 *  The image to display above the text.
 */
@property (nonatomic, nullable) UIImage *image;

/**
 *  The identifier of the theme to apply to the tooltip prior to presenting it.
 */
@property (nonatomic, nullable) NSString *themeIdentifier;

/**
 *  Theme values to apply after any other prior theming has been applied.
 */
@property (nonatomic, nullable) NSDictionary<NSString *, id> *themeOverrides;

@end
