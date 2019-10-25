//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import Foundation
import CoreGraphics

/**
 *  UIColor extension methods.
 */
@objc public extension UIColor {
    
    /**
     *  Returns a randomly selected color.
     *
     *  @return A randomly selected `UIColor` object.
     */
    @objc public class func random() -> UIColor {
        
        let r = CGFloat(RBRandom.double(withMinimumValue: 0, maximumValue: 1))
        let g = CGFloat(RBRandom.double(withMinimumValue: 0, maximumValue: 1))
        let b = CGFloat(RBRandom.double(withMinimumValue: 0, maximumValue: 1))
        
        return UIColor(red: r, green: g, blue: b, alpha: 1.0)
    }
    
    /**
     *  Returns the hex color code for this color.
     *
     *  @return The hex color code.
     */
    @objc public func hexString() -> String {
        
        var red: CGFloat = 0
        var green: CGFloat = 0
        var blue: CGFloat = 0
        var alpha: CGFloat = 0
        
        self.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
        
        let r = Int(red * 255)
        let g = Int(green * 255)
        let b = Int(blue * 255)
        let a = Int(alpha * 255)
        
        return String(format: "%.2x%.2x%.2x%.2x", r, g, b, a)
    }
    
    /**
     *  Creates a `UIColor` object from a hex color code.
     *
     *  @param hexString The hex color code to parse. May begin with '#' or '0x'. The alpha channel is optional.
     *
     *  @return The resulting `UIColor` object.
     */
    @objc public convenience init?(hexString: String) {
        
        var string = hexString.trimmingCharacters(in: .whitespacesAndNewlines).lowercased()
        
        if string.count < 6 {
            return nil
        }
        
        //
        
        if (string.hasPrefix("#")) {
            string.removeFirst()
        } else if string.hasPrefix("0X") {
            string.removeFirst(2)
        }
        
        if string.count == 6 {
            string.append("FF")
        }
        
        if string.count != 8 {
            return nil
        }
        
        let ri = string.startIndex
        let gi = string.index(ri, offsetBy: 2)
        let bi = string.index(gi, offsetBy: 2)
        let ai = string.index(bi, offsetBy: 2)
        
        let sr = String(string[ri..<gi])
        let sg = String(string[gi..<bi])
        let sb = String(string[bi..<ai])
        let sa = String(string[ai...])
        
        guard let r = UInt8(sr, radix: 16) else { return nil }
        guard let g = UInt8(sg, radix: 16) else { return nil }
        guard let b = UInt8(sb, radix: 16) else { return nil }
        guard let a = UInt8(sa, radix: 16) else { return nil }
        
        self.init(red: CGFloat(r) / 255.0,
                  green: CGFloat(g) / 255.0,
                  blue: CGFloat(b) / 255.0,
                  alpha: CGFloat(a) / 255.0)
    }
    
    /**
     *  Returns the inverse of this color.
     *
     *  @return The inverse color.
     */
    @objc public func inverse() -> UIColor {
        
        var red: CGFloat = 0
        var green: CGFloat = 0
        var blue: CGFloat = 0
        var alpha: CGFloat = 0
        
        self.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
        return UIColor(red: 1.0 - red, green: 1.0 - green, blue: 1.0 - blue, alpha: alpha)
    }
}

