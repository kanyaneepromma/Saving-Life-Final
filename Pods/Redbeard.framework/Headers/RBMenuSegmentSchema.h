//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Redbeard/RBMenuSegmentButtonSchema.h>

/**
 *  A schema describing a menu segment.
 */
@interface RBMenuSegmentSchema : NSObject

/**
 *  The unique identifier of the segment. Identifier is also used as theme identifier within the menu theme.
 */
@property (nonatomic, readonly, nullable) NSString *identifier;

/**
 *  Theme values to apply after any other prior theming has been applied.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *themeOverrides;

/**
 *  The header view to display above the items in the segment. Note `RBMenuSegmentHeaderView` may serve for most purposes.
 */
@property (nonatomic, readonly, nullable) UIView *headerView;

/**
 *  An array of RBMenuSegmentButton schemas.
 */
@property (nonatomic, readonly, nonnull) NSArray<RBMenuSegmentButtonSchema *> *buttons;

/**
 *  Initializes the menu segment schema.
 *
 *  @param identifier               The unique identifier of the segment.
 *  @param headerView               The header view to display above the items in the segment. Note `RBMenuSegmentHeaderView` may serve for most purposes.
 *  @param buttons                  An array of segment button schemas (of type `RBMenuSegmentButtonSchema`).
 *  @param themeOverrides   Theme values to apply after any other prior theming has been applied.
 *
 *  @return The initialized menu segment schema.
 */
- (nonnull instancetype)initWithIdentifier:(nonnull NSString *)identifier
                                headerView:(nullable UIView *)headerView
                                     buttons:(nonnull NSArray<RBMenuSegmentButtonSchema *> *)buttons
                            themeOverrides:(nullable NSDictionary<NSString *, id> *)themeOverrides;

@end
