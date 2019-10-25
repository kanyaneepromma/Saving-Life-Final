//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Measures the time taken to complete a task.
 *
 * @param task       The task block.  The given block should be called when the task is complete.
 * @param completion The completion block with the result.
 */
static inline void measureTask(void (^task)(void (^capture)(void)), void (^completion)(NSTimeInterval timeTaken))
{
    if(completion && task)
    {
        NSDate *before = [NSDate date];
        
        task(^{
            completion([[NSDate date] timeIntervalSinceDate:before]);
        });
    }
    else if(completion && !task)
    {
        completion(0);
    }
}
