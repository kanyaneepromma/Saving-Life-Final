//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import Foundation
/*
public extension Data {
    
    public func utf8StringValue() -> String {
        let retval = String(data: self, encoding: .utf8)
        return retval ?? ""
    }
}

public extension Array {
    
    public func contains<T>(obj: T) -> Bool where T : Equatable {
        return self.filter({$0 as? T == obj}).count > 0
    }
    
    /**
     * Runs a binary search on the `Array` to find the range that matches according to `matchBlock`.
     * It assumes that the `Array` is sorted and the matching elements are contiguous.
     *
     * @param startIndex The initial start index of the matching range. Must be initialized, the default should be 0.
     * @param finalIndex The initial end index of the matching range. Must be initialized, the default should be `count` - 1.
     * @param matchBlock The block used to determine the `RBBinarySearchResult` match for a given element.
     
     * @return Whether or not the binary search was successful and if so the result indexes.
     */
    public func binarySearch(startIndex: Int, endIndex: Int, matchBlock: @escaping (_ obj: Any) -> RBBinarySearchResult) -> (success: Bool, startIndex: Int, endIndex: Int) {
        
        var first = startIndex
        var last = endIndex
        
        while last >= first {
            
            let imid = first + ((last - first) / 2)
            let res = matchBlock(self[imid])
            
            if res == RBBinarySearchResult.lessThan {
                first = imid + 1
            } else if res == RBBinarySearchResult.greaterThan {
                if imid > 0 {
                    last = imid - 1
                } else {
                    break // Not found
                }
            } else if res == RBBinarySearchResult.match {
                
                // We found a match!
                first = imid
                last = imid
                
                // Work Backwards
                var i = first - 1
                while i >= 0 && i < count {
                    
                    if matchBlock(self[i]) != RBBinarySearchResult.match {
                        break
                    }
                    
                    first = i
                    
                    if i == 0 {
                        break
                    }
                    
                    i -= 1
                }
                
                // Work Forwards
                
                for idx in last + 1..<count {
                    
                    if matchBlock(self[idx]) != RBBinarySearchResult.match {
                        break
                    }
                    
                    last = idx
                }
                
                //
                
                return (success: true, startIndex: first, endIndex: last)
            }
        }
        
        //
        
        return (success: false, startIndex: NSNotFound, endIndex: NSNotFound)
    }

    
    public mutating func popLastObject() -> Any? {
        if count > 0 {
            let index: Int = self.count - 1
            let obj = self[index]
            remove(at: index)
            return obj
        }
        return nil
    }
    
    public func arrayWithItems(matching matchBlock: @escaping (_ obj: Any?) -> Bool?) -> [Any] {
        if matchBlock != nil {
            var matches = [AnyHashable]()
            for obj: Any? in self {
                if matchBlock(obj)! {
                    if let anObj = obj {
                        matches.append(anObj as! AnyHashable)
                    }
                }
            }
            return matches
        }
        return [Any]()
    }
    
    var firstObject: Any? {
        if self.count > 0 {
            return self[0]
        }
        return nil
    }
    
    public func stringByCombiningComponents(withSeparator separator: String) -> String {
        var s = ""
        let a = self
        for i in 0..<a.count {
            if i > 0 {
                s += "\(separator)\((a[i] as AnyObject).description)"
            }
            else {
                s += (a[i] as AnyObject).description
            }
        }
        return s
    }
    public func arrayExcludingObjects(_ excludingObjects: [AnyObject]) -> [AnyObject] {
        var rv = self as [AnyObject]
        for obj: AnyObject in self as [AnyObject] {
            if excludingObjects.contains(where: {$0 === obj}) {
                while let elementIndex = rv.index(where: {$0 === obj}) {
                    rv.remove(at: elementIndex)
                }
            }
        }
        return rv
    }
    
    /**
     * Adds the elements of self to a new `NSArray` performing `transformBlock` on each element.
     * Nil results from `transformBlock` results in the item not being added.
     *
     * @param transformBlock The block to run on each element before adding to the new `NSArray`.
     * @return The new `NSArray` containing the transformed elements.
     * @warning `transformBlock` must not be `nil`!
     */
    public func arrayByTransformingElements(withBlock transformBlock: (_ index: Int, _ value: Any) -> Any?) -> [Any?] {
        var array = [Any?]()
        
        for i in 0..<count {
            if let modifiedValue = transformBlock(i, self[i]) {
                array.append(modifiedValue)
            }
        }
        return array
    }

    
    public func copy(with zone: NSZone? = nil) -> Any
    {
        return type(of:self).init(self)
    }
    
    /**
     * Gets a random element of the `NSArray`, or `nil` if the `NSArray` is empty.
     *
     * @return A random element of the `NSArray` or nil.
     */
    public func randomObject() -> Any? {
        return count > 0 ? self[Int(RBRandom.unsignedInteger(withMinimumValue: 0, maximumValue: UInt32((count - 1))))] : nil
    }
}
/*
extension NSArray {
    func index(inRange index: Int) -> Bool {
        return index < count
    }
    
    func arrayByTransformingElements(withBlock transformBlock: @escaping (_ index: Int, _ value: Any) -> Any?) -> [Any] {
        var array = [AnyHashable]()
        for i in 0..<count {
            let value = self[i]
            let modifiedValue = transformBlock(i, value)
            if modifiedValue != nil {
                array.append(modifiedValue! as! AnyHashable)
            }
        }
        return array
    }
    open func stringByCombiningComponents(withSeparator separator: String) -> String {
        var s = ""
        let a = self
        for i in 0..<a.count {
            if i > 0 {
                s += "\(separator)\((a[i] as AnyObject).description)"
            }
            else {
                s += (a[i] as AnyObject).description
            }
        }
        return s
    }
    
    
    //    func transformElements(withBlock transformBlock: @escaping (_ index: Int, _ value: Any) -> Any) {
    //        for i in 0..<count {
    //            let transformedValue = transformBlock(i, self[i]) as? Any
    //            if transformedValue != nil {
    //                self[i] = transformedValue
    //            }
    //            else {
    //                remove(at: i)
    //                i -= 1
    //            }
    //        }
    //    }
}

extension NSMutableArray {
    func transformElements(withBlock transformBlock: @escaping (_ index: Int, _ value: Any) -> Any) {
        for var i in 0..<count {
            let transformedValue = transformBlock(i, self[i]) as? Any
            if transformedValue != nil {
                self[i] = transformedValue!
            }
            else {
                remove(i)
                i -= 1
            }
        }
    }
}
*/

