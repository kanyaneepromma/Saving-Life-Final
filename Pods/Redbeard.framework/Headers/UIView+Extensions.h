//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/**
 *  `UIView` extension methods.
 */
@interface UIView (Extensions)

/**
 *  Cancels all animations on this view and if specified, it's subviews too.
 *
 *  @param includingSubviews Whether or not to cancel the animations on all descendent views too.
 */
- (void)removeAllAnimations:(BOOL)includingSubviews;

#pragma mark -
#pragma mark Snapshot

/**
 *  Gets a snapshot of the given frame of this `UIView`.
 *
 *  @param rect The frame of the `UIView` to take a snapshot of.
 *
 *  @return The snapshot `UIImage` object.
 */
- (UIImage *)snapshotOfRect:(CGRect)rect;

#pragma mark -
#pragma mark System Frames in Local View

/**
 *  Gets the absolute frame of the status bar.
 *
 *  @return The `CGRect` frame value.
 */
- (CGRect)statusBarFrame;

/**
 *  Gets the absolute frame of the keyboard.
 *
 *  @return The `CGRect` frame value.
 */
- (CGRect)keyboardFrame;

/**
 *  The absolute insets that would avoid the status bar.
 *
 *  @return The `UIEdgeInsets` insets value.
 */
- (UIEdgeInsets)insetsForStatusBar;

/**
 *  The absolute insets that would avoid the keyboard.
 *
 *  @return The `UIEdgeInsets` insets value.
 */
- (UIEdgeInsets)insetsForKeyboard;

/**
 *  The absolute insets that would avoid both the status bar and keyboard.
 *
 *  @return The `UIEdgeInsets` insets value.
 */
- (UIEdgeInsets)insetsForStatusBarAndKeyboard;

/**
 *  Gets the frame in this `UIView` that the status bar occupies.
 *
 *  @return The `CGRect` frame value.
 */
- (CGRect)statusBarFrameInView;

/**
 *  Gets the frame in this `UIView` that the keyboard occupies.
 *
 *  @return The `CGRect` frame value.
 */
- (CGRect)keyboardFrameInView;

/**
 *  The insets in the bounds of this `UIView` to avoid the space in this view
 *  that the status bar occupies.
 *
 *  @return The `UIEdgeInsets` insets value.
 */
- (UIEdgeInsets)insetsForStatusBarInView;

/**
 *  The insets in the bounds of this `UIView` to avoid the space in this view
 *  that the keyboard occupies.
 *
 *  @return The `UIEdgeInsets` insets value.
 */
- (UIEdgeInsets)insetsForKeyboardInView;

/**
 *  The insets in the bounds of this `UIView` to avoid the space in this view
 *  that both the status bar and keyboard occupy.
 *
 *  @return The `UIEdgeInsets` insets value.
 */
- (UIEdgeInsets)insetsForStatusBarAndKeyboardInView;

@end
