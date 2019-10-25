//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import Foundation

/**
 *  A block that is called when a HTTP status code within the 2xx range is not found or when a network transfer has failed.
 *
 *  @param operation        The network operation.
 *  @param httpStatusCode   The HTTP status code if a HTTP error occured, otherwise -1 indicating a network transfer error.
 *  @param error            If a network transfer error occurred, an error object indicating the failure, otherwise `nil`.
 */
public typealias NetworkOperationOnErrorBlock = (_ operation: RBNetworkOperation, _ httpStatusCode: Int,  _ error: Error?) -> Void

/**
 *  A block that is called when a HTTP status code within the 2xx range is found.
 *
 *  @param operation        The network operation.
 *  @param httpStatusCode   The HTTP status code.
 */
public typealias NetworkOperationOnSuccessBlock = (_ operation: RBNetworkOperation, _ httpStatusCode: Int) -> Void

/**
 *  A block that is called when a network operation has completed.
 *
 *  @param operation    The completed network operation.
 *  @param error        If an error occurred, an error object indicating network transfer failure, otherwise `nil`.
 */
public typealias NetworkOperationOnCompletionBlock = (_ operation: RBNetworkOperation, _ error: Error?) -> Void

/**
 *  A block that is called periodically to update the current progress of a network response being received.
 *
 *  @param operation                The network operation.
 *  @param bytesSent                The number of bytes sent since the last time this delegate method was called.
 *  @param totalBytesSent           The total number of bytes sent so far.
 *  @param totalBytesExpectedToSend The expected length of the body data, (-1) if unknown.
 */
public typealias NetworkOperationOnProgressBlock = (_ operation: RBNetworkOperation, _ bytesSent: Int64, _ totalBytesSent: Int64, _ totalBytesExpectedToSend: Int64) -> Void

/**
 *  A delegate to be notified of events to the network operation.
 */
@objc public protocol RBNetworkOperationDelegate: NSObjectProtocol {
    
    @objc optional func networkOperation(_ operation: RBNetworkOperation, didReceive response: URLResponse, completionHandler: ((URLSession.ResponseDisposition) -> Swift.Void)?) -> Bool
    
    @objc optional func networkOperation(_ operation: RBNetworkOperation, willPerformHTTPRedirection response: HTTPURLResponse, newRequest request: URLRequest, completionHandler: ((URLRequest?) -> Swift.Void)?) -> Bool
    
    @objc optional func networkOperation(_ operation: RBNetworkOperation, didReceiveChallenge challenge: URLAuthenticationChallenge, completionHandler:((URLSession.AuthChallengeDisposition, URLCredential?) -> Swift.Void)?) -> Bool
    
    @objc optional func networkOperation(isWaitingForConnectivity operation: RBNetworkOperation)
    
    @objc optional func networkOperation(_ operation: RBNetworkOperation, bytesSent: Int64, totalBytesSent: Int64, totalBytesExpectedToSend: Int64)
    
    @objc optional func networkOperation(_ operation: RBNetworkOperation, didCompleteWithError error: Error?)
}

/**
 *  A network operation.
 */
@objcMembers public class RBNetworkOperation: NSObject {
    
    private var currentData: Data?
    private var task: URLSessionTask
    
    internal private(set) var uniqueHash: String?
    
    internal var onErrorBlock: NetworkOperationOnErrorBlock? = nil
    internal var onSuccessBlock: NetworkOperationOnSuccessBlock? = nil
    internal var onCompletionBlock: NetworkOperationOnCompletionBlock? = nil
    internal var onProgressBlock: NetworkOperationOnProgressBlock? = nil
    
    /**
     *  A delegate to receive events.
     */
    public weak var delegate: RBNetworkOperationDelegate?
    
    /**
     *  The original request.
     */
    public var originalRequest: URLRequest? {
        return task.originalRequest
    }
    
    /**
     *  The current request.
     */
    public var currentRequest: URLRequest? {
        return task.currentRequest
    }
    
    /**
     *  The current state of the underlying `URLSessionTask`.
     */
    public var state: URLSessionTask.State {
        return task.state
    }
    
    /**
     *  The underlying response object, `nil` until completion.
     */
    public var response: URLResponse? {
        return task.response
    }
    
    /**
     *  The underlying HTTP response object, `nil` until completion or if the request was not of type `HTTP`.
     */
    public var httpResponse: HTTPURLResponse? {
        return self.response as? HTTPURLResponse
    }
    
    /**
     *  The response data, `nil` until completion.
     */
    public var data: Data? {
        return self.currentData
    }
    
    /**
     *  The HTTP status code if available otherwise 0.
     */
    public var httpStatusCode: Int {
        if let response = self.response as? HTTPURLResponse {
            return response.statusCode
        }
        return 0
    }
        
    /**
     *  The metrics for this operation `nil` until completion.
     */
    public internal(set) var metrics: URLSessionTaskMetrics?
   
