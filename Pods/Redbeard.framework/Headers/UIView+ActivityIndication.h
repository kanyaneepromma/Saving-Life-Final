//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBActivityView.h>

/**
 *  `UIView` activity indication.
 */
@interface UIView (ActivityIndication) <RBActivityViewDelegate>

/**
 *  The activity view.
 */
@property (nonatomic, readonly, nullable) RBActivityView *activityView;

/**
 *  Whether or not the activity indicator is currently active.
 */
@property (nonatomic, readonly) BOOL activityRunning;

/**
 *  Stops all of the currently running indeterminate activities.
 */
- (void)stopAllIndeterminateActivities;

/**
 *  Starts an indeterminate activity.
 */
- (void)startIndeterminateActivity;

/**
 *  Stops an indeterminate activity.
 */
- (void)stopIndeterminateActivity;

/**
 *  Starts a determinate activity with the given unique identifier used to provide updates.
 *
 *  @param indentifier The unique identifier of this determinate activity job.
 */
- (void)startDeterminateActivityWithID:(nonnull NSString *)indentifier;

/**
 *  Stops the determinate activity with the given unique identifier.
 *
 *  @param indentifier The unique identifier of the determinate activity to stop.
 */
- (void)stopDeterminateActivityWithID:(nonnull NSString *)indentifier;

/**
 *  Updates the progress of a determinate activity.
 *
 *  @param progress   The current progress from 0 to 1.
 *  @param text       A string describing the current state of the determinate activity.
 *  @param identifier The unique identifier of the determinate activity.
 */
- (void)setDeterminateActivityProgress:(float)progress withText:(nullable NSString *)text withID:(nonnull NSString *)identifier;

#pragma mark -
#pragma mark Subclassing

/**
 *  Called when the activity indicator will become active.
 */
- (void)viewActivitiesWillBegin;

/**
 *  Called when the activity indicator did become active.
 */
- (void)viewActivitiesDidBegin;

/**
 *  Called when the activity indicator will become inactive.
 */
- (void)viewActivitiesWillStop;

/**
 *  Called when the activity indicator did become inactive.
 */
- (void)viewActivitiesDidStop;

@end
