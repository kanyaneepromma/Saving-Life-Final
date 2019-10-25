//
//  GoogleSignin.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 28/3/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import GoogleSignIn
import Firebase

class GoogleSignin: UIViewController , GIDSignInDelegate , GIDSignInUIDelegate{
    override func viewDidLoad() {
        super.viewDidLoad()
        GIDSignIn.sharedInstance().clientID = FirebaseApp.app()?.options.clientID
        GIDSignIn.sharedInstance().delegate = self
        GIDSignIn.sharedInstance().uiDelegate = self
        NotificationCenter.default.addObserver(self, selector: #selector(didSignIn), name: NSNotification.Name("SuccessfulSignInNotification"), object: nil)
    }
    func sign(_ signIn: GIDSignIn!, didSignInFor user: GIDGoogleUser!, withError error: Error!) {
        print("Google Sing In didSignInForUser")
        if let error = error {
            print(error.localizedDescription)
            return
        }
        guard let authentication = user.authentication else { return }
        let credential = GoogleAuthProvider.credential(withIDToken: (authentication.idToken)!, accessToken: (authentication.accessToken)!)
        // When user is signed in
        Auth.auth().signIn(with: credential, completion: { (user, error) in
            if let error = error {
                print("Login error: \(error.localizedDescription)")
                return
            }
        })
        NotificationCenter.default.post(
            name: Notification.Name("SuccessfulSignInNotification"), object: nil, userInfo: nil)
    }
    @objc func didSignIn()  {
        self.navigationController?.pushViewController(Choice(), animated: true)
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self)
    }
    // Start Google OAuth2 Authentication
    private func sign(_ signIn: GIDSignIn?, present viewController: Choice?) {
        print("sign")
    }
    // After Google OAuth2 authentication
    func sign(_ signIn: GIDSignIn?, dismiss viewController: UIViewController?) {
        // Close OAuth2 authentication window
        dismiss(animated: true) {() -> Void in }
    }
    @IBAction func ggBTN(_ sender: Any) {
        GIDSignIn.sharedInstance().signIn()
        
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
