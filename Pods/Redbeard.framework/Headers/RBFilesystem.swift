//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  Filesystem convenience methods.
 */
@objcMembers public class RBFilesystem: NSObject {
    
    /**
     *  Gets the local filesystem path to the given system directory.
     *
     *  @param pathDirectory The system directory.
     *
     *  @return The retrieved path.
     */
    public class func path(pathDirectory: FileManager.SearchPathDirectory) -> String? {
        let results = NSSearchPathForDirectoriesInDomains(pathDirectory, .userDomainMask, true)
        
        guard let path = results.first else {
            return nil
        }
        
        return path
    }
    
    /**
     *  The path to the documents directory.
     */
    public class func pathToDocumentsDirectory() -> String {
        return RBFilesystem.path(pathDirectory: .documentDirectory) ?? ""
    }
    
    /**
     *  The path to the temporary directory.
     */
    public class func pathToTemporaryDirectory() -> String {
        return NSTemporaryDirectory()
    }
    
    /**
     *  The path to the bundle directory.
     */
    public class func pathToBundleDirectory() -> String {
        
        guard let path = Bundle.main.resourcePath else {
            return ""
        }
        
        return path
    }
    
    /**
     *  The path to the cache directory.
     */
    public class func pathToCacheDirectory() -> String {
        return RBFilesystem.path(pathDirectory: FileManager.SearchPathDirectory.cachesDirectory) ?? ""
    }
    
    /**
     *  Retrieves a list of the files at the path given that match the given extension. Excludes directories.
     *
     *  @param path             The path to retrieve the list of files from.
     *  @param includeFullPaths Whether each item should include the full path, or just the name.
     *  @param extension        Optional extension to match. (Assumes no `.` (dot))
     *
     *  @return The `Array` file list.
     */
    public class func files(path: String, includeFullPaths: Bool, extension: String?) -> [String] {
        
        guard let items = try? FileManager.default.contentsOfDirectory(atPath: denormalizeFilePath(path)) else {
            return [String]()
        }
        
        var rv = [String]()
        
        for f in items {
            
            var isDir: ObjCBool = false
            let fpath = URL(fileURLWithPath: path).appendingPathComponent(f).path
            
            let exists = FileManager.default.fileExists(atPath: fpath, isDirectory: &isDir)
            
            if exists && isDir.boolValue == false {
                
                if let ext = `extension`, fpath.lowercased().hasSuffix("." + ext) == false {
                    continue
                }
                
                if includeFullPaths {
                    rv.append(fpath)
                }
                else {
                    rv.append(f)
                }
            }
        }
        
        return rv
    }
    
    /**
     *  Retrieves a list of the directories at the path given.
     *
     *  @param path             The path to retrieve the list of directories from.
     *  @param includeFullPaths Whether each item should include the full path, or just the name.
     *
     *  @return The `Array` directory list.
     */
    public class func directories(path: String, includeFullPaths: Bool) -> [String]? {
        
        guard let items = try? FileManager.default.contentsOfDirectory(atPath: denormalizeFilePath(path)) else {
            return [String]()
        }
        
        var rv = [String]()

        for f in items {
            
            var isDir: ObjCBool = false
            let fpath = URL(fileURLWithPath: path).appendingPathComponent(f).path
            
            let exists = FileManager.default.fileExists(atPath: fpath, isDirectory: &isDir)
            
            if exists && isDir.boolValue {
                if includeFullPaths {
                    rv.append(fpath)
                }
                else {
                    rv.append(f)
                }
            }
        }
        
        return rv
    }
    
    
    /**
     *  Determines whether or not a file exists at the given path.
     *
     *  @param path The path to the file.
     *
     *  @return Whether or not the file exists.
     */
    public class func fileExists(path: String) -> Bool {
        return FileManager.default.fileExists(atPath: denormalizeFilePath(path))
    }
    
    /**
     *  Determines whether or not a directory exists at the given path.
     *
     *  @param path The path to the directory.
     *
     *  @return Whether or not the directory exists.
     */
    public class func directoryExists(path: String) -> Bool {
        
        var isDir: ObjCBool = false
        
