//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import Foundation

@objcMembers open class RBTabBar : UIView {
    
    private var _items: [RBTabBarItem] = [RBTabBarItem]()
    private var _buttons: [RBButton : UIViewController] = [RBButton : UIViewController]()
    
    private var positioner: RBTabBarPositioner?
    
    public weak var parent: RBTabController?
    
    open var height: CGFloat = 49 {
        didSet {
            
            if height != oldValue {
                positioner?.tabBarHeight = height
                parent?.calculateAdditionalSafeAreaInsets()
                
                setNeedsLayout()
                parent?.view.setNeedsLayout()
            }
        }
    }
    
    open var margin: UIEdgeInsets = UIEdgeInsets.zero {
        didSet {
            
            if margin != oldValue {
                positioner?.margin = margin
                setNeedsLayout()
            }
        }
    }
        
    public var items: [RBTabBarItem] {
        return _items
    }
    
    required public init(items: [RBTabBarItem]) {
        super.init(frame: CGRect.zero)
        setup(items: items)
    }
    
    required public init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    func setup(items: [RBTabBarItem]) {
        _items = items
        
        var views = [UIView]()
        
        for v in items {
            views.append(v.contentView)
        }
        
        positioner = RBTabBarPositioner(schema: RBTabBarPositionerSchema(views: views, configuration: items))
        positioner?.tabBarHeight = self.height
        
        for (index, item) in items.enumerated() {
            
            if item.isViewOnly {
                continue
            }
            
            if let button = item.button {
                
                if index == 0 {
                    button.isSelected = true
                }
                
                _buttons[button] = item.viewController!
                button.addTarget(self, action: #selector(self.buttonTapped(button:)), for: .touchUpInside)
            }
        }
    }
    
    override open func layoutSubviews() {
        super.layoutSubviews()
        layout()
    }
    
    open func layout() {
        
        guard let p = positioner else {
            return
        }
        
        let insets = UIEdgeInsetsMake(0, 0, safeAreaInsets.bottom - height, 0)
        let frame = CGRectInner(bounds, insets)
        RBPositioner.position(positioner: p, views: p.schema.views, parent: self, frame: frame, completion: nil)
    }
    
    @objc func buttonTapped(button: RBButton) {
    
        guard let vc = _buttons[button] else {
            return
        }
        
        for (item, _) in _buttons {
            
            if item == button {
                item.isSelected = true
            } else {
                item.isSelected = false
            }
        }
        
        self.parent?.setViewController(vc: vc, completion: nil)
    }
    
    override open func applyTheme(_ theme: [String : Any]) {
        super.applyTheme(theme)
        
        RB_THEME_SET(theme, &height, "height")
        RB_THEME_SET(theme, &margin, "margin")
        
        for item in items {
            
            if item.isViewOnly {
                item.contentView.theme.applyChanges(theme[item.themeIdentifier])
            } else {
                item.button?.theme.pushChanges(theme["buttons"] as? [String : Any])
                item.button?.theme.pushChanges(theme[item.themeIdentifier] as? [String : Any])
            }
        }
    }
    
    open override class func generateThemeSchema(withParent parent: RBThemeSchema?) -> RBThemeSchema {
        
        let themeSchema = super.generateThemeSchema(withParent: parent)
        
        themeSchema.setPropertyWithName("margin", typeName: "UIEdgeInsets", notes: "The margin to provide around the buttons.")
        themeSchema.setPropertyWithName("height", nativeType: RBThemeNativeType.decimal, notes: "The height of the tab bar in pt.")
        
        themeSchema.setPropertyWithName("buttons", type: RBButton.self, notes: "The theme of the tab buttons.")
        themeSchema.setPropertyWithName("[identifier]", type: RBButton.self, notes: "The theme of the item for the specified theme identifier.")
        
        return themeSchema
    }
    
}

//MARK: - RBTabBar

/**
 *  Tab bar items.
 */
@objcMembers public class RBTabBarItem: NSObject {

    /**
     *  Whether or not to fill all available space.
     */
    public private (set) var fill: Bool = false
    
    /**
     *  The location of the item.
     */
    public private (set) var alignment: RBHorizontalAlignment = RBHorizontalAlignment.center
    
    /**
     *  The theme identifier of the item.
     */
    public var themeIdentifier: String = ""
    
    /**
     *  The view controller that provides the contents of the item.
     */
    public private(set) var viewController: UIViewController?
    
    public private (set) var view: UIView?
    public private (set) var button: RBButton?
    public private (set) var isViewOnly: Bool = false
    
    public var contentView: UIView {
        return (button ?? view)!
    }
    
    /**
     *  Initializes a new `RBTabItem` that displays a custom view.
     *
     *  @param view             The custom view.
     *  @param alignment        The location of the view.
     *  @param fill             Fill available space.
     *
     *  @return The initialized `RBTabItem`.
     */
    public init(view: UIView, alignment: RBHorizontalAlignment, fill: Bool) {
        
        self.view = view
        self.fill = fill
        self.alignment = alignment
        
        self.isViewOnly = true
        
        super.init()
    }
    
