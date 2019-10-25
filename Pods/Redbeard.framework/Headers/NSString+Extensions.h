//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#define UTF8StringFromMacroParameter(x) (#x)
#define NSStringFromMacroParameter(x) [NSString stringWithUTF8String:#x]

/**
 *  `NSString` extensions.
 */
@interface NSString (Extensions)

/**
 *  The `NSRange` of the whole string.
 */
@property (nonatomic, readonly) NSRange rangeOfWholeString;

/**
 *  Combines two strings together.  Treats `nil` values as empty strings.
 *
 *  @param stringA The first string.
 *  @param stringB The second string.
 *
 *  @return The combined string.
 */
+ (nonnull NSString *)stringByCombiningString:(nullable NSString *)stringA withString:(nullable NSString *)stringB;

/**
 *  Parses a boolean from the given string.
 *
 *  If the string was `nil` or did not contain a valid boolean value, the default value is returned.
 *
 *  @param string       The string value.
 *  @param defaultValue The default boolean value.
 *
 *  @return The resulting boolean value.
 */
+ (BOOL)boolValueFromString:(nullable NSString *)string defaultValue:(BOOL)defaultValue;

/**
 *  Removes the last path component from a URL string.
 */
@property (nonatomic, readonly, nonnull) NSString *urlStringByDeletingLastPathComponent;

/**
 *  Removes the path extension from a URL string.
 */
@property (nonatomic, readonly, nonnull) NSString *urlStringByDeletingPathExtension;

/**
 *  Appends the given path extension to the URL string.
 *
 *  @param pathExtension The path extension to append.
 *
 *  @return The resulting URL string.
 */
- (nonnull NSString *)urlStringByAppendingPathExtension:(nonnull NSString *)pathExtension;

/**
 *  Appends the given path component to the URL string.
 *
 *  @param pathComponent The path component to append.
 *
 *  @return The resulting URL string.
 */
- (nonnull NSString *)urlStringByAppendingPathComponent:(nonnull NSString *)pathComponent;

/**
 *  Encodes the unicode literals in the string to hex.
 */
@property (nonatomic, readonly, nonnull) NSString *stringByEncodingUnicodeLiterals;

/**
 *  Determines whether the string ends with the given string.
 *
 *  @param str           The end string to check for.
 *  @param caseSensitive Whether or not the comparison should be case sensitive.
 *
 *  @return Whether or not the end string was found.
 */
- (BOOL)endsWith:(nonnull NSString *)str caseSensitive:(BOOL)caseSensitive;

/**
 *  Determines whether the string ends with the given string.
 *  The check is case sensitive.
 *
 *  @param str The end string to check for.
 *
 *  @return Whether or not the end string was found.
 */
- (BOOL)endsWith:(nonnull NSString *)str;

/**
 *  Determines whether the string begins with the given string.
 *
 *  @param str           The beginning string to check for.
 *  @param caseSensitive Whether or not the comparison should be case sensitive.
 *
 *  @return Whether or not the beginning string was found.
 */
- (BOOL)beginsWith:(nonnull NSString *)str caseSensitive:(BOOL)caseSensitive;

/**
 *  Determines whether the string begins with the given string.
 *  The check is case sensitive.
 *
 *  @param str The beginning string to check for.
 *
 *  @return Whether or not the beginning string was found.
 */
- (BOOL)beginsWith:(nonnull NSString *)str;

/**
 *  Trims a given number of characters from the start of the string.
 *
 *  @param numChars The number of characters to trim.
 *
 *  @return The trimmed `NSString` object.
 */
- (nonnull NSString *)stringTrimmedFromStart:(NSUInteger)numChars;

/**
 *  Trims a given number of characters from the end of the string.
 *
 *  @param numChars The number of characters to trim.
 *
 *  @return The trimmed `NSString` object.
 */
- (nonnull NSString *)stringTrimmedFromEnd:(NSUInteger)numChars;

/**
 *  Removes the given string from the end if it exists.
 *
 *  @param str           The string to remove.
 *  @param caseSensitive Whether the string match is case sensitive.
 *
 *  @return The new `NSString` object.
 */
- (nonnull NSString *)stringByRemovingStringFromEnd:(nonnull NSString *)str caseSensitive:(BOOL)caseSensitive;

/**
 *  Removes the given string from the start if it exists.
 *
 *  @param str           The string to remove.
 *  @param caseSensitive Whether the string match is case sensitive.
 *
 *  @return The new `NSString` object.
 */
- (nonnull NSString *)stringByRemovingStringFromStart:(nonnull NSString *)str caseSensitive:(BOOL)caseSensitive;

/**
 *  Determines whether the given string is equal to this string.
 *
 *  @param string        The string to compare.
 *  @param caseSensitive Whether the comparison should be case sensitive.
 *
 *  @return Whether or not the strings match.
 */
- (BOOL)isEqualToString:(nonnull NSString *)string caseSensitive:(BOOL)caseSensitive;

/**
 *  Determines whether this string and the string given are the same
 *  when trimmed and case insensitive.
 *
 *  @param string The string to compare.
 *
 *  @return Whether or not the strings match.
 */
- (BOOL)matches:(nullable NSString *)string;

/**
 *  Gets a substring with the given number of characters from the start and end of the string.
 *  For example, values of 0 will match the whole string.
 *
 *  @param fromStart The number of characters from the start of the string.
 *  @param fromEnd   The number of characters from the end of the string.
 *
 *  @return The substring `NSString` object.
 */
