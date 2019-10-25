//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

// Note - a given key can exist in only one group.
/*
/**
 *  A cache that persists items to disk.
 */
@objc public class RBDataPersistentCache: NSObject {
    
    @objc public static let defaultMaximumDiskCacheSize: Int = 262144000 // 250MB
    
    private let diskQueue: DispatchQueue(label: "RBDataPersistentCache")
    
    private static let metaDataFilename = "metadata.json"
    private static let metaDataSizeKey = "size"
    private static let dataFileExpiryIntervalExtension = "expiry_interval"
    private static let dataFileGroupExtension = "group_name"

    //
    
    /**
     *  The path to which items are stored.
     */
    @objc public private(set) var storagePath: String
    
    /**
     *  The maximum size in bytes of the cache.
     */
    @objc public private(set) var maximumCacheSizeInBytes: Int = RBDataPersistentCache.defaultMaximumDiskCacheSize
    
    /**
     *  The current size of the cache in bytes.
     */
    @objc public private(set) var cacheSizeInBytes: Int = 0
    
    private var fileManager = FileManager()
    var cacheMetaDataFilePath: String?
    
    /**
     *  Initializes a new persistent cache with default settings.
     *
     *  @return The initialized persistent cache.
     */
    @objc public convenience override init() {
        self.init(storagePath: RBFilesystem.pathToCacheDirectory(), maximumCacheSize: RBDataPersistentCache.defaultMaximumDiskCacheSize, namespace: "default")
    }
    
    /**
     *  Initializes a new persistent cache with the given settings.
     *
     *  @param storagePath             The path at which to store items.
     *  @param maximumCacheSizeInBytes The maximum size of the cache in bytes.
     *  @param ns                      The namespace of the cache.
     *
     *  @return The initialized cache.
     */
    @objc public init(storagePath: String, maximumCacheSize maximumCacheSizeInBytes: Int, namespace ns: String) {
        super.init()
        
        self.storagePath = storagePath
        
        if maximumCacheSizeInBytes >= 0 {
            self.maximumCacheSizeInBytes = maximumCacheSizeInBytes
        }
        
        cacheMetaDataFilePath = URL(fileURLWithPath: self.storagePath).appendingPathComponent(metaDataFilename).absoluteString
        
        let queueNamespace = "\(REDBEARD_NAMESPACE).\(ns)"
        diskQueue = DispatchQueue(label: queueNamespace.utf8EncodedString())
        
        diskQueue?.sync(execute: {() -> Void in
            
            self.isValid = true
            var isDirectory = ObjCBool(false)
        
            if (self.fileManager?.fileExists(atPath: self.storagePath, isDirectory: &isDirectory))! {
            
                if !isDirectory.boolValue {
                    self.error = NSErrorMake(0, "A file exists where the cache directory is needed.")
                    self.isValid = false
                }
            }
            else {
                let error: Error? = nil
                try? self.fileManager?.createDirectory(atPath: self.storagePath, withIntermediateDirectories: true, attributes: nil)
                
                if error != nil {
                    self.error = error
                    self.isValid = false
                }
            }
           
            let metaData = try? RBJson.deserialise(fromFile: self.cacheMetaDataFilePath!)
            self.cacheSizeInBytes = UInt((metaData as! [AnyHashable: Any])[metaDataSizeKey] as! Int)
        })
    }
    
