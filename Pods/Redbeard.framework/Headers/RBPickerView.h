//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/UIView+FormField.h>

@protocol RBPickerViewDelegate;

/**
 *  An item picker view that extends the `UIPickerView`.
 */
@interface RBPickerView : UIView

/**
 *  A delegate to receive selection events.
 */
@property (nonatomic, weak, nullable) id<RBPickerViewDelegate> delegate;

/**
 *  Gets or sets the array of option items.
 */
@property (nonatomic, nullable) NSArray<NSString *> *items;

/**
 *  Gets or sets the selected item.
 */
@property (nonatomic, nullable) NSString *selectedItem;

/**
 *  The height of each row. Default = 35.
 */
@property (nonatomic) CGFloat rowHeight;

/**
 *  The text color of items.
 */
@property (nonatomic, nullable) UIColor *textColor;

/**
 *  The text color of the selected item.
 */
@property (nonatomic, nullable) UIColor *selectedTextColor;

@end

/**
 *  A delegate to receive selection events from `RBPickerView` objects.
 */
@protocol RBPickerViewDelegate <NSObject>

@optional

/**
 *  Called when the picker view did select a different value.
 *
 *  @param pickerView The picker view object.
 *  @param value      The new value that was selected.
 */
- (void)pickerView:(nonnull RBPickerView *)pickerView valueChangedTo:(nullable NSString *)value;

@end
