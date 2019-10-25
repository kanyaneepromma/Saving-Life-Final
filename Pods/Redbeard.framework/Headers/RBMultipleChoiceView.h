//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/UIView+FormField.h>

/**
 *  An item for a multiple choice field.
 */
@interface RBMultipleChoiceViewOption : NSObject

/**
 *  The value of the item.
 */
@property (nonatomic, readonly, nonnull) NSString *value;

/**
 *  The display text of the item.
 */
@property (nonatomic, readonly, nullable) NSString *displayText;

/**
 *  The display image of the item.
 */
@property (nonatomic, readonly, nullable) UIImage *displayImage;

/**
 *  Initializes the item.
 *
 *  @param value       The value of the item.
 *  @param displayText The display text of the item.
 *
 *  @return The initialized item.
 */
- (nonnull instancetype)initWithValue:(nonnull NSString *)value displayText:(nonnull NSString *)displayText;

/**
 *  Initializes the item.
 *
 *  @param value        The value of the item.
 *  @param displayText  The display text of the item.
 *  @param displayImage The display image of the item.
 *
 *  @return The initialized item.
 */
- (nonnull instancetype)initWithValue:(nonnull NSString *)value displayText:(nullable NSString *)displayText displayImage:(nullable UIImage *)displayImage;

@end

@protocol RBMultipleChoiceViewDelegate;

/**
 *  A multiple choice field.
 */
@interface RBMultipleChoiceView : UIControl

/**
 *  A delegate to receive item selection events.
 */
@property (nonatomic, weak, nullable) id<RBMultipleChoiceViewDelegate> delegate;

/**
 *  Whether or not multiple selection is allowed. Default = `NO`.
 */
@property (nonatomic) BOOL allowsMultipleSelection;

/**
 *  Whether or not the last selected item can be unselected. Default = `YES`.
 */
@property (nonatomic) BOOL zeroSelectionAllowed;

/**
 *  An array of `RBMultipleChoiceViewOption` objects.
 */
@property (nonatomic, nullable) NSArray<RBMultipleChoiceViewOption *> *options;

/**
 *  The values of the options that are selected.
 */
@property (nonatomic, readonly, nonnull) NSArray<NSString *> *selectedValues;

/**
 *  The size of the selection cells. Default = 50, 50.
 */
@property (nonatomic) CGSize optionSize;

/**
 *  The overall positioner used. You may theme this positioner. Default values =
 *  spacing = 0,
 *  dimensions = 1,
 *  margin = [0, 0, 0, 0],
 *  orientation = `RBOrientationVertical`,
 *  sizing = `RBGridPositionerSizeEvenly`.
 */
@property (nonatomic, nonnull, readonly) RBGridPositioner *positioner;

/**
 *  Updates the selection state of the option with the given value.
 *
 *  @param selected Whether or not to update the option to selected (`YES`) or unselected (`NO`).
 *  @param value    The value of the option to update.
 */
- (void)setSelected:(BOOL)selected forOptionValue:(nonnull NSString *)value;

/**
 *  Unselect all options.
 */
- (void)unselectAllOptions;

/**
 *  Converts an array of strings to `RBMultipleChoiceViewOption` options where the value and display text are the same.
 *
 *  @param strings  The list of strings to convert from.
 *
 *  @return Array of `RBMultipleChoiceViewOption` options.
 */
+ (nonnull NSArray<RBMultipleChoiceViewOption *> *)options:(nonnull NSArray<NSString *> *)strings;


@end

/**
 *  A delegate to receive option selection events from an `RBMultipleChoiceView` object.
 */
@protocol RBMultipleChoiceViewDelegate <NSObject>

@optional

/**
 *  Called when an option was selected.
 *
 *  @param multipleChoiceView  The multiple choice field.
 *  @param option              The option that is being selected.
 */
- (void)multipleChoiceView:(nonnull RBMultipleChoiceView *)multipleChoiceView didSelectOption:(nonnull RBMultipleChoiceViewOption *)option;

/**
 *  Called when an option was unselected.
 *
 *  @param multipleChoiceView  The multiple choice field.
 *  @param option              The option that is being unselected.
 */
- (void)multipleChoiceView:(nonnull RBMultipleChoiceView *)multipleChoiceView didDeselectOption:(nonnull RBMultipleChoiceViewOption *)option;

@end
