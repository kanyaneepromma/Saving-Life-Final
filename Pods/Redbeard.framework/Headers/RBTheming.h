//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#import <Redbeard/RBThemeSet.h>

/**
 *  Provides access to the themes.
 */
@interface RBTheming : NSObject

/**
 *  The singleton `RBTheming` object.
 */
@property (class, nonnull, readonly) RBTheming *main;

/**
 *  The set of theme assignments.
 */
@property (nonatomic, readonly, nonnull) RBThemeSet *themeSet;

/**
 *  Causes all NEW `RBThemeTracker` objects to have their `disableTheming` match this value.
 *  You may set this to `YES` to easily disable theming across your application as newly instantiated views 
 *  and view controllers will have their theme.disabledTheming set to this value.
 *  Default = NO.
 */
@property (nonatomic) BOOL disableTheming;

/**
 *  Causes all NEW `RBThemeTracker` objects to have their `shouldApplyThemingOnMaterialization` match this value.
 *  You may set this to `YES` to easily stop theming being applied when a views 'didMoveToSuperview' event occurs.
 *  You may set this to `YES` to easily stop theming being applied when a view controllers viewWillAppear event occurs.
 *  Default = YES.
 */
@property (nonatomic) BOOL shouldApplyThemingOnMaterialization;

/**
 *  Creates a new theming object using the given config file.
 *
 *  @param fileName     The theme config file within the bundle e.g. `theme.config`.
 *
 *  @return The initialized theming object.
 */
- (nonnull instancetype)initWithThemeConfig:(nonnull NSString *)fileName;

/**
 *  Retrieves the theme with the given identifier.
 *
 *  @param themeIdentifier  The identifier of the theme.
 *
 *  @return The `id` theme value.
 */
- (nullable id)themeWithIdentifier:(nonnull NSString *)themeIdentifier;

/**
 *  Convenience method to retrieve the font for the given theme identifier.
 *
 *  @param identifier  The identifier of the theme.
 *
 *  @return The `UIFont` theme value.
 */
- (nullable UIFont *)fontForIdentifier:(nonnull NSString *)identifier;

/**
 *  Convenience method to retrieve the color for the given theme identifier.
 *
 *  @param identifier  The identifier of the theme.
 *
 *  @return The `UIColor` theme value.
 */
- (nullable UIColor *)colorForIdentifier:(nonnull NSString *)identifier;


/**
 *  Convenience method to retrieve the string for the given theme identifier.
 *
 *  @param identifier  The identifier of the theme.
 *
 *  @return The string theme value.
 */
- (nullable NSString *)stringForIdentifier:(nonnull NSString *)identifier;

/**
 *  Retrieves the name that will be used by the theming engine to refer to a given class.
 *  This calls `NSStringFromClass` and retrieves and uses the final class component only i.e. MyModule.MyClass > MyClass.
 *
 *  @param c  The class.
 *
 *  @return The class name.
 */
+ (nonnull NSString *)themingClassName:(nonnull Class)c;

/**
 *  Convenience method to call `UIView.theme.applyChanges` for each string and View pair in the provided dictionary.
 *
 *  @param theme    The theme.
 *  @param views    List of views to applyChanges to.
 *  @param keys     List of keys to be used to extract the specific theme from the theme dictionary.
 */
+ (void)applyChanges:(nonnull NSDictionary<NSString *, id> *)theme views:(nonnull NSArray<UIView *> *)views keys:(nonnull NSArray<NSString *> *)keys;

#pragma mark -
#pragma mark Auto wiring

/**
 *  Automatically applies theming to `UIView` properties found on the object provided. Important: the properties must be marked `@objc var` or, alternatively, IBOutlet for wiring to occur.
 *
 *  @param object       The object containing the views to theme (should inherit from NSObject).
 *  @param theme        The theme dictionary.
 *  @param ignore       A list of property names that you would explictly not like to automatically theme.
 */
+ (void)autoApplyChanges:(nonnull id)object theme:(nonnull NSDictionary<NSString *, id> *)theme ignore:(nullable NSArray<NSString *> *)ignore;

#pragma mark -
#pragma mark Reading

