//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Redbeard/RBPropertyListTracker.h>

@class RBThemeSchema;

/**
 * Represents a theming event.
 */
typedef NS_ENUM(NSInteger, RBThemeTrackerEvent)
{
    /**
     *  Raised when clearPreviousThemingValues is encountered.
     */
    RBThemeTrackerEventClearPreviousThemingValues,
    
    /**
     *  Raised when theme disabledTheming is set
     */
    RBThemeTrackerEventDisableTheming,
    
    /**
     *  Raised when theme shouldApplyThemingOnMaterialization is set
     */
    RBThemeTrackerEventShouldApplyThemingOnMaterialization
};

/**
 *  A delegate to provide theming integration to a view or object.
 */
@protocol RBThemeTrackerDelegate <NSObject>

@required

/**
 *  Called when a new theme should be applied to the receiver. Only called if the theme is not `nil`.
 *
 *  @param theme The theme dictionary that is being applied.
 */
- (void)applyTheme:(nonnull NSDictionary<NSString *, id> *)theme;

/**
 *  Generates a theme schema that describes the theming options available on the receiver.
 *
 *  @param parent The optional parent schema for recursion protection.
 *
 *  @return The generated `RBThemeSchema` object.
 */
+ ( nonnull RBThemeSchema *)generateThemeSchemaWithParent:(nullable RBThemeSchema *)parent;

@optional

/**
 *  Determines whether or not theme updates can currently be applied.  If not, changes will
 *  continue to mount until the next time changes are processed and this method returns `true`.
 *
 *  @return Determines whether or not theme updates can currently be applied.
 */
- (BOOL)canApplyThemeUpdates;

/**
 *  Called when `applyTheme:` will be called and before the theme changes
 *  have been applied. Only called if the theme is not `nil`.
 *
 *  @param theme The theme dictionary that is being applied.
 */
- (void)willApplyTheme:(nonnull NSDictionary<NSString *, id> *)theme;

/**
 *  Called when `applyTheme:` has been called and the theme changes have been committed.
 *  Only called if the theme is not `nil`.
 *
 *  @param theme The theme dictionary that is being applied.
 */
- (void)didApplyTheme:(nonnull NSDictionary<NSString *, id> *)theme;

/**
 *  Called when if one of the `RBThemeTrackerEvent` events are raised.
 *  Provides UIView's or UIViewController's to take action
 *  action on internally held UIView's that may not be exposed.
 *  For example RBButton (which is a subclass of UIButton) has the inherited internal UILabel 'titleLabel' and
 *  UIImageView 'imageView' views. On receiving this method call RBButton calls `theme.clear` on the titleLabel
 *  and imageView respectively. Additionally the disableTheming, and shouldApplyThemingOnMaterialization values
 *  are set accordingly on the internal imageView and titleLabel.
 *
 *  @param event    The event that needs to be processed.
 */
- (void)processThemeEvent:(RBThemeTrackerEvent)event;

@end

/**
 *  Manages a theme and tracks it's changes.
 */
@interface RBThemeTracker : RBPropertyListTracker

/**
 *  The delegate to receive theme tracking events.
 */
@property (nonatomic, readonly, weak, nullable) id<RBThemeTrackerDelegate> delegate;

/**
 *  The `Class` of the associated object if the object is subclass of `UIView` or `UIViewController`. It is `nil` otherwise.
 */
@property (nonatomic, readonly, nullable) Class classification;

/**
 *  The theme identifier from which to extract theme information from.
 *  Setting this will remove all previous custom overrides as well as removing the class theme (if any).
 *  If this is set to `nil` or if the identifier did not return a theme the default class theme (if any) will resume being used. 
 */
@property (nonatomic, nullable) NSString *identifier;

/**
 *  Indicates that theming for the associated object should be applied automatically on materialization. Default `YES`.
 *  For `UIView` and subclass objects the didMoveToSuperView method is utilised as an 
 *  indication of materialization and theming is applied when this event occurs.
 *  For `UIViewController` and subclass objects the viewWillAppear method is utilised as an 
 *  indication materialization and theming is applied when this event occurs.
 *  In other cases this has no affect (it applies only to `UIView` and `UIViewController`).
 *
 *  Note you may want to set this to `NO` in cases where a custom UIView contains subviews and the custom views theme is 
 *  forwarded to the subviews examples of this include `RBFormView`
 */
@property (nonatomic) BOOL shouldApplyThemingOnMaterialization;

/**
 *  Disables any further theming from being applied. This causes the `processChange:` from having any effect. Default `NO`.
 *  NB. it is the `processChange:` method that calls the delegates `applyTheme:` method when there are changings awaiting to be processed.
 */
@property (nonatomic) BOOL disableTheming;

/**
 *  Initializes a new theme tracker with the given class and delegate.
 *
 *  @param classification   The `Class` of the associated object if (and only if) the object is subclass of `UIView` or `UIViewController`. Otherwise set to `nil`.
 *  @param delegate         The delegate to receive theme tracking events.
 *
 *  @return The initialized object.
 */
- (nonnull instancetype)initWithClassification:(nonnull Class)classification delegate:(nonnull id<RBThemeTrackerDelegate>)delegate;

/**
 *  Initializes a new theme tracker with the given delegate.
 *
 *  @param delegate         The delegate to receive theme tracking events.
 *
 *  @return The initialized object.
 */
- (nonnull instancetype)initWithDelegate:(nonnull id<RBThemeTrackerDelegate>)delegate;

/**
 *  Convenience method that pushes a theme change and processes the change. Simply calls pushChanges followed by processChanges.
 *
 *  @param changes The theme (that will be cast to a Dictionary of type [String : Any]) to merge.
 */
- (void)applyChanges:(nullable id)changes;

/**
 *  Manually applies the full theme (using the value of the currentStateThemeKey if available).
 */
- (void)apply;

/**
 *  Resets theming removing all theming values and then reloads as normal via class theme and then via identifier.
 *  Note any custom theming values that may have been previously applied will of course no longer be set.
 */
- (void)reset;

/**
 *  Removes all theming values that may currently be present.
 */
- (void)clear;

#pragma mark -
#pragma mark State Themes

/**
 *  The key of the current activated state of the theme - or `nil` if in the normal state.
 */
@property (nonatomic, readonly, nullable) NSString *currentStateThemeKey;

/**
 *  Applies the normal state of the theme.
 */
- (void)applyNormalStateTheme;

/**
 *  Re-applies the current state of the theme.
 */
- (void)applyCurrentState;

/**
 *  Applies the given state theme.
 *
 *  @param key The unique key of the state.
 */
- (void)applyStateThemeWithKey:(nonnull NSString *)key;

/**
 *  Helper method that sets the property `shouldApplyThemingOnMaterialization`.
 *  on all the views that have been passed.
 *
 *  @param views        The views to set the property on.
 *  @param apply        Whether or not to apply theming on materialization.
 */
+ (void)setShouldApplyThemingOnMaterializationForViews:(nullable NSArray<UIView *> *)views apply:(BOOL)apply;

@end
