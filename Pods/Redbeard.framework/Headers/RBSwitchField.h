//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/UIView+FormField.h>

/**
 *  A managed `UISwitch` with an optional label.
 */
@interface RBSwitchField : UIControl

/**
 *  The margin around the `UISwitch` view.
 */
@property (nonatomic) UIEdgeInsets margin;

/**
 *  The spacing between the `UISwitch` view and it's label (if there is one).
 */
@property (nonatomic) CGFloat spacing;

/**
 *  The tint color when the switch is on.
 */
@property (nonatomic, nullable) UIColor *onTintColor;

/**
 *  The tint color of the switch.
 */
@property (nonatomic, nonnull) UIColor *tintColor;

/**
 *  The tint color of the thumb of the switch.
 */
@property (nonatomic, nullable) UIColor *thumbTintColor;

/**
 *  The image to display when the switch is on.
 */
@property (nonatomic, nullable) UIImage *onImage;

/**
 *  The image to display when the switch is off.
 */
@property (nonatomic, nullable) UIImage *offImage;

/**
 *  The label text to display next to the switch.
 */
@property (nonatomic, nullable) NSString *labelText;

/**
 *  Whether to display the label to the left or the right of the switch.
 */
@property (nonatomic) RBHorizontalAlignment labelAlignment;

/**
 *  Gets or sets whether the switch is on.
 */
@property (nonatomic, getter=isOn) BOOL on;

/**
 *  Updates the switch's state with an animation.
 *
 *  @param on       Whether the switch should be turned on (`true`) or off (`false`).
 *  @param animated Whether or not the transition should be animated.
 */
- (void)setOn:(BOOL)on animated:(BOOL)animated;

@end