/**
 *  Reads an enumeration value from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param enumTypeName The name of the enumeration type.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (NSInteger)enumNumberFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name enumTypeName:(nonnull NSString *)enumTypeName defaultValue:(int)defaultValue;

/**
 *  Reads an enumeration value from a theme value.
 *
 *  @param value        The theme value.
 *  @param enumTypeName The name of the enumeration type.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (NSInteger)enumNumberFromTheme:(nonnull NSString *)value enumTypeName:(nonnull NSString *)enumTypeName defaultValue:(int)defaultValue;

/**
 *  Reads an array of numbers from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable NSArray *)numberArrayFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(nullable NSArray *)defaultValue;

/**
 *  Reads a string from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable NSString *)stringFromTheme:(nonnull NSDictionary <NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(nullable NSString *)defaultValue;

/**
 *  Reads a string from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable NSString *)stringFromTheme:(nonnull NSString *)value defaultValue:(nullable NSString *)defaultValue;

/**
 *  Reads an `NSNumber` from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable NSNumber *)numberFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(nullable NSNumber *)defaultValue;

/**
 *  Reads an `NSNumber` from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable NSNumber *)numberFromTheme:(nonnull id)value defaultValue:(nullable NSNumber *)defaultValue;

/**
 *  Reads a float from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (float)floatFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(float)defaultValue;

/**
 *  Reads a float from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (float)floatFromTheme:(nonnull id)value defaultValue:(float)defaultValue;

/**
 *  Reads a boolean from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (BOOL)boolFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(BOOL)defaultValue;

/**
 *  Reads a boolean from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (BOOL)boolFromTheme:(nonnull id)value defaultValue:(BOOL)defaultValue;

/**
 *  Reads an integer from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (NSInteger)integerFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(NSInteger)defaultValue;

/**
 *  Reads an integer from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (NSInteger)integerFromTheme:(nonnull id)value defaultValue:(NSInteger)defaultValue;

/**
 *  Reads an unsigned integer from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (NSUInteger)unsignedIntegerFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(NSUInteger)defaultValue;

/**
 *  Reads an unsigned integer from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (NSUInteger)unsignedIntegerFromTheme:(nonnull id)value defaultValue:(NSUInteger)defaultValue;

/**
 *  Reads a `UIEdgeInsets` value from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (UIEdgeInsets)edgeInsetsFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(UIEdgeInsets)defaultValue;

/**
 *  Reads a `UIEdgeInsets` value from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (UIEdgeInsets)edgeInsetsFromTheme:(nonnull NSArray *)value defaultValue:(UIEdgeInsets)defaultValue;

/**
 *  Reads a `CGRect` value from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (CGRect)rectFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(CGRect)defaultValue;

/**
 *  Reads a `CGRect` value from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (CGRect)rectFromTheme:(nonnull NSArray *)value defaultValue:(CGRect)defaultValue;

/**
 *  Reads a `CGSize` value from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (CGSize)sizeFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(CGSize)defaultValue;

/**
 *  Reads a `CGSize` value from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (CGSize)sizeFromTheme:(nonnull NSArray *)value defaultValue:(CGSize)defaultValue;

/**
 *  Reads a `UIFont` from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable UIFont *)fontFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(nullable UIFont *)defaultValue;

/**
 *  Reads a `UIFont` from a theme value.
 *
 *  @param theme        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable UIFont *)fontFromTheme:(nonnull NSDictionary<NSString *, id> *)theme defaultValue:(nullable UIFont *)defaultValue;

/**
 *  Reads a `UIColor` from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable UIColor *)colorFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(nullable UIColor *)defaultValue;

/**
 *  Reads a `UIColor` from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable UIColor *)colorFromTheme:(nonnull NSString *)value defaultValue:(nullable UIColor *)defaultValue;

/**
 *  Reads an image from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read. Note the image can be tinted if a color value with the  name [name]TintColor is present in the dictionary.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable UIImage *)imageFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(nullable UIImage *)defaultValue; // inc. insets (resizable)

/**
 *  Reads an image from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable UIImage *)imageFromTheme:(nonnull NSString *)value defaultValue:(nullable UIImage *)defaultValue;

/**
 *  Reads a text style name from a theme dictionary.
 *
 *  @param theme        The theme dictionary.
 *  @param name         The key of the element in the dictionary to read.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable NSString *)textStyleFromTheme:(nonnull NSDictionary<NSString *, id> *)theme named:(nonnull NSString *)name defaultValue:(nullable NSString *)defaultValue;

/**
 *  Reads a text style name from a theme value.
 *
 *  @param value        The theme value.
 *  @param defaultValue The default value to use if a value could not be read.
 *
 *  @return The resulting value.
 */
+ (nullable NSString *)textStyleFromTheme:(nonnull NSString *)value defaultValue:(nullable NSString *)defaultValue;

#define RB_THEME_SET(theme, selector, property, key) \
property = [RBTheming selector:theme named:key defaultValue:property]

#define RB_THEME_SET_ENUM(theme, nameOfEnumType, property, key) \
property = [RBTheming enumNumberFromTheme:theme named:key enumTypeName:nameOfEnumType defaultValue:property]

@end
