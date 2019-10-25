//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/RBButton.h>

@protocol RBToggleButtonDelegate;

/**
 *  A button that toggles between any number of specified modes.
 */
@interface RBToggleButton : RBButton

/**
 *  A delegate that receives mode change events.
 */
@property (nonatomic, weak, nullable) id<RBToggleButtonDelegate> delegate;

/**
 *  The total number of button modes. Default = `2`.
 */
@property (nonatomic) NSUInteger modes;

/**
 *  The index of the current mode that is selected. Note this is zero indexed.
 */
@property (nonatomic) NSUInteger mode;

@end

/**
 *  A delegate that receives mode change events from an `RBToggleButton`.
 */
@protocol RBToggleButtonDelegate <NSObject>

@optional

/**
 *  Called when a toggle button was tapped by the user.
 *
 *  @param toggleButton The `RBToggleButton` object.
 */
- (void)toggleButtonWasTapped:(nonnull RBToggleButton *)toggleButton;

/**
 *  Whether or not the toggle button should change modes.
 *
 *  @param toggleButton The `RBToggleButton` object.
 *  @param mode         The index of the mode that will be switched to if accepted.
 *  @param fromMode     The index of the mode that will be switched from if accepted.
 *  @param byUser       Whether or not the mode change is caused by a user interaction.
 *
 *  @return Whether or not to allow the mode change.
 */
- (BOOL)toggleButton:(nonnull RBToggleButton *)toggleButton shouldSelectMode:(NSUInteger)mode fromMode:(NSUInteger)fromMode byUser:(BOOL)byUser;

/**
 *  Called when a toggle button will change modes.
 *
 *  @param toggleButton The `RBToggleButton` object.
 *  @param mode         The index of the mode that will be switched to.
 *  @param fromMode     The index of the mode that will be switched from.
 *  @param byUser       Whether or not the mode change is caused by a user interaction.
 */
- (void)toggleButton:(nonnull RBToggleButton *)toggleButton willSelectMode:(NSUInteger)mode fromMode:(NSUInteger)fromMode byUser:(BOOL)byUser;

/**
 *  Called when a toggle button has changed modes.
 *
 *  @param toggleButton The `RBToggleButton` object.
 *  @param mode         The index of the mode that was switched to.
 *  @param fromMode     The index of the mode that was switched from.
 *  @param byUser       Whether or not the mode change is caused by a user interaction.
 */
- (void)toggleButton:(nonnull RBToggleButton *)toggleButton didSelectMode:(NSUInteger)mode fromMode:(NSUInteger)fromMode byUser:(BOOL)byUser;

@end