    /**
     *  Initializes a new `RBTabItem`.
     *
     *  @param vc               The view controller.
     *  @param title            The title to apply to the tab button.
     *  @param image            The image to apply to the tab button.
     *  @param alignment        The location of the tab button.
     *  @param fill             Fill available space.
     *
     *  @return The initialized `RBTabItem`.
     */
    public init(vc: UIViewController, title: String?, image: UIImage?, alignment: RBHorizontalAlignment,  fill: Bool) {
        super.init()
        
        let button = RBButton()
        
        if title != nil {
            button.applyTitle(title)
        }
        
        if image != nil {
            button.apply(image)
        }
        
        self.fill = true
        self.button = button
        self.viewController = vc
        self.alignment = alignment
    }
}

//MARK: - RBTabBarPositioner

class RBTabBarPositionerSchema : RBSchemaPositionerSchema {
    
    var items: [RBTabBarItem]
    
    required init(views: [UIView], configuration: Any?) {
        self.items = configuration as! [RBTabBarItem]
        super.init(views: views, configuration: items)
    }
}

class RBTabBarPositioner: RBSchemaPositioner {
    
    var tabBarHeight: CGFloat = 0.0
    
    override open func calculate(numberOfViews: Int, viewPort: CGSize, sizeBlock: (Int, CGSize) -> CGSize) -> RBPositionerResult {
        
        if numberOfViews == 0 {
            return RBPositionerResult.empty()
        }
        
        guard let schema = schema as? RBTabBarPositionerSchema else {
            fatalError("Invalid schema")
        }
        
        //
        
        var frames = [CGRect]()
        var items = schema.items
        
        var fillCount = 0
        var area = CGSize.zero
        let height = viewPort.height
        var shouldFitEqually = false
        
        for i in 0..<numberOfViews {
            
            let size = sizeBlock(i, viewPort)
            
            area.width += size.width
            area.height = max(area.height, size.height)
            
            if items[i].fill {
                fillCount += 1
            }
        }
        
        //
        
        if area.width > viewPort.width {
            shouldFitEqually = true
        }
        
        //
        
        if shouldFitEqually {
            
            var x: CGFloat = 0
            let width = viewPort.width / CGFloat(numberOfViews)
            
            // Do left, then center, then right
            for i in 0..<items.count {
                
                let item = items[i]
                
                if item.alignment == .left {
                    frames.append(CGRect(x: x, y: 0, width: width, height: height))
                    x += width
                }
                else {
                    // In first pass we set zero-rects to correctly allocate slot
                    frames.append(CGRect.zero)
                }
            }
            
            // Center
            for i in 0..<items.count {
                
                let item = items[i]
                
                if item.alignment == .center {
                    frames.append(CGRect(x: x, y: 0, width: width, height: height))
                    x += width
                }
            }
            
            // Right
            for i in 0..<items.count {
                
                let item = items[i]
                
                if item.alignment == .right {
                    frames.append(CGRect(x: x, y: 0, width: width, height: height))
                    x += width
                }
            }
        } else {
            
            var left: CGFloat = 0
            var center: CGFloat = -1
            var right: CGFloat = viewPort.width
            
            var centerSize: CGFloat = 0
            
            let emptySpace: CGFloat = viewPort.width - area.width
            let fillBy: CGFloat = fillCount > 0 ? (emptySpace / CGFloat(fillCount)) : 0
            
            for i in 0..<items.count {
                
                let item = items[i]
                let size = sizeBlock(i, viewPort)
                
                if item.alignment == .left {
                    let width: CGFloat = item.fill ? size.width + fillBy : size.width
                    frames.append(CGRect(x: left, y: 0, width: width, height: height))
                    left += width
                }
                else if item.alignment == RBHorizontalAlignment.right {
                    let width: CGFloat = item.fill ? size.width + fillBy : size.width
                    frames.append(CGRect(x: right - width, y: 0, width: width, height: height))
                    right -= width
                }
                else if item.alignment == RBHorizontalAlignment.center {
                    centerSize += item.fill ? size.width + fillBy : size.width
                    frames.append(CGRect.zero)
                }
            }
            
            // Now do center
            center = (viewPort.width / 2) - (centerSize / 2)
            
            if left > center {
                center = left
            }
            
            if center + centerSize > right {
                center = right - centerSize
            }
            
            // Center must be left of 'left' and right of 'right' values
            for i in 0..<items.count {
                
                let item = items[i]
                
                if item.alignment == .center {
                    let size = sizeBlock(i, viewPort)
                    let width = item.fill ? size.width + fillBy : size.width
                    frames[i] = CGRect(x: center, y: 0, width: width, height: height)
                    center += width
                }
            }
        }
        
        let contentSize = RBPositioner.union(frames: &frames).size
        return RBPositionerResult(frames: frames, contentSize: contentSize)
    }
}
