//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBThemeSet.h>

/**
 *  Loads the theme include file routes and builds an ordered and categorized collection of
 *  theme files for loading.
 */
@interface RBThemeFileCollection : NSObject

/**
 *  Post fixes that are to be used.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *overridePostfixes;

/**
 *  All of the filenames of all types of theme file.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *allFilenames;

/**
 *  All of the filenames of the theme include files.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *includeFilenames;

/**
 *  All of the filenames of the theme files.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *themeFilenames;

/**
 *  Initializes a new theme file collection by searching the bundle with given root set file.
 *
 *  @param fileName File name containing the theme configuration file within the bundle e.g. `themeset.json`.
 *  @param error    A pointer to assign a `NSError*` object to in the event of an error.
 *
 *  @return The initialized theme file collection object.
 */
- (nonnull instancetype)initWithConfig:(nonnull NSString *)fileName error:(NSError * _Nullable * _Nullable)error;

/**
 *  Initializes a new theme file collection by loading from a serialized collection.
 *
 *  @param dictionary The serialized collection.
 *
 *  @return The initialized theme file collection object.
 */
- (nonnull instancetype)initWithSerializedDictionary:(nonnull NSDictionary<NSString *, NSArray<NSString *>*> *)dictionary;

/**
 *  Serializes the theme file collection to a property list.
 *
 *  @return The serialized theme file collection property list.
 */
- (nonnull NSDictionary<NSString *, NSArray<NSString *>*> *)serializedDictionary;

/**
 *  Compares the receiver to the given instance of `RBThemeFileCollection` and determines
 *  whether they are identical.
 *
 *  @param collection The `RBThemeFileCollection` object to compare the receiver to.
 *
 *  @return Whether or not the two `RBThemeFileCollection` objects are identical.
 */
- (BOOL)identicalTo:(nonnull RBThemeFileCollection *)collection;

/**
 *  Imports the theme files in the collection to the given `RBThemeSet` object.
 *
 *  @param themeSet The `RBThemeSet` object to import to.
 *  @param error    A pointer to assign a `NSError*` object to in the event of an error.
 */
- (void)importInto:(nonnull RBThemeSet *)themeSet error:(NSError * _Nullable * _Nullable)error;

@end
