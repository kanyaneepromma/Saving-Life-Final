//
//  Input.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 2/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import TextFieldEffects
import JSSAlertView

class Input: UIViewController {

    @IBOutlet weak var nameTF: KaedeTextField!
    @IBOutlet weak var telTF: KaedeTextField!

    override func viewDidLoad() {
        super.viewDidLoad()
        self.hideKeyboardWhenTappedAround() 
    }
    @IBAction func deleteBTN(_ sender: Any) {
        nameTF.text = ""
        telTF.text = ""
    }
    @IBAction func saveBTN(_ sender: Any) {
        check()
    }
    //MARK: - Hidden Navigation
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        navigationController?.setNavigationBarHidden(true, animated: animated)
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        navigationController?.setNavigationBarHidden(false, animated: animated)
    }
}
extension Input: UITextFieldDelegate{
    //MARK - UITextField Delegates
    func check(){
        if(nameTF?.text?.characters.count == 0 || telTF?.text?.characters.count == 0)
        {
            //try
            var alertview = JSSAlertView().danger(
                self,
                title: "กรุณากรอกชื่อและเบอร์โทร")
        }
        else{
            let alert = JSSAlertView().show(
                self,
                title: "ยินดีต้อนรับ คุณ \(nameTF.text ?? "")",
                text: "เบอร์โทรของคุณคือ \(telTF.text ?? "") \nข้อมูลถูกต้องหรือไม่",
                cancelButtonText: "Cancel", color: UIColorFromHex(0x42e2f4, alpha: 1),
                iconImage: #imageLiteral(resourceName: "love"))
            alert.addAction {
                UserDefaults.standard.set("\(self.nameTF.text ?? "")", forKey: "Name")
                UserDefaults.standard.set("\(self.telTF.text ?? "")", forKey: "Tel")
                self.navigationController?.pushViewController(GoogleSignin(), animated: true)
            }
            alert.addCancelAction {
                print("Edit")
            }
        }
    }
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
            
            let allowedCharacters = CharacterSet(charactersIn:"0123456789")
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
