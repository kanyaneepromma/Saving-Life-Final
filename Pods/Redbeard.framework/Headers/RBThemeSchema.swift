//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

import Foundation

/**
 *  The native types that are supported as theme property values.
*/
 @objc public enum RBThemeNativeType : Int {
    /**
     *  An integer value.
     */
    case integer
    /**
     *  A decimal number.
     */
    case decimal
    /**
     *  A percentage decimal.
     */
    case decimalPercentage
    /**
     *  A boolean value.
     */
    case boolean
}

@objcMembers public class RBThemeSchema : NSObject {
    
    var typeName = ""
    
    var typeIsEnum = false
    var enumValues = [String]()
    
    var typeClass: AnyClass?
    
    var notes = [String]()
    var states = [RBThemeSchemaState]()
    
    weak var parentSchema: RBThemeSchema?
    public var fields = [String: RBThemeSchema]()
    
    class func getClassList() -> [AnyClass] {
        
        let expectedClassCount = objc_getClassList(nil, 0)
        let allClasses = UnsafeMutablePointer<AnyClass?>.allocate(capacity: Int(expectedClassCount))
        let autoreleasingAllClasses = AutoreleasingUnsafeMutablePointer<AnyClass>(allClasses)
        let actualClassCount:Int32 = objc_getClassList(autoreleasingAllClasses, expectedClassCount)
        
        var classes = [AnyClass]()
        for i in 0 ..< actualClassCount {
            if let currentClass: AnyClass = allClasses[Int(i)] {
                classes.append(currentClass)
            }
        }
        
        allClasses.deallocate()
        return classes
    }
    
    public class func allTypesWithSchemas() -> [AnyClass] {
        
        var classes = [AnyClass]()
        let allClasses = RBThemeSchema.getClassList()
        
        for c in allClasses {
            if let method = class_getClassMethod(c, Selector("generateThemeSchemaWithParent:")) {
                classes.append(c)
            }
        }
        
        let types = classes.filter({ (objClass) -> Bool in
            
            let typeName = NSStringFromClass(objClass)
            
            if typeName.hasPrefix("Redbeard.RB") || typeName.hasPrefix("RB") {
                return true
            }
            
            switch typeName {
            case "UIView", "UIViewController", "UILabel", "UIButton", "UISwitch":
                return true
            default:
                return false
            }
        })
        
        return types
    }

    public class func trees(forTypes types: [AnyClass]) throws -> [[String: Any]] {
        
        var map = [String: AnyClass]()
        var typeSchemas = [[String: Any]]()
        
        let queue = RBProcessingQueue()
        for c in types {
            let n = NSStringFromClass(c)
            
            map[n] = c
            queue.enqueueItem(n)
        }
        
        while queue.pendingItems.count > 0 {
            
            let name = queue.pendingItems.first as! String
            let type: AnyClass = map[name]!
            
            if !type.responds(to: Selector("generateThemeSchemaWithParent:")) {
                throw RBError.compliance(reason: "Attempted to generate schema for `\(name)` which does not respond to generateThemeSchemaWithParent:")
            }
            
            let themeSchema = type.generateThemeSchema(withParent: nil)
            typeSchemas.append(themeSchema.dictionary())
            
            let typeLinks = themeSchema.typeLinks()
            
            for linkClass in typeLinks {
                let n = NSStringFromClass(linkClass)
                
                map[n] = linkClass
                queue.enqueueItem(n)
            }
            
            queue.markItem(name, asProcessed: true)
        }
        
        print("TYPES: \(queue.items)")
        return typeSchemas
    }
    
    public init(typeClass: AnyClass, withParentSchema parentSchema: RBThemeSchema?) {
        super.init()
        
        self.typeClass = typeClass
        typeName = NSStringFromClass(typeClass)
        self.parentSchema = parentSchema
    }
    
    public init(nativeType: RBThemeNativeType, withParentSchema parentSchema: RBThemeSchema?) {
        super.init()
        
        typeName = "\(nativeType)"
        self.parentSchema = parentSchema
    }
    
