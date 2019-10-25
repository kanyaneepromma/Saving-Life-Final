//
//  dataCell.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 22/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import Firebase
import SwiftyJSON
import Kingfisher

class dataCell: UICollectionViewCell {
    var ref: DatabaseReference!
    var storageRef: StorageReference!
    var profile: ProfileCare?
    var pic: URLL?
    @IBOutlet weak var imgView: UIImageView!
    override func awakeFromNib() {
        super.awakeFromNib()
        ref = Database.database().reference()
        retrieveData()
    }
    func retrieveData(){
        self.ref.child("User/CareGiver/\(CaregiverUID)").observeSingleEvent(of: .value, with: { (snapshot) in
            if snapshot.exists(){
                let profileRawData = snapshot.value as? Dictionary<String,Any>
                let profileJSON = JSON(profileRawData)
                do{
                    let profileData = try JSONDecoder().decode(ProfileCare.self, from: profileJSON.rawData())
                    self.profile = profileData
                    var id = self.profile?.Followed ?? []
                }catch let error{
                    print(error)
                }
            } else {
            }
        })
    }

}
