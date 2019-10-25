//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

@objc public protocol RBNetworkClientDelegate: NSObjectProtocol {
    
    @objc optional func networkClient(_ networkClient: RBNetworkClient, operation: RBNetworkOperation, didReceive response: URLResponse, completionHandler: ((URLSession.ResponseDisposition) -> Swift.Void)? ) -> Bool
    
    @objc optional func networkClient(_ networkClient: RBNetworkClient, operation: RBNetworkOperation, willPerformHTTPRedirection response: HTTPURLResponse, newRequest request: URLRequest, completionHandler: ((URLRequest?) -> Swift.Void)? ) -> Bool
    
    @objc optional func networkClient(_ networkClient: RBNetworkClient, operation: RBNetworkOperation, didReceiveChallenge challenge: URLAuthenticationChallenge, completionHandler:((URLSession.AuthChallengeDisposition, URLCredential?) -> Swift.Void)? ) -> Bool
    
    @objc optional func networkClient(_ networkClient: RBNetworkClient, isWaitingForConnectivity operation: RBNetworkOperation)
        
    @objc optional func networkClient(_ networkClient: RBNetworkClient, operation: RBNetworkOperation, bytesSent: Int64, totalBytesSent: Int64, totalBytesExpectedToSend: Int64)
    
    @objc optional func networkClient(_ networkClient: RBNetworkClient, operation: RBNetworkOperation, didCompleteWithError error: Error?)
}

@objcMembers public class RBNetworkClient: NSObject, URLSessionDelegate, URLSessionDataDelegate, URLSessionTaskDelegate {
    
    var taskHashes = [String: Int]()
    var tasks = [Int: RBNetworkOperation]()
    let lockQueue = DispatchQueue(label: "RBNetworkClient")
    
    //
    
    public var printRequestURL: Bool = false
    public var printRequestBody: Bool = false
    public var printRequestHeaders: Bool = false
    
    public var printResponseURL: Bool = false
    public var printResponseBody: Bool = false
    public var printResponseHeaders: Bool = false
    
    /**
     *  A delegate to receive rest client events.
     */
    public weak var delegate: RBNetworkClientDelegate?
    
    public private(set) var session: URLSession?
    public private(set) var configuration: URLSessionConfiguration
    
    public var applyAdditionalHeaders: [String : String]? // TODO: add comments from httpAdditionalHeaders to this
    
    public convenience override init() {
        self.init(configuration: URLSessionConfiguration.default)
    }
    
    public init(configuration: URLSessionConfiguration) {
        self.configuration = configuration
        super.init()
        self.session = URLSession(configuration: configuration, delegate: self, delegateQueue: nil)
    }
    
    deinit {
        self.session?.invalidateAndCancel()
    }
    
    private func operation(task: URLSessionTask) -> RBNetworkOperation? {
        return tasks[task.taskIdentifier]
    }
    
    private func addTask(task: URLSessionTask, operation: RBNetworkOperation) {
        lockQueue.sync {
            tasks[task.taskIdentifier] = operation
            
            if let hash = operation.uniqueHash {
                taskHashes[hash] = task.taskIdentifier
            }
        }
    }
    
    private func removeTask(task: URLSessionTask) {
        lockQueue.sync {
            if let operation = tasks[task.taskIdentifier] {
                tasks.removeValue(forKey: task.taskIdentifier)
                
                if let hash = operation.uniqueHash {
                    taskHashes.removeValue(forKey: hash)
                }
                
            }
        }
    }
    
    public func cancelAllRequests() {
        lockQueue.sync {
            for (_, operation) in tasks {
                operation.cancel()
            }
        }
    }
    
    // MARK: -
    // MARK: - Create
    
    public func create(request: URLRequest) -> RBNetworkOperation? {
        return self.create(request: request, onProgress: nil, onCompletion: nil)
    }
    
    public func create(urlString: String,
        onProgress: NetworkOperationOnProgressBlock?,
        onCompletion: NetworkOperationOnCompletionBlock?) -> RBNetworkOperation? {
        guard let value = URL(string: urlString) else { return nil }
        return self.create(request: URLRequest(url: value), onProgress: onProgress, onCompletion: onCompletion)
    }
    
