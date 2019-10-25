//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/UIView+FormField.h>
#import <Redbeard/RBInputView.h>

/**
 *  A multi-line text input field.
 */
@interface RBTextView : UITextView<RBInputViewDelegate>

/**
 *  The minimum size that the text input field will request of it's container.
 */
@property (nonatomic) CGSize minimumSize;

/**
 *  The maximum size that the text input field will request of it's container.
 */
@property (nonatomic) CGSize maximumSize;

/**
 *  The placeholder text to be displayed when the field is empty.
 */
@property (nonatomic, nullable) NSString *placeholder;

@end
