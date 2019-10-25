//
//  CareHome.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 21/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import Firebase
import SwiftyJSON
import Floaty
import JSSAlertView
import GoogleSignIn

class CareHome: UIViewController {
    var ref: DatabaseReference!
    var profile: ProfileCare?
    var senior: ProfileSenior?
    var location: Location?
    
    @IBOutlet weak var collectView: UICollectionView!
    @IBOutlet weak var profilePostition: UIImageView!
    let floaty = Floaty()
    @IBOutlet weak var locationView: UIView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        ref = Database.database().reference()
        self.registerCollectionCell()
        self.collectView.dataSource = self
        self.collectView.delegate = self
        observeData()
        floatyBTN()
        setLoggedState(state: true)
        locationView.addSubview(profilePostition)
    }
    func floatyBTN(){
        floaty.addItem("เพิ่มผู้ใช้งาน", icon: #imageLiteral(resourceName: "old"), handler: { item in
            let ScanQRView = ScanQRViewController()
            ScanQRView.delegate = self
            self.present(ScanQRView, animated: true, completion: nil)
            //self.navigationController?.pushViewController(ScanQRViewController(), animated: true)
            self.floaty.close()
        })
        floaty.addItem("ดูข้อมูลสุขภาพ", icon: #imageLiteral(resourceName: "care"), handler: { item in
            self.navigationController?.pushViewController(viewData(), animated: true)
            self.floaty.close()
        })
        floaty.addItem("ตั้งค่า", icon: #imageLiteral(resourceName: "icons8-services-500"), handler: { item in
            self.navigationController?.pushViewController(CareSetting(), animated: true)
            self.floaty.close()
        })
        floaty.addItem("ออกจากระบบ", icon: #imageLiteral(resourceName: "icons8-exit-512"), handler: { item in
            GIDSignIn.sharedInstance().signOut()
            self.setLoggedState(state: false)
            self.navigationController?.pushViewController(Welcome(), animated: true)
            self.floaty.close()
        })
        self.view.addSubview(floaty)
    }
    func observeData(){
        self.ref.child("User/CareGiver/\(CaregiverUID)").observeSingleEvent(of: .value, with: { (snapshot) in
            if snapshot.exists(){
                let profileRawData = snapshot.value as! [String:AnyObject] //as? Dictionary<String,Any>
                let profileJSON = JSON(profileRawData)
                #if DEBUG
                print("CViewController")
                print(profileJSON)
                #endif
                // print("Exist")
                
                do{
                    //.self หน้าคือในตัว .selfหลังคือทั้งหมดในคลาส
                    let profileData = try JSONDecoder().decode(ProfileCare.self, from: profileJSON.rawData())
                    self.profile = profileData
                    //for loop
                    self.collectView.reloadData()
                    print("count: \(self.profile?.Followed?.count ?? 0)")
                    // print(profileData)
                    // print("------")
                }catch let error{
                    print(error)
                }
            } else {
            }
        })
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
    //MARK :- Savestate
    func setLoggedState(state: Bool){
        if state == true{
            UserDefaults.standard.set(true, forKey: "Caregiver_is_authenticated") // save true flag to UserDefaults
        }
        else{
            
        }
    }
    func getLoggedState() -> Bool {
        if UserDefaults.standard.bool(forKey: "Caregiver_is_authenticated") != nil{
            return UserDefaults.standard.bool(forKey: "Caregiver_is_authenticated")
        }
        return false
    }
}
extension CareHome: UICollectionViewDelegateFlowLayout {
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        return CGSize( width: 150, height: 150)
    }
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, insetForSectionAt section: Int) -> UIEdgeInsets {
        return UIEdgeInsets(top: 0, left: 0, bottom: 0, right: 0)
    }
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, minimumInteritemSpacingForSectionAt section: Int) -> CGFloat {
        
        return 1.0
        
    }
}
//layout
extension CareHome: UICollectionViewDelegate, UICollectionViewDataSource {
    
    func registerCollectionCell(){
        self.collectView.register(UINib(nibName: "homeCell", bundle: nil), forCellWithReuseIdentifier: "homeCell")
    }
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        
        return self.profile?.Followed?.count ?? 0
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectView.dequeueReusableCell(withReuseIdentifier: "homeCell", for: indexPath) as! homeCell
        //cell.backgroundColor = UIColor.clear
        let id = self.profile?.Followed?[indexPath.row] ?? ""
        self.ref.child("User/Senior/\(id)/ProfileURL").observeSingleEvent(of: .value, with: { (snapshot) in
            let imgRawData = snapshot.value as? [String:AnyObject] //as? Dictionary<String,Any>
            let imgJSON = JSON(imgRawData)
            //print("HomeCell at careHOME: \(imgJSON["URL"].string ?? "")")
            
            cell.imgView.kf.setImage(with: URL(string: "\(imgJSON["URL"].string ?? "")"), placeholder: #imageLiteral(resourceName: "iCON2"))
        })
        //cell.imgView.layer.cornerRadius = 50
        return cell
    }
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, minimumLineSpacingForSectionAt section: Int) -> CGFloat {
        return 8
    }
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        print(indexPath.row)
        //location
        if let id = self.profile?.Followed?[indexPath.row]{
            self.ref.child("User/Senior/\(id)/Location").observe(.value, with: { (snapshot) in
                //print(snapshot)
                let locationRawData = snapshot.value as? [String:AnyObject] //as? Dictionary<String,Any>
                let locationJSON = JSON(locationRawData)
                print(locationJSON)
                //print(locationJSON ?? "")
                do{
                    //.self หน้าคือในตัว .selfหลังคือทั้งหมดในคลาส
                    let locationData = try JSONDecoder().decode(Location.self, from: locationJSON.rawData())
                    //print(locationData)
                    
                    self.location = locationData
                    self.profilePostition.frame.origin = CGPoint(x:  Double(self.location!.LocationX!)! * 33 ,y: 165 - Double(self.location!.LocationY!)! * 33) 
                }catch let error{
                    print(error)
                }
            })
        }
    }
}
extension CareHome: QRCodeDelegate{
    func scanResult(value: String) {
        print(value)
        ref = Database.database().reference()
        //get data
        print("มีไง \(value)")
        var allFollower = self.profile?.Followed ?? []
        print(allFollower)
        
        // check existing senior
        if allFollower.contains(value) {
            // this should alert to user already exist senior
            print("YES")
        } else {
            let alertview = JSSAlertView().show(
                self,
                title: "พบผู้ใช้งาน",
                text: "ยินดีต้อนรับ",
                buttonText: "OK",
                color: UIColorFromHex(0xffccce, alpha: 1),
                iconImage: #imageLiteral(resourceName: "iCON2"))
            
            allFollower.append(value)
            print(allFollower)
             self.ref.child("User/CareGiver/\(CaregiverUID)/Followed").setValue(allFollower)
        }
    }
}
