//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  A delegate observer collection delegate.
 */
@objc public protocol RBObserverCollectionDelegate: NSObjectProtocol {
   
    /**
     *  Called when the last delegate observer was removed and the collection became empty.
     *
     *  @param observerCollection The observer collection object.
     */
    @objc optional func observerCollectionBecameEmpty(_ observerCollection: RBObserverCollection)
    
    /**
     *  Called when the first delegate observer was added and the collection became non-empty.
     *
     *  @param observerCollection The observer collection object.
     */
    @objc optional func observerCollectionBecameNonEmpty(_ observerCollection: RBObserverCollection)
}

/**
 *  A weak or strong collection of observer delegates.
 */
@objcMembers public class RBObserverCollection: NSObject {
    
    private let lockQueue = DispatchQueue(label: "RBObserverCollection")
    
    private(set) var observers = NSPointerArray.weakObjects()
    
    /**
     *  A delegate to be informed of collection events.
     */
    weak var delegate: RBObserverCollectionDelegate?
   
    /**
     *  The number of observers currently referenced in the collection.
     */
    private(set) var observerCount: Int = 0
    
    /**
     *  Whether or not the delegate observers are stored with strong references (retained).
     */
    private(set) var doesRetainObservers: Bool = false

    /**
     *  Initializes a new observer collection that keeps weak references (does not retain)
     *  to its delegate observer objects.
     *
     *  @return The initialized observer collection object.
     */
    public override init() {
        super.init()
    }
    
    /**
     *  Initializes a new observer collection that keeps strong references (retains) to its
     *  delegate observer objects.
     *
     *  @return The initialized observer collection object.
     */
    public init(withStrongReferences strong: Bool) {
        super.init()
        
        self.doesRetainObservers = strong
        self.observers = strong ? NSPointerArray.strongObjects() : NSPointerArray.weakObjects()
    }
    
    /**
     *  Enumerates the delegate observer objects in the collection.
     *
     *  @param enumerationBlock The enumeration block to call on each delegate observer object.
     */
    public func enumerateObservers(withBlock enumerationBlock: @escaping (AnyObject, Bool) -> Void) {
       
        //lockQueue.sync { // TODO: commented this as it causes a crash
            
            if self.observers.count == 0 {
                return
            }
            
            let stop = false
            
            for i in 0..<self.observers.count {
                if let observer = self.observers.object(at: i) {
                    enumerationBlock(observer, stop)
                    // TODO: get enumerationBlock to return true/false as 'stop' indicator
                    // TODO: change name of enumerationBlock?
                    
                    if stop {
                        break
                    }
                }
            }
        //}
    }
    
    /**
     *  Add a new delegate observer to the collection.
     *
     *  @param observer The observer object to add to the collection.
     */
    public func addObserver(_ observer: AnyObject) {
       
        self.observers.compact()
        
        var count = 0
        
        lockQueue.sync {
            for i in 0..<self.observers.count {
                if let object = self.observers.object(at: i) {
                    if object === observer {
                        return // Already added
                    }
                }
            }
            
            self.observers.addObject(observer)
            self.observerCount = self.observers.count
            count = self.observerCount
        }
    
        if count == 1 {
            self.delegate?.observerCollectionBecameNonEmpty?(self)
        }
    }
    
    /**
     *  Remove a delegate observer from the collection.
     *
     *  @param observer The observer object to remove from the collection.
     */
    public func removeObserver(_ observer: AnyObject) {
        
        self.observers.compact()
        
        var count = 0
        var didRemoveObserver = false
      
        lockQueue.sync {
            
            for i in 0..<self.observers.count {
                if let obj = self.observers.object(at: i) {
                    if obj === observer {
                        self.observers.removeObject(at: i)
                        didRemoveObserver = true
                        break
                    }
                }
            }
            
            self.observerCount = self.observers.count
            count = self.observerCount
        }
        
        let becameEmpty = didRemoveObserver && count == 0

        if becameEmpty {
            self.delegate?.observerCollectionBecameEmpty?(self)
        }
    }
}

fileprivate extension NSPointerArray {
    
    func addObject(_ object: AnyObject?) {
        guard let strongObject = object else { return }
        
        let pointer = Unmanaged.passUnretained(strongObject).toOpaque()
        addPointer(pointer)
    }
    
    func insertObject(_ object: AnyObject?, at index: Int) {
        guard index < count, let strongObject = object else { return }
        
        let pointer = Unmanaged.passUnretained(strongObject).toOpaque()
        insertPointer(pointer, at: index)
    }
    
    func replaceObject(at index: Int, withObject object: AnyObject?) {
        guard index < count, let strongObject = object else { return }
        
        let pointer = Unmanaged.passUnretained(strongObject).toOpaque()
        replacePointer(at: index, withPointer: pointer)
    }
    
    func object(at index: Int) -> AnyObject? {
        guard index < count, let pointer = self.pointer(at: index) else { return nil }
        return Unmanaged<AnyObject>.fromOpaque(pointer).takeUnretainedValue()
    }
    
    func removeObject(at index: Int) {
        guard index < count else { return }
        removePointer(at: index)
    }
}
