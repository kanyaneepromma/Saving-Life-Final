//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `NSURLRequest` extensions.
 */
@interface NSURLRequest (Extensions)

/**
 *  A human readable debugging description of the `NSURLRequest` object.
 */
@property (nonatomic, readonly, nonnull) NSString *outputDescription;

/**
 *  Generates a unique hash for the `NSURLRequest` with the exception
 *  of the given http header names which are ignored.
 *
 *  @param httpHeaderExceptions An `NSArray` of HTTP header names to ignore.
 *
 *  @return The unique hash `NSString` object.
 */
- (nonnull NSString *)uniqueHashWithHTTPHeaderExceptions:(nullable NSArray<NSString *> *)httpHeaderExceptions;

/**
 *  A unique hash string for the `NSURLRequest`.
 */
@property (nonatomic, readonly, nonnull) NSString *uniqueHash;

#pragma mark -
#pragma mark FACTORY

/**
 *  Generates a HTTP 'Authorization' header with the given credentials.
 *
 *  @param username The username to use.
 *  @param password The password to use.
 *
 *  @return A `NSDictionary` object containing the header.
 */
+ (nonnull NSDictionary<NSString *, NSString *> *)authorizationHeaderWithUsername:(nonnull NSString *)username password:(nonnull NSString *)password;

/**
 *  Creates a new HTTP GET request.
 *
 *  @param url               The URL of the request.
 *  @param customHTTPHeaders The custom HTTP headers to include.
 *
 *  @return The new `NSURLRequest` object.
 */
+ (nonnull NSURLRequest *)httpGetRequestWithURL:(nonnull NSString *)url customHTTPHeaders:(nullable NSDictionary<NSString *, NSString *> *)customHTTPHeaders;

/**
 *  Creates a new HTTP POST request.
 *
 *  @param url               The URL of the request.
 *  @param data              The HTTP body data of the request.
 *  @param customHTTPHeaders The custom HTTP headers to include.
 *
 *  @return The new `NSURLRequest` object.
 */
+ (nonnull NSURLRequest *)httpPostRequestWithURL:(nonnull NSString *)url andData:(nullable NSData *)data customHTTPHeaders:(nullable NSDictionary<NSString *, NSString *> *)customHTTPHeaders;

@end