    public func create(url: URL,
                             onProgress: NetworkOperationOnProgressBlock?,
                             onCompletion: NetworkOperationOnCompletionBlock?) -> RBNetworkOperation? {
        return self.create(request: URLRequest(url: url), onProgress: onProgress, onCompletion: onCompletion)
    }
    
    // MARK: -
    // MARK: - Create HTTP
    
    public func create(urlString: String,
                             onProgress: NetworkOperationOnProgressBlock?,
                             onError: NetworkOperationOnErrorBlock?,
                             onSuccess: NetworkOperationOnSuccessBlock?) -> RBNetworkOperation? {
        guard let value = URL(string: urlString) else { return nil }
        return self.create(request: URLRequest(url: value), onProgress: onProgress, onError: onError, onSuccess: onSuccess)
    }
        
    public func create(url: URL,
                             onProgress: NetworkOperationOnProgressBlock?,
                             onError: NetworkOperationOnErrorBlock?,
                             onSuccess: NetworkOperationOnSuccessBlock?) -> RBNetworkOperation? {
        let request = URLRequest(url: url)
        return self.createNetworkOperation(request: request, typeOf: RBNetworkOperation.self, onProgress: onProgress, onError: onError, onSuccess: onSuccess, onCompletion: nil)
    }
    
    // MARK: -
    // MARK: - Core Create HTTP Network Operation
    
    public func create(request: URLRequest,
                             onProgress: NetworkOperationOnProgressBlock?,
                             onError: NetworkOperationOnErrorBlock?,
                             onSuccess: NetworkOperationOnSuccessBlock?) -> RBNetworkOperation? {
        
        return self.createNetworkOperation(request: request, typeOf: RBNetworkOperation.self, onProgress: onProgress, onError: onError, onSuccess: onSuccess, onCompletion: nil)
    }
    
    public func create(request: URLRequest,
                             typeOf: RBNetworkOperation.Type,
                             onProgress: NetworkOperationOnProgressBlock?,
                             onError: NetworkOperationOnErrorBlock?,
                             onSuccess: NetworkOperationOnSuccessBlock?) -> RBNetworkOperation? {
        
        return self.createNetworkOperation(request: request, typeOf: typeOf, onProgress: onProgress, onError: onError, onSuccess: onSuccess, onCompletion: nil)
    }
    
    // MARK: -
    // MARK: - Core Create Network Operation
    
    public func create(request: URLRequest,
                             onProgress: NetworkOperationOnProgressBlock?,
                             onCompletion: NetworkOperationOnCompletionBlock?) -> RBNetworkOperation? {
        
        return self.createNetworkOperation(request: request, typeOf: RBNetworkOperation.self, onProgress: onProgress, onError: nil, onSuccess: nil, onCompletion: onCompletion)
    }
    
    public func create(request: URLRequest,
                             typeOf: RBNetworkOperation.Type,
                             onProgress: NetworkOperationOnProgressBlock?,
                             onCompletion: NetworkOperationOnCompletionBlock?) -> RBNetworkOperation? {
        
        return self.createNetworkOperation(request: request, typeOf: typeOf, onProgress: onProgress, onError: nil, onSuccess: nil, onCompletion: onCompletion)
    }
    
    // MARK: -
    // MARK: - Base Create Network Operation
    
    private func createNetworkOperation(request: URLRequest,
                                        typeOf: RBNetworkOperation.Type,
                                        onProgress: NetworkOperationOnProgressBlock?,
                                        onError: NetworkOperationOnErrorBlock?,
                                        onSuccess: NetworkOperationOnSuccessBlock?,
                                        onCompletion: NetworkOperationOnCompletionBlock?) -> RBNetworkOperation? {
        
        var r = request // Copy
        
        if let headers = self.applyAdditionalHeaders {
            for (key, value) in headers {
                r.addValue(value, forHTTPHeaderField: key)
            }
        }
        
        if let task = self.session?.dataTask(with: r) {
            
            let operation = typeOf.init(task: task)
            operation.onProgressBlock = onProgress
            
            if onError != nil || onSuccess != nil {
                operation.onErrorBlock = onError
                operation.onSuccessBlock = onSuccess
            } else {
                operation.onCompletionBlock = onCompletion
            }
            
            self.addTask(task: task, operation: operation)
            return operation
        }
        
        return nil
    }
    
    // MARK: -
    // MARK: Actions
    
