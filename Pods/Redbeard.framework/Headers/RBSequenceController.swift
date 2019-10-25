//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  The sequence controller delegate to receive transition change events.
 */
@objc public protocol RBSequenceControllerDelegate: NSObjectProtocol {
   
    /**
     *  The controller did start the sequence.
     *
     *  @param sequenceController The sequence controller object.
     */
    @objc optional func sequenceDidStart(with sequenceController: RBSequenceController)
    
    /**
     *  The controller did complete the transition to a step.
     *
     *  @param stepIndex          The step index that was transitioned to.
     *  @param sequenceController The sequence controller object.
     */
    @objc optional func sequenceDidCompleteStep(_ stepIndex: Int, with sequenceController: RBSequenceController)
    
    /**
     *  The controller did complete the sequence.
     *
     *  @param sequenceController The sequence controller.
     *  @param willRepeat         Whether the controller will automatically repeat the sequence.
     */
    @objc optional func sequenceDidComplete(with sequenceController: RBSequenceController, willRepeat: Bool)
}

/**
 *  Manages a sequence of transitions.
 */
@objcMembers public class RBSequenceController: NSObject {
    
    var timer: Timer?
    var didStart: Bool = false
    var isExecutingStep: Bool = false
    var sequenceSteps = [RBSequenceStep]()
    var currentSequenceStep: RBSequenceStep?
    
    /**
     *  The delegate to receive transition change events.
     */
    public weak var delegate: RBSequenceControllerDelegate?
    
    /**
     *  The number of steps in the sequence.
     */
    public private(set) var stepCount: Int = 0
    
    /**
     *  The index of the current step in the sequence.
     */
    public private(set) var stepIndex: Int = 0
    
    /**
     *  Whether or not the controller should automatically move to the next step.
     */
    public var automaticStepEnabled: Bool = false
    
    /**
     *  The delay that the controller should observe between a step being completed
     *  and transitioning to the next step.
     */
    public var automaticStepDelay: TimeInterval = 0.0 {
        didSet {
            if automaticStepDelay != oldValue {
                timer?.invalidate()
                timer = Timer(timeInterval: automaticStepDelay, target: self, selector: #selector(self.nextStep), userInfo: nil, repeats: true)
            }
        }
    }
    
    /**
     *  Whether or not the controller should automatically repeat the sequence when it finishes.
     */
    public var shouldRepeatAtEnd: Bool = false
    
    /**
     *  Add a step to the sequence.
     *
     *  @param sequenceStep The `RBSequenceStep` object to add.
     */
    public func add(_ sequenceStep: RBSequenceStep) {
        sequenceSteps.append(sequenceStep)
        stepCount += 1
    }
    
    /**
     *  Starts the sequence.
     *
     *  @return Whether or not the operation completed successfully.
     */
    public func start() -> Bool {
        didStart = true
        
        let rv = nextStep()
        delegate?.sequenceDidStart?(with: self)
        return rv
    }
    
    /**
     *  Transitions to the next step in the sequence.
     *
     *  @return Whether or not the operation completed successfully.
     */
    public func nextStep() -> Bool {
       
        if isExecutingStep {
            return false
        }
        
        timer?.invalidate()
        
        if stepIndex == stepCount {
           
            delegate?.sequenceDidComplete?(with: self, willRepeat: shouldRepeatAtEnd)
            
            if !shouldRepeatAtEnd {
                return false
            }
            else {
                stepIndex = 0
            }
        }
       
        isExecutingStep = true
        
        let sequenceStep = sequenceSteps[stepIndex]
        
        _ = sequenceStep.run(withCompletion: {() -> Void in
            self.stepIndex += 1
            self.delegate?.sequenceDidCompleteStep?(self.stepIndex - 1, with: self)
            
            if self.automaticStepEnabled {
                
                if self.automaticStepDelay > 0 {
                    
                    self.timer = Timer.scheduledTimer(timeInterval: self.automaticStepDelay, target: self, selector: #selector(self.nextStep), userInfo: nil, repeats: true)
                }
                else {
                    self.perform(#selector(self.nextStep), with: nil, afterDelay: 0)
                }
            }
            self.isExecutingStep = false
        })
        
        return true
    }
    
    /**
     *  Resets to the first step in the sequence.
     */
    public func resetAndRewind() {
        timer?.invalidate()
        stepIndex = 0
    }
}

