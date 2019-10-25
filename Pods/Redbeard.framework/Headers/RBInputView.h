//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol RBInputViewDelegate;

/**
 *  An abstract managed base input view class.
 *  Provides a consistent API for managing the current value and events.
 */
@interface RBInputView : UIView

/**
 *  A delegate to provide current value updating. Must not be `nil`.
 */
@property (nonatomic, weak, nullable) id<RBInputViewDelegate> delegate;

/**
 *  The current value of the input view.
 */
@property (nonatomic, nullable) id currentValue;

/**
 *  The target that the input view is displaying for.
 */
@property (nonatomic, nonnull) UIResponder *target;

/**
 *  Closes the input view.
 */
- (void)closeInputView;

#pragma mark -
#pragma mark Subclassing

/**
 *  The desired height of this type of input view.
 *
 *  @return The desired height.
 */
+ (CGFloat)desiredHeight;

/**
 *  Called when the current value was changed.  Implement this
 *  method to update the UI accordingly.
 */
- (void)currentValueDidChange;

/**
 *  Called when the current value should be updated from the input UI.
 */
- (void)updateCurrentValue;

/**
 *  Called when the input view opened.
 */
- (void)didOpen;

/**
 *  Called when the input view closed.
 */
- (void)didClose;

@end

/**
 *  A delegate to provide current value updating with an `RBInputView` object.
 */
@protocol RBInputViewDelegate <NSObject>

@required

/**
 *  Notifies the delegate that the input view value changed.
 *
 *  @param inputView The input view.
 *  @param value     The new value.
 */
- (void)inputView:(nonnull RBInputView *)inputView valueChanged:(nullable id)value;

/**
 *  Gets the value that should be initially displayed in the input view.
 *
 *  @param inputView The input view requesting the value.
 *
 *  @return The value that should be initially displayed.
 */
- (nullable id)dataForInputView:(nonnull RBInputView *)inputView;

@end
