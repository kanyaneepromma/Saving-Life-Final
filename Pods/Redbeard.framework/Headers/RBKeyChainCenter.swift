//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

/**
 *  Provides access to the key chain.
 */
@objcMembers public class RBKeyChainCenter {
    
    /**
     *  Updates or creates the account with the given name using the given raw data.
     *
     *  @param account The name of the account to create or update.
     *  @param data    The data to associate with the account.
     *
     *  @return Whether or not the operation was successful.
     */
    public class func addOrUpdateAccount(_ account: String, with data: Data) -> Bool {
        
        if RBKeyChainCenter.accountExists(account) {
            
            var query = [AnyHashable: Any](minimumCapacity: 5)
            query[kSecClass as String] = kSecClassGenericPassword as Any    // Generic passwords
            query[kSecAttrAccount as String] = account                      // Account
            
            var update = [AnyHashable: Any](minimumCapacity: 5)
            update[kSecValueData as String] = data // New data
            
            let status: OSStatus = SecItemUpdate(query as CFDictionary, update as CFDictionary)
            
            if status == errSecSuccess {
                return true
            }
            
            self.printStatus(status)
        }
        else { // Insert
            
            var query = [AnyHashable: Any](minimumCapacity: 5)
            query[kSecClass as String] = kSecClassGenericPassword as Any    // Passwords
            query[kSecAttrAccount as String] = account                      // Account
            
            // Get dictionary of attributes back
            query[kSecReturnAttributes as String] = kCFBooleanTrue as Any
            
            // Only allow on this device AND when unlocked, TODO:// add this as param
            query[kSecAttrAccessible as String] = kSecAttrAccessibleWhenUnlockedThisDeviceOnly as Any
           
            query[kSecValueData as String] = data // Actual data stored here
            
            var queryResult: AnyObject?
            
            let status = withUnsafeMutablePointer(to: &queryResult) {
                SecItemAdd(query as CFDictionary, UnsafeMutablePointer($0))
            }
            
            if status == errSecSuccess {
                return true
            }
            
            self.printStatus(status)
        }
        
        return false
    }
    
    /**
     *  Checks whether or not an account exists with the given name.
     *
     *  @param account The name of the account to check exists.
     *
     *  @return Whether or not the account was found.
     */
    public class func accountExists(_ account: String) -> Bool {
        
        var query = [AnyHashable: Any](minimumCapacity: 5)
        
        query[kSecClass as String] = kSecClassGenericPassword as Any        //Generic passwords
        query[kSecReturnData as String] = kCFBooleanTrue as Any             //get data back
        query[kSecAttrAccount as String] = account                          // Account
        
        var queryResult: AnyObject?
        let status = withUnsafeMutablePointer(to: &queryResult) {
            SecItemCopyMatching(query as CFDictionary, UnsafeMutablePointer($0))
        }
        
        if status == errSecSuccess {
            return true
        }
        else if status == errSecItemNotFound {
            return false
        }
        
        self.printStatus(status)
        return false
    }
    
    /**
     *  Deletes an account with the given name.
     *
     *  @param account The name of the account to delete.
     *
     *  @return Whether or not the operation was successful.
     */
    public class func deleteAccount(_ account: String) -> Bool {
        
        var query = [AnyHashable: Any](minimumCapacity: 5)
        
        query[kSecClass as String] = kSecClassGenericPassword as Any            // Generic passwords
        query[kSecReturnData as String] = kCFBooleanTrue as Any                 // Get data back
        query[kSecAttrAccount as String] = account                              // Account
        
        let status: OSStatus = SecItemDelete(query as CFDictionary)
        
        if status == errSecSuccess {
            return true
        }
        
        self.printStatus(status)
        
        return false
    }
    
    /**
     *  Retrieves all of the available key chain accounts.
     *
     *  @return An array of account `Dictionary` objects.
     */
    public class func getAllAccounts() -> [Any]? {
        
        var query = [AnyHashable: Any](minimumCapacity: 5)
        
