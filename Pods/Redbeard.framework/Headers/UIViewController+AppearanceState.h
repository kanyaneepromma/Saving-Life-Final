//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  `UIViewController` appearance state.
 *
 *  Tracks the current appearance state of the view controller.
 */
@interface UIViewController (AppearanceState)

/**
 *  The view controller is currently appearing.
 */
@property (nonatomic, readonly) BOOL isAppearing;

/**
 *  The view controller is currently disappearing.
 */
@property (nonatomic, readonly) BOOL isDisappearing;

/**
 *  The view controller has appeared.
 */
@property (nonatomic, readonly) BOOL didAppear;

/**
 *  The view controller has disappeared.
 */
@property (nonatomic, readonly) BOOL didDisappear;

@end
