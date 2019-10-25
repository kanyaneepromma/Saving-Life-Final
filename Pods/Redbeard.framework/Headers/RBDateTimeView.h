//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBTextField.h>
#import <Redbeard/RBDateTimeInputView.h>

/**
 *  A date and time form field.
 */
@interface RBDateTimeView : RBTextField<RBInputViewDelegate>

/**
 *  The date and time selection mode.
 */
@property (nonatomic) RBDateTimeViewMode mode;

/**
 *  The locale. Default = `[NSLocale currentLocale]`. Setting nil returns to default.
 */
@property (null_resettable, nonatomic, strong) NSLocale   *locale;

/**
 *  The calendar. Default = `[NSLocale currentLocale]`. Setting nil returns to default.
 */
@property (null_resettable, nonatomic, copy)   NSCalendar *calendar;

/**
 *  The timeZone. Default = `nil`. Use current time zone or time zone from calendar
 */
@property (nullable, nonatomic, strong) NSTimeZone *timeZone;

/**
 *  The date. Default = current date when input view created.
 */
@property (nonatomic, strong, nonnull) NSDate *date;

/**
 *  The minimum date range . Default = `nil`. When min > max, the values are ignored.
 */
@property (nullable, nonatomic, strong) NSDate *minimumDate;

/**
 *  The maximum date range . Default = `nil`. When min > max, the values are ignored.
 */
@property (nullable, nonatomic, strong) NSDate *maximumDate;

/**
 *  Set the current date.
 *
 *  @param date         The date.
 *  @param animated     Animate the change.
 */
- (void)setDate:(nonnull NSDate *)date animated:(BOOL)animated;

@end