extension NSObject {
    func isEqual<T: Equatable>(type: T.Type, a: Any, b: Any) -> Bool? {
        guard let a = a as? T, let b = b as? T else { return nil }
        
        return a == b
    }
    /*
    class func selectorBelongs(toProtocol selector: Selector, `protocol`: `Protocol`) -> Bool {
        for optionbits in 0..<(1 << 2) {
            let `required` = Bool((optionbits & 1))
            let instance = Bool(!optionbits & (1 << 1))
            
            let hasMethod: objc_method_description = protocol_getMethodDescription(`protocol`, selector, `required`, instance)
            if hasMethod.name || hasMethod.types {
                return true
            }
        }
        return false
    }
 */
}

public extension Dictionary {
    public func allKeys() -> [Any] {
        var keysList = [Any]()
        for key in self {
            keysList.append(key.key)
        }
        return keysList
    }
    
    
    /**
     *  Applies the given transformation block on each value.
     *  Nil values returned by `transformBlock` result in removal.
     *
     *  @param transformBlock The block to execute on each element of the dictionary. Returning `nil` from the block results in the key-value being removed.
     */
    public mutating func transformValues(withBlock transformBlock: @escaping (_ key: String, _ value: Any) -> Any?) {
        let keys = self.allKeys()
        for key in keys {
            let transformedValue = transformBlock(key as! String, self[key as! Key]!)
            if transformedValue != nil {
                self[key as! Key] = (transformedValue as! Value)
            }
            else {
                self.removeValue(forKey: key as! Key)
            }
        }
    }
    
