//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/** The data type of an SQLite table field. */
typedef NS_ENUM(NSInteger, RBSQLiteFieldType)
{
    /** An integer data type of an SQLite table field. */
    RBSQLiteFieldTypeInteger,

    /** An float data type of an SQLite table field. */
    RBSQLiteFieldTypeFloat,
    
    /** An text data type of an SQLite table field. */
    RBSQLiteFieldTypeText,
    
    /** An blob data type of an SQLite table field. */
    RBSQLiteFieldTypeBlob,
    
    /** An null data type of an SQLite table field. */
    RBSQLiteFieldTypeNull,
    
    /** An unknown data type of an SQLite table field. */
    RBSQLiteFieldTypeUnknown
};

/**
 *  Describes a SQLite table column.
 */
@interface RBSQLiteFieldSchema : NSObject

/**
 *  The field name, corresponds to the SQLite column name.
 */
@property (nonatomic, readonly, nonnull)  NSString *name;

/**
 *  The data type.
 */
@property (nonatomic, readonly) RBSQLiteFieldType type;

/**
 *  Determines if the null values are allowed for this field in the corresponding SQLite column.
 */
@property (nonatomic, readonly) BOOL allowsNull;

/**
 *  Determines if this field should autoincrement, in this case the field type should be an integer.
 */
@property (nonatomic, readonly) BOOL autoincrement;

/**
 *  Determines if this is the primary key field.
 */
@property (nonatomic, readonly) BOOL isPrimaryKey;

/**
 *  Initializes a new `RBSQLiteFieldSchema` object that describes a SQLite table column.
 *
 *  @param name          The name of the field, corresponds to the SQLite column name.
 *  @param type          The data type of this field.
 *  @param allowsNull    Set to `YES` to allow null values to be used in the corresponding SQLite column.
 *
 *  @return A newly initialized and populated `RBSQLiteFieldSchema` object.
 */
- (nonnull instancetype)initWithName:(nonnull NSString *)name
                        type:(RBSQLiteFieldType)type
                  allowsNull:(BOOL)allowsNull;

/**
 *  Initializes a new `RBSQLiteFieldSchema` object that describes the primary key column for an SQLite table.
 *
 *  @param name          The name of the field, corresponds to the SQLite column name.
 *  @param type          The data type of this field.
 *
 *  @return A newly initialized and populated `RBSQLiteFieldSchema` object.
 */
- (nonnull instancetype)initPrimaryKeyWithName:(nonnull NSString *)name
                                  type:(RBSQLiteFieldType)type;
/**
 *  Creates a query string fragment to to be used as part of an SQL CREATE TABLE query.
 *
 *  @return Returns a formatted SQL query string fragment.
 */
- (nonnull NSString *)createTableFieldQueryString;

@end
