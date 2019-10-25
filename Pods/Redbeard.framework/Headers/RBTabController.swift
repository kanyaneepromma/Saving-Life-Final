//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  A delegate to receive tab page selection events.
 */
@objc public protocol RBTabControllerDelegate: NSObjectProtocol {
    
    /**
     *  Called to notify that a tab should be selected.
     *
     *  @param vc               The view controller.
     *  @param animated         Whether or not the transition to the page will be animated.
     */
    @objc func tabBar(tabBar: RBTabController, shouldSelect vc: UIViewController, animated: Bool) -> Bool
    
    /**
     *  Called to notify that a tab was selected.
     *
     *  @param vc               The view controller.
     *  @param animated         Whether or not the transition to the page will be animated.
     */
    @objc func tabBar(tabBar: RBTabController, didSelect vc: UIViewController, animated: Bool)
}

/**
 *  A tab bar controllers that manages pages with tabs.
 */
@objcMembers open class RBTabController: UIViewController {
   
    private var previousViewController: UIViewController?
    
    /**
     *  A delegate to receive tab page selection events.
     */
    public weak var delegate: RBTabControllerDelegate?
    
    /**
     *  The animator that is used to provide animated transitions.
     */
    public var animator: RBNavigationAnimator?
    
    /**
     *  A tab bar
     */
    public var tabBar: RBTabBar? {
        didSet {
            
            if let value = oldValue {
                value.removeFromSuperview()
                value.parent = nil
            }
            
            if let value = tabBar {
                view.addSubview(value)
                value.parent = self
                tabBarIsHidden = false
            } else {
                tabBarIsHidden = true
            }
            
            calculateAdditionalSafeAreaInsets()
            
            view.setNeedsLayout()
            view.setNeedsDisplay()
        }
    }
    
    /**
     *  Animator to be used when showing or hiding the tabBar.
     */
    public var tabBarAnimator: RBAnimator = RBAnimator.newDefaultAnimator()
    
    /**
     *  Whether or not the tabBar is hidden.
     */
    public private(set) var tabBarIsHidden: Bool = true
    
    /**
     *  The number of tab pages currently in the container.
     */
    public var viewControllers: [UIViewController]  = [UIViewController]() {
        didSet {
            
            for vc in oldValue {
                vc.view.removeFromSuperview()
            }
            
            //
            
            if viewControllers.count > 0 {
                setViewController(ignoreShouldSelect: true, vc: viewControllers[0], animator: animator, completion: nil)
            }
        }
    }
    
    /**
     *  Gets the selected tab page via the index. Returns < 0 if a page is not set.
     */
    public var selectedIndex: Int {
    
        for (i, vc) in viewControllers.enumerated() {
            
            if vc == selectedViewController {
                return i
            }
        }
        
        return -1;
    }
   
    /**
     *  Gets the selected tab page.
     */
    public private (set) var selectedViewController: UIViewController?
    
    open override func viewWillLayoutSubviews() {
        super.viewWillLayoutSubviews()
        layout()
    }
    
    internal func calculateAdditionalSafeAreaInsets() {
        
        if let tabBarView = tabBar, tabBarIsHidden == false {
            
            let insets = UIEdgeInsetsMake(0, 0, tabBarView.height, 0)
            
            if insets != self.additionalSafeAreaInsets {
                self.additionalSafeAreaInsets = insets
            }
            
        } else {
            
            if UIEdgeInsets.zero != self.additionalSafeAreaInsets {
                self.additionalSafeAreaInsets = UIEdgeInsets.zero
            }
        }
    }
    
    public func setViewController(vc: UIViewController, completion: (() -> Void)?) {
        setViewController(ignoreShouldSelect: false, vc: vc, animator: animator, completion: completion)
    }
    
    public func setViewController(vc: UIViewController, animator: RBNavigationAnimator?, completion: (() -> Void)?) {
        setViewController(ignoreShouldSelect: false, vc: vc, animator: animator, completion: completion)
    }
    
    func setViewController(ignoreShouldSelect: Bool, vc: UIViewController, animator: RBNavigationAnimator?, completion: (() -> Void)?) {
    
        var nvc: UIViewController?
        
        for viewController in viewControllers {
            if viewController == vc {
                nvc = vc
                break
            }
        }
        
        //
        
        guard let newViewController = nvc else {
            return
        }
        
        if newViewController == selectedViewController {
            return
        }

        //
        
        previousViewController = selectedViewController
        
        //
        
        let animated = previousViewController != nil && viewControllers.count > 0 && animator != nil
        
        if !ignoreShouldSelect {
            
            if !tabBarShouldSelect(vc: newViewController, animated: animated) {
                return
            }
            
            if !(delegate?.tabBar(tabBar: self, shouldSelect: newViewController, animated: animated) ?? true) {
                return
            }
        }
        
        //
        
        selectedViewController = newViewController
        layout(animator: animator, completion: completion)
        
        //
        
        tabBarDidSelect(vc: newViewController, animated: animated)
        delegate?.tabBar(tabBar: self, didSelect: newViewController, animated: animated)
        
        view.setNeedsLayout()
    }
    
