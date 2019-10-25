//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBSQLiteFieldSchema.h>

/**
 *  Converts an SQLITE_TYPE integer value to it's corresponding `RBSQLiteFieldType` type
 *
 *  @param type The SQLite type (SQLITE_INTEGER, SQLITE_FLOAT, SQLITE_TEXT, SQLITE_BLOB, SQLITE_NULL).
 *
 *  @return Returns the corresponding `RBSQLiteFieldType` for the SQLITE field type.
 */
extern inline RBSQLiteFieldType RBSQLiteFieldTypeFromSQLiteType(int type);

@interface RBSQLiteResultSet : NSObject

/**
 *  Indicates that there is returned data.
 */
@property (nonatomic, readonly) BOOL hasResults;

/**
 *  The number of rows in this set.
 */
@property (nonatomic, readonly) NSUInteger rowCount;

/**
 *  The number of columns in this set.
 */
@property (nonatomic, readonly) NSUInteger columnCount;

/**
 *  An array of `NSString` objects detailing column names.
 */
@property (nonatomic, readonly, nonnull) NSArray<NSString *> *columnNames;

/**
 *  An array of `NSNumber` objects that hold `RBSQLiteFieldType` values for columns.
 */
@property (nonatomic, readonly, nonnull) NSArray<NSNumber *> *columnTypes;

/**
 *  An array of values containing data as retreived from SQLite. This is a single flat array and is used in conjection with row and column counts to structure and retreive data in a tabulated format correctly.
 */
@property (nonatomic, readonly, nonnull) NSArray *fields;

/**
 *  The scalar value for an SQL scalar query. Convenience property that returns the data from the first row and first column of the result set.
 */
@property (nonatomic, readonly, nullable) id scalarValue;

/**
 *  Initializes a new `RBSQLiteResultSet` object populating it with an existing `RBSQLiteResultSet`.
 *
 *  @param resultSet The `RBSQLiteResultSet` from which to populate.
 *
 *  @return A newly initialized and populated `RBSQLiteResultSet` object.
 */
- (nonnull instancetype)initWithResultSet:(nonnull RBSQLiteResultSet *)resultSet;

/**
 *  Initializes a new `RBSQLiteResultSet` object populating it with data.
 *
 *  @param columnNames An array of `NSString` objects detailing column names.
 *  @param columnTypes An array of `NSNumber` objects holding `RBSQLiteFieldType` values for columns.
 *  @param fieldValues An array containing the data values for this result set.
 *
 *  @return A newly initialized and populated `RBSQLiteResultSet` object.
 */
- (nonnull instancetype)initWithColumnNames:(nonnull NSArray<NSString *> *)columnNames columnTypes:(nonnull NSArray<NSNumber *> *)columnTypes fieldValues:(nonnull NSArray *)fieldValues;

/**
 *  Retreives the column index for the given column name.
 *
 *  @param name The column name.
 *
 *  @return The column index.
 */
- (NSUInteger)columnIndexForName:(nonnull NSString *)name;

/**
 *  Retrieves the column name for the given index.
 *
 *  @param index The column index.
 *
 *  @return The column name.
 */
- (nonnull NSString *)columnNameAtIndex:(NSUInteger)index;

/**
 *  Retrives the `RBSQLiteFieldType` column type for the given column index.
 *
 *  @param index The column index.
 *
 *  @return The `RBSQLiteFieldType` column type.
 */
- (RBSQLiteFieldType)columnTypeAtIndex:(NSUInteger)index;

/**
 *  Retrieves the value for the given column and row index.
 *
 *  @param index The column index.
 *  @param row   The row index.
 *
 *  @return The value.
 */
- (nonnull id)valueAtIndex:(NSUInteger)index forRow:(NSUInteger)row;

/**
 *  Retreives the value for the given column name and row index.
 *
 *  @param columnName The column name.
 *  @param row        The row index.
 *
 *  @return The value.
 */
- (nonnull id)valueForColumnName:(nonnull NSString *)columnName forRow:(NSUInteger)row;

/**
 *  Retreives the values for a given row index.
 *
 *  @param row The row index.
 *
 *  @return An array of values representing the data for that SQLite row.
 */
- (nonnull NSArray *)valuesAtRow:(NSUInteger)row;

@end

/**
 *  Mutable version of `RBSQLiteResultSet` that can be used to setup a tabular structure (rows and columns) to which data can be added to later.
 */
@interface RBSQLiteMutableResultSet : RBSQLiteResultSet

/**
 *  Adds a new column to the result set structure.
 *
 *  @param name The column name.
 *  @param type The column type as an SQLITE type (SQLITE_INTEGER, SQLITE_FLOAT, SQLITE_TEXT, SQLITE_BLOB, SQLITE_NULL).
 *
 *  @return Returns `YES` if successful.
 */
- (BOOL)addColumn:(nonnull NSString *)name SQLiteType:(int)type;

/**
 *  Returns the current row index.
 *
 *  @return The row index.
 */
- (NSUInteger)currentRow;

/**
 *  Returns the current column index.
 *
 *  @return The column index.
 */
- (NSUInteger)currentColumn;

/**
 *  Adds a new value to the data array.
 *
 *  @param value The value.
 *
 *  @return Returns `YES` if successful.
 */
- (BOOL)pushFieldValue:(nonnull id)value;

@end
