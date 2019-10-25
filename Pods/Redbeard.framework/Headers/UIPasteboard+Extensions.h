//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  `UIPasteboard` extension methods.
 */
@interface UIPasteboard (Extensions)

/**
 *  Clears the pasteboard.
 */
- (void)clear;

/**
 *  Sets the value of the pasteboard and ensures it is cleared by the given `NSDate`.
 *
 *  @param string The string to set the pasteboard to.
 *  @param date   The date by which it must be cleared.
 */
- (void)setString:(nonnull NSString *)string clearByDate:(nonnull NSDate *)date;

@end
