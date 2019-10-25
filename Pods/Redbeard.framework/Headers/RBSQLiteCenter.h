//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBSQLiteVFS.h>
#import <Redbeard/RBSQLiteVFSFile.h>


/**
 *  Centrally manages low level access to SQLite databases.
 */
@interface RBSQLiteCenter : NSObject

/**
 *  The shared singleton `RBSQLiteCenter`.
 */
@property (class, nonnull, readonly) RBSQLiteCenter *shared;

#pragma mark -
#pragma mark VFS

/**
 *  <#Description#>
 *
 *  @param vfs             <#vfs description#>
 *  @param setAsDefaultVFS <#setAsDefaultVFS description#>
 *
 *  @return <#return value description#>
 */
- (BOOL)registerVFS:(nonnull RBSQLiteVFS *)vfs setAsDefaultVFS:(BOOL)setAsDefaultVFS;

/**
 *  <#Description#>
 *
 *  @param name <#name description#>
 *
 *  @return <#return value description#>
 */
- (BOOL)deregisterVFSWithName:(nonnull NSString *)name;

/**
 *  <#Description#>
 *
 *  @param name <#name description#>
 *
 *  @return <#return value description#>
 */
- (nonnull RBSQLiteVFS *)vfsWithName:(nonnull NSString *)name;

#pragma mark -
#pragma mark General

/**
 *  Converts an NSDate into an ISO 8601 formatted string (yyyy-MM-ddTHH:mm:ssZ).
 *
 *  @param date The date.
 *
 *  @return An ISO 8601 formatted date.
 */
- (nonnull NSString *)stringFromDate:(nonnull NSDate *)date;

/**
 *  Converts an ISO 8601 formatted string into an `NSDate`
 *
 *  @param string An ISO 8601 formatted string (yyyy-MM-ddTHH:mm:ssZ).
 *
 *  @return The `NSDate`
 */
- (nullable NSDate *)dateFromString:(nonnull NSString *)string;

/**
 *  Converts a `NSNumber` into its string representation.
 *
 *  @param number The number.
 *
 *  @return The string representation.
 */
- (nonnull NSString *)stringFromNumber:(nonnull NSNumber *)number;

/**
 *  Converts a decimal formatted number string into an `NSNumber'.
 *
 *  @param string The decimal formatted string.
 *
 *  @return The number.
 */
- (nullable NSNumber *)numberFromString:(nonnull NSString *)string;

@end
