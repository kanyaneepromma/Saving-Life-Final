//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  A delegate of a managed form control, received control value update events.
 */
@protocol RBFormFieldValueDelegate <NSObject>

@required

/**
 *  Called when the current value of a control has changed.
 *
 *  @param controlValue     The new value of the control.
 *  @param fromControlValue The previous value of the control.
 *  @param field            The control view who's current value is changing.
 */
- (void)controlValueDidChangeTo:(nullable id)controlValue from:(nullable id)fromControlValue withField:(nonnull UIView *)field;

/**
 *  Called when the current value of a control will change.
 *
 *  @param controlValue     The new value of the control.
 *  @param fromControlValue The previous value of the control.
 *  @param field            The control view who's current value is changing.
 */
- (void)controlValueWillChangeTo:(nullable id)controlValue from:(nullable id)fromControlValue withField:(nonnull UIView *)field;

@end

/**
 *  Form field value and validation management.
 */
@interface UIView (FormField)

/**
 *  Whether or not the field did validate.
 */
@property (nonatomic) BOOL didValidate;

/**
 *  Whether or not validation has been performed on the field.
 */
@property (nonatomic) BOOL validationProcessed;

/**
 *  The current value of the field.
 */
@property (nonatomic, nullable) id controlValue;

/**
 *  The delegate to receive control value update events.
 */
@property (nonatomic, weak, nullable) id<RBFormFieldValueDelegate> controlValueDelegate;

/**
 *  Updates the theme state of the field according to it's validation status.
 */
- (void)updateFormFieldThemeState;

/**
 *  Sets the `controlValue` property without calling events such as `controlValueWillChangeTo:`, `controlValueDelegate` ...
 *  Useful when setting inital values or programmtically setting values.
 *
 *  @param controlValue     The control value to set.
 */
- (void)setControlValueWithoutInvokingEventsAndDelegates:(nullable id)controlValue;

/**
 *  Sets the `inputAccessoryView` property.
 *
 *  @param view     The input accessory view.
 */
- (void)applyInputAccessoryView:(nullable UIView *)view;

#pragma mark -
#pragma mark Subclassing

/**
 *  Whether or not this view is a form field.
 */
@property (nonatomic, readonly) BOOL isFormField;

/**
 *  Whether or not the form field uses an input view to edit.
 */
@property (nonatomic, readonly) BOOL formFieldDoesUseInputView;

/**
 *  Called to preprocess the control value before it's set.
 *
 *  @param controlValue The new control value.
 *
 *  @return The processed new control value.
 */
- (nullable id)processControlValueBeforeChange:(nullable id)controlValue;

/**
 *  Called when the control value will be updated.
 *
 *  @param controlValue     The new control value being assigned.
 *  @param fromControlValue The previous control value being replaced.
 */
- (void)controlValueWillChangeTo:(nullable id)controlValue from:(nullable id)fromControlValue;

/**
 *  Called when the control value was updated.
 *
 *  @param controlValue     The new control value being assigned.
 *  @param fromControlValue The previous control value being replaced.
 */
- (void)controlValueDidChangeTo:(nullable id)controlValue from:(nullable id)fromControlValue;

@end
