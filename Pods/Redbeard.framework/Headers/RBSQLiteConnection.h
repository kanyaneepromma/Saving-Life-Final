//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBSQLiteResult.h>
#import <Redbeard/RBSQLiteResultSet.h>
#import <Redbeard/RBSQLiteTableSchema.h>
#import <Redbeard/RBSQLiteFieldSchema.h>

/** The state of an SQLite connection. */
typedef NS_ENUM(NSInteger, RBSQLiteConnectionState)
{
    /** The SQLite connection is broken. */
    RBSQLiteConnectionStateBroken = 0,
    
    /** The SQLite connection is closed. */
    RBSQLiteConnectionStateClosed,
    
    /** The SQLite connection is open. */
    RBSQLiteConnectionStateOpen,
    
    /** The SQLite connection is busy. */
    RBSQLiteConnectionStateBusy
};

/** A connection to an SQLite database. */
@interface RBSQLiteConnection : NSObject

/** The filesystem path to the database file. */
@property (nonatomic, readonly, nonnull) NSString *dataFilePath;

/** The current state of the database connection. */
@property (atomic, readonly) RBSQLiteConnectionState state;

/**
 * Opens the connection to the specified database file.
 *
 * @param target The filesystem path to the database file on disk. Create an in memory database by passing in `:memory:`.
 * @return `true` if the connection was opened successfully, `false` if there was an error.
 */
- (BOOL)connectToFile:(nonnull NSString *)target;

/**
 * Opens the connection to the specified database file using a virtual filesystem.
 *
 * @param target The filesystem path to the database file on disk.
 * @param flags One or more `sqlite3` connection flags to use when opening the connection.
 * @param vfs The name of the registered virtual filesystem to use.
 * @return `true` if the connection was opened successfully, `false` if there was an error.
 */
- (BOOL)connectToFile:(nonnull NSString *)target withFlags:(int)flags usingVFS:(nonnull NSString *)vfs;

/**
 * Closes the connection to the database.
 *
 * @return `true` if the connection was closed successfully.
 */
- (BOOL)disconnect;

#pragma mark -
#pragma mark Queries

/**
 * Executes an SQL query and returns the result set.
 *
 * @param queryString The SQL query string to execute, where the '?' character denotes a binding.
 * @param bindings The objects to bind respectively to the query string.
 * @return An `RBSQLiteResult` object that provides the resulting data for the executed SQL query, or `nil` if there was an error.
 */
- (nonnull RBSQLiteResult *)execute:(nonnull NSString *)queryString bindings:(nullable NSArray *)bindings;

#pragma mark -
#pragma mark Tables

/**
 * Determines whether a table with the given name exists in the database.
 *
 * @param name The name of the table.
 * @return `true` if the table exists, `false` if not.
 */
- (BOOL)tableExistsWithName:(nonnull NSString *)name;

/**
 * Inspects the table with the given name and creates an `RBSQLiteTableSchema` object describing it.
 *
 * @param tableName The name of the table.
 * @return The `RBSQLiteTableSchema` object, or `nil` if there was an error.
 */
- (nullable RBSQLiteTableSchema *)schemaFromTableName:(nonnull NSString *)tableName;

/**
 * Creates a new table, or adjusts an existing table with the same name, using the given `RBSQLiteTableSchema`.
 *
 * Note: This method only adds missing fields, it does not adjust existing fields.
 *
 * @param schema The schema that describes the table to create or amend to.
 * @return `true` if the table was created or amended successfully and now matches the schema, `false` if there was an error.
 */
- (BOOL)createOrUpdateTableWithSchema:(nonnull RBSQLiteTableSchema *)schema;

/**
 * Creates a new table using the given `RBSQLiteTableSchema`.
 *
 * @param schema The schema that describes the table to create.
 * @return An `RBSQLiteResult` object that provides the information about the executed SQL query.
 */
- (nonnull RBSQLiteResult *)createTableWithSchema:(nonnull RBSQLiteTableSchema *)schema;

/**
 * Adjusts an existing table with the same name to match the given `RBSQLiteTableSchema`.
 *
 * Note: This method only adds missing fields, it does not adjust existing fields.
 *
 * @param schema The schema that describes the table to adjust to.
 * @return `true` if the table was updated successfully, `false` if there was an error.
 */
- (BOOL)updateTableWithSchema:(nonnull RBSQLiteTableSchema *)schema; // THIS ONLY ADDS MISSING FIELDS

/**
 * Adds a new field to a database table.
 *
 * @param field The schema of the field to add.
 * @param tableName The name of the table to add the new field to.
 * @return An `RBSQLiteResult` object that provides the information about the executed SQL query.
 */
- (nonnull RBSQLiteResult *)addField:(nonnull RBSQLiteFieldSchema *)field toTable:(nonnull NSString *)tableName;

#pragma mark -
#pragma mark Last ROWID

/** The primary key of the last inserted row. */
@property (nonatomic, readonly) long long int lastInsertedRowId;

#pragma mark -
#pragma mark Errors

/** The error message of the last operation that failed. */
@property (nonatomic, readonly, nullable) NSString *lastErrorMessage;

/** Prints the last error message to the console. */
- (void)logErrorMessage;

#pragma mark -
#pragma mark Backup

/**
 * Copies all tables and data from this database connection to the given database connection.
 *
 * @param databaseConnection The database connection to backup to.
 * @return `true` if the backup was successful, `false` if there was an error.
 */
- (BOOL)backupDatabaseToDatabase:(nonnull RBSQLiteConnection *)databaseConnection;

/**
 * Copies all tables and data from this database connection to a file.
 *
 * @param filename The local filesystem path to create the backup SQLite database file at.
 * @param flags One or more `sqlite3` connection flags to use when opening the connection to the backup file.
 * @param vfs The name of the registered virtual filesystem to use when opening the connection to the backup file.
 * @return `true` if the backup was successful, `false` if there was an error.
 */
- (BOOL)backupDatabaseToFile:(nonnull NSString *)filename withFlags:(int)flags usingVFS:(nonnull NSString *)vfs;

/**
 * Reads all of the tables and data from the specified SQLite file into this connection.
 *
 * @param filename The path to the database file to read from.
 * @param flags One or more `sqlite3` connection flags to use when opening the connection.
 * @param vfs The name of the registered virtual filesystem to use when opening the connection.
 * @return `true` if the transfer was successful, `false` if there was an error.
 */
- (BOOL)populateDatabaseFromFile:(nonnull NSString *)filename withFlags:(int)flags usingVFS:(nonnull NSString *)vfs;

@end
