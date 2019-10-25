//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  Manages a queue of items to be processed.
 */
@objcMembers public class RBProcessingQueue : NSObject {
    
    /**
     *  The total set of items that were queued to be processed.
     */
    public private(set) var items: Set<AnyHashable> = Set<AnyHashable>()
    
    /**
     *  The set of items that were queued and have been processed.
     */
    public private(set) var pendingItems: Set<AnyHashable> = Set<AnyHashable>()
    
    /**
     *  The set of items that were queued and have not yet been processed.
     */
    public private(set) var processedItems: Set<AnyHashable> = Set<AnyHashable>()
    
    /**
     *  Adds a new item to the queue to be processed.
     *
     *  @param item The item to add to the queue.
     */
    public func enqueueItem(_ item: AnyHashable) {
        
        if self.items.contains(item) {
            return
        } else {
            self.items.update(with: item)
            self.pendingItems.update(with: item)            
        }
    }
    
    /**
     *  Marks whether an item in the queue has been processed.
     *
     *  @param item      The item to mark as processed or not processed.
     *  @param processed Whether or not the item should be marked as processed (true) or unprocessed (false).
     */
    public func markItem(_ item: AnyHashable, asProcessed processed: Bool) {
        
        if !self.items.contains(item) {
            return
        }
        
        let exists = self.processedItems.contains(item)
        
        if exists && processed {
            return
        }
        
        if !exists && !processed {
            return
        }
        
        if exists && !processed {
            self.processedItems.remove(item)
            self.pendingItems.update(with: item)
        }
        else if !exists && processed {
            self.processedItems.update(with: item)
            self.pendingItems.remove(item)
        }
    }
}