        query[kSecClass as String] = kSecClassGenericPassword as Any            // Generic passwords
        query[kSecMatchLimit as String] = kSecMatchLimitAll as Any              // Get all matches as array
        query[kSecReturnAttributes as String] = kCFBooleanTrue as Any           // Get dictionary of attributes back
        
        var queryResult: AnyObject?
        let status = withUnsafeMutablePointer(to: &queryResult) {
            SecItemCopyMatching(query as CFDictionary, UnsafeMutablePointer($0))
        }
        
        if status == errSecSuccess {
            return queryResult as? [Any]
        }
        
        self.printStatus(status)
        return nil
    }
    
    /**
     *  Retrieves the key chain account with the given name.
     *
     *  @param account The name of the account to retrieve.
     *
     *  @return The account `NSDictionary`, or `nil` if the account was not found.
     */
    public class func getAccount(_ account: String) -> [AnyHashable: Any]? {
        
        var query = [AnyHashable: Any](minimumCapacity: 5)
        
        query[kSecClass as String] = kSecClassGenericPassword as Any            // Generic passwords
        query[kSecReturnAttributes as String] = kCFBooleanTrue as Any           // Get dictionary of attributes back
        query[kSecAttrAccount as String] = account                              // Account
       
        var queryResult: AnyObject?
        let status = withUnsafeMutablePointer(to: &queryResult) {
            SecItemCopyMatching(query as CFDictionary, UnsafeMutablePointer($0))
        }
        
        if status == errSecSuccess {
            return queryResult as? [AnyHashable: Any]
        }
        
        self.printStatus(status)
        
        return nil
    }
    
    /**
     *  Retrieves the raw data for the account with the given name.
     *
     *  @param account The name of the account for which to retrieve the data.
     *
     *  @return The raw data of the account, or `nil` if the account was not found.
     */
    public class func getAccountData(_ account: String) -> Data? {
        
        var query = [AnyHashable: Any](minimumCapacity: 5)
        
        query[kSecClass as String] = kSecClassGenericPassword as Any            // Generic passwords
        query[kSecReturnData as String] = kCFBooleanTrue as Any                 // Get data back
        query[kSecAttrAccount as String] = account                              // Account
        
        var queryResult: AnyObject?
        let status = withUnsafeMutablePointer(to: &queryResult) {
            SecItemCopyMatching(query as CFDictionary, UnsafeMutablePointer($0))
        }
        
        if status == errSecSuccess {
            if let item = queryResult as? [AnyHashable : AnyObject] {
                return item[kSecValueData as String] as? Data
            }
        }
        
        self.printStatus(status)
        
        return nil
    }
    
    /**
     *  Deletes all of the key chain accounts.
     *
     *  @return Whether or not the operation was successful.
     */
    public class func deleteAllAccounts() -> Bool {
        
        let accounts = self.getAllAccounts() ?? [Any]()
        
        for account in accounts {
            if let account = account as? [AnyHashable: Any], let accountName = account["acct"] as? String {
                _ = self.deleteAccount(accountName)
            }
        }
        
        return true
    }
    
    /**
     *  Prints the given status value to the console.
     *
     *  @param status The status value to print.
     */
    class func printStatus(_ status: OSStatus) {
        switch status {
            case errSecAllocate:
                print("KEYCHAIN ERROR: Failed to allocate memory!")
            case errSecAuthFailed:
                print("KEYCHAIN: Auth failed!")
            case errSecDecode:
                print("KEYCHAIN ERROR: Unable to decode provided data!")
            case errSecDuplicateItem:
                print("KEYCHAIN: Duplicate item!")
            case errSecInteractionNotAllowed:
                print("KEYCHAIN: User interaction with security server not allowed!")
            case errSecItemNotFound:
                print("KEYCHAIN: Item not found!")
            case errSecNotAvailable:
                print("KEYCHAIN: No keychain is available!")
            case errSecParam:
                print("KEYCHAIN ERROR: One or more parameters passed were invalid!")
            case errSecSuccess:
                print("KEYCHAIN: Success!")
            case errSecUnimplemented:
                print("KEYCHAIN ERROR: Function or operation not implemented!")
            default:
                print("KEYCHAIN: Unknown error code!")
        }
    }
}
