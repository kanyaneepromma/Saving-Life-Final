//
//  Choice.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 4/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import SwiftyGif
import Firebase

class Choice: UIViewController {
    var ref: DatabaseReference!
    @IBOutlet weak var imgView: UIImageView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //sunflower
        //let url = URL(string: "https://media.giphy.com/media/2wgWvXFyK1zmMm8NTe/giphy.gif")
        //multicolor flower
        let url = URL(string: "https://media0.giphy.com/media/1zKf2dBnUKZt3XdP02/200w.gif?cid=790b76115ca5bcf97338617536008138")
        self.imgView.setGifFromURL(url)
        ref = Database.database().reference()
    
    }
    @IBAction func seniorBTN(_ sender: Any) {
        
        let name = UserDefaults.standard.string(forKey: "Name") ?? ""
        let tel = UserDefaults.standard.string(forKey: "Tel") ?? ""
        SavetoDBSenior(name: name, tel: tel)
        self.navigationController?.pushViewController(Permission(), animated: true)
    }
    @IBAction func careBTN(_ sender: Any) {
        let name = UserDefaults.standard.string(forKey: "Name") ?? ""
        let tel = UserDefaults.standard.string(forKey: "Tel") ?? ""
        SavetoDBCare(name: name, tel: tel)
        self.navigationController?.pushViewController(CareHome(), animated: true)
    }
    func SavetoDBSenior(name: String, tel: String){
        self.ref.child("User/Senior/\(SeniorUID)/DataSenior").updateChildValues([
            "Name_Senior": name,
            "Tel_Senior": tel,
            "Role": "Senior"
            ])
    }
    func SavetoDBCare(name: String, tel: String){
        self.ref.child("User/CareGiver/\(CaregiverUID)").updateChildValues([
            "Name_Care": name,
            "Tel_Care": tel,
            "Role": "Care Giver"
            ])
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
