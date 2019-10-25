//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  `UIGestureRecognizer` extension methods.
 */
@objc public extension UIGestureRecognizer {
    
    /**
     *  Cancels the current gesture being recognised.
     */
    @objc public func cancel() {
        if isEnabled {
            isEnabled = false
            isEnabled = true
        }
    }
}
