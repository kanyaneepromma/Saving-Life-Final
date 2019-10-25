//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "RBInputView.h"
#import "RBPickerView.h"

/**
 *  A list item selection input view.
 */
@interface RBListInputView : RBInputView<RBPickerViewDelegate>

/**
 *  The underlying `RBPickerView` object.
 */
@property (nonatomic, readonly, nonnull) RBPickerView *picker;

/**
 *  A list of string list items.
 */
@property (nonatomic, nonnull) NSArray<NSString *> *list;

@end
