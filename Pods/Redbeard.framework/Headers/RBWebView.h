//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  A `UIWebView` with extended functionality.
 */
@interface RBWebView : UIWebView

/**
 *  Whether or not the insets are automatically adjusted when the keyboard opens and closes.
 */
@property (nonatomic) BOOL shouldAdjustInsetForKeyboard;

/**
 *  Whether or not the web view sizes to it's content (`sizeThatFitsSize:`).
 */
@property (nonatomic) BOOL sizeToContent;

@end
