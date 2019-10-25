//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBPaneViewController.h>

/**
 *  Manages a stack of horizontally-scrollable panes.
 */
@interface RBPaneContainerViewController : UIViewController

/**
 *  An array of `RBPaneViewController` objects.
 */
@property (nonatomic, readonly, nullable) NSArray<RBPaneViewController *> *panes;

/**
 *  Pushes a new pane to the container.
 *
 *  @param paneViewController The pane view controller to push.
 *  @param animated           Whether the push should be animated.
 *  @param completion         An optional block to be called when the operation is complete.
 */
- (void)pushPane:(nonnull RBPaneViewController *)paneViewController animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Pops the top pane view controller from the container.
 *
 *  @param animated   Whether or not the operation should be animated.
 *  @param completion An optional block to be called when the operation is complete.
 */
- (void)popPaneWithAnimation:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Pops all panes above the specified pane in the stack, such that the given pane
 *  is at the top after the operation is complete.
 *
 *  @param paneViewController The pane to pop to.
 *  @param animated           Whether or not the operation should be animated.
 *  @param completion         An optional block to be called when the operation is complete.
 */
- (void)popToPane:(nonnull RBPaneViewController *)paneViewController animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

/**
 *  Scrolls to reveal the specified pane.
 *
 *  @param paneViewController The pane to reveal.
 *  @param animated           Whether or not the operation should be animated.
 *  @param completion         An optional block to be called when the operation is complete.
 */
- (void)revealPane:(nonnull RBPaneViewController *)paneViewController animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

@end
