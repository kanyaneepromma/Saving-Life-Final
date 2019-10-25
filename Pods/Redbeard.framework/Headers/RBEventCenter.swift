//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//
import Foundation
import UIKit

/**
 * Listens for global events.
 */
@objc public protocol RBEventListener: NSObjectProtocol {
    /**
     * Receives and handles a raised event.
     *
     * @param eventName  The name of the event raised.
     * @param sender     The object that raised the event.
     * @param data       The user data associated with the event.
     * @param completion The completion that must be called when the event has been handled.
     */
    @objc func event(_ eventName: String, wasRaisedBy sender: Any?, withData data: Any?, completion: () -> Void)
}

/**
 * The global events center.
 */
@objcMembers public class RBEventCenter: NSObject {
    
    // TODO: BUG FIX: WHEN REGISTERING/UNREGISTERING, LOWERCASE THE EVENT NAMES SO THEY
    //       MATCH TO THE LOWERCASED NAMES THAT ARE CALLED LATER!
    
    fileprivate static let lockQueue = DispatchQueue(label: "RBEventCenter")
    fileprivate static var globalEventListeners = RBEventListeners()
    
    /**
     * Register an object as a listener for an event.
     *
     * @param listener  An object that implements `RBEventListener`.
     * @param event The name of the event to be notified of.
     */
    public class func register(_ listener: RBEventListener, forEvent event: String) {
        
        //TODO: self.log("Registering listener of type %@ for event %@", args: listener.self  as! CVarArg, eventName)
        
        lockQueue.sync {
            RBEventCenter.globalEventListeners.register(listener: listener, forEvent: event)
        }
    }
    
    /**
     * Unregister an object as a listener for an event.
     *
     * @param listener  The currently registered listener for the event.
     * @param event The name of the event to stop being notified of.
     */
    public class func unregisterListener(_ listener: RBEventListener, forEvent event: String) {
        
        //TODO: self.log("Unregistering listener of type %@ from event %@", args: listener.self as! CVarArg, eventName)
        
        lockQueue.sync {
            globalEventListeners.unregister(listener: listener, forEvent: event)
        }
    }
    
    /**
     * Unregister an object as a listener for all events.
     *
     * @param listener  The currently registered listener for one or more events.
     */
    public class func unregisterListener(_ listener: RBEventListener) {
        
        //TODO: self.log("Unregistering listener of type %@ from ALL events...", args: listener.self as! CVarArg)
        
        lockQueue.sync {
            globalEventListeners.unregister(listener: listener)
        }
    }
    
    /**
     * Raise an event.
     *
     * @param event                 The name of the event to raise.
     * @param sender                The object that raised the event.
     * @param data                  User data to provide to listeners of the event.
     * @param handleSynchronously   Whether the listeners will be informed synchronously (`true`) or simultaneously (`false`).
     * @param completion            The completion block to be called when the event has been handled.
     */
    public class func raiseEvent(withName event: String, withSender sender: Any?, withData data: Any?, handleSynchronously: Bool, completion: (() -> Void)?) {
        
        //TODO: self.log("Raising event '%@' [by caller of type %@]", args: eventName, sender.self as! CVarArg)
        
        lockQueue.sync {
            
            let handlers = globalEventListeners.handlers(forEvent: event)
            RBEventCenter.raiseEvent(withName: event, withSender: sender, withData: data, handleSynchronously: handleSynchronously, completion: completion, handlers: handlers)
        }
    }
    
    fileprivate class func raiseEvent(withName event: String, withSender sender: Any?, withData data: Any?, handleSynchronously: Bool, completion: (() -> Void)?, handlers: [RBEventListenerRef]) {
        
        if handlers.count == 0 {
            completion?()
        }
        
        //
        
        if handleSynchronously {
            
            var nextListeners = handlers
            let ref = nextListeners.popLast()
            
            if let listener = ref?.value {
                listener.event(event, wasRaisedBy: sender, withData: data, completion: {
                    
                    RBEventCenter.raiseEvent(withName: event,
                                             withSender: sender,
                                             withData: data,
                                             handleSynchronously: handleSynchronously,
                                             completion: completion,
                                             handlers: nextListeners)
                })
            } else {
                
                RBEventCenter.raiseEvent(withName: event,
                                         withSender: sender,
                                         withData: data,
                                         handleSynchronously: handleSynchronously,
                                         completion: completion,
                                         handlers: nextListeners)
            }
        }
        else {
            
            var remaining: Int = handlers.count
            
            for ref in handlers {
                
                let currentCount = remaining
                
                if let listener = ref.value {
                    
                    listener.event(event, wasRaisedBy: sender, withData: data, completion: {
                        remaining = currentCount - 1
                        
                        if remaining < 1 {
                            completion?()
                        }
                    })
                    
                } else {
                    
                    remaining = currentCount - 1
                    
                    if remaining < 1 {
                        completion?()
                    }
                }
            }
        }
    }
}

fileprivate class RBEventListenerRef {
    
    private(set) weak var value: AnyObject?
    
    init(value: AnyObject?) {
        self.value = value
    }
}

fileprivate class RBEventListeners {
    
    var listeners = [String: [RBEventListenerRef]]()
    
    func handlers(forEvent eventName: String) -> [RBEventListenerRef] {
        
        guard let event = self.normaliseEventName(eventName: eventName) else {
            return [RBEventListenerRef]()
        }
        
        return listeners[event] ?? [RBEventListenerRef]()
    }
    
    func register(listener: RBEventListener, forEvent eventName: String) {
        
        guard let event = self.normaliseEventName(eventName: eventName) else {
            return
        }
        
        //
        
        var list: [RBEventListenerRef]? = listeners[event]
        
        if list == nil {
            
            list = [RBEventListenerRef]()
            list?.append(RBEventListenerRef(value: listener))
            listeners[event] = list
            
        } else {
            
            var found = false
            
            for object in list! {
                if object.value === listener {
                    found = true
                    break
                }
            }
            
            if !found {
                list?.append(RBEventListenerRef(value: listener))
            }
        }
    }
    
    func unregister(listener: RBEventListener) {
        
        for (key, _) in listeners {
            unregister(listener: listener, forEvent: key)
        }
    }
    
    func unregister(listener: RBEventListener, forEvent eventName: String) {
        
        guard let event = self.normaliseEventName(eventName: eventName) else {
            return
        }
        
        //
        
        var list: [RBEventListenerRef]? = listeners[event]
        
        if list == nil {
            return
        }
        
        var index = -1
        
        for (i, object) in list!.enumerated() {
            if object.value === listener {
                index = i
                break
            }
        }
        
        if index != -1 {
            list?.remove(at: index)
        }
    }
    
    func compact(forEvent eventName: String) {
        
        guard let event = self.normaliseEventName(eventName: eventName) else {
            return
        }
        
        //
        
        if let list = listeners[event] {
            
            listeners[event] = list.filter({ (listener) -> Bool in
                return listener.value != nil
            })
        }
    }
    
    func normaliseEventName(eventName: String) -> String? {
        let event = eventName.lowercased().trimmingCharacters(in: CharacterSet.whitespacesAndNewlines)
        
        if event.count > 0 {
            return event
        }
        
        return nil
    }
}
