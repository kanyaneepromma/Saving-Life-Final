//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

//#import "RBLayoutView.h"
//#import "RBLazyLayoutView.h"

#import "RBMenuSegmentHeaderView.h"
#import "RBMenuSegmentButtonSchema.h"

@class RBMenuView;
@class RBLayoutView;
@class RBLazyLayoutView;

/**
 *  A menu segment view. Note theming is applied for items in the following order, 
 *  theme from json, (if item is top or bottom) apply top/bottom theme > apply theme from button schema theme identifier >
 *  apply theme from button schema override.
 */
@interface RBMenuSegmentView : UIView

/**
 *  The `RBMenuView` that this segment belongs to.
 */
@property (nonatomic, weak, nullable) RBMenuView *menuView;

/**
 *  The unique identifier of the segment.
 */
@property (nonatomic, readonly, nonnull) NSString *identifier;

/**
 *  Theme values to apply after any other prior theming has been applied.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *themeOverrides;

/**
 *  The header view to display above the button items.
 */
@property (nonatomic, nullable) UIView *headerView;

/**
 *  An array of RBMenuSegmentButton schemas.
 */
@property (nonatomic, nullable) NSArray<RBMenuSegmentButtonSchema *> *buttons;

/**
 *  The identfiers of the buttons that are toggled on.
 */
@property (nonatomic, readonly, nonnull) NSArray<NSString *> *toggledButtonIdentifiers;

/**
 *  The height to use for buttons (including toggle buttons).  Default = 50.
 */
@property (nonatomic) CGFloat buttonHeights;

/**
 *  The height to use custom buttons. Default = 50.
 */
@property (nonatomic) CGFloat customButtonHeights;

/**
 *  The overall layout positioner used. You may theme this positioner. Default values =
 *  spacing = 5,
 *  dimensions = 1,
 *  margin = [0, 0, 0, 0],
 *  orientation = `RBOrientationVertical`,
 *  sizing = `RBGridPositionerSizeEvenly`.
 */
@property (nonatomic, nonnull, readonly) RBGridPositioner *positioner;

/**
 *  The layout positioner used for the buttons and items. You may theme this positioner. Default values =
 *  spacing = 5,
 *  dimensions = 1,
 *  margin = [0, 0, 0, 0],
 *  orientation = `RBOrientationVertical`,
 *  sizing = `RBGridPositionerSizeEvenly`.
 */
@property (nonatomic, nonnull, readonly) RBGridPositioner *itemPositioner;

/**
 *  Initializes a new `RBMenuSegmentView`.
 *
 *  @param identifier   The unique identifier of the segment.
 *  @param menuView     The associated `RBMenuView` this segment belongs to.
 *  @param themeOverrides   Theme values to apply after any other prior theming has been applied.
 *
 *  @return The initialized `RBMenuSegmentView`.
 */
- (nonnull instancetype)initWithIdentifier:(nonnull NSString *)identifier
                                  menuView:(nonnull RBMenuView *)menuView
                            themeOverrides:(nullable NSDictionary<NSString *, id> *)themeOverrides;

#pragma mark -
#pragma mark Toggle

/**
 *  Sets the selected state of the toggle button at the given index.
 *
 *  @param selected     Whether or not the toggle button should be selected.
 *  @param identifier   The indentifier of the toggled button.
 */
- (void)setToggleButtonSelected:(BOOL)selected forIdentifier:(nonnull NSString*)identifier;

@end
