//
//  API.swift
//  Savinglife
//
//  Created by Kanyanee P on 23/1/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import Foundation
import Firebase
import GoogleSignIn

//API Estimote

struct API {
    static let Estimote_API_appID: String = "estimoteproject-5u3"
    static let Estimote_API_appToken: String = "837338f12ba2e91ef7138844e5811f81"
    static let Estimote_API_locaionID: String = "gridwhiz-office-version-0-2-4"
    //static let Estimote_API_locaionID: String = "me-bor" 7026800
    

}

var xPoint: Double?
var yPoint: Double?
var ref: DatabaseReference!
var UID:String = ""
//let SeniorUID = Auth.auth().currentUser!.uid
//let SeniorUID = "0"
let SeniorUID = Auth.auth().currentUser!.uid
let CaregiverUID = Auth.auth().currentUser!.uid
