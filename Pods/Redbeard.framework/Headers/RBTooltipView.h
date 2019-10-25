//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Redbeard/RBTooltipContainerView.h>

#import <Redbeard/RBImageView.h>
#import <Redbeard/RBLabel.h>

/**
 *  A tooltip view that can present a message and/or an image to the user.
 */
@interface RBTooltipView : RBTooltipContainerView

/**
 *  The underlying image view.
 */
@property (nonatomic, readonly, nonnull) RBImageView *imageView;

/**
 *  The underlying label view.
 */
@property (nonatomic, readonly, nonnull) RBLabel *label;

/**
 *  The margin to apply around the content of the tooltip.
 */
@property (nonatomic) UIEdgeInsets margin;

/**
 *  The spacing to apply between the image and the label when both are in use.
 */
@property (nonatomic) CGFloat spacing;

/**
 *  The message string to display in the tooltip.
 */
@property (nonatomic, nullable) NSString *message;

/**
 *  The attributed message string to display in the tooltip.
 */
@property (nonatomic, nullable) NSAttributedString *attributedMessage;

/**
 *  The image to display in the tooltip.
 */
@property (nonatomic, nullable) UIImage *image;

@end