    /**
     *  Asynchronously stores the given data item.
     *
     *  @param dataItem       The data item to store.
     *  @param key            The unique key to store the item with.
     *  @param group          The group in which to store the item (optional).
     *  @param expiryInterval The time span after which the item expires.
     *  @param completion     An optional block to be called when storage is complete.
     */
    public func storeDataItem(_ dataItem: Data, key: String, group: String?, expiryInterval: TimeInterval, completion: @escaping () -> ()?) {
        
        if !isValid {
            return
        }
        
        let keyHash: String = key.base64
        let filePath: String = URL(fileURLWithPath: storagePath).appendingPathComponent(keyHash).absoluteString
        let expiryIntervalFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileExpiryIntervalExtension).absoluteString
        let groupNameFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileGroupExtension).absoluteString
        
        diskQueue?.async(execute: {() -> Void in
            self.fileManager?.createFile(atPath: filePath, contents: dataItem, attributes: nil)
        
            if expiryInterval != 0.0 {
                self.fileManager?.createFile(atPath: expiryIntervalFilePath, contents: "\(expiryInterval)".utf8DataValue, attributes: nil)
            }
            
            if group?.count != nil {
                self.fileManager?.createFile(atPath: groupNameFilePath, contents: group?.utf8DataValue, attributes: nil)
            }
            
            self.cacheSizeInBytes += UInt(dataItem.count)
            self.fileManager?.createFile(atPath: self.cacheMetaDataFilePath!, contents: "\(self.cacheSizeInBytes)".utf8DataValue, attributes: nil)
            
            //Salman Comment self.log("Stored item, cache at %lu bytes.", UInt(self.cacheSizeInBytes))
            
            if self.cacheSizeInBytes > self.maximumCacheSizeInBytes {
                self.prune() // Dispatches async task.
            }
           
            if completion != nil {
                DispatchQueue.main.async(execute: {() -> Void in
                    completion()
                })
            }
        })
    }
    
    /**
     *  Determines whether a non-expired item is stored for the given key.
     *
     *  @param key The key to search for.
     *
     *  @return Whether or not an item was found.
     */
    @objc public func dataItemExists(withKey key: String) -> Bool {
       
        if !isValid {
            return false
        }
        
        let keyHash: String = key.base64
        let filePath: String = URL(fileURLWithPath: storagePath).appendingPathComponent(keyHash).absoluteString
        let expiryIntervalFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileExpiryIntervalExtension).absoluteString
        
        var exists = false
        
        diskQueue?.sync(execute: {() -> Void in
           
            if self.fileManager?.fileExists(atPath: filePath, isDirectory: nil) ?? false {
            
                if self.fileManager?.fileExists(atPath: expiryIntervalFilePath, isDirectory: nil) ?? false {
                    
                    var notExpired = false
                
                    if self.fileManager?.fileExists(atPath: expiryIntervalFilePath, isDirectory: nil) ?? false {
                        let expiryInterval = TimeInterval((Double((try? String(contentsOfFile: expiryIntervalFilePath, encoding: .utf8)) ?? "") ?? 0.0))
                        let fileCreationDate = (try? self.fileManager?.attributesOfItem(atPath: filePath)[.creationDate]) as? Date
                        let expiryDate = fileCreationDate?.addingTimeInterval(expiryInterval)
                       
                        notExpired = expiryDate?.compare(Date()) == .orderedDescending
                    }
                    else {
                        // No expiry.
                        notExpired = true
                    }
                    if notExpired {
                        exists = true
                    }
                }
                else {
                    // No Expiry.
                    exists = true
                }
            }
        })
        
        if exists {
            //Salman Comment log("Cache item found to exist!")
        }
        else {
            //Salman Comment log("Cache item found to not exist!")
        }
        return exists
    }
    
    /**
     *  Determines whether a non-expired item is stored for the given key.
     *
     *  @param key        The key to search for.
     *  @param completion The completion block that is called with the result.
     */
    @objc public func fetchDataItem(withKey key: String, completion: @escaping (_: Data?) -> Void) {
       
        if !isValid {
        
            if (completion != nil) {
                completion(nil)
            }
            return
        }
        
        let keyHash: String = key.base64
        let filePath: String = URL(fileURLWithPath: storagePath).appendingPathComponent(keyHash).absoluteString
        let expiryIntervalFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileExpiryIntervalExtension).absoluteString
        
        diskQueue?.async(execute: {() -> Void in
        
            var valid = false
            
            if self.fileManager?.fileExists(atPath: filePath, isDirectory: nil) ?? false {
                
                var notExpired = false
            
                if self.fileManager?.fileExists(atPath: expiryIntervalFilePath, isDirectory: nil) ?? false {
                    let expiryInterval = TimeInterval((Double((try? String(contentsOfFile: expiryIntervalFilePath, encoding: .utf8)) ?? "") ?? 0.0))
                    let fileCreationDate = (try? self.fileManager?.attributesOfItem(atPath: filePath)[.creationDate]) as? Date
                    let expiryDate = fileCreationDate?.addingTimeInterval(expiryInterval)
                   
                    notExpired = expiryDate?.compare(Date()) == .orderedDescending
                }
                else {
                    // No expiry.
                    notExpired = true
                }
                if notExpired {
                    valid = true
                    //Salman Comment self.log("Cache hit!")
                }
                else {
                    //Salman Comment self.log("Cache miss - item expired.")
                }
            }
            else {
                //Salman Comment self.log("Cache miss - does not exist.")
            }
            
            var data: Data? = nil
            
            if valid {
                data = NSData(contentsOfFile: filePath) as Data?
                //Salman Comment self.log("Read %lu bytes!", UInt(data?.count))
            }
            
            if completion != nil {
                DispatchQueue.main.async(execute: {() -> Void in
                    completion(data)
                })
            }
        })
    }
    
    /**
     *  Removes the data item stored with the given key.
     *
     *  @param key The key with which the item stored is to be removed.
     */
    @objc public func removeDataItem(withKey key: String) {
        
        if !isValid {
            return
        }
        
        let keyHash: String = key.base64
        let filePath: String = URL(fileURLWithPath: storagePath).appendingPathComponent(keyHash).absoluteString
        let expiryIntervalFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileExpiryIntervalExtension).absoluteString
        let groupNameFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileGroupExtension).absoluteString
        
        diskQueue?.async(execute: {() -> Void in
            let fileSize = (try? self.fileManager?.attributesOfItem(atPath: filePath)[.size])
            try? self.fileManager?.removeItem(atPath: filePath)
            try? self.fileManager?.removeItem(atPath: expiryIntervalFilePath)
            try? self.fileManager?.removeItem(atPath: groupNameFilePath)
            
            self.cacheSizeInBytes -= UInt(fileSize as! Int)
            
            self.fileManager?.createFile(atPath: self.cacheMetaDataFilePath!, contents: "\(self.cacheSizeInBytes)".utf8DataValue(), attributes: nil)
        })
    }
    
    /**
     *  Removes all stored data items in the cache.
     */
    @objc public func removeAllExpiredItems() {
       
        if !isValid {
            return
        }
        
        diskQueue?.async(execute: {() -> Void in
            var atLeastOneItemWasRemoved = false
            let filenames = try? self.fileManager?.contentsOfDirectory(atPath: self.storagePath)
        
            for filename: String in filenames!! {
            
                if URL(fileURLWithPath: filename).pathExtension.count == 0 {
                    let filePath: String = URL(fileURLWithPath: self.storagePath).appendingPathComponent(filename).absoluteString
                    let expiryIntervalFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileExpiryIntervalExtension).absoluteString
                    let groupNameFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileGroupExtension).absoluteString
                    
                    let expiryInterval = TimeInterval((Double((try? String(contentsOfFile: expiryIntervalFilePath, encoding: .utf8)) ?? "") ?? 0.0))
                    let fileCreationDate = (try? self.fileManager?.attributesOfItem(atPath: filePath)[.creationDate]) as? Date
                    let expiryDate = fileCreationDate?.addingTimeInterval(expiryInterval)
                    let notExpired: Bool = expiryDate!.compare(Date()) == .orderedDescending
                
                    if !notExpired {
                        let fileSize = try? self.fileManager?.attributesOfItem(atPath: filePath)[.size]
                       
                        try? self.fileManager?.removeItem(atPath: filePath)
                        try? self.fileManager?.removeItem(atPath: expiryIntervalFilePath)
                        try? self.fileManager?.removeItem(atPath: groupNameFilePath)
                        
                        self.cacheSizeInBytes -= UInt(fileSize as! Int)
                        atLeastOneItemWasRemoved = true
                    }
                }
            }
           
            if atLeastOneItemWasRemoved {
                self.fileManager?.createFile(atPath: self.cacheMetaDataFilePath!, contents: "\(self.cacheSizeInBytes)".utf8DataValue(), attributes: nil)
            }
        })
    }
    
    func removeAllItems(withGroup group: String) {
       
        if !isValid {
            return
        }
        
        diskQueue?.async(execute: {() -> Void in
        
            if group.count != 0 {
                
                // By Group
                var atLeastOneItemWasRemoved = false
                let filenames = try? self.fileManager?.contentsOfDirectory(atPath: self.storagePath)
            
                for filename: String in filenames!! {
                
                    if URL(fileURLWithPath: filename).pathExtension.count == 0 {
                       
                        let filePath: String = URL(fileURLWithPath: self.storagePath).appendingPathComponent(filename).absoluteString
                        let expiryIntervalFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileExpiryIntervalExtension).absoluteString
                        let groupNameFilePath: String = URL(fileURLWithPath: filePath).appendingPathExtension(dataFileGroupExtension).absoluteString
                        
                        let groupOnDisk = try? String(contentsOfFile: groupNameFilePath, encoding: .utf8)
                    
                        if (groupOnDisk == group) {
                            let fileSize = (try? self.fileManager?.attributesOfItem(atPath: filePath)[.size])
                           
                            try? self.fileManager?.removeItem(atPath: filePath)
                            try? self.fileManager?.removeItem(atPath: expiryIntervalFilePath)
                            try? self.fileManager?.removeItem(atPath: groupNameFilePath)
                            
                            self.cacheSizeInBytes -= UInt(fileSize as! Int)
                            atLeastOneItemWasRemoved = true
                        }
                    }
                }
                
                if atLeastOneItemWasRemoved {
                    self.fileManager?.createFile(atPath: self.cacheMetaDataFilePath!, contents: "\(self.cacheSizeInBytes)".utf8DataValue(), attributes: nil)
                }
            }
            else {
                try? self.fileManager?.removeItem(atPath: self.storagePath)
                try? self.fileManager?.createDirectory(atPath: self.storagePath, withIntermediateDirectories: true, attributes: nil)
                
                self.cacheSizeInBytes -= 0
                
                self.fileManager?.createFile(atPath: self.cacheMetaDataFilePath!, contents: "\(self.cacheSizeInBytes)".utf8DataValue(), attributes: nil)
            }
        })
    }
    
    // MARK: -
    // MARK: Internal
    
    func prune() {
        diskQueue?.async(execute: {() -> Void in
            
            let diskCacheURL = URL(fileURLWithPath: self.storagePath, isDirectory: true)
            let resourceKeys = [URLResourceKey.isDirectoryKey, URLResourceKey.contentModificationDateKey, URLResourceKey.totalFileAllocatedSizeKey]
            
            // This enumerator prefetches useful properties for our cache files.
            let fileEnumerator: FileManager.DirectoryEnumerator? = self.fileManager?.enumerator(at: diskCacheURL, includingPropertiesForKeys: resourceKeys, options: .skipsHiddenFiles, errorHandler: nil)
            
            var remainingDataFiles = [AnyHashable: Any]()
            var urlsToDelete = [AnyHashable]()
            
            for fileURL in fileEnumerator! {
            
                if (fileURL as! URL).pathExtension.count != nil {
                    continue
                }
                
                let resourceValues = try? (fileURL as! NSURL).resourceValues(forKeys: resourceKeys)
                let expiryIntervalFileURL = (fileURL as! URL).appendingPathExtension(dataFileExpiryIntervalExtension)
                
                let expiryInterval = TimeInterval((Double((try? String(contentsOf: expiryIntervalFileURL, encoding: .utf8)) ?? "") ?? 0.0))
                let fileModificationDate = resourceValues![.contentModificationDateKey] as? Date
                let expiryDate = fileModificationDate?.addingTimeInterval(expiryInterval)
                
                if !(NSDate().laterDate(expiryDate!).compare(expiryDate!) == .orderedSame) {
                    
                    // Not Expired.
                    if let aValues = resourceValues {
                        remainingDataFiles[fileURL as! AnyHashable] = aValues
                    }
                }
                else {
                    // Expired.
                    urlsToDelete.append(fileURL as! AnyHashable)
                   
                    self.cacheSizeInBytes -= UInt(resourceValues![.totalFileAllocatedSizeKey] as! Int)
                }
            }
            for fileURL in urlsToDelete {
                let expiryIntervalFileURL = (fileURL as! URL).appendingPathExtension(dataFileExpiryIntervalExtension) as? URL
                let groupNameFileURL = (fileURL as! URL).appendingPathExtension(dataFileGroupExtension) as? URL
               
                try? self.fileManager?.removeItem(at: (fileURL as! URL))
                
                if let aURL = expiryIntervalFileURL {
                    try? self.fileManager?.removeItem(at: aURL)
                }
                
                if let aURL = groupNameFileURL {
                    try? self.fileManager?.removeItem(at: aURL)
                }
            }
           
            if self.cacheSizeInBytes > self.maximumCacheSizeInBytes {
            
                // Target half of our maximum cache size for this cleanup pass.
                let desiredCacheSize: UInt = self.maximumCacheSizeInBytes / 2
                
                // Sort the remaining cache files by their last modification time (oldest first).
                let sortedFiles = (remainingDataFiles as! NSMutableDictionary).keysSortedByValue(options: .concurrent, usingComparator: {(obj1, obj2) -> ComparisonResult in
                
                    let dict1 = (obj1 as! NSDictionary)
                    let dict2 = (obj2 as! NSDictionary)
                    let date1 = dict1.value(forKey: URLResourceKey.contentModificationDateKey.rawValue) as! Date
                    let date2 = dict2.value(forKey: URLResourceKey.contentModificationDateKey.rawValue) as! Date
                    
                    return date1.compare(date2)
                })
               
                // Delete files until we fall below our desired cache size.
                for fileURL in sortedFiles {
                    let expiryIntervalFileURL = (fileURL as? URL)?.appendingPathExtension(dataFileExpiryIntervalExtension)
                    let groupNameFileURL = (fileURL as? URL)?.appendingPathExtension(dataFileGroupExtension)
                
                    try? self.fileManager?.removeItem(at: (fileURL as! URL))
                    
                    if let aURL = expiryIntervalFileURL {
                        try? self.fileManager?.removeItem(at: aURL)
                    }
                    
                    if let aURL = groupNameFileURL {
                        try? self.fileManager?.removeItem(at: aURL)
                    }
                    
                    let totalAllocatedSize = (remainingDataFiles[fileURL as! AnyHashable] as! NSDictionary).value(forKey: URLResourceKey.totalFileAllocatedSizeKey.rawValue)
                    
                    self.cacheSizeInBytes -= UInt(totalAllocatedSize as! Int)
                    
                    if self.cacheSizeInBytes < desiredCacheSize {
                        break
                    }
                }
            }
            //Salman Comment self.log("Pruned cache, now at %lu bytes.", UInt(self.cacheSizeInBytes))
        })
    }
}
*/
