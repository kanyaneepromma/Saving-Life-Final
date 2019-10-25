//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//
import Foundation;
import UIKit

/**
 *  A block that performs the initialization part of an `RBSequenceStep` object.
 *
 *  @param ^completion The block to be called when the operation is complete. `contextData` will be passed to the next part of the
 *  `RBSequenceStep` operation.
 */
public typealias RBSequenceStepInitializationBlock = (_ completion: ([AnyHashable: Any]?) -> ()) -> Void

/**
 *  A block that performs the completion part of an `RBSequenceStep` object.
 *
 *  @param contextData A dictionary of assignments that was passed from the initialization part of the `RBSequenceStep` operation.
 *  @param ^completion The block to be called when the operation is complete.
 */
public typealias RBSequenceStepCompletionBlock = (_ contextData: [AnyHashable: Any], _ completion: ()-> ()) -> Void


/**
 *  A step in a sequence.
 */
@objcMembers public class RBSequenceStep: NSObject {
    
    /**
     *  The block to be called when transitioning into the sequence step.
     */
    public private(set) var initializationBlock: RBSequenceStepInitializationBlock?
    
    /**
     *  The block to be called when transitioning out of the sequence step.
     */
    public private(set) var completionBlock: RBSequenceStepCompletionBlock?
    
    /**
     *  The time in seconds to wait after the step has been fully transitioned into.
     */
    public private(set) var presentationDuration: TimeInterval = 0.0
    
    /**
     *  Whether or not the step is currently active and running.
     */
    public private(set) var isRunning: Bool = false
    
    /**
     *  Initializes a new sequence step.
     *
     *  @param initializationBlock  The block to be called when transitioning into the sequence step.
     *  @param completionBlock      The block to be called when transitioning out of the sequence step.
     *  @param presentationDuration The time in seconds to wait after the step has been fully transitioned into.
     *
     *  @return The initialized object.
     */
    public init(initializationBlock: RBSequenceStepInitializationBlock?, completionBlock: RBSequenceStepCompletionBlock?, presentationDuration: TimeInterval) throws {
        super.init()
        
        if !(initializationBlock != nil) {
            throw RBError.general(reason: "No initializationBlock given.")
        }
        
        if !(completionBlock != nil) {
            throw RBError.general(reason: "No completionBlock given.")
        }
        
        self.initializationBlock = initializationBlock
        self.completionBlock = completionBlock
        self.presentationDuration = presentationDuration
    }
    
    /**
     *  Runs the sequence step by transitioning into the step, waiting for the duration and transitioning out.
     *
     *  @param completion An optional completion block to be called when the step has completed the final transition out.
     *
     *  @return Whether or not the transition was run successfully.
     */
    public func run(withCompletion completion: @escaping () -> ()?) -> Bool {
        
        if isRunning {
            return false
        }
        
        isRunning = true
        
        DispatchQueue.main.async(execute: {() -> Void in
            self.initializationBlock = { (completion) in
                _ = RBThreading.dispatchTaskBlock({() -> Void in
                    self.completionBlock = { (contextData, completion) in
                        self.isRunning = false
                        completion()
                    }
                }, afterDelay: self.presentationDuration, using: DispatchQueue.main)
            }
        })
        
        return true
    }
}