    /**
     * Creates a new `NSDictionary` object by copying respectively the contents of
     * `dictionaryA` and then `dictionaryB`.
     *
     * @param dictionaryA The first `NSDictionary` to copy.
     * @param dictionaryB The second `NSDictionary` to copy.
     * @return The merged `NSDictionary`.
     */
    public static func dictionary(byMergingDictionary dictionaryA: [AnyHashable: Any]?, withDictionary dictionaryB: [AnyHashable: Any]?) -> [AnyHashable: Any]? {
        if ((dictionaryA?.count) != nil) && ((dictionaryB?.count) != nil) {
            return dictionaryA?.mergedDictionary(withDictionary: dictionaryB!)
        }
        else if dictionaryA?.count != nil {
            return dictionaryA
        }
        else if dictionaryB?.count != nil {
            return dictionaryB
        }
        return nil
    }
    
    
    /**
     * Creates a new `NSDictionary` object by copying respectively the contents of
     * this `NSDictionary` and then the given `NSDictionary`.
     *
     * @param dictionary The `NSDictionary` to copy.
     * @return The merged `NSDictionary`.
     */
    // Dictionary given takes priority.
    public func mergedDictionary(withDictionary dictionary: [AnyHashable: Any]) -> [AnyHashable: Any] {
        var dictionary: [Key: Value] = dictionary as! [Key: Value]
        var rv = self
        let existingKeys = keys
        for key in dictionary {
            if existingKeys.contains(where: {$0 == key.key}) {
                let obj = dictionary[key.key]
                if (obj is [AnyHashable: Any]) {
                    rv[key.key] = (rv[key.key] as! [AnyHashable: Any]).mergedDictionary(withDictionary: obj as! [AnyHashable : Any]) as? Value
                }
                else {
                    rv[key.key] = obj
                }
            }
            else {
                rv[key.key] = dictionary[key.key]
            }
        }
        return rv
    }
    
    public func allValue() -> [Any] {
        var allValues = [Any]()
        for dict in self {
            allValues.append(self[dict.key]!)
        }
        return allValues
    }
    
    // MARK: -
    // MARK: TRANSFORMS
    
    /**
     * Creates a new dictionary by using the given transformation block on each value.
     *
     * @param transformBlock The block to execute on each element of the dictionary. Returning `nil` from the block results in the key-value being removed.
     * @return The new dictionary with transformed elements.
     */
    public func dictionaryByTransformingValues(withBlock transformBlock: @escaping (_ key: String, _ value: Any) -> Any?) -> [AnyHashable: Any] {
        var dict = [AnyHashable: Any]()
        for key in self {
            let transformedValue = transformBlock(key.key as! String, self[key.key]!)
            if transformedValue != nil {
                dict[key.key as AnyHashable] = transformedValue!
            }
            else {
                dict.removeValue(forKey: key.key as AnyHashable)
            }
        }
        return dict
    }
    
    //    func value(forKey key: Any) -> Any {
    //        for (key,value) in self {
    //            if key == key {
    //                return value
    //            }
    //        }
    //    }
    
    
    
    
    
    /**
     * Creates a new `NSDictionary` object removing all `NSNull` values.
     *
     * @param recursive Whether to recursively do the same for all child `NSDictionary` and `NSArray` values.
     * @return The new `NSDictionary` with no `NSNull` values inside.
     */
    public func dictionary(withNullsRemovedRecursive recursive: Bool) -> [AnyHashable: Any] {
        var rv = [AnyHashable: Any]()
        
        for key in self {
            if let value = self[key.key], !(value is NSNull) {
                if (value is [AnyHashable: Any]) && recursive {
                    let value = value as! [AnyHashable: Any]
                    rv[key.key as AnyHashable] = value.dictionary(withNullsRemovedRecursive: true)
                }
                else {
                    rv[key.key as AnyHashable] = value
                }
            }
        }
        return rv
    }
    
    /**
     * Creates a new dictionary by transferring values from the given dictionary using
     * the given { source key: destination key } mapping.
     *
     * @param dictionary The source dictionary to read from.
     * @param mapping The { source key: destination key } mapping.
     * @return The new dictionary.
     */
    public init?(dictionary: [AnyHashable: Any], withMapping mapping: [AnyHashable: Any]) {
        let dict:NSMutableDictionary? = [AnyHashable:Any]() as? NSMutableDictionary
        dict?.transfer(from: dictionary, withMapping: mapping)
        guard dict != nil else {
            return nil
        }
        return nil
    }
    
