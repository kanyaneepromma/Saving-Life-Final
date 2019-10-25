//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import Foundation

/**
 * The singleton center for the retrieval of images.
 * Automatically caches images into memory. Set `memoryCache.totalCostLimit` to zero if you would not like to cache.
 * If a cached image is used then any delegate methods will not be triggered only the completion will be called.
 */
@objcMembers public class RBImageCenter: NSObject {

    private var imageProcessingQueue = DispatchQueue(label: "RBImageCenter")
    
    /**
     * The shared singleton.
     */
    public static let shared: RBImageCenter = RBImageCenter()
    
    /**
     * The network client to use when downloading images over the network.
     */
    public var networkClient: RBNetworkClient = RBNetworkClient()
    
    /**
     *  The underlying `NSCache` that is used to cache images processed by `RBImageCenter`. By default the cache size is 100 MB.
     */
    public var memoryCache: NSCache<NSString, UIImage> = NSCache<NSString, UIImage>()
    
    /**
     * Gets an image from the bundle.
     *
     * @param name   The name of the image in the bundle.
     *
     * @return       The retrieved image.
     */
    public class func bundleImage(withName name: String) -> UIImage? {
        // These are already caches
        return UIImage(named: name)
    }
    
    /**
     * Gets a resizable image from the bundle.
     *
     * @param name   The name of the image in the bundle.
     * @param insets The fixed edge insets to use for the resizeable image.
     *
     * @return       The retrieved image.
     */
    public class func resizableImage(withName name: String, with insets: UIEdgeInsets) -> UIImage? {
        if name.count == 0 {
            return nil
        }
        
        let orig: UIImage? = self.bundleImage(withName: name)
        if orig != nil {
            return orig?.resizableImage(withCapInsets: insets)
        }
        
        return nil
    }
    
    /**
     * Gets an image from the given filesystem path.
     *
     * @param path   The path of the image in the filesystem.
     *
     * @return       The retrieved image.
     */
    public class func image(withPath path: String) -> UIImage? {
        return UIImage(contentsOfFile: path)
    }
    
    override init() {
        super.init()
        
        memoryCache.totalCostLimit = 1024 * 1024 * 100 // 100MB
    }
    
    /**
     * Gets a glyph image from the bundle, optionally with a specified color or size.
     *
     * @param name       The name of the glyph image in the bundle.
     * @param tintColor The optional color with which to tint the glyph.
     * @param size       The optional size (specified in height points) with which to scale the glyph.
     *
     * @return           The requested glyph image.
     */
    public func glyphImage(name: String, tintColor: UIColor?, size: Float?) -> UIImage? {
        return internalGlyphImage(name: name, tintColor: tintColor, size: size)
    }
    
    /**
     * Gets a glyph image from the bundle, optionally with a specified color or size.
     *
     * @param name       The name of the glyph image in the bundle.
     * @param tintColor  The optional color with which to tint the glyph.
     * @param size       The optional size (specified in height points) with which to scale the glyph. Pass zero to ignore.
     *
     * @return           The requested glyph image.
     */
    public func glyphImage(name: String, tintColor: UIColor?, size: Float) -> UIImage? {
        return internalGlyphImage(name: name, tintColor: tintColor, size: size <= 0 ? nil : size)
    }
    
    private func internalGlyphImage(name: String, tintColor: UIColor?, size: Float?) -> UIImage? {
        
        let glyphImageName = "glyph-\(name)"
        
        if tintColor == nil && size == nil {
            
            // Try Redbeard Framework
            var image = UIImage(named: glyphImageName, in: Bundle(for: RBImageCenter.self), compatibleWith: nil)
            
            if image == nil { // try in main bundle
                image = UIImage(named: glyphImageName, in: Bundle.main, compatibleWith: nil)
            }
            
            return image
            
        } else {
            
            let cacheKey = "\(glyphImageName)-\(tintColor?.hexString() ?? "")-\(size ?? 0)"
            
            if let image = self.image(cacheKey) {
                return image
            }
            
            // Try Redbeard Framework
            var image = UIImage(named: glyphImageName, in: Bundle(for: RBImageCenter.self), compatibleWith: nil)
            
            if image == nil { // try in main bundle
                image = UIImage(named: glyphImageName, in: Bundle.main, compatibleWith: nil)
            }
            
            //
            
            if let imageValue = image {
                
                if let sizeValue = size {
                    let aspect = imageValue.size.width / imageValue.size.height
                    let height = CGFloat(sizeValue)
                    image = image?.scaledImage(with: CGSize(width: height * aspect, height: height))
                }
                
                if let tintValue = tintColor {
                    image = image?.fillingMask(with: tintValue)
                }
                
                // Store into memory cache
                self.add(image: image!, key: cacheKey)
            }
            
            return image
        }
    }
    
