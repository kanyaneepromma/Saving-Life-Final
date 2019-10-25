//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

//#import <Redbeard/RBBaseCellView.h>
@class RBBaseCellView;

/**
 *  A menu button schema.
 */
@interface RBMenuSegmentButtonSchema : NSObject

/**
 *  The unique identifier of the button. Identifier is also used as theme identifier within the segment theme.
 */
@property (nonatomic, readonly, nonnull) NSString *identifier;

/**
 *  The title for the button that will be created from this schema.
 */
@property (nonatomic, readonly, nullable) NSString *title;

/**
 *  Theme values to apply after any other prior theming has been applied.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *themeOverrides;

/**
 *  The custom cell to use instead of the default (`RBBaseCellView`).
 */
@property (nonatomic, readonly, nullable) RBBaseCellView *custom;

/**
 *  Indicates that is is a schema that can be toggled.
 */
@property (nonatomic, readonly) BOOL canBeToggled;

/**
 *  Initializes a new menu button schema.
 *
 *  @param identifier           The unique identifier of the button.
 *  @param title                The title of the button.
 *  @param canBeToggled         Whether or not the button can be toggled.
 *  @param themeOverrides       Theme values to apply after any other prior theming has been applied.
 *
 *  @return The initialized menu button schema.
 */
- (nonnull instancetype)initWithIdentifier:(nonnull NSString *)identifier
                                     title:(nullable NSString *)title
                              canBeToggled:(BOOL)canBeToggled
                            themeOverrides:(nullable NSDictionary *)themeOverrides;

/**
 *  Initializes a new custom button schema.
 *
 *  @param identifier           The unique identifier of the button.
 *  @param custom               The custom cell view.
 *  @param themeOverrides       Theme values to apply after any other prior theming has been applied.
 *
 *  @return The initialized menu custom button schema.
 */
- (nonnull instancetype)initCustomWithIdentifier:(nonnull NSString *)identifier
                                          custom:(nonnull RBBaseCellView *)custom
                                  themeOverrides:(nullable NSDictionary *)themeOverrides;

/**
 *  Initializes a new menu button schema.
 *
 *  @param identifier           The unique identifier of the button.
 *  @param title                The title of the button.
 *  @param canBeToggled        Whether or not the button can be toggled.
 *  @param themeOverrides       Theme values to apply after any other prior theming has been applied.
 *
 *  @return The initialized menu button schema.
 */
+ (nonnull RBMenuSegmentButtonSchema *)buttonWithIdentifier:(nonnull NSString *)identifier
                                                      title:(nullable NSString *)title
                                               canBeToggled:(BOOL)canBeToggled
                                             themeOverrides:(nullable NSDictionary<NSString *, id> *)themeOverrides;
@end
