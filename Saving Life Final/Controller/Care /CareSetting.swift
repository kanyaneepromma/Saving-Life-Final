//
//  CareSetting.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 22/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import TextFieldEffects
import Firebase
import JSSAlertView
import GoogleSignIn


class CareSetting: UIViewController {

    var ref: DatabaseReference!
    @IBOutlet weak var nameTF: KaedeTextField!
    @IBOutlet weak var telTF: KaedeTextField!

    override func viewDidLoad() {
        super.viewDidLoad()
        ref = Database.database().reference()
        changeValue()
        self.hideKeyboardWhenTappedAround() 
    }
    func changeValue(){
        self.ref.child("User/CareGiver/\(CaregiverUID)/Name_Care").observeSingleEvent(of: .value, with: { snapshot in
            let message = snapshot.value as? String
            self.nameTF.text = "\(message ?? "")"
        })
        self.ref.child("User/CareGiver/\(CaregiverUID)/Tel_Care").observeSingleEvent(of: .value, with: { snapshot in
            let message = snapshot.value as? String
            self.telTF.text = "\(message ?? "")"
        })
        
    }
    @objc func saveUser(){
        print("Click")
        if(nameTF?.text?.characters.count == 0 || telTF?.text?.characters.count == 0)
        {
            //try
            var alertview = JSSAlertView().danger(
                self,
                title: "กรุณากรอกชื่อและเบอร์โทร")
        }
        else{
            self.ref.child("User/CareGiver/\(CaregiverUID)").updateChildValues([
                "Name_Care": "\(nameTF?.text ?? "")",
                "Tel_Care":  "\(telTF?.text ?? "")"
                ])
            //JSSAlertView.show(self, title: "\(nameTF?.text ?? "")")
            self.navigationController?.popViewController(animated: true)
        }
        
    }
    override func viewWillAppear(_ animated: Bool) {
        navigationItem.title = "แก้ไขข้อมูล"
        let nav = self.navigationController?.navigationBar
        nav?.barStyle = UIBarStyle.default
        nav?.barTintColor = UIColor(red: 185/255, green: 220/255, blue: 255/255, alpha: 1.0)
        nav?.tintColor = UIColor.white
        nav?.shadowColor = UIColor.black
        let savBarButtonItem = UIBarButtonItem(title: "Save", style: .done, target: self, action: #selector(saveUser))
        self.navigationItem.rightBarButtonItem  = savBarButtonItem
    }
}
extension CareSetting: UITextFieldDelegate{
    //MARK - UITextField Delegates
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        //
        
        //For numers
        if textField == telTF {
            //limit
            let maxLength = 10
            let currentString: NSString = textField.text! as NSString
            let newString: NSString =
                currentString.replacingCharacters(in: range, with: string) as NSString
            return newString.length <= maxLength
            
            let allowedCharacters = CharacterSet(charactersIn:"0123456789")//Here change this characters based on your requirement
            let characterSet = CharacterSet(charactersIn: string)
            return allowedCharacters.isSuperset(of: characterSet)
        }
        else{
            let maxLength = 20
            let currentString: NSString = textField.text! as NSString
            let newString: NSString =
                currentString.replacingCharacters(in: range, with: string) as NSString
            return newString.length <= maxLength
        }
        return true
    }
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        if let nextField = textField.superview?.viewWithTag(textField.tag + 1) as? UITextField {
            nextField.becomeFirstResponder()
        } else {
            // Not found, so remove keyboard.
            textField.resignFirstResponder()
        }
        // Do not add a line break
        return false
        
    }
}
