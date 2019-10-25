//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBPaneViewController.h>

/**
 *  A pane page view that can be added to an `RBPaneViewController`.
 */
@interface RBPaneView : UIView

/**
 *  The `RBPaneViewController` that this pane view belongs to.
 */
@property (nonatomic, weak, readonly, nullable) RBPaneViewController *controller;

/**
 *  Initializes a new pane view.
 *
 *  @param controller The `RBPaneViewController` that the pane view will belong to.
 *
 *  @return The initialized pane view.
 */
- (nonnull instancetype)initWithController:(nonnull RBPaneViewController *)controller;

@end
