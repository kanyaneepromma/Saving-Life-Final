//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//
import UIKit
import Foundation

/**
 *  A managed memory cache for `Data` objects.
 */
@objcMembers public class RBDataMemoryCache: NSObject, RBDataCache {
    
    public static let defaultMaximumMemoryCacheSize: Int = 104857600 // 100MB
    
    private let lockQueue = DispatchQueue(label: "RBDataMemoryCache")
    private var items = [String: RBDataMemoryCacheRecord]()
    
    /**
     *  The maximum size that the cache can be in bytes.
     */
    public private(set) var maximumCacheSizeInBytes: Int = RBDataMemoryCache.defaultMaximumMemoryCacheSize
    
    /**
     *  The current size of the cache.
     */
    public private(set) var cacheSizeInBytes: Int = 0
    
    /**
     *  Creates a new cache with the given maximum size.
     *
     *  @param maximumCacheSizeInBytes The maximum size that the cache can be in bytes.
     *
     *  @return The new cache object.
     */
    public init(maximumCacheSize maximumCacheSizeInBytes: Int) {
        super.init()
        
        if maximumCacheSizeInBytes >= 0 {
            self.maximumCacheSizeInBytes = maximumCacheSizeInBytes
        }
    }
    
    public func storeDataItem(_ dataItem: Data, key: String, expiryInterval: TimeInterval) -> Bool {
        return self.storeDataItem(dataItem, key: key, group: "", expiryInterval: expiryInterval)
    }
    
    public func storeDataItem(_ dataItem: Data, key: String, group: String, expiryInterval: TimeInterval) -> Bool {
        
        let item = RBDataMemoryCacheRecord(key: RBDataMemoryCache.generateKey(withKey: key, withGroup: group),
                                           size: dataItem.count,
                                           data: dataItem,
                                           expiry: Date().addingTimeInterval(expiryInterval))
        
        lockQueue.sync {
            items[key] = item
            cacheSizeInBytes += item.size
            
            if cacheSizeInBytes > maximumCacheSizeInBytes {
                prune()
            }
        }
        
        return true
    }
    
    public func dataItemExists(withKey key: String) -> Bool {
        return self.dataItemExists(withKey: key, withGroup: "")
    }
    
    public func dataItemExists(withKey key: String, withGroup group: String) -> Bool {
        
        var rv = false
        let k = RBDataMemoryCache.generateKey(withKey: key, withGroup: group)
        
        lockQueue.sync {
            
            if let item = items[k] {
                if item.expiry <= Date() {
                    rv = true
                }
            }
        }
        
        return rv
    }
    
    
    public func fetchDataItem(withKey key: String) -> Data? {
        return self.fetchDataItem(withKey: key, withGroup: "")
    }
    
    public func fetchDataItem(withKey key: String, withGroup group: String) -> Data? {
        
        var data: Data? = nil
        let k = RBDataMemoryCache.generateKey(withKey: key, withGroup: group)
        
        lockQueue.sync {
            if let item = items[k] {
                if item.expiry <= Date() {
                    data = item.data
                }
            }
        }
        
        return data
    }
    
    
    public func removeDataItem(withKey key: String) {
        self.removeDataItem(withKey: key, withGroup: "")
    }
    
    public func removeDataItem(withKey key: String, withGroup group: String) {
        lockQueue.sync {
            let k = RBDataMemoryCache.generateKey(withKey: key, withGroup: group)
            if let item = items[k] {
                cacheSizeInBytes -= item.size
                items.removeValue(forKey: k)
            }
        }
    }
    
    /**
     *  Remove all of the items stored in the given group.
     *
     *  @param group The group for which to remove all stored data items.
     */
    public func removeAllItems(withGroup group: String) {
        
        lockQueue.sync {
            
            let keys = items.keys
            let g = RBDataMemoryCache.generateGroup(withGroup: group)
            
            for key in keys {
                if key.starts(with: g) {
                    if let item = items[key] {
                        cacheSizeInBytes -= item.size
                        items.removeValue(forKey: key)
                    }
                }
            }
        }
    }
    
    /**
     *  Removes all data items that have expired.
     */
    public func removeAllExpiredItems() {
        
        lockQueue.sync {
            
            let keys = items.keys
            
            for key in keys {
                
                if let item = items[key] {
                    if item.expiry <= Date() {
                        cacheSizeInBytes -= item.size
                        items.removeValue(forKey: key)
                    }
                }
            }
        }
    }
    
    // MARK: -
    // MARK: Internal
    
    func prune() {
        
        self.removeAllExpiredItems() // Aquires lock hence outside
        
        lockQueue.sync {
            
            if cacheSizeInBytes > maximumCacheSizeInBytes {
                let targetCacheSize = Int(maximumCacheSizeInBytes / 2)
                
                var dates = [Date: String]() // TODO: what if 2 dates are the exact same?
                let keys = items.keys
                
                for key in keys {
                    if let item = items[key] {
                        dates[item.expiry] = key
                    }
                }
                
                // Earliest first
                for date in dates.keys.sorted() {
                    if let key = dates[date], let item = items[key] {
                        cacheSizeInBytes -= item.size
                        items.removeValue(forKey: key)
                    }
                    
                    if cacheSizeInBytes <= targetCacheSize {
                        break
                    }
                }
            }
        }
    }
    
    //
    
    class func generateKey(withKey key: String, withGroup group: String) -> String {
        
        let k = key.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines)
        let g = RBDataMemoryCache.generateGroup(withGroup: group)
        
        if g.count > 0 {
            return "\(g)_\(k)"
        } else {
            return "_\(k)"
        }
    }
    
    class func generateGroup(withGroup group: String) -> String {
        let g = group.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines)
        
        if g.count > 0 {
            return "g_\(group)"
        } else {
            return g
        }
    }
}

private class RBDataMemoryCacheRecord {
    let key: String
    let size: Int
    let data: Data
    let expiry: Date
    
    init(key: String, size: Int, data: Data, expiry: Date) {
        self.key = key
        self.size = size
        self.data = data
        self.expiry = expiry
    }
}