    public func resume(operation: RBNetworkOperation) {
        operation.resume()
    }
    
    public func suspend(operation: RBNetworkOperation) {
        operation.suspend()
    }
    
    public func cancel(operation: RBNetworkOperation) {
        operation.cancel()
    }
    
    
    // MARK: -
    // MARK: URLSessionDelegate
    
    // TODO: provide delegate methods for the below 3 methods
    
    public func urlSession(_ session: URLSession, didBecomeInvalidWithError error: Error?) {
        print("URLSessionDelegate - didBecomeInvalidWithError")
    }
    
    public func urlSession(_ session: URLSession, didReceive challenge: URLAuthenticationChallenge, completionHandler: @escaping (URLSession.AuthChallengeDisposition, URLCredential?) -> Swift.Void) {
        print("URLSessionDelegate - didReceive challenge")
        completionHandler(URLSession.AuthChallengeDisposition.performDefaultHandling, nil)
    }
    
    public func urlSessionDidFinishEvents(forBackgroundURLSession session: URLSession) {
        print("URLSessionDelegate - urlSessionDidFinishEvents")
    }
    
    // MARK: -
    // MARK: URLSessionDataDelegate
    
    public func urlSession(_ session: URLSession, dataTask: URLSessionDataTask, didReceive response: URLResponse, completionHandler: @escaping (URLSession.ResponseDisposition) -> Swift.Void) {
        
        guard let operation = self.operation(task: dataTask) else {
            completionHandler(.allow)
            return
        }
        
        var handled = false
        
        if let value = self.delegate?.networkClient?(self, operation: operation, didReceive: response, completionHandler: completionHandler) {
            if value {
                handled = true
            }
        }
        
        if let value = operation.delegate?.networkOperation?(operation, didReceive: response, completionHandler: handled ? nil : completionHandler) {
            if value {
                handled = true
            }
        }
        
        if !handled {
            completionHandler(.allow)
        }
    }
    
    /*
     * Deliberately commented out, these are 'optional' delegate methods. Not implementing these so that iOS provides default implementations
     *
    public func urlSession(_ session: URLSession, dataTask: URLSessionDataTask, didBecome downloadTask: URLSessionDownloadTask) {
        print("\(dataTask.taskIdentifier) - URLSessionDataDelegate - didBecome downloadTask")
    }
    
    public func urlSession(_ session: URLSession, dataTask: URLSessionDataTask, didBecome streamTask: URLSessionStreamTask) {
        print("\(dataTask.taskIdentifier) - URLSessionDataDelegate - didBecome streamTask")
    }
     
    */
    
    public func urlSession(_ session: URLSession, dataTask: URLSessionDataTask, didReceive data: Data) {
        
        guard let operation = operation(task: dataTask) else {
            return
        }
        
        operation.appendData(data: data) // Append data
    }
    
    public func urlSession(_ session: URLSession, dataTask: URLSessionDataTask, willCacheResponse proposedResponse: CachedURLResponse, completionHandler: @escaping (CachedURLResponse?) -> Swift.Void) {
        completionHandler(proposedResponse)
    }
    
    // MARK: -
    // MARK: - URLSessionTaskDelegate
    
    public func urlSession(_ session: URLSession, task: URLSessionTask, willBeginDelayedRequest request: URLRequest, completionHandler: @escaping (URLSession.DelayedRequestDisposition, URLRequest?) -> Swift.Void) {
        completionHandler(URLSession.DelayedRequestDisposition.continueLoading, request)
    }
    
    public func urlSession(_ session: URLSession, taskIsWaitingForConnectivity task: URLSessionTask) {
        
        guard let operation = operation(task: task) else {
            return
        }
        
        self.delegate?.networkClient?(self, isWaitingForConnectivity: operation)
        operation.delegate?.networkOperation?(isWaitingForConnectivity: operation)
    }
    