    /**
     *  Initializes a new network operation.
     *
     *  @param task The underlying task.
     *
     *  @return The initialized network operation.
     */
    public required init(task: URLSessionTask) {
        
        self.task = task
        
        if let request = task.originalRequest {
            self.uniqueHash = RBNetworkOperation.uniqueHash(request: request)
        }
    }
    
    public func resume() {
        task.resume()
    }
    
    public func suspend() {
        task.suspend()
    }
    
    public func cancel() {
        task.cancel()
    }
    
    internal func appendData(data: Data) {
        
        if self.currentData == nil {
            self.currentData = Data()
        }
        
        self.currentData?.append(data)
    }
    
    /**
     *  Deserializes the `data` property to a JSON object.
     *
     *  @return The JSON as dictionary or an array of dictionaries as appropriate or `nil` if `data` is empty or the response was invalid.
     */
    public func dataAsJson() -> Any? {
        
        guard let bytes = self.data else {
            return nil
        }
        
        if bytes.count == 0 {
            return nil
        }
        
        //
        
        return RBJson.deserialise(data: self.data!)
    }
    
    /**
     *  Deserializes the `data` property to a typed `RBJsonObject` object.
     *
     *  @return The JSON as a specific `RBJsonObject` instance or `nil` if `data` is empty or the response was invalid.
     */
    public func dataToJson<T: RBJsonObject>() -> [T]? {
        return dataToJson(jsonPath: nil)
    }
    
    /**
     *  Deserializes the `data` property to a typed `RBJsonObject` object.
     *
     *  @param jsonPath     Optional json path to first follow before deserialisation of the json to the specified type occurs e.g. `data.results[0]`.
     *
     *  @return The JSON as a specific `RBJsonObject` instance or `nil` if `data` is empty or the response was invalid.
     */
    public func dataToJson<T: RBJsonObject>(jsonPath: String?) -> [T]? {
        
        if let path = jsonPath {
            
            if let value = dataAsJson() as? [String : Any] {
                
                guard let rawJson = RBJson.traverse(json: value, path: path) as? [[String : Any]] else { return nil }
                return RBJsonObject.objects(array: rawJson)
                
            } else if let value = dataAsJson() as? [[String : Any]] {
                
                guard let rawJson = RBJson.traverse(json: value, path: path) as? [[String : Any]] else { return nil }
                return RBJsonObject.objects(array: rawJson)
            }
            
            return nil
            
        } else {
            
            guard let value = dataAsJson() as? [[String : Any]] else {
                return nil
            }
            
            return RBJsonObject.objects(array: value)
        }
    }
    
    /**
     *  Deserializes the `data` property to a typed array of `RBJsonObject` objects.
     *
     *  @return The JSON as an array of specific `RBJsonObject` instances or `nil` if `data` is empty or the response was invalid.
     */
    public func dataToJson<T: RBJsonObject>() -> T? {
        return dataToJson(jsonPath: nil)
    }
    
    /**
     *  Deserializes the `data` property to a typed array of `RBJsonObject` objects.
     *
     *  @param jsonPath     Optional json path to first follow before deserialisation of the json to the specified type occurs e.g. `data.results[0]`.
     *
     *  @return The JSON as an array of specific `RBJsonObject` instances or `nil` if `data` is empty or the response was invalid.
     */
    public func dataToJson<T: RBJsonObject>(jsonPath: String?) -> T? {
        
        if let path = jsonPath {
            
            if let value = dataAsJson() as? [String : Any] {
                
                guard let rawJson = RBJson.traverse(json: value, path: path) as? [String : Any] else { return nil }
                return T.init(dictionary: rawJson)
                
            } else if let value = dataAsJson() as? [[String : Any]] {
                
                guard let rawJson = RBJson.traverse(json: value, path: path) as? [String : Any] else { return nil }
                return T.init(dictionary: rawJson)
            }
            
            return nil
            
        } else {
            
            guard let value = dataAsJson() as? [String : Any] else {
                return nil
            }
            
            return T.init(dictionary: value)
        }
    }
    
    /**
     *  Deserializes the `data` property to a typed array of `RBJsonObject` objects.
     *
     *  @param encoding     Optional string encoding to use. Default = `UTF8`.
     *
     *  @return The data as a decoded string or `nil` if `data` is empty or the response was invalid.
     */
    public func dataToString(encoding: String.Encoding = String.Encoding.utf8) -> String? {
        
        guard let bytes = self.data else {
            return nil
        }
        
        if bytes.count == 0 {
            return nil
        }
        
        //
        
        return String(bytes: bytes, encoding: String.Encoding.utf8)
    }
    
    private class func uniqueHash(request: URLRequest) -> String {
        
        var string = "\(request.url?.absoluteString ?? "")-\(request.httpMethod ?? "")"
        
        if let headers = request.allHTTPHeaderFields {
            for (key, value) in headers {
                string += "\(key)=\(value)"
            }
        }
        
        // TODO: hash data if available
        /*if let data = request.httpBody {
            
        }*/
        
        return string.md5Hash
    }
}

