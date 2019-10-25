//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/UIView+FormField.h>
#import <Redbeard/RBInputView.h>

/**
 *  A single-line text input field.
 */
@interface RBTextField : UITextField<RBInputViewDelegate>

/**
 *  The margin of space to provide around the text.
 */
@property (nonatomic) UIEdgeInsets textMargin;

/**
 *  The color of the placeholder text.
 */
@property (nonatomic, nullable) UIColor *placeholderColor;

/**
 *  The margin to apply to the left view.
 */
@property (nonatomic) UIEdgeInsets leftViewMargin;

/**
 *  The margin to apply to the right view.
 */
@property (nonatomic) UIEdgeInsets rightViewMargin;

/**
 *  Sets the `leftView` to an `RBImageView` with the give image. If `nil` is provided this removes any previously assigned `RBImageView`
 *  on the `leftView`. Setting nil only removes the `RBImageView` previously assigned if `leftView` contains another UIView it will NOT
 *  be set to `nil`.
 */
@property (nonatomic, nullable) UIImage *leftViewImage;

/**
 *  Sets the `rightView` to an `RBImageView` with the give image. If `nil` is provided this removes any previously assigned `RBImageView`
 *  on the `rightView`. Setting nil only removes the `RBImageView` previously assigned if `rightView` contains another UIView it will NOT
 *  be set to `nil`.
 */
@property (nonatomic, nullable) UIImage *rightViewImage;

#pragma mark -
#pragma mark Subclassing

/**
 *  Determines whether the control value will be updated live as text changes.
 */
@property (nonatomic, readonly) BOOL shouldUpdateControlValueOnTextChange;

/**
 *  Determines whether the text should be updated when the control value changes.
 */
@property (nonatomic, readonly) BOOL shouldUpdateTextOnControlValueChange;

/**
 *  Called when the text changes.
 */
- (void)textDidChange;

/**
 *  Whether or not the field should allow the keyboard to open when it is tapped.
 */
@property (nonatomic, readonly) BOOL shouldBeginEditing;

/**
 *  Called when the keyboard opened and editing has begun.
 */
- (void)didBeginEditing;

/**
 *  Whether or not the field should allow the keyboard to close.
 */
@property (nonatomic, readonly) BOOL shouldEndEditing;

/**
 *  Called when the keyboard closed and editing has ended.
 */
- (void)didEndEditing;

/**
 *  Whether or not to permit the user edit.
 *
 *  @param range  The range of the text that has been changed.
 *  @param string The string that the text has been changed to.
 *
 *  @return Whether or not to permit the change.
 */
- (BOOL)shouldChangeCharactersInRange:(NSRange)range replacementString:(nonnull NSString *)string;

/**
 *  Whether or not the field should clear.
 */
@property (nonatomic, readonly) BOOL shouldClear;

/**
 *  Whether or not the field should return.
 */
@property (nonatomic, readonly) BOOL shouldReturn;

@end