    public init(typeName: String, withParentSchema parentSchema: RBThemeSchema?) {
        super.init()
        
        self.typeName = typeName
        self.parentSchema = parentSchema
    }
    
    public init(enumTypeName: String, withParentSchema parentSchema: RBThemeSchema?) {
        super.init()
        
        typeIsEnum = true
        typeClass = String.self as? AnyClass
        typeName = enumTypeName
        self.parentSchema = parentSchema
        
        guard let set = RBEnum.strings(forEnumerationType: typeName), set.count > 0 else {
            fatalError("Enumeration \(typeName) does not have a defined string mapping.")
        }
        
        for s in set {
            enumValues.append(s.description)
        }
    }
    
    public init(enumTypeName: String, enumValues: [String], withParentSchema parentSchema: RBThemeSchema?) {
        super.init()
        
        typeIsEnum = true
        typeClass = String.self as? AnyClass
        typeName = enumTypeName
        self.parentSchema = parentSchema

        self.enumValues = enumValues
    }
    
    public override init() {
        super.init()
    }
    
    public func importSchema(_ themeSchema: RBThemeSchema) {
        self.notes.append(contentsOf: themeSchema.notes)
        self.states.append(contentsOf: themeSchema.states)
        self.fields.merge(themeSchema.fields) { (current, _) -> RBThemeSchema in
            current
        }
    }
    
    public func importProperties(_ properties: [String], from themeSchema: RBThemeSchema) {
        for property in properties {
            if let schema = themeSchema.fields[property] {
                setPropertyWithName(property, schema: schema)
            }
        }
    }
    
    public func addNote(_ noteString: String) {
        
        if noteString.count > 0 {
            self.notes.append(noteString)
        }
    }
    
    public func add(_ state: RBThemeSchemaState) {
        self.states.append(state)
    }
    
    func typeIsAncestor(_ type: AnyClass) -> Bool {
        
        if let c = self.typeClass {
            if c.isSubclass(of: type) { return true }
        }
        
        if let s = self.parentSchema {
            if s.typeIsAncestor(type) { return true }
        }
        
        return false
    }
    
    @discardableResult
    public func setPropertyWithName(_ propertyName: String, schema themeSchema: RBThemeSchema) -> RBThemeSchema? {
        
        if propertyName.count == 0 {
            return nil
        }
        
        self.fields[propertyName] = themeSchema
        return themeSchema
    }
    
    @discardableResult
    public func setPropertyWithName(_ propertyName: String, type: AnyClass, notes: String?) -> RBThemeSchema? {
        
        if type.responds(to: Selector("generateThemeSchemaWithParent:")) {
            if typeIsAncestor(type) {
                // Recursion protection - abort.
                if type == UIView.self {
                    return setPropertyWithName(propertyName, typeName: NSStringFromClass(type), notes: notes)
                }
                return nil
            }
            // RBThemeSchema *themeSchema = [type generateThemeSchemaWithParent:self];
            let themeSchema = RBThemeSchema(typeClass: type, withParentSchema: self)
            // Note: This is a link with additional properties added.
            if let n = notes { themeSchema.addNote(n) }
            return setPropertyWithName(propertyName, schema: themeSchema)
        }
        else {
            if type == UIColor.self {
                setPropertyWithName("\(propertyName)Alpha", nativeType: RBThemeNativeType.decimalPercentage, notes: "The alpha channel of the color.")
            }
            else if type == UIImage.self {
                setPropertyWithName("\(propertyName)TintColor", typeName: NSStringFromClass(UIColor.self), notes: "The tint color of the image.")
            }
            return setPropertyWithName(propertyName, typeName: NSStringFromClass(type), notes: notes)
        }
    }
    
    @discardableResult
    public func setPropertyWithName(_ propertyName: String, nativeType: RBThemeNativeType, notes: String?) -> RBThemeSchema? {
        let typeName = "\(nativeType)"
        return setPropertyWithName(propertyName, typeName: typeName, notes: notes)
    }
    
