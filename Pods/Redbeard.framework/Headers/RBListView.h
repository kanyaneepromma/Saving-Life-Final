//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBTextField.h>
#import <Redbeard/RBListInputView.h>

/**
 *  An option for a list field.
 */
@interface RBListViewOption : NSObject

/**
 *  The value of the item.
 */
@property (nonatomic, readonly, nullable) NSString *value;

/**
 *  The display text of the item.
 */
@property (nonatomic, readonly, nullable) NSString *displayText;

/**
 *  Initializes the list field item.
 *
 *  @param value       The value of the item.
 *  @param displayText The display text of the item.
 *
 *  @return The initialized list field item.
 */
- (nonnull instancetype)initWithValue:(nonnull NSString *)value displayText:(nonnull NSString *)displayText;

@end

/**
 *  A list field.
 */
@interface RBListView : RBTextField<RBInputViewDelegate>

/**
 *  An array of `RBListViewOption` objects.
 */
@property (nonatomic, nullable) NSArray<RBListViewOption *> *options;

/**
 *  The current selected item value.
 */
@property (nonatomic, nullable) NSString *selectedValue;

/**
 *  The current selected item display text.
 */
@property (nonatomic, nullable) NSString *selectedDisplayText;

/**
 *  Converts an array of strings to `RBListViewOption` options where the value and display text are the same.
 *
 *  @param strings  The list of strings to convert from.
 *
 *  @return Array of `RBListViewOption` options.
 */
+ (nonnull NSArray<RBListViewOption *> *)options:(nonnull NSArray<NSString *> *)strings;

@end
