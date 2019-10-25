//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBBaseThemeSet.h>

/**
 *  A theme set that pre-processes imported constants and themes.
 */
@interface RBThemeSet : RBBaseThemeSet

/**
 *  The available themes by their name.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *themes;

#pragma mark -
#pragma mark Importing

/**
 *  The themes that are pending being processed and imported to the set.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *pendingThemes;

/**
 *  Imports theme data with the given name.
 *
 *  @param data     The theme data.
 *  @param name     The name of the theme data.
 *  @param error    The error to set on error.
 */
- (void)import:(nonnull id)data withName:(nonnull NSString *)name error:(NSError * _Nullable * _Nullable)error;

/**
 *  Processes the pending themes and constants and makes them available.
 *
 *  @param error A pointer to an `NSError*` object that is assigned in the event of an error.
 */
- (void)processPendingImportsWithError:(NSError * _Nullable * _Nullable)error;

#pragma mark -
#pragma mark Serialisation

/**
 *  Serializes the pre-processed themes and constants in the theme set.
 *
 *  @return The `NSData` object representing the serialized theme set.
 */
- (nonnull NSData *)serialize;

/**
 *  Deserializes and imports a serialized theme set.
 *
 *  @param themeSetData The `NSData` object representing the serialized theme set.
 */
- (void)deserializeAndImportFrom:(nonnull NSData *)themeSetData;

@end
