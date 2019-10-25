//
//  Permission.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 21/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import RAMPaperSwitch
import JSSAlertView
import paper_onboarding
import CoreLocation
import HealthKit

class Permission: UIViewController {

    @IBOutlet weak var finishView: DesignableView!
    @IBOutlet weak var txtLabel: UITextView!
    @IBOutlet weak var onboarding: PaperOnboarding!
    private let locationManager = CLLocationManager()
    let healthStore = HKHealthStore()
    @IBOutlet weak var healthkitBTN: UIButton!
    @IBOutlet weak var locationBTN: UIButton!
    @IBOutlet weak var finish: UIButton!
    override func viewDidLoad() {
        super.viewDidLoad()
        //setupPaperOnboardingView()
        onboarding.dataSource = self
        onboarding.delegate = self
        self.locationManager.delegate = self
        self.locationManager.desiredAccuracy = kCLLocationAccuracyBest
        //button
        healthkitBTN.setTitle("อนุญาตให้เข้าถึง Healthkit", for: .normal)
        CheckAuth()
    }

    
    @IBAction func healthkitBTN(_ sender: Any) {
        
        let healthKitTypes: Set = [
            // access step count
            HKObjectType.quantityType(forIdentifier: HKQuantityTypeIdentifier.stepCount)!,
            HKObjectType.quantityType(forIdentifier: HKQuantityTypeIdentifier.distanceWalkingRunning)!,
            HKObjectType.quantityType(forIdentifier: HKQuantityTypeIdentifier.heartRate),
            HKObjectType.quantityType(forIdentifier: HKQuantityTypeIdentifier.flightsClimbed)!
            
        ]
        healthStore.requestAuthorization(toShare: healthKitTypes as! Set<HKSampleType>, read: healthKitTypes as! Set<HKObjectType>) { (bool, error) in
            if let e = error {
                print("oops something went wrong during authorisation \(e.localizedDescription)")
            } else {
                print("User has completed the authorization flow")
                self.healthkitBTN.setTitle("อนุญาตเรียบร้อย", for: .normal)
                UserDefaults.standard.set(true, forKey: "Healthkit")
            }
        }
    }
    func CheckAuth(){
        var hk = UserDefaults.standard.bool(forKey: "Healthkit")
        let loc = UserDefaults.standard.bool(forKey: "Location")
        if hk == true && loc == true{
            finish.setBackgroundColor(UIColor(red: 140/255, green: 237/255, blue: 181/255, alpha: 1.0), for: .normal)
            finishView.shadowColor = UIColor(red: 140/255, green: 237/255, blue: 181/255, alpha: 1.0)
                finish.setTitle("เรียบร้อยไปเลย", for: .normal)
            finishView.isHidden = false
            finish.addTarget(Any?.self
                , action: #selector(handleRegister)
                , for: .touchUpInside)
        }
    }
    @objc
    func handleRegister(){
        self.navigationController?.pushViewController(SeniorHome(), animated: true)
    }

    @IBAction func locationBTN(_ sender: Any) {
         self.locationManager.requestAlwaysAuthorization()
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
    fileprivate let items = [OnboardingItemInfo(informationImage: #imageLiteral(resourceName: "iCON2"),
                                                title: "Welcome",
                                                description: "เราจำเป็นต้องขออนุญาตให้เข้าถึงข้อมูลสถานที่และข้อมูลสุขภาพของคุณ",
                                                pageIcon: #imageLiteral(resourceName: "Mascot_Transparent"),
                                                color: UIColor(red: 0.40, green: 0.56, blue: 0.71, alpha: 1.00),
                                                titleColor: UIColor.white, descriptionColor: UIColor.white, titleFont: Permission.titleFont, descriptionFont: Permission.descriptionFont),
                             
                             OnboardingItemInfo(informationImage: #imageLiteral(resourceName: "iCON2"),
                                                title: "Location",
                                                description: "ขออนุญาตเข้าถึงข้อมูลสถานที่",
                                                pageIcon: #imageLiteral(resourceName: "iCON2"),
                                                color: UIColor(red: 0.40, green: 0.69, blue: 0.71, alpha: 1.00),
                                                titleColor: UIColor.white, descriptionColor: UIColor.white, titleFont: Permission.titleFont, descriptionFont: Permission.descriptionFont),
                             
                             OnboardingItemInfo(informationImage: #imageLiteral(resourceName: "iCON2"),
                                                title: "Healthkit",
                                                description: "ขออนุญาตเข้าถึงข้อมูลสุขภาพใน Healthkit",
                                                pageIcon: #imageLiteral(resourceName: "iCON2"),
                                                color: UIColor(red: 0.61, green: 0.56, blue: 0.74, alpha: 1.00),
                                                titleColor: UIColor.white, descriptionColor: UIColor.white, titleFont: Permission.titleFont, descriptionFont: Permission.descriptionFont),]
    
}
extension Permission: PaperOnboardingDelegate, PaperOnboardingDataSource{
    private func setupPaperOnboardingView() {
        let onboarding = PaperOnboarding()
        onboarding.delegate = self
        onboarding.dataSource = self
        onboarding.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(onboarding)
        
        // Add constraints
        for attribute: NSLayoutConstraint.Attribute in [.left, .right, .top, .bottom] {
            let constraint = NSLayoutConstraint(item: onboarding,
                                                attribute: attribute,
                                                relatedBy: .equal,
                                                toItem: view,
                                                attribute: attribute,
                                                multiplier: 1,
                                                constant: 0)
            view.addConstraint(constraint)
        }
    }
    func onboardingItemsCount() -> Int {
        return 3
    }
    
    func onboardingItem(at index: Int) -> OnboardingItemInfo {
        return items[index]
    }
    
    
}
//MARK: Constants
extension Permission {
    
    private static let titleFont = UIFont(name: "Nunito-Bold", size: 36.0) ?? UIFont.boldSystemFont(ofSize: 36.0)
    private static let descriptionFont = UIFont(name: "OpenSans-Regular", size: 20.0) ?? UIFont.systemFont(ofSize: 20.0)
}
// MARK: - Core Location Delegate
extension Permission: CLLocationManagerDelegate {
    
    
    func locationManager(_ manager: CLLocationManager,
                         didChangeAuthorization status: CLAuthorizationStatus) {
        
        switch status {
            
        case .notDetermined         : self.locationBTN.setTitle("ยังไม่ได้ตัดสินใจเลย", for: .normal)        // location permission not asked for yet
        case .authorizedWhenInUse   : self.locationBTN.setTitle("อนุญาตให้ใช้เฉพาะตอนที่แอพทำงาน", for: .normal)
        UserDefaults.standard.set(true, forKey: "Location")// location authorized
        case .authorizedAlways      : self.locationBTN.setTitle("อนุญาตแล้ว", for: .normal)
            UserDefaults.standard.set(true, forKey: "Location")
        // location authorized
        case .restricted            : self.locationBTN.setTitle("จำกัดไว้", for: .normal)              // TODO: handle
        case .denied                : self.locationBTN.setTitle("ไม่อนุญาต", for: .normal)
            self.locationBTN.setTitleColor(UIColor.red, for: .normal)
            // TODO: handle
        }
    }
}
