//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBSQLiteFieldSchema.h>

/**
 *  Describes a SQLite table.
 */
@interface RBSQLiteTableSchema : NSObject // Immutable

/**
 *  The table name.
 */
@property (nonatomic, readonly, nonnull) NSString *name;

/**
 *  An array of `RBSQLiteFieldSchema` objects that describe the table columns.
 */
@property (nonatomic, readonly, nonnull) NSArray<RBSQLiteFieldSchema *> *fields; // of RBSQLiteFieldSchema types

/**
 *  Initializes a new `RBSQLiteTableSchema` object that describes a SQLite table.
 *
 *  @param name   The table name.
 *  @param fields An array of `RBSQLiteFieldSchema` objects.
 *
 *  @return A newly initialized `RBSQLiteTableSchema` object representing a SQLite table.
 */
- (nonnull instancetype)initWithName:(nonnull NSString *)name fields:(nonnull NSArray<RBSQLiteFieldSchema *> *)fields;

/**
 *  Retrieve the `RBSQLiteFieldSchema` for a specific field (SQLite column).
 *
 *  @param fieldName The name of the field to return.
 *
 *  @return Returns a `RBSQLiteFieldSchema` for the given field name.
 */
- (nonnull RBSQLiteFieldSchema *)fieldWithName:(nonnull NSString *)fieldName;

/**
 *  Creates a SQL query that can be used to create the SQLite table described by this `RBSQLiteTableSchema` instance.
 *
 *  @return A formatted SQL CREATE TABLE query.
 */
- (nonnull NSString *)createTableQueryString;

@end