    func layout() {
        
        guard let frontViewController = selectedViewController else {
            return
        }
        
        frontViewController.view.frame = view.bounds
        
        layoutTabBar()
    }
    
    func tabBarFrames() -> (onScreen: CGRect, offScreen: CGRect) {
        
        guard let tabBarView = tabBar else {
            return (.zero, .zero)
        }
        
        let frame = view.bounds
        let tabBarHeight = tabBarView.height + (view.safeAreaInsets.bottom - tabBarView.height)
        let tabBarSize = CGSize(width: frame.width, height: tabBarHeight)
        
        let onScreenFrame = CGRectAlign(tabBarSize, .bottom, .center, frame)
        let offScreenFrame = CGRect(origin: CGPoint(x: 0, y: frame.height + 1), size: CGSize(width: frame.width, height: tabBarHeight))
        
        return (onScreenFrame, offScreenFrame)
    }
    
    func layoutTabBar() {
        
        if let tabBarView = self.tabBar {
            
            if tabBarIsHidden {
                return
            }
            
            //
            
            if tabBarView.superview != self.view {
                tabBarView.removeFromSuperview()
                self.view.addSubview(tabBarView)
            }
            
            let frames = tabBarFrames()
            tabBarView.frame = frames.onScreen
            self.view.bringSubview(toFront: tabBarView) // Always at the top
        }
    }
    
    func layout(animator: RBNavigationAnimator?, completion: (() -> Void)?) {
        
        let animated = previousViewController != nil && viewControllers.count > 0 && animator != nil
        
        let backViewController = previousViewController
        guard let frontViewController = selectedViewController else {
            return
        }
        
        //
        
        // ADD VIEW CONTROLLER
        self.addChildViewController(frontViewController)
        frontViewController.didMove(toParentViewController: self)
        
        // LOAD NEW VIEW IF NECESSARY
        frontViewController.view.removeFromSuperview()
        
        // APPEARANCE MESSAGES
        self.viewControllerWillAppear(frontViewController, animated: animated)
        
        if let viewController = backViewController {
            self.viewControllerWillDisappear(viewController, animated: animated)
        }
        
        // ADD VIEW
        self.view.addSubview(frontViewController.view)
        
        // Ready to set
        
        // Initial Frame
        if frontViewController.view.frame != view.contentBounds {
            frontViewController.view.frame = view.contentBounds
        }
        
        // ANIMATION
        
        let finalise: () -> Void = {
            
            // APPEARANCE MESSAGES
            self.viewControllerDidAppear(frontViewController, animated: animated)
            
            if let viewController = backViewController {
                viewController.view.removeFromSuperview()
                self.viewControllerDidDisappear(viewController, animated: animated)
            }
            
            //
            
            self.layoutTabBar()
            
            //completion block here
            completion?()
        }
        
        if animated {
            
            animator?.animatePush(withContainer: self.view,
                                  withBack: previousViewController!.view,
                                  withFront: frontViewController.view,
                                  completion: finalise)
        } else {
            finalise()
        }
    }
    
    public func hideTabBar(hide: Bool, animated: Bool) {
        
        guard let tabBarView = tabBar else {
            return
        }
        
        if tabBarIsHidden == hide {
            return
        }
        
        //
        
        tabBarIsHidden = hide
        let frames = tabBarFrames()
        
        if hide {
        
            tabBarAnimator.perform(withAnimation: animated, changes: { () -> [UIView]? in
                
                tabBarView.frame = frames.offScreen
                return [tabBarView]
                
            }) {
                tabBarView.isHidden = true
                self.calculateAdditionalSafeAreaInsets()
                self.view.setNeedsLayout()
            }
        } else {
            
            tabBarView.frame = frames.offScreen // Set correct off screen location first
            
            tabBarAnimator.perform(withAnimation: animated, changes: { () -> [UIView]? in
                
                tabBarView.isHidden = false
                tabBarView.frame = frames.onScreen
                
                return [tabBarView]
                
            }) {
                self.calculateAdditionalSafeAreaInsets()
                self.view.setNeedsLayout()
            }
        }
    }
    
    // MARK: -
    // MARK: Subclassing
    
    /**
     *  Called to notify that a tab will be selected.
     *
     *  @param vc               The view controller.
     *  @param animated         Whether or not the transition to the page will be animated.
     */
    public func tabBarShouldSelect(vc: UIViewController, animated: Bool) -> Bool {
        return true
    }
    
    /**
     *  Called to notify that a tab was selected.
     *
     *  @param vc               The view controller.
     *  @param animated         Whether or not the transition to the page will be animated.
     */
    public func tabBarDidSelect(vc: UIViewController, animated: Bool) {
    }
}
