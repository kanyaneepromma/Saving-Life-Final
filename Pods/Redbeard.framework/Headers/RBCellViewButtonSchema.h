//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  A schema describing a cell view button.
 */
@interface RBCellViewButtonSchema : NSObject

/**
 *  The unique identifier of the button.
 */
@property (nonatomic, readonly, nonnull) NSString *identifier;

/**
 *  The title of the button.
 */
@property (nonatomic, readonly, nullable) NSString *title;

/**
 *  The image of the button.
 */
@property (nonatomic, readonly, nullable) UIImage *image;

/**
 *  Whether or not this button is the primary button.
 *  There can be only one primary button per side of a cell (left or right).
 *  The primary button is the one that expands and becomes selected when
 *  the cell is swiped.
 */
@property (nonatomic, readonly) BOOL isPrimaryButton;

/**
 *  Theme values to apply after any other prior theming has been applied.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *themeOverrides;

/**
 *  Initializes a new cell view button schema.
 *
 *  @param identifier       The unique identifier of the button.
 *  @param title            The button title.
 *  @param image            The image for the button.
 *  @param isPrimaryButton  Whether or not this button is the primary button on it's side.
 *  @param themeOverrides   Theme values to apply after any other prior theming has been applied.
 *
 *  @return The initialized schema.
 */
- (nonnull instancetype)initWithIdentifier:(nonnull NSString *)identifier
                                     title:(nullable NSString *)title
                                     image:(nullable UIImage *)image
                           isPrimaryButton:(BOOL)isPrimaryButton
                            themeOverrides:(nullable NSDictionary *)themeOverrides;

@end
