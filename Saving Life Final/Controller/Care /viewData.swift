//
//  viewData.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 22/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import Firebase
import SwiftyJSON
import Floaty
import GoogleSignIn
import JSSAlertView

class viewData: UIViewController {
    var profile: ProfileCare?
    var senior: ProfileSenior?
    var ref: DatabaseReference!
    let floaty = Floaty()
    @IBOutlet weak var stepsWeekLB: UILabel!
    @IBOutlet weak var stepsLB: UILabel!
    @IBOutlet weak var heartLB: UILabel!
    @IBOutlet weak var fcTodayLB: UILabel!
    @IBOutlet weak var fcWeeklyLB: UILabel!

    @IBOutlet weak var collectView: UICollectionView!
    override func viewDidLoad() {
        super.viewDidLoad()

        ref = Database.database().reference()
        //collectionview
        self.registerCollectionCell()
        self.collectView.dataSource = self
        self.collectView.delegate = self
        observeData()
        floatyBTN()
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
    func floatyBTN(){
        floaty.addItem("เพิ่มผู้ใช้งาน", icon: #imageLiteral(resourceName: "old"), handler: { item in
            let ScanQRView = ScanQRViewController()
            ScanQRView.delegate = self
            self.present(ScanQRViewController(), animated: true, completion: nil)
            //self.navigationController?.pushViewController(ScanQRViewController(), animated: true)
            self.floaty.close()
        })
        floaty.addItem("หน้าหลัก", icon: #imageLiteral(resourceName: "iCON2"), handler: { item in
            self.navigationController?.pushViewController(CareHome(), animated: true)
            self.floaty.close()
        })
        floaty.addItem("ตั้งค่า", icon: #imageLiteral(resourceName: "icons8-services-500"), handler: { item in
            self.navigationController?.pushViewController(CareSetting(), animated: true)
            self.floaty.close()
        })
        floaty.addItem("ออกจากระบบ", icon: #imageLiteral(resourceName: "icons8-exit-512"), handler: { item in
            GIDSignIn.sharedInstance().signOut()
            self.navigationController?.pushViewController(Welcome(), animated: true)
            self.floaty.close()
        })
        self.view.addSubview(floaty)
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
extension viewData: UICollectionViewDelegateFlowLayout {
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

extension viewData: UICollectionViewDelegate, UICollectionViewDataSource {
    
    func registerCollectionCell(){
        self.collectView.register(UINib(nibName: "dataCell", bundle: nil), forCellWithReuseIdentifier: "dataCell")
    }
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        
        return self.profile?.Followed?.count ?? 0
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectView.dequeueReusableCell(withReuseIdentifier: "dataCell", for: indexPath) as! dataCell
        //cell.backgroundColor = UIColor.clear
        let id = self.profile?.Followed?[indexPath.row] ?? ""
        self.ref.child("User/Senior/\(id)/ProfileURL").observeSingleEvent(of: .value, with: { (snapshot) in
            let imgRawData = snapshot.value as? [String:AnyObject] //as? Dictionary<String,Any>
            let imgJSON = JSON(imgRawData)
            print(imgJSON["URL"].string ?? "")
            
            cell.imgView.kf.setImage(with: URL(string: "\(imgJSON["URL"].string ?? "")"), placeholder: #imageLiteral(resourceName: "iCON2"))
        })
        //cell.imgView.layer.cornerRadius = cell.imgView.frame.height/2
        return cell
    }
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, minimumLineSpacingForSectionAt section: Int) -> CGFloat {
        return 1
    }
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        print(indexPath.row)
        //location
        if let id = self.profile?.Followed?[indexPath.row]{
            var Daily = ref.child("User/Senior/\(id ?? "")/HealthData/DailySteps")
            Daily.observeSingleEvent(of: .value, with: { snapshot in
                let message = snapshot.value as? String
                self.stepsLB.text = message
            })
            
            var Weekly = ref.child("User/Senior/\(id ?? "")/HealthData/WeeklySteps")
            Weekly.observeSingleEvent(of: .value, with: { snapshot in
                let message = snapshot.value as? String
                self.stepsWeekLB.text = message
            })
            
            var HR = ref.child("User/Senior/\(id ?? "")/HealthData/Heartrate")
            HR.observeSingleEvent(of: .value, with: { snapshot in
                let message = snapshot.value as? String
                self.heartLB.text = message
            })
            var FCDaily = ref.child("User/Senior/\(id ?? "")/HealthData/flightsClimbedToday")
            FCDaily.observeSingleEvent(of: .value, with: { snapshot in
                let message = snapshot.value as? String
                self.fcTodayLB.text = message
            })
            var FCWeekly = ref.child("User/Senior/\(id ?? "")/HealthData/flightsClimbedWeekly")
            FCWeekly.observeSingleEvent(of: .value, with: { snapshot in
                let message = snapshot.value as? String
                self.fcWeeklyLB.text = message
            })
        }
    }
}
extension viewData: QRCodeDelegate{
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


