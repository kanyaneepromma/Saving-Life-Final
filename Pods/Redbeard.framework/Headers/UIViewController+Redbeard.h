//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  `UIViewController` extensions.
 */
@interface UIViewController (Redbeard)

/**
 *  Initializes the view controller without an XIB/NIB.
 *
 *  @return The initialized view controller object.
 */
- (nonnull instancetype)initWithoutNib;

/**
 *  Whether or not the view has been loaded and is available yet.
 */
@property (nonatomic, readonly) BOOL viewIsAvailable;

// Returns true if one of the parent view controllers is the one given.

/**
 *  Determines whether this view controller is a successor in the heirarchy
 *  of the given view controller.
 *
 *  @param viewController The potential ancestor view controller.
 *
 *  @return Whether or not the given view controller is a parent.
 */
- (BOOL)isChildOfViewController:(nonnull UIViewController *)viewController;

@end
