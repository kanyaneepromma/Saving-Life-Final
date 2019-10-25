//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `NSDate` extensions.
 */
@interface NSDate (Extensions)

/**
 * Calculates the beginning of the day of this `NSDate`.
 *
 * @return A new `NSDate` at the beginning of the day of this `NSDate`.
 */
- (nonnull NSDate *)beginningOfDay;

/**
 * Whether this `NSDate` is today.
 *
 * @return `true` if it is today, `false` if not.
 */
- (BOOL)isToday;

/**
 * Creates an `NSDate` for today at the given time.
 *
 * @param hour The hour of the day.
 * @param minute The minute of the hour.
 * @param second The second of the minute.
 * @return The `NSDate` object.
 */
+ (nonnull NSDate *)todayAtHour:(int)hour minute:(int)minute second:(int)second;

/**
 * Creates an `NSDate` for the given date at the given time.
 *
 * @param date The calendar date to apply the time components to.
 * @param hour The hour of the day.
 * @param minute The minute of the hour.
 * @param second The second of the minute.
 * @return The `NSDate` object.
 */
+ (nonnull NSDate *)date:(nonnull NSDate *)date atHour:(int)hour minute:(int)minute second:(int)second;

/**
 * Creates an `NSDate` for the given date at the beginning of the day.
 *
 * @param date The calendar date.
 * @return The `NSDate` object.
 */
+ (nonnull NSDate *)dateWithZeroTime:(nonnull NSDate *)date;

/**
 * Creates an `NSDate` for today plus the given `NSTimeInterval`.
 *
 * @param interval The `NSTimeInterval` from the beginning of the day.
 * @return The `NSDate` object.
 */
+ (nonnull NSDate *)todayAtInterval:(NSTimeInterval)interval;

/**
 * Creates an `NSDate` for the given date at the given time.
 *
 * @param date The calendar date to use.
 * @param time The time of the day to use.
 * @return The `NSDate` object.
 */
+ (nonnull NSDate *)dateTimeFromDate:(nonnull NSDate *)date time:(nonnull NSDate *)time;

/**
 *  Gets the date at the given interval from the start of the day.
 *
 *  @param timeIntervalFromStartOfDay The time interval since the start of the day.
 *
 *  @return The new `NSDate` object.
 */
- (nonnull NSDate *)dateAtTimeIntervalFromStartOfDay:(NSTimeInterval)timeIntervalFromStartOfDay;

/**
 *  Gets the `NSTimeInterval` from the start of the day.
 *
 *  @return The interval from the start of the day.
 */
- (NSTimeInterval)timeIntervalFromStartOfDay;

@end
