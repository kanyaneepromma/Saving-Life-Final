//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol RBActivityViewDelegate;

/**
 * A view that displays activity indication.
 *
 * There are two types of activity - determinate (with progress) and non-determinate (without progress).
 */
@interface RBActivityView : UIView

/**
 * An optional delegate to be informed of the state of activity indication.
 */
@property (nonatomic, weak, nullable) id<RBActivityViewDelegate> delegate;

/**
 * Whether or not the activity indication is currently active.
 */
@property (nonatomic, readonly) BOOL isActive;

/**
 * The number of indeterminate activities that are currently active.
 */
@property (nonatomic, readonly) NSInteger indeterminateActivityCount;

/**
 * Starts an indeterminate activity.
 */
- (void)startIndeterminateActivity;

/**
 * Stops an indeterminate activity.
 */
- (void)stopIndeterminateActivity;

/**
 * Stop all indeterminate activities.
 */
- (void)stopAllIndeterminateActivities;

/**
 * The number of determinate activities that are currently active.
 */
@property (nonatomic, readonly) NSInteger determinateActivityCount;

/**
 * Start a determinate activity with the given identifier.
 *
 * @param identifier The unique identifier for the activity.
 */
- (void)startDeterminateActivityWithID:(nonnull NSString *)identifier;

/**
 * Stop a determinate activity with the given identifier.
 *
 * @param identifier The unique identifier for the activity.
 */
- (void)stopDeterminateActivityWithID:(nonnull NSString *)identifier;

/**
 * Update the progress of the determinate activity with the given identifier.
 *
 * @param progress   The current progress value from 0 to 1.
 * @param text       The message to display that describes the current state of the activity.
 * @param identifier The unique identifier for the activity.
 */
- (void)setDeterminateActivityProgress:(float)progress withText:(nullable NSString *)text withID:(nonnull NSString *)identifier;

@end

/**
 * A delegate of an `RBActivityView` that is informed of the state of activity indication.
 */
@protocol RBActivityViewDelegate <NSObject>

@optional

/**
 *  The activity view will begin to visually indicate activity.
 *
 *  @param activityView The `RBActivityView` object.
 */
- (void)activityViewWillBecomeActive:(nonnull RBActivityView *)activityView;

/**
 *  The activity view began visually indicating activity.
 *
 *  @param activityView The `RBActivityView` object.
 */
- (void)activityViewDidBecomeActive:(nonnull RBActivityView *)activityView;

/**
 *  The activity view will stop visually indicating activity.
 *
 *  @param activityView The `RBActivityView` object.
 */
- (void)activityViewWillBecomeInactive:(nonnull RBActivityView *)activityView;

/**
 *  The activity view stopped visually indicating activity.
 *
 *  @param activityView The `RBActivityView` object.
 */
- (void)activityViewDidBecomeInactive:(nonnull RBActivityView *)activityView;

@end