- (nonnull NSString *)substringFromStart:(NSUInteger)fromStart fromEnd:(NSUInteger)fromEnd;

/**
 *  Gets a substring with the start and end index of the range.
 *
 *  @param fromIndex The index at the start of the substring.
 *  @param toIndex   The index at the end of the substring.
 *
 *  @return The substring `NSString` object.
 */
- (nonnull NSString *)substringFromIndex:(NSUInteger)fromIndex toIndex:(NSUInteger)toIndex;

/**
 *  Tabs the string to the given level taking into account newlines.
 *
 *  @param level The level of indentation to tab.
 *
 *  @return The tabbed `NSString` object.
 */
- (nonnull NSString *)tabbedStringWithLevel:(int)level;

/**
 *  An indented copy of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *tabbedString;

/**
 *  A UTF-8 encoded `NSData` copy of the string.
 */
@property (nonatomic, readonly, nonnull) NSData *utf8DataValue;

/**
 *  A trimmed copy of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *trimmedString;

/**
 *  Determines whether or not the given string exists within this string.
 *
 *  @param string The string to match.
 *
 *  @return Whether or not the string was matched.
 */
- (BOOL)containsString:(nonnull NSString *)string;

/**
 *  Gets a random character from the string.
 */
@property (nonatomic, readonly) unichar randomCharacter;

/**
 *  Repeats the given string by the given number of times with the given separator inbetween occurances.
 *
 *  @param string        The string to repeat.
 *  @param numberOfTimes The number of times to repeat the string.
 *  @param separator     The separator to use between occurances of the string.
 *
 *  @return The new `NSString` object.
 */
+ (nonnull NSString *)stringByRepeatingString:(nonnull NSString *)string
                        numberOfTimes:(NSUInteger)numberOfTimes
                            separator:(nonnull NSString *)separator;

/**
 *  Returns the underlying bridged `CFStringRef` reference of this string.
 */
@property (nonatomic, readonly, nonnull) CFStringRef CFStringRef;

/**
 *  Capitalises the first letter of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *stringWithUppercaseFirstLetter;

/**
 *  Lowercases the first letter of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *stringWithLowercaseFirstLetter;

/**
 *  An MD5 hash of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *MD5Hash;

/**
 *  A base-64 encoded version of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *base64String;

/**
 *  A URL-encoded version of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *urlEncodedString;

/**
 *  A URL-decoded version of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *urlDecodedString;

/**
 *  Whether or not the URL string is for the local filesystem.
 */
@property (nonatomic, readonly) BOOL isLocalUrlSchema;

/**
 *  The protocol component of the string.  e.g. http://
 */
@property (nonatomic, readonly, nullable) NSString *protocolComponent; // i.e. http://

/**
 *  The protocol of the URL string.  e.g. http
 */
@property (nonatomic, readonly, nullable) NSString *protocolString; // i.e. http

/**
 *  Removes the protocol component of the string.  e.g. www.google.com (removing http://).
 */
@property (nonatomic, readonly, nonnull) NSString *stringByRemovingProtocolString; // i.e. www.google.com

/**
 *  Splits the string into parts.
 *
 *  @param separator    The separator string with which to split.
 *  @param trim         Whether or not to trim the components.
 *  @param removeBlanks Whether or not to remove empty components.
 *
 *  @return An `NSArray` of string components.
 */
- (nonnull NSArray<NSString *> *)componentsSeparatedByCharactersInSet:(nonnull NSCharacterSet *)separator trim:(BOOL)trim removeBlanks:(BOOL)removeBlanks;

/**
 *  A slug version of the string.
 */
@property (nonatomic, readonly, nonnull) NSString *slug;

#pragma mark -
#pragma mark String Walking

/**
 *  Gets the number of components in the string with the given separator character.
 *
 *  @param separatorCharacter The separator character.
 *
 *  @return The resulting number of components.
 */
- (NSUInteger)numberOfComponentsWithSeparator:(unichar)separatorCharacter;

/**
 *  Extracts the components in the range given from the string using the given separator character.
 *
 *  @param range              The range of components to extract.
 *  @param separatorCharacter The separator character.
 *
 *  @return The resulting string of components.
 */
- (nonnull NSString *)stringByExtractingComponentsInRange:(NSRange)range withSeparator:(unichar)separatorCharacter;

/**
 *  Removes the first components from the string using the given separator character.
 *
 *  @param separatorCharacter The separator character.
 *
 *  @return The resulting string.
 */
- (nonnull NSString *)stringByRemovingFirstComponentWithSeparator:(unichar)separatorCharacter;

/**
 *  Removes the last component from the string using the given separator character.
 *
 *  @param separatorCharacter The separator character.
 *
 *  @return The resulting string.
 */
- (nonnull NSString *)stringByRemovingLastComponentWithSeparator:(unichar)separatorCharacter;

/**
 *  Extracts the last component from the string using the given separator character.
 *
 *  @param separatorCharacter The separator character.
 *
 *  @return The resulting component.
 */
- (nonnull NSString *)lastComponentWithSeparator:(unichar)separatorCharacter;

/**
 *  Adds a component to the string with the given separator character.
 *
 *  @param componentString    The component string to append.
 *  @param separatorCharacter The separator character.
 *
 *  @return The resulting string.
 */
- (nonnull NSString *)stringByAppendingComponent:(nonnull NSString *)componentString withSeparator:(unichar)separatorCharacter;

@end
