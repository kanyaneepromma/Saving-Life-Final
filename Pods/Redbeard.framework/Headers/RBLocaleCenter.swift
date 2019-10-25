//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import UIKit

/**
 *  Provides locality-specific serialisations and conversions - e.g. dates, numbers, currencies, etc.
 */
@objcMembers public class RBLocaleCenter : NSObject {
    
    fileprivate static let lockQueue = DispatchQueue(label: "RBLocaleCenter")
    
    /**
     *  The default date formatting style.
     */
    private(set) var defaultDateStyle: DateFormatter.Style = .none
    
    /**
     *  The default time formatting style.
     */
    private(set) var defaultTimeStyle: DateFormatter.Style = .none
    
    /**
     *  The default number formatting style.
     */
    private(set) var defaultNumberStyle: NumberFormatter.Style = .none
    
    
    private var dateFormatter: DateFormatter = DateFormatter()
    private var numberFormatter: NumberFormatter  = NumberFormatter()
    private var dateFormatterUniversalTime: DateFormatter = {
        let dateFormatter = DateFormatter()
        dateFormatter.timeZone = TimeZone(identifier: "UTC")!
        return dateFormatter
    }()
    
    /**
     *  The main locale center.
     */
    public static let main: RBLocaleCenter = RBLocaleCenter()
    
    private func setDefaultNumberStyle(_ defaultNumberStyle: NumberFormatter.Style) {
        if self.defaultNumberStyle != defaultNumberStyle {
            RBLocaleCenter.lockQueue.sync {
                self.defaultNumberStyle = defaultNumberStyle
            }
        }
    }
    
    private func setDefaultDateStyle(_ defaultDateStyle: DateFormatter.Style) {
        if self.defaultDateStyle != defaultDateStyle {
            RBLocaleCenter.lockQueue.sync {
                self.defaultDateStyle = defaultDateStyle
            }
        }
    }
    
    private func setDefaultTimeStyle(_ defaultTimeStyle: DateFormatter.Style) {
        if self.defaultTimeStyle != defaultTimeStyle {
            RBLocaleCenter.lockQueue.sync {
                self.defaultTimeStyle = defaultTimeStyle
            }
        }
    }
    
    /**
     *  Parses a string to retrieve a number.
     *
     *  @param numberString The string that contains a number.
     *
     *  @return The resulting `NSNumber` object or `nil`.
     */
    public func number(from numberString: String?) -> NSNumber? {
        return number(from: numberString, using: defaultNumberStyle)
    }
    
    /**
     *  Parses a string to retrieve a number.
     *
     *  @param numberString The string that contains a number.
     *  @param numberStyle  The formatting style to expect in the string.
     *
     *  @return The resulting `NSNumber` object or `nil`.
     */
    public func number(from numberString: String?, using numberStyle: NumberFormatter.Style) -> NSNumber? {
        
        if let string = numberString {
            
            var number: NSNumber?
            
            RBLocaleCenter.lockQueue.sync {
                numberFormatter.numberStyle = numberStyle
                number = numberFormatter.number(from: string)
            }
            
            return number
        }
        
        return nil
    }
    
    /**
     *  Formats a number to a string.
     *
     *  @param number The number to format.
     *
     *  @return The resulting formatted string.
     */
    public func string(from number: NSNumber) -> String {
        return string(from: number, using: self.defaultNumberStyle)
    }
    
    /**
     *  Formats a number to a string.
     *
     *  @param number      The number to format.
     *  @param numberStyle The formatting style to use.
     *
     *  @return The resulting formatted string.
     */
    public func string(from number: NSNumber, using numberStyle: NumberFormatter.Style) -> String {
        
        var string = ""
        
        RBLocaleCenter.lockQueue.sync {
            numberFormatter.numberStyle = numberStyle
            string = numberFormatter.string(from: number) ?? ""
        }
        
        return string
    }
    
    /**
     *  Parses a date from a string.
     *
     *  @param dateString    The string to parse.
     *  @param universalTime Whether the date is UTC.
     *
     *  @return The parsed `NSDate` object.
     */
    public func date(from dateString: String, universalTime: Bool) -> Date? {
        return date(from: dateString, usingDateStyle: defaultDateStyle, time: defaultTimeStyle, universalTime: universalTime)
    }
    
    /**
     *  Parses a date from a string.
     *
     *  @param dateString    The string to parse.
     *  @param dateStyle     The formatting style to expect for the date component of the string.
     *  @param timeStyle     The formatting style to expect for the time component of the string.
     *  @param universalTime Whether the date is UTC.
     *
     *  @return The parsed `Date` object.
     */
    public func date(from dateString: String, usingDateStyle dateStyle: DateFormatter.Style, time timeStyle: DateFormatter.Style, universalTime: Bool) -> Date? {
        
        var date: Date?
        
        RBLocaleCenter.lockQueue.sync {
            var dateFormatter: DateFormatter? = nil
            
            if universalTime {
                dateFormatter = dateFormatterUniversalTime
            }
            else {
                dateFormatter = self.dateFormatter
            }
            
            dateFormatter?.dateStyle = dateStyle
            dateFormatter?.timeStyle = timeStyle
            date = dateFormatter?.date(from: dateString)
        }
        
        return date
    }
    
    /**
     *  Formats an `Date` into a string.
     *
     *  @param date          The `NSDate` to format.
     *  @param universalTime Whether the date is UTC.
     *
     *  @return The formatted string value.
     */
    public func string(from date: Date, universalTime: Bool) -> String {
        return string(from: date, usingDateStyle: defaultDateStyle, time: defaultTimeStyle, universalTime: universalTime)
    }
    
    /**
     *  Formats an `Date` into a string.
     *
     *  @param date          The `Date` to format.
     *  @param dateStyle     The formatting style to use for the date component.
     *  @param timeStyle     The formatting style to use for the time component.
     *  @param universalTime Whether the date is UTC.
     *
     *  @return The formatted string value.
     */
    public func string(from date: Date?, usingDateStyle dateStyle: DateFormatter.Style, time timeStyle: DateFormatter.Style, universalTime: Bool) -> String {
        
        var dateString = ""
        
        RBLocaleCenter.lockQueue.sync {
            var dateFormatter: DateFormatter? = nil
            
            if universalTime {
                dateFormatter = dateFormatterUniversalTime
            }
            else {
                dateFormatter = self.dateFormatter
            }
            
            dateFormatter?.dateStyle = dateStyle
            dateFormatter?.timeStyle = timeStyle
            dateString = dateFormatter?.string(from: date ?? Date()) ?? ""
        }
        
        return dateString
    }
}