    // MARK: -
    // MARK: ACCESSORS
    
    /**
     * Gets a random key from the `NSDictionary`.
     *
     * @return The randomly chosen key.
     */
    public func randomKey() -> String? {
        let keys = allKeys()
        let number = Int(arc4random_uniform(UInt32(keys.count)))
        return keys[number] as? String
    }
    
    /**
     * Gets a random value from the `NSDictionary`.
     *
     * @return The randomly chosen value.
     */
    public func randomValue() -> Any? {
        if let key = randomKey() {
            return self[key as! Key]
        }
        return nil
    }
    
    /**
     * Gets an `NSString` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func string(withKey key: String, withDefault def: String?) -> String? {
        if !string(withKey: key)!.isEmpty {
            return string(withKey: key)!
        }else {
            return def
        }
    }
    
    /**
     * Gets an `NSNumber` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func number(withKey key: String, withDefault def: NSNumber?) -> NSNumber? {
        let value = self[key as! Key]
        
        if (value is NSNull) {
            return nil
        }
        else if (value is NSNumber) {
            return value as? NSNumber
        }
        else if (value is String) {
            return RBLocaleCenter.main.number(from: value as? String)
        }
        
        return nil
    }
    
    /**
     * Gets an `NSString` value with the given key, or `nil` if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @return The retrieved value.
     */
    public func string(withKey key: String) -> String? {
        if let value = self[key as! Key], value is NSNull {
            return nil
        }
        
        if let value = self[key as! Key], value is String {
            return value as? String
        }
        else if let value = self[key as! Key], value is NSNumber {
            return "\((value as? String))"
        }
        return nil
    }
    
    /**
     * Gets a localized `NSString` value with the given key, or `nil` if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @return The retrieved value.
     */
    public func localizedString(withKey key: String) -> String? {
        let nameKey = "\(key)_Key"
        let commentKey = "\(key)_Comment"
        
        let name: String = self[nameKey as! Key].debugDescription
        let comment: String = self[commentKey as! Key].debugDescription
        
        return !name.isEmpty || !comment.isEmpty ? self[key as! Key] as? String : NSLocalizedString(name, comment: comment)
        
    }
    
    /**
     * Gets an enumeration value for the given enumeration type with the given key,
     * or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param enumType The name of the enumeration type to convert.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func enumNumber(withKey key: String, enumType: String, withDefault def: Int) -> Int {
        if !NSNull.objectIsNull(key as Any) && !NSNull.objectIsNull(enumType as Any) {
            if let value = self[key as! Key], value is NSNumber {
                return Int(truncating: value as! NSNumber)
            }
            else if let value = self[key as! Key], value is String {
                return RBEnum.value(with: value as! String, forEnumerationType: enumType)
            }
        }
        return def
    }
    
    /**
     * Gets an `NSNumber` value with the given key, or `nil` if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @return The retrieved value.
     */
    public func number(withKey key: String) -> NSNumber? {
        let value = self[key as! Key]
        if (value is NSNull) {
            return nil
        }
        else if (value is NSNumber) {
            return value as? NSNumber
        }
        else if (value is String) {
            return RBLocaleCenter.main.number(from: value as? String)
        }
        return nil
    }
    
