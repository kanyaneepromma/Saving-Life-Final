//
//  homeCell.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 22/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import Firebase
import SwiftyJSON
import Kingfisher

class homeCell: UICollectionViewCell {
    
    @IBOutlet weak var imgView: UIImageView!
    //var profileSenior: [ProfileSenior] = []
    //var profileCare: [ProfileCare] = []
    var ref: DatabaseReference!
    var storageRef: StorageReference!
    var profile: ProfileCare?
    var pic: URLL?

    override func awakeFromNib() {
        super.awakeFromNib()
        ref = Database.database().reference()
        storageRef = Storage.storage().reference()
        retrieveData()
    }
    func retrieveData(){
        self.ref.child("User/CareGiver/\(CaregiverUID)").observeSingleEvent(of: .value, with: { (snapshot) in
            if snapshot.exists(){
                self.ref = Database.database().reference()
                let profileRawData = snapshot.value as? Dictionary<String,Any>
                let profileJSON = JSON(profileRawData)
                do{
                    let profileData = try JSONDecoder().decode(ProfileCare.self, from: profileJSON.rawData())
                    self.profile = profileData
                    var id = self.profile?.Followed ?? []
                    //print("CollectionViewCell")
                    //print(id)
                    //read each data in array
                    
                }catch let error{
                    print(error)
                }
            } else {
            }
        })
    }

}
