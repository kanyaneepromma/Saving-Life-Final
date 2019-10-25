//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `NSData` extensions.
 */
@interface NSData (Extensions)

/**
 * Creates an `NSData` object by deserialising a base-64 string.
 *
 * @param aString The base-64 string to deserialise.
 * @return The deserialised `NSData`.
 */
+ (nonnull NSData *)dataFromBase64String:(nonnull NSString *)aString;

/**
 * Creates an `NSData` object by deserialising a base-64 `NSData` object.
 *
 * @param base64Data The base-64 data to deserialise.
 * @return The deserialised `NSData`.
 */
+ (nonnull NSData *)dataFromBase64Data:(nonnull NSData *)base64Data;

/**
 * Reads the data from a `dispatch_data_t` into a new `NSData`.
 *
 * @param data The `dispatch_data_t` object to read from.
 * @return The new `NSData`.
 */
+ (nonnull NSData *)fromDispatchData:(nonnull dispatch_data_t)data;

/**
 * The UTF8 string representation of the contents of this `NSData`.
 */
- (nonnull NSString *)utf8StringValue;

/**
 * The base-64 string representation of the contents of this `NSData`.
 */
- (nonnull NSString *)base64StringValue;

/**
 * An MD5 hash of the contents of this `NSData`.
 */
- (nonnull NSString *)md5StringValue;

/**
 * Unzips the data in this `NSData` using the GZip algorithm, returning the inflated data.
 *
 * @return The new `NSData` containing the unzipped (inflated) data.
 */
- (nullable NSData *)gzipInflate;

/**
 * Zips the data in this `NSData` using the GZip algorithm, returning the zipped (deflated) data.
 *
 * @return The new `NSData` containing the zipped (deflated) data.
 */
- (nonnull NSData *)gzipDeflate;

@end