    /**
     * Gets an `char` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func char(withKey key: String, withDefault def: Int8) -> Int8 {
        let number = self.number(withKey: key, withDefault: Int(def) as NSNumber)
        return number as! Int8? ?? 0
    }
    
    /**
     * Gets an `unsigned char` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func unsignedChar(withKey key: String, withDefault def: UInt8) -> UInt8 {
        let number = self.number(withKey: key, withDefault: Int(def) as NSNumber)
        return number as! UInt8? ?? 0
    }
    
    /**
     * Gets an `short` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func short(withKey key: String, withDefault def: Int16) -> Int16 {
        let number = self.number(withKey: key, withDefault: Int(def) as NSNumber)
        return number as! Int16? ?? 0
    }
    
    /**
     * Gets an `unsigned short` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func unsignedShort(withKey key: String, withDefault def: UInt16) -> UInt16 {
        let number = self.number(withKey: key, withDefault: Int(def) as NSNumber)
        return number as! UInt16? ?? 0
    }
    
    /**
     * Gets an `int` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func int(withKey key: String, withDefault def: Int) -> Int {
        let number = self.number(withKey: key, withDefault: def as NSNumber)
        return Int(truncating: number ?? 0)
    }
    
    /**
     * Gets an `unsigned int` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func unsignedInt(withKey key: String, withDefault def: UInt) -> UInt {
        let number = self.number(withKey: key, withDefault: Int(def) as NSNumber)
        return UInt(truncating: number ?? 0)
    }
    
    /**
     * Gets an `long` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func long(withKey key: String, withDefault def: Int) -> Int {
        let number = self.number(withKey: key, withDefault: def as NSNumber)
        return Int(truncating: number ?? 0)
    }
    
    /**
     * Gets an `unsigned long` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func unsignedLong(withKey key: String, withDefault def: UInt) -> UInt {
        let number = self.number(withKey: key, withDefault: Int(def) as NSNumber)
        return UInt(truncating: number ?? 0)
    }
    
    /**
     * Gets an `long long` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func longLong(withKey key: String, withDefault def: Int64) -> Int64 {
        let number = self.number(withKey: key, withDefault: def as NSNumber)
        return number as! Int64? ?? 0
    }
    
    /**
     * Gets an `unsigned long long` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func unsignedLongLong(withKey key: String, withDefault def: UInt64) -> UInt64 {
        let number = self.number(withKey: key, withDefault: def as NSNumber)
        return number as! UInt64? ?? 0
    }
    
    /**
     * Gets an `float` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func float(withKey key: String, withDefault def: Float) -> Float {
        let number = self.number(withKey: key, withDefault: def as NSNumber)
        return Float(truncating: number ?? 0.0)
    }
    
    /**
     * Gets an `double` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func double(key: String, withDefault def: Double) -> Double {
        let number = self.number(withKey: key, withDefault: def as NSNumber)
        return Double(truncating: number ?? 0.0)
    }
    
    /**
     * Gets an `BOOL` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func bool(withKey key: String, withDefault def: Bool) -> Bool {
        let number = self.number(withKey: key, withDefault: (def ? 1 : 0))
        return number != 0
    }
    
    /**
     * Gets an `NSInteger` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func integer(withKey key: String, withDefault def: Int) -> Int {
        let number = self.number(withKey: key, withDefault: def as NSNumber)
        return Int(truncating: number ?? 0)
    }
    
    /**
     * Gets an `NSUInteger` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func unsignedInteger(withKey key: String, withDefault def: Int) -> Int {
        let number = self.number(withKey: key, withDefault: Int(def) as NSNumber)
        return Int(truncating: (number ?? 0))
    }
    
    /**
     * Gets an `CGSize` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @return The retrieved value.
     */
    public func size(withKey key: String, withDefault def: CGSize) -> CGSize {
        let v = self[key as! Key]
        
        if (v is String) {
            return CGSizeFromString(v as! String)
        }
        
        if (v is [Any]) {
            let v = v as? [Int]
            return CGSize(width: CGFloat(Float(v![0])), height: CGFloat(Float(v![1])))
        }
        
        return def
    }
    
    /**
     * Gets an `NSDate` value with the given key, or the given default value if the value could not be retrieved.
     *
     * @param key The key to lookup the value with.
     * @param def The default value to return in the event of a retrieval failure.
     * @param interpretAsUniversalTime Whether the date being read is in the UTC timezone.
     * @return The retrieved value.
     */
    public func date(withKey key: String, withDefault def: Date?, interpretAsUniversalTime: Bool) -> Date? {
        if let v = self[key as! Key], v is String {
            return RBLocaleCenter.main.date(from: v as! String, universalTime: interpretAsUniversalTime)
        }
        return def
    }
    
