//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBNavigationController.h>
#import <Redbeard/RBPresentationController.h>
#import <Redbeard/RBPaneContainerViewController.h>
#import <Redbeard/RBSidebarContainerViewController.h>

@class RBTabController;

/**
 *  Provides access to parent view controllers of interest.
 */
@interface UIViewControllerParentCollection : NSObject

/**
 *  Initializes the collection with the given view controller.
 *
 *  @param viewController The subject view controller to provide parental access for.
 *
 *  @return The initialized collection object.
 */
- (nonnull instancetype)initWithViewController:(nonnull UIViewController *)viewController;

/**
 *  The closest parent navigation controller in the view controller heirarchy, or `nil` if none exists.
 */
@property (nonatomic, readonly, nullable) RBNavigationController *navigationController;

/**
 *  The closest parent sidebar container in the view controller heirarchy, or `nil` if none exists.
 */
@property (nonatomic, readonly, nullable) RBSidebarContainerViewController *sidebarContainer;

/**
 *  The closest parent pane container in the view controller heirarchy, or `nil` if none exists.
 */
@property (nonatomic, readonly, nullable) RBPaneContainerViewController *paneContainer;

/**
 *  The closest parent tab controller in the view controller heirarchy, or `nil` if none exists.
 */
@property (nonatomic, readonly, nullable) RBTabController *tabController;

@end
