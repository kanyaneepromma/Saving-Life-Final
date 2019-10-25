//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/UIViewControllerParentCollection.h>

/**
 *  Provides easy access to parents of interest in the heirarchy.
 */
@interface UIViewController (Parents)

/**
 *  Provides easy access to parents of interest in the heirarchy.
 */
@property (nonatomic, readonly, nonnull) UIViewControllerParentCollection *parents;

@end
