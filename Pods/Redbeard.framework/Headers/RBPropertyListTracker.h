//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Tracks the changes made to a property list (root being a dictionary), allowing the latest changes
 * to be processed on demand.
 */
@interface RBPropertyListTracker : NSObject

// Always kept up to date.

/**
 *  The latest value including pending changes.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *latestValue;

// Updated when changes are processed.

/**
 *  The latest value of processed changes. Does not include unprocessed changes.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> * currentValue;

/**
 *  Changes that are pending being processed.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> * pendingChanges;

/**
 *  Pushes a set of changes and merges these with the current set.
 *  This allows cumulative changes to be applied.
 *
 *  @param changes The change set to merge.
 *
 *  @return Whether the change was successfully pushed.
 */
- (BOOL)pushChanges:(nullable NSDictionary<NSString *, id> *)changes;

/**
 *  Process and merge the unprocessed changes that have been pushed.
 */
- (void)processChanges;

@end
