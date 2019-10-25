//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * `NSObject` debugging extensions.
 *
 * Provides a clean mechanism for an object to log any state changes, warnings
 * or error messages to the console.  The properties `loggingEnabled` and
 * `loggingName` determine whether the logging will occur and how each log
 * message will be prefixed, so that it is easy to differentiate between the
 * logs of each object.
 */
@interface NSObject (Debugging)

/** Whether this object should be logging. */
@property (nonatomic) BOOL loggingEnabled;

/** The name prefix to use when this object logs messages. */
@property (nonatomic, nullable) NSString *loggingName;

/**
 * Logs to the console the format and parameters, prefixed by the type
 * and logging name of this object.
 *
 * @param format The format string.
 * @param ... The parameters to bind to the format string.
 */
- (void)log:(nonnull NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

/**
 * If the condition is false, it logs to the console the format and parameters,
 * prefixed by the type and logging name of this object.
 *
 * @param condition The condition to check.
 * @param format The format string.
 * @param ... The parameters to bind to the format string.
 */
- (void)logAssert:(BOOL)condition format:(nonnull NSString *)format, ... NS_FORMAT_FUNCTION(2, 3);

/**
 * Whether logging is enabled for this class object.
 */
+ (BOOL)loggingEnabled;

/**
 * Sets whether logging is enabled for this class object.
 *
 * @param loggingEnabled The value to set.
 */
+ (void)setLoggingEnabled:(BOOL)loggingEnabled;

/**
 * Logs to the console the format and parameters, prefixed by the type name.
 *
 * @param format The format string.
 * @param ... The parameters to bind to the format string.
 */
+ (void)log:(nonnull NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

/**
 * If the condition is false, it logs to the console the format and parameters,
 * prefixed by the type name.
 *
 * @param condition The condition to check.
 * @param format The format string.
 * @param ... The parameters to bind to the format string.
 */
+ (void)logAssert:(BOOL)condition format:(nonnull NSString *)format, ... NS_FORMAT_FUNCTION(2, 3);

@end
