//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  A `UILabel` with some extensions.
 */
@interface RBLabel : UILabel

/**
 *  The padding to provide around the text.
 */
@property (nonatomic) UIEdgeInsets padding;

/**
 *  Whether or not user actions should be enabled.
 *  User actions are such as copy and paste are displayed when the user taps and holds on the text.
 */
@property (nonatomic) BOOL userActionsEnabled; // Cut/Copy/Paste enabled

@end