    public func urlSession(_ session: URLSession, task: URLSessionTask, willPerformHTTPRedirection response: HTTPURLResponse, newRequest request: URLRequest, completionHandler: @escaping (URLRequest?) -> Swift.Void) {
        
        guard let operation = self.operation(task: task) else {
            completionHandler(request)
            return
        }
        
        var handled = false
        
        
        if let value = self.delegate?.networkClient?(self,
                                                 operation: operation,
                                                 willPerformHTTPRedirection: response,
                                                 newRequest: request,
                                                 completionHandler: completionHandler) {
            if value {
                handled = true
            }
        }
        
        if let value = operation.delegate?.networkOperation?(operation,
                                                             willPerformHTTPRedirection: response,
                                                             newRequest: request,
                                                             completionHandler: handled ? nil : completionHandler) {
            if value {
                handled = true
            }
        }
        
        if !handled {
            completionHandler(request)
        }
    }
    
    public func urlSession(_ session: URLSession, task: URLSessionTask, didReceive challenge: URLAuthenticationChallenge, completionHandler: @escaping (URLSession.AuthChallengeDisposition, URLCredential?) -> Swift.Void) {
        
        guard let operation = self.operation(task: task) else {
            completionHandler(URLSession.AuthChallengeDisposition.performDefaultHandling, nil)
            return
        }
        
        var handled = false
        
        if let value = self.delegate?.networkClient?(self,
                                                  operation: operation,
                                                  didReceiveChallenge: challenge,
                                                  completionHandler: completionHandler) {
            if value {
                handled = true
            }
        }
        
        if let value = operation.delegate?.networkOperation?(operation,
                                                             didReceiveChallenge: challenge,
                                                             completionHandler: handled ? nil : completionHandler) {
            if value {
                handled = true
            }
        }
        
        if !handled {
            completionHandler(URLSession.AuthChallengeDisposition.performDefaultHandling, nil)
        }
    }
    
    /*
     * Deliberately commented out, these are 'optional' delegate methods. Not implementing these so that iOS provides default implementations
     *
    public func urlSession(_ session: URLSession, task: URLSessionTask, needNewBodyStream completionHandler: @escaping (InputStream?) -> Swift.Void) {
        print("\(task.taskIdentifier) - URLSessionTaskDelegate - needNewBodyStream")
    }
    
    */
    
    public func urlSession(_ session: URLSession, task: URLSessionTask, didSendBodyData bytesSent: Int64, totalBytesSent: Int64, totalBytesExpectedToSend: Int64) {
        
        guard let operation = operation(task: task) else {
            return
        }
        
        self.delegate?.networkClient?(self,
                                   operation: operation,
                                   bytesSent: bytesSent,
                                   totalBytesSent: totalBytesSent,
                                   totalBytesExpectedToSend: totalBytesExpectedToSend)
        
        operation.delegate?.networkOperation?(operation,
                                              bytesSent: bytesSent,
                                              totalBytesSent: totalBytesSent,
                                              totalBytesExpectedToSend: totalBytesExpectedToSend)
        
        // Doing blocks last, so that they are the 'last' to be aware of things. Delegates are priority 1
        operation.onProgressBlock?(operation, bytesSent, totalBytesSent, totalBytesExpectedToSend)
    }
    
    public func urlSession(_ session: URLSession, task: URLSessionTask, didFinishCollecting metrics: URLSessionTaskMetrics) {
        
        guard let operation = operation(task: task) else {
            return
        }
        
        operation.metrics = metrics
    }
    
    public func urlSession(_ session: URLSession, task: URLSessionTask, didCompleteWithError error: Error?) {
        
        guard let operation = operation(task: task) else {
            return
        }
        
        self.delegate?.networkClient?(self, operation: operation, didCompleteWithError: error)
        operation.delegate?.networkOperation?(operation, didCompleteWithError: error)
        
        self.removeTask(task: task)
                
        // Doing blocks last, so that they are the 'last' to be aware of things. Delegates are priority 1
        
        if let onCompletion = operation.onCompletionBlock {
            onCompletion(operation, error)
        } else { // HTTP
            
            if let e = error { // Look into transfer error first
                operation.onErrorBlock?(operation, operation.httpStatusCode, e)
            } else {
                
                if let response = operation.httpResponse { // Lets see if we have HTTPURLResponse
                    
                    // Now check status codes
                    if response.statusCode >= 200 && response.statusCode < 300 {
                        operation.onSuccessBlock?(operation, response.statusCode)
                    } else {
                        operation.onErrorBlock?(operation, response.statusCode, error)
                    }
                    
                } else {
                    operation.onErrorBlock?(operation, 0, error)
                }
            }
        }
    }
}