        if !FileManager.default.fileExists(atPath: denormalizeFilePath(path), isDirectory: &isDir) {
            return false
        }
        
        return isDir.boolValue
    }
    
    /**
     *  Creates a directory at the given path.
     *
     *  @param path The path to create a directory at.
     *
     *  @return Whether or not the operation was successful.
     */
    public class func createDirectory(path: String) -> Bool {
        
        do {
            try FileManager.default.createDirectory(atPath: denormalizeFilePath(path), withIntermediateDirectories: true, attributes: nil)
            return true
        } catch {
            return false
        }
    }
    
    /**
     *  Gets the modified date of the item at the given path.
     *
     *  @param path The path to the item.
     *
     *  @return The `Date` result.
     */
    public class func modifiedDate(path: String) -> Date? {
        
        guard let attributes = try? FileManager.default.attributesOfItem(atPath: denormalizeFilePath(path)) else {
            return nil
        }
        
        if let date = attributes[.modificationDate] as? Date {
            return date
        }
        
        return nil
    }
    
    /**
     *  Removes the file at the given path.
     *
     *  @param path The path to the file to remove.
     *
     *  @return Whether or not the operation was successful.
     */
    public class func removeFile(path: String) -> Bool {
        
        do {
            try FileManager.default.removeItem(atPath: denormalizeFilePath(path))
            return true
        } catch {
            return false
        }
    }
    
    // MARK: -
    // MARK: Disk I/O
    
    /**
     *  Reads data from the disk asynchronously.
     *
     *  @param queue       The dispatch queue, pass nil to use main dispatch queue.
     *  @param path        The path to the item to read.
     *  @param filterBlock An optional block to filter the data.
     *  @param completion  The completion block providing the result on completion.
     *
     *  @return A task handle that can be used to cancel the operation.
     */
    public class func readDataOnce(queue: DispatchQueue? = nil, path: String, filterBlock: ((_ data: Data) -> Data)? = nil, completion: ((_ data: Data?, _ error: Error?, _ wasCancelled: Bool) -> Void)? = nil) -> RBCancellableTask {
        
        // TODO: Convert this to an RBOperation.
        let resolvedPath = denormalizeFilePath(path)
        
        let workQueue = DispatchQueue.global(qos: .default)
        let io = DispatchIO(type: DispatchIO.StreamType.random, path: UnsafePointer<Int8>(resolvedPath), oflag: O_RDONLY, mode: 0, queue: workQueue, cleanupHandler: { (error) in
        })
        
        var wasCancelled = false
        
        let cancellableTask = RBCancellableBlockTask {
            wasCancelled = true
            io?.close()
            
            (queue ?? DispatchQueue.main).async {
                completion?(nil, nil, true)
            }
        }
        
        if io == nil {
            return cancellableTask
        }
        
        //
            
        var readData = Data()
        
        io?.setLimit(lowWater: Int.max)
        io?.read(offset: 0, length: Int.max, queue: workQueue, ioHandler: { (done, data, error) in
            
            if error != 0 {
                
                io?.close()
                
                let desc = "Read from disk failed with error code: \(error)"
                let err = NSError(domain: "Redbeard", code: -1, userInfo: [NSLocalizedDescriptionKey: desc])
                
                completion?(nil, RBError.error(reason: err), error == ECANCELED)
                return
            }
            
            // Read Data
            data?.enumerateBytes(block: { (buffer, size, bool) in
                readData.append(buffer)
            })
            
            if done {
                
                if wasCancelled {
                    io?.close()
                    
                    (queue ?? DispatchQueue.main).async {
                        completion?(nil, nil, true)
                    }
                    
                    return
                }
                
                // Apply Filter
                if (filterBlock != nil) && readData.count > 0 {
                    readData = filterBlock!(readData)
                }
                
                io?.close()
                
                (queue ?? DispatchQueue.main).async {
                    
                    if wasCancelled {
                        completion?(nil, nil, true)
                    } else {
                        completion?(readData, nil, false)
                    }
                }
            }
        })
        
        return cancellableTask
    }
    
    class func denormalizeFilePath(_ path: String) -> String {
        return URL(fileURLWithPath: path).path
    }
}