    @discardableResult
    public func setPropertyWithName(_ propertyName: String, typeName: String, notes: String?) -> RBThemeSchema? {
        let themeSchema = RBThemeSchema(typeName: typeName, withParentSchema: self)
        if let n = notes { themeSchema.addNote(n) }
        return setPropertyWithName(propertyName, schema: themeSchema)
    }
    
    @discardableResult
    public func setEnumPropertyWithName(_ propertyName: String, enumerationTypeName: String, notes: String?) -> RBThemeSchema? {
        let themeSchema = RBThemeSchema(enumTypeName: enumerationTypeName, withParentSchema: self)
        if let n = notes { themeSchema.addNote(n) }
        return setPropertyWithName(propertyName, schema: themeSchema)
    }
    
    @discardableResult
    public func setEnumPropertyWithName(_ propertyName: String, enumerationTypeName: String, enumValues: [String], notes: String?) -> RBThemeSchema? {
        let themeSchema = RBThemeSchema(enumTypeName: enumerationTypeName, enumValues: enumValues, withParentSchema: self)
        if let n = notes { themeSchema.addNote(n) }
        return setPropertyWithName(propertyName, schema: themeSchema)
    }
    
    public func removeState(withName stateName: String) {
        
        if stateName.count == 0 {
            return
        }
        
        if self.states.isEmpty {
            return
        }
        
        for i in 0..<self.states.count {
            
            let state = self.states[i]
            if state.name == stateName {
                self.states.remove(at: i)
                break
            }
        }
    }
    
    public func removeProperty(withName propertyName: String) {
        
        if propertyName.count == 0 {
            return
        }
        
        if self.fields.isEmpty {
            return
        }
        
        if self.fields[propertyName] != nil {
            self.fields.removeValue(forKey: propertyName)
        }
    }
    
     public func removeAllNotes() {
        self.notes.removeAll()
    }
    
    public func removeAllStates() {
        self.states.removeAll()
    }
    
    public func removeAllProperties() {
        self.fields.removeAll()
    }
    
    public func dictionary() -> [String: Any] {
        
        var schemaPropertyList = [String: Any]()
        schemaPropertyList["type"] = RBThemeSchema.removeModuleName(typeName)
        
        if let schema = parentSchema {
            schemaPropertyList["parentType"] = RBThemeSchema.removeModuleName(schema.typeName)
        } else {
            if let value = typeClass?.superclass() {
                schemaPropertyList["parentType"] = RBThemeSchema.removeModuleName(NSStringFromClass(value))
            }
        }
        
        if self.notes.count > 0 {
            schemaPropertyList["notes"] = self.notes
        }
        
        if self.states.count > 0 {
            
            var sink = [[String : Any]]()
            
            for state in self.states {
                sink.append(state.dictionary())
            }
            
            schemaPropertyList["states"] = sink
        }
        
        if self.fields.count > 0 {
            
            var sink = [String : [String : Any]]()
            
            for (name, field) in self.fields {
                sink[name] = field.dictionary()
            }
            
            schemaPropertyList["properties"] = sink
        }
        
        if self.typeIsEnum {
            schemaPropertyList["enumerationValues"] = enumValues
        }
        
        return schemaPropertyList
    }
    
    func typeLinks() -> [AnyClass] {
        
        var types = [AnyClass]()
        var classes = [String: AnyClass]()
        
        if let value = typeClass {
            if value.instancesRespond(to: Selector("generateThemeSchemaWithParent:")) {
                let name = NSStringFromClass(value)
                classes[name] = value
                types.append(value)
            }
        }
        
        for (_, schema) in self.fields {
            let t = schema.typeLinks()
            for value in t {
                let name = NSStringFromClass(value)
                if classes[name] != nil {
                    types.append(value)
                }
            }
        }
        
        return types
    }
    
    class func removeModuleName(_ typeName: String) -> String {
        
        var name = typeName
        
        if let dot = name.lastIndex(of: ".") {
            let index = name.index(dot, offsetBy: 1)
            name = String(name[index...])
        }
        
        let charactersToRemove = CharacterSet.alphanumerics.inverted
        return name.components(separatedBy: charactersToRemove).joined(separator: "")
    }
}