    /**
     * Creates a new dictionary by copying the elements from this dictionary, overriding all
     * elements with the key postfix given.
     *
     * For example, if the postfix is "iPad", { "name": "iPhone", "name_iPad": "iPad" } will be merged to
     * { "name": "iPad", "name_iPad": "iPad" }, and if `removeOverridesAfterApply` then
     * { "name": "iPad" }
     *
     * @param priorityPostfix The key postfix to denote an override.
     * @param removeOverridesAfterApply Removes the override elements (those with the postfix) after merge.
     * @return The merged dictionary.
     *
     */
    // Merges the dictionary (self), recursively opting for those key/values with the given postfix, i.e. "_iPad"
    
    public func mergedDictionary(withPriorityPostfix priorityPostfix: String, removeOverridesAfterApply: Bool) -> [AnyHashable: Any] {
        var mergedDictionary = [AnyHashable: Any]()
        var processed = [AnyHashable]()
        
        for key in self {
            let key = key.key as! String
            var key_Generic: String? = nil
            var key_Priority: String? = nil
            
            if key.ends(with: priorityPostfix) {
                key_Generic = (key as NSString).substring(to: (key.count) - (priorityPostfix.count))
                key_Priority = key
            }
            else {
                key_Generic = key
                key_Priority = "\(key)\(priorityPostfix)"
            }
            
            if processed.contains(key_Generic!) {
                continue
            }
            processed.append(key_Generic!)
            
            let value = self[key_Generic  as! Key]
            let value_Priority = self[key_Priority  as! Key]
            if (value != nil) && !(value_Priority != nil) {
                if (value is [AnyHashable: Any]) {
                    let value = value as! NSDictionary
                    mergedDictionary[key_Generic!] = value.mergedDictionary(withPriorityPostfix: priorityPostfix, removeOverridesAfterApply: removeOverridesAfterApply)
                }
                else if (value is [Any]) {
                    let value = value as! NSArray
                    mergedDictionary[key_Generic!] = value.mergedArray(withPriorityPostfix: priorityPostfix, removeOverridesAfterApply: removeOverridesAfterApply)
                }
                else {
                    mergedDictionary[key_Generic!] = value
                }
            }
            else if !((value != nil) && (value_Priority != nil)) {
                if (value_Priority is [AnyHashable: Any]) {
                    let value_Priority = value_Priority as! NSDictionary
                    mergedDictionary[key_Generic!] = value_Priority.mergedDictionary(withPriorityPostfix: priorityPostfix, removeOverridesAfterApply: removeOverridesAfterApply)
                }
                else if (value_Priority is [Any]) {
                    let value_Priority = value_Priority as! NSArray
                    mergedDictionary[key_Generic!] = value_Priority.mergedArray(withPriorityPostfix: priorityPostfix, removeOverridesAfterApply: removeOverridesAfterApply)
                }
                else {
                    mergedDictionary[key_Generic!] = value_Priority
                }
            }
            else {
                //            NSAssert([value class] == [value_Priority class],
                //                     @"Error merging dictionaries, %@ (%@) and %@ (%@) are not of the same type!",
                //                     key_Generic, [value class], key_Priority, [value_Priority class]);
                if (value is [AnyHashable: Any]) {
                    let merged = NSDictionary()
                    merged.setValuesForKeys(value as? [String : Any] ?? [String : Any]())
                    merged.setValuesForKeys(value_Priority as? [String : Any] ?? [String : Any]())
                    // Convert to immutable if both sources are immutable.
                    if !(value is [AnyHashable: Any]) && !(value_Priority is [AnyHashable: Any]) {
                        //                        merged = merged
                    }
                    mergedDictionary[key_Generic!] = merged.mergedDictionary(withPriorityPostfix: priorityPostfix, removeOverridesAfterApply: removeOverridesAfterApply)
                }
                else if (value is [Any]) {
                    let value_Priority = value_Priority as! NSArray
                    mergedDictionary[key_Generic!] = value_Priority.mergedArray(withPriorityPostfix: priorityPostfix, removeOverridesAfterApply: removeOverridesAfterApply)
                }
                else if (value_Priority != nil) {
                    mergedDictionary[key_Generic!] = value_Priority
                }
            }
            if removeOverridesAfterApply {
                mergedDictionary.removeValue(forKey: key_Priority!)
            }
        }
        return mergedDictionary
    }
    
