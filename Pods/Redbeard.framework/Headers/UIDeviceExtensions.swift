//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import AudioToolbox

@objc public enum RBDeviceSizeProfile : Int {
    
    case unknown
    case small
    case medium
    case large
}

/**
 *  `UIDevice` extension methods.
 */
@objc public extension UIDevice {
    
    /**
     *  Determines whether the device is a simulator.
     */
    @objc public var isSimulator: Bool {
        
        #if !(TARGET_IPHONE_SIMULATOR)
            return true
        #endif
        
        return false
    }
    
    /**
     *  Make the device vibrate (if it is possible).
     */
    @objc public func vibrate() {
        #if !(TARGET_IPHONE_SIMULATOR)
            AudioServicesPlaySystemSound(kSystemSoundID_Vibrate)
        #endif
    }
    
    /**
     *  Determines whether or not the system version is equal to the version given.
     *
     *  @param systemVersion The version to compare to the actual system version.
     *
     *  @return Whether or not the system version is equal to the version given.
     */
    @objc public func systemVersionIsEqual(to systemVersion: String) -> Bool {
        return self.systemVersion.compare(systemVersion, options: .numeric, range: nil, locale: NSLocale.current) == ComparisonResult.orderedSame
    }
    
    /**
     *  Determines whether or not the system version is greater than the version given.
     *
     *  @param systemVersion The version to compare to the actual system version.
     *
     *  @return Whether or not the system version is greater than the version given.
     */
    @objc public func systemVersionIsGreaterThan(_ systemVersion: String) -> Bool {
        return self.systemVersion.compare(systemVersion, options: .numeric, range: nil, locale:NSLocale.current) == ComparisonResult.orderedDescending
    }
    
    /**
     *  Determines whether or not the system version is greater than or equal to the version given.
     *
     *  @param systemVersion The version to compare to the actual system version.
     *
     *  @return Whether or not the system version is greater than or equal to the version given.
     */
    @objc public func systemVersionIsGreaterThanOrEqual(to systemVersion: String) -> Bool {
       return self.systemVersion.compare(systemVersion, options: .numeric, range: nil, locale: NSLocale.current) != ComparisonResult.orderedAscending
    }
    
    /**
     *  Determines whether or not the system version is less than the version given.
     *
     *  @param systemVersion The version to compare to the actual system version.
     *
     *  @return Whether or not the system version is less than the version given.
     */
    @objc public func systemVersionIsLessThan(_ systemVersion: String) -> Bool {
       return self.systemVersion.compare(systemVersion, options: .numeric, range: nil, locale: NSLocale.current) == ComparisonResult.orderedAscending
    }
    
    /**
     *  Determines whether or not the system version is less than or equal to the version given.
     *
     *  @param systemVersion The version to compare to the actual system version.
     *
     *  @return Whether or not the system version is less than or equal to the version given.
     */
    @objc public func systemVersionIsLessThanOrEqual(to systemVersion: String) -> Bool {
        return self.systemVersion.compare(systemVersion, options: .numeric, range: nil, locale: NSLocale.current) != ComparisonResult.orderedDescending

    }
    
    /**
     *  Make the device emit the keyboard click sound (if it is possible).
     */
    @objc public func keyboardClickSound() {
        playInputClick()
    }
    
    @objc public var modelName: String {
        var systemInfo = utsname()
        uname(&systemInfo)
        
        let machineMirror = Mirror(reflecting: systemInfo.machine)
        let identifier = machineMirror.children.reduce("") { identifier, element in
            guard let value = element.value as? Int8, value != 0 else { return identifier }
            return identifier + String(UnicodeScalar(UInt8(value)))
        }
        
        return identifier
    }
    
    @objc public var sizeProfile: RBDeviceSizeProfile {
        
        switch self.userInterfaceIdiom {
        case .phone:
            
            switch UIScreen.main.nativeBounds.height {
            case 0...1599:
                return .small
            case 1600...2199:
                return .medium
            case 2200...9999:
                return .large
            default:
                return .unknown
            }
            
        case .pad:
            
            switch UIScreen.main.nativeBounds.height {
            case 0...1599:
                return .small
            case 1600...2199:
                return .medium
            case 2200...9999:
                return .large
            default:
                return .unknown
            }
        
        default:
            return .unknown
        }
    }
}

