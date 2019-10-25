//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  Performs animations with a given configuration.
 */
@objcMembers public class RBAnimator: NSObject, NSCopying, RBThemeTrackerDelegate {
    
    public typealias RBAnimatorCompletionBlock = () -> ()
    private static let lockQueue = DispatchQueue(label: "RBAnimator")
    
    //
    
    public static let defaultDuration: CGFloat = 0.2
    public static let defaultDelay: CGFloat = 0.0
    public static let defaultSpringVelocity: CGFloat = 0.0
    public static let defaultSpringDampening: CGFloat = 0.7
    public static let defaultCurve: UIViewAnimationCurve = .linear
    public static let defaultOptions:UIViewAnimationOptions = UIViewAnimationOptions(rawValue: 0)
    
    //
    
    private var postAnimationActions = [() -> ()]()
    private var pendingAnimations: Int = 0
   
    //
    
    /**
     *  The theme tracker object. Use this to add further theme changes, apply and re-apply themes.
     */
    public private(set) var theme: RBThemeTracker?
    
    /**
     *  The duration of the animation in seconds.
     */
    public var duration: CGFloat = RBAnimator.defaultDuration
    
    /**
     *  The delay before beginning the animation in seconds.
     */
    public var delay: CGFloat = RBAnimator.defaultDelay
    
    /**
     *  The velocity of the spring animation. 0 = no spring
     */
    public var springVelocity: CGFloat = RBAnimator.defaultSpringVelocity
    
    /**
     *  The dampening of the spring animation, determining how quickly the initial force subsides.
     */
    public var springDampening: CGFloat = RBAnimator.defaultSpringDampening
    
    /**
     *  The curve of the animation.
     */
    public var curve: UIViewAnimationCurve = RBAnimator.defaultCurve
    
    /**
     *  The animation options.
     */
    public var options: UIViewAnimationOptions = RBAnimator.defaultOptions
    
    /**
     *  Creates a new instance of an animator configured with the default settings.
     *
     *  @return The new animator object.
     */
    public class func newDefaultAnimator() -> RBAnimator {
        let animator = RBAnimator()
        return animator
    }
    
    /**
     *  Creates a new instance of an animator configured with the default spring animation settings.
     *
     *  @return The new animator object.
     */
    public class func newDefaultSpring() -> RBAnimator {
        let animator = RBAnimator()
        animator.duration = 0.4
        animator.springVelocity = 0.8
        animator.springDampening = 0.7
        return animator
    }
    
    /**
     *  Creates a new instance of an animator configured to mimick the keyboard transition animation.
     *
     *  @return The new animator object.
     */
    public class func newDefaultKeyboardAnimator() -> RBAnimator {
        let animator = RBAnimator()
        animator.duration = CGFloat(RBUICenter.shared.keyboardAnimationDuration)
        animator.curve = RBUICenter.shared.keyboardAnimationCurve
        return animator
    }
    
    public override init() {
        super.init()
        theme = RBThemeTracker(delegate: self)
    }
    
    public func copy(with zone: NSZone?) -> Any {
        let animator = RBAnimator()
        animator.duration = duration
        animator.delay = delay
        animator.springVelocity = springVelocity
        animator.springDampening = springDampening
        animator.options = options
        animator.curve = curve
        return animator
    }
    
    /**
     *  Enqueues a block to be executed after all currently queued animations are complete.
     *
     *  @param actionBlock The block to execute.
     */
    public func perform(afterAnimations actionBlock: @escaping () -> ()) {
        if pendingAnimations > 0 {
            RBAnimator.lockQueue.sync {
                postAnimationActions.append(actionBlock)
            }
        }
        else {
            perform(inMainThread: {() -> Void in
                actionBlock()
            })
        }
    }
    
    /**
     *  Perform the given changes with an animation.
     *
     *  @param animated   Whether or not the changes should be animated.
     *  @param changes    The changes block that will be called to make the UI changes. viewsToLayout should contain the list of the `UIViews` to animate.
     *  @param completion An optional block to be called when the animation has completed.
     */
    public func perform(withAnimation animated: Bool, changes: @escaping () -> [UIView]?, completion:RBAnimatorCompletionBlock?) {
        
        let performChanges: () -> () = {() -> Void in
            
            guard let viewsToLayout = changes() else {
                return
            }
            
            for view in viewsToLayout {
                view.setNeedsLayout()
                
                if animated {
                    view.layoutIfNeeded()
                }
            }
        }
        
        let onCompletion: () -> () = {() -> Void in
            
            if self.pendingAnimations > 0 {
                self.pendingAnimations -= 1
            }
            
            completion?()
            
            if self.pendingAnimations == 0 {
                var actions: [() -> ()]? = nil
                
                RBAnimator.lockQueue.sync {
                    actions = self.postAnimationActions
                    self.postAnimationActions.removeAll()
                }
                
                self.perform(inMainThread: {() -> Void in
                    
                    if let array = actions {
                        for action in array {
                            action()
                        }
                    }
                })
            }
        }
        
        if animated {
            
            pendingAnimations += 1
            
            UIView.setAnimationCurve(self.curve)
            
            if springVelocity > 0 {
                
                UIView.animate(withDuration: TimeInterval(self.duration),
                               delay: TimeInterval(self.delay),
                               usingSpringWithDamping: self.springDampening,
                               initialSpringVelocity: self.springVelocity,
                               options: self.options,
                               animations: performChanges,
                               completion: {(_ finished: Bool) -> Void in
                                
                                onCompletion()
                })
            }
            else {
                UIView.animate(withDuration: TimeInterval(self.duration),
                               delay: TimeInterval(self.delay),
                               options: self.options,
                               animations: performChanges,
                               completion: {(_ finished: Bool) -> Void in
                                
                                onCompletion()
                })
            }
        }
        else {
            perform(inMainThread: {() -> Void in
                performChanges()
                completion?()
            })
        }
    }
    
    public func perform(inMainThread action: @escaping () -> ()) {
        
        if Thread.isMainThread {
            action()
        }
        else {
            DispatchQueue.main.async(execute: action)
        }
    }
    
    // MARK: -
    // MARK: RBThemeTrackerDelegate
    
    public class func generateThemeSchema(withParent parent: RBThemeSchema?) -> RBThemeSchema {
        
        let themeSchema = RBThemeSchema(typeClass: self, withParentSchema: parent)
        
        themeSchema.setPropertyWithName("duration", nativeType: .decimal, notes: "The duration of the animation (in seconds).")
        themeSchema.setPropertyWithName("delay", nativeType: .decimal, notes: "The delay before starting the animation (in seconds).")
        themeSchema.setPropertyWithName("springDampening", nativeType: .decimal, notes: "The dampening factor to apply to the spring effect (0.0 - 1.0).")
        themeSchema.setPropertyWithName("springVelocity", nativeType: .decimal, notes: "The initial velocity to apply to the spring effect.")
        
        return themeSchema
    }
    
    public func applyTheme(_ theme: [String: Any]) {
        
        RB_THEME_SET(theme, &duration, "duration")
        RB_THEME_SET(theme, &delay, "delay")
        RB_THEME_SET(theme, &springDampening, "springDampening")
        RB_THEME_SET(theme, &springVelocity, "springVelocity")
    }
}