    /**
     * Retrieves a decoded image asynchronously over HTTP using the request given. Start's immediately.
     *
     * @param queue         The dispatch queue, pass nil to use main dispatch queue.
     * @param request       The network request to use for retrieval.
     * @param caching       Whether or not to cache the image or use a cached copy if possible.
     * @param progress      The completion block to be called on completion or failure. Must not be `nil`.
     * @param completion    The completion block to be called on completion or failure. Must not be `nil`.
     *
     * @return              The image network operation
     */
    @discardableResult
    public func image(queue: DispatchQueue? = nil,
                      request: URLRequest,
                      caching: Bool = true,
                      progress: ImageNetworkOperationOnProgressBlock?,
                      completion: ImageNetworkOperationOnCompletionBlock?) -> RBImageNetworkOperation? {
                
        let operation = self.networkClient.create(request: request, typeOf: RBImageNetworkOperation.self, onProgress: { (op, bytesSent, totalBytesSent, totalBytesExpectedToSend) in
            if let imageNetworkOperation = op as? RBImageNetworkOperation {
                
                (queue ?? DispatchQueue.main).async {
                    imageNetworkOperation.onImageProgressBlock?(bytesSent, totalBytesSent, totalBytesExpectedToSend)
                }
            }
        }, onCompletion: { (op, error) in
            
            guard let imageNetworkOperation = op as? RBImageNetworkOperation else {
                return
            }
            
            if error != nil {
                
                (queue ?? DispatchQueue.main).async {
                    imageNetworkOperation.onImageCompletionBlock?(nil, error)
                }
                
                return
            }
            
            if imageNetworkOperation.httpStatusCode < 200 || imageNetworkOperation.httpStatusCode > 299 {
                
                (queue ?? DispatchQueue.main).async {
                    let e = RBError.validation(reason: "HTTP status code: \(imageNetworkOperation.httpStatusCode) outside range \(200) - \(299)")
                    imageNetworkOperation.onImageCompletionBlock?(nil, e)
                }
                
                return
            }
            
            guard let data = imageNetworkOperation.data, data.count > 0 else {
                
                (queue ?? DispatchQueue.main).async {
                    let e = RBError.validation(reason: "Empty data")
                    imageNetworkOperation.onImageCompletionBlock?(nil, e)
                }
                
                return
            }
                
            guard let image = UIImage(data: data) else {
                
                (queue ?? DispatchQueue.main).async {
                    let e = RBError.validation(reason: "Unable to decode image")
                    imageNetworkOperation.onImageCompletionBlock?(nil, e)
                }
                
                return
            }
            
            // Store into memory cache
            
            if caching {
                self.add(image: image, key: imageNetworkOperation.uniqueHash)
            }
            
            (queue ?? DispatchQueue.main).async {
                imageNetworkOperation.onImageCompletionBlock?(image, nil)
            }
        })
        
        //
        
        if let imageNetworkOperation = operation as? RBImageNetworkOperation {
            imageNetworkOperation.onImageProgressBlock = progress
            imageNetworkOperation.onImageCompletionBlock = completion
            
            resume(operation: imageNetworkOperation, caching: caching)
            return imageNetworkOperation
        }
        
        return nil
    }
    
    /**
     * Retrieves a decoded image asynchronously from disk using path given. Start's immediately.
     *
     * @param queue          The dispatch queue, pass nil to use main dispatch queue.
     * @param path           The path to use for retrieval.
     * @param caching        Whether or not to cache the image or use a cached copy if possible.
     * @param completion   The completion block to be called on completion or failure. Must not be `nil`.
     *
     * @return               The image network operation
     */
    @discardableResult
    public func imageFromDisk(queue: DispatchQueue? = nil,
                              path: String,
                              caching: Bool = true,
                              completion: ImageDiskOperationOnCompletionBlock?) -> RBCancellableTask? {
        
        if caching {
            
            if let image = self.image(path) {
                (queue ?? DispatchQueue.main).async {
                    completion?(image, nil)
                }
                
                return nil
            }
        }
        
        return RBFilesystem.readDataOnce(queue: queue, path: path, filterBlock: nil) { (data, error, wasCancelled) in

            if wasCancelled {
                
                (queue ?? DispatchQueue.main).async {
                    completion?(nil, RBError.cancellation(reason: "Cancelled"))
                }
                
                return
            }
            
            if let e = error {
                
                (queue ?? DispatchQueue.main).async {
                    completion?(nil, RBError.error(reason: e))
                }
                
                return
            }
            
            guard let d = data else {
                
                (queue ?? DispatchQueue.main).async {
                    completion?(nil, RBError.validation(reason: "Data empty"))
                }
                
                return
            }
            
            DispatchQueue.global(qos: .default).async {
                
                guard var image = UIImage(data: d) else {
                    
                    (queue ?? DispatchQueue.main).async {
                        completion?(nil, RBError.validation(reason: "Unable to decode image from data of size \(data?.count ?? 0)"))
                    }
                    
                    return
                }
                
                image = UIImage.decodedImage(with: image) // Decode ahead of time
                
                if caching {
                    self.add(image: image, key: path)
                }
                
                (queue ?? DispatchQueue.main).async {
                    completion?(image, nil)
                }
            }
        }
    }
    
    /**
     * Removes any cached copy of an image at the given path.
     *
     * @param path   The path of the image in the filesystem.
     */
    public func removeFromCache(path: String) {
        remove(key: path)
    }
    
    /**
     * Removes any cached copy of an image at the given URLRequest.
     *
     * @param request   The URLRequest that details the location of the image.
     */
    public func removeFromCache(request: URLRequest) {
        
        guard let operation = self.networkClient.create(request: request) else {
            return
        }
        
        remove(key: operation.uniqueHash)
    }
    
    // MARK: - Actions
    
    private func image(_ key: String?) -> UIImage? {
        guard let hash = key else { return nil }
        return memoryCache.object(forKey: hash as NSString)
    }
    
    private func add(image: UIImage, key: String?) {
        guard let hash = key else { return }
        let bytes = image.cgImage!.bytesPerRow * image.cgImage!.height
        self.memoryCache.setObject(image, forKey: hash as NSString, cost: bytes)
    }
    
    private func remove(key: String?) {
        guard let hash = key else { return }
        self.memoryCache.removeObject(forKey: hash as NSString)
    }
    
    private func resume(operation: RBImageNetworkOperation, caching: Bool) {
        
        if caching == false {
            operation.resume()
            return
        }
        
        //
        
        if !operation.isCachedResponse {
            if let image = self.image(operation.uniqueHash) {
                operation.isCachedResponse = true
                operation.onImageCompletionBlock?(image, nil)
            } else {
                operation.resume()
            }
        }
    }
}
