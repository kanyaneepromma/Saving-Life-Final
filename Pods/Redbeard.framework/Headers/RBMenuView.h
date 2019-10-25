//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

//#import "RBLayoutView.h"

#import <Redbeard/RBMenuSegmentSchema.h>
#import <Redbeard/RBMenuSegmentView.h>
@class RBLayoutView;
@protocol RBMenuViewDelegate;

/**
 *  A segmented menu of buttons.
 */
@interface RBMenuView : UIView

/**
 *  A delegate to receive button selection events.
 */
@property (nonatomic, weak, nullable) id<RBMenuViewDelegate> delegate;

/**
 *  An array of `RBMenuSegmentSchema` objects.
 */
@property (nonatomic, nullable) NSArray<RBMenuSegmentSchema *> *segmentItems;

/**
 *  The overall layout positioner used. You may theme this positioner. Default values =
 *  spacing = 0,
 *  dimensions = 1,
 *  margin = [0, 0, 0, 0],
 *  orientation = `RBOrientationVertical`,
 *  sizing = `RBGridPositionerSizeEvenly`.
 */
@property (nonatomic, nonnull, readonly) RBGridPositioner *positioner;

/**
 *  Gets the segment view with the given identifier.
 *
 *  @param segmentIdentifier The name of the segment.
 *
 *  @return The `RBMenuSegmentView` object.
 */
- (nullable RBMenuSegmentView *)segmentViewWithIdentifier:(nonnull NSString *)segmentIdentifier;

@end

/**
 *  A delegate to receive button selection events for a `RBMenuView` object.
 */
@protocol RBMenuViewDelegate <NSObject>

@optional

/**
 *  Called when a menu button is tapped.
 *
 *  @param menuView             The `RBMenuView` object.
 *  @param segmentIdentifier    The identifier of the segment.
 *  @param identifier           The identifier of the button.
 */
- (void)menuView:(nonnull RBMenuView *)menuView segmentIdentifier:(nonnull NSString*)segmentIdentifier didSelectButtonWithIdentifier:(nonnull NSString *)identifier;

/**
 *  Called when a menu toggle button is tapped.
 *
 *  @param menuView                 The `RBMenuView` object.
 *  @param segmentIdentifier        The name of the segment.
 *  @param identifier               The identifier of the toggle button.
 *  @param selected                 Whether or not the toggle button was selected (true) or unselected (false).
 */
- (void)menuView:(nonnull RBMenuView *)menuView segmentIdentifier:(nonnull NSString*)segmentIdentifier didToggleButtonWithIdentifier:(nonnull NSString *)identifier selectionDidChangeTo:(BOOL)selected;

@end