    /**
     * Creates a new `NSDictionary` object by copying respectively the contents of
     * each dictionary in the array `dictionaries`.
     *
     * @param dictionaries An `NSArray` of `NSDictionary` objects.
     * @return The merged `NSDictionary`.
     */
    public static func dictionary(byMergingDictionariesRespectively dictionaries: [[AnyHashable: Any]]) -> [AnyHashable: Any] {
        var mergedDictionary = [AnyHashable: Any]()
        
        for dictionary in dictionaries {
            if dictionary.count > 0 {
                mergedDictionary = Dictionary.dictionary(byMergingDictionary: mergedDictionary, withDictionary: dictionary)!
            }
        }
        return mergedDictionary
    }
    
    /**
     * Creates a new `NSDictionary` object by removing all keys that aren't
     * in the given array of keys.  This is done recursively to all child
     * `NSDictionary` objects too.
     *
     * @param onlyLeafKeys The keys to keep.
     * @return The new `NSDictionary`.
     */
    // Prunes all leaf keys (non-NSDictionary/NSArray values) except those specified.
    public func prunedDictionary(withOnlyLeafKeys onlyLeafKeys: [String]) -> [AnyHashable: Any] {
        var rv = [AnyHashable: Any]()
        
        for key in self {
            let obj = self[key.key]
            
            if (obj is [AnyHashable: Any]) {
                rv[key.key as AnyHashable] = (obj as! NSDictionary).prunedDictionary(withOnlyLeafKeys: onlyLeafKeys)
            }
            else if (obj is [Any]) {
                rv[key.key as AnyHashable] = (obj as! NSArray).prunedArray(withOnlyLeafKeys: onlyLeafKeys)
            }
            else if onlyLeafKeys.contains(key.key as! String) {
                rv[key.key as AnyHashable] = obj
            }
        }
        return rv
    }
    
}

public extension String {
    
    public func contains(_ str: String) -> Bool {
        return self.range(of: str)?.lowerBound.encodedOffset != NSNotFound
    }
//    public func urlStringByDeletingLastPathComponent() -> String {
//        let rangeOfDot = self.range(of: "/", options: .backwards)
//        if rangeOfDot.length != 0 {
//            return (self as? NSString)?.substring(to: Int(rangeOfDot.location) - 1)
//        }
//        return self
//    }
    
    public static func string(byRepeating string: String, numberOfTimes: Int, separator: String) -> String {
        var separator = separator
        var numberOfTimes = numberOfTimes
        if numberOfTimes < 1 {
            return ""
        }
        var s = string
        numberOfTimes -= 1
        if separator == "" {
            separator = ""
        }
        while numberOfTimes > 0 {
            s += "\(separator)\(string)"
            numberOfTimes -= 1
        }
        return s
    }

    
    public func lastComponent(withSeparator separatorCharacter: String) -> String {
        let separatorString = "\(separatorCharacter)"
        return (components(separatedBy: separatorString).last)!
    }
    
    public func utf8DecodedString()-> String {
        let data = self.data(using: .utf8)
        if let message = String(data: data!, encoding: .nonLossyASCII){
            return message
        }
        return ""
    }
    
    public func utf8EncodedString()-> String {
        let messageData = self.data(using: .nonLossyASCII)
        let text = String(data: messageData!, encoding: .utf8)
        return text!
    }
    
    public func utf8DataValue() -> Data {
        return data(using: .utf8) ?? Data()
    }
    
    public func copy(with zone: NSZone? = nil) -> Any
    {
        return type(of:self).init(self)
    }
}

extension DispatchIO {
    @available(swift, introduced: 4)
    public convenience init?(
        type: StreamType,
        path: UnsafePointer<Int8>,
        oflag: Int32,
        mode: mode_t,
        queue: DispatchQueue,
        cleanupHandler: @escaping (_ error: Int32) -> Void)
    {
        self.init(__type: type.rawValue, path: path, oflag: oflag, mode: mode, queue: queue, handler: cleanupHandler)
    }
}

extension Equatable {}
*/
