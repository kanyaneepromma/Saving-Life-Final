//
//  SeniorHome.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 20/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import Photos
import Firebase
import Photos
import FirebaseStorage
import GoogleSignIn
import HealthKit
import Instructions
import JSSAlertView


class SeniorHome: UIViewController, UINavigationControllerDelegate{
    @IBOutlet weak var profileIMG: UIImageView!
    var ref: DatabaseReference!
    var storageRef: StorageReference!
    var location: EILLocation!
    var backgroundIndoorLocationManager: EILBackgroundIndoorLocationManager!
    var locationManager: EILIndoorLocationManager!
    let healthStore = HKHealthStore()
    var coachMarksController = CoachMarksController()
    let imagePickerController = UIImagePickerController()
    var fetchLocationTask: UIBackgroundTaskIdentifier = UIBackgroundTaskIdentifier.invalid
    @IBOutlet weak var qrBTN: UIButton!
    @IBOutlet weak var imgPicker: UIButton!
    @IBOutlet weak var LogoutBTN: UIButton!
    @IBOutlet weak var SettingBTN: UIButton!
    @IBOutlet weak var testView: UIView!
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        ref = Database.database().reference()
        storageRef = Storage.storage().reference()
        imagePickerController.delegate = self
        self.coachMarksController.dataSource = self
        let skipView = CoachMarkSkipDefaultView()
        skipView.setTitle("Skip", for: .normal)
        
        self.coachMarksController.skipView = skipView
        coachMarksController.overlay.allowTap = true
        saveHealthData()
        profilePic()
        //config
        ESTConfig.setupAppID(API.Estimote_API_appID , andAppToken: API.Estimote_API_appToken)
        //background
        self.backgroundIndoorLocationManager = EILBackgroundIndoorLocationManager()
        self.backgroundIndoorLocationManager.delegate = self
        self.fetchLocationAndStartPositioninig()
        
        self.locationManager = EILIndoorLocationManager()
        self.locationManager.delegate = self
        self.locationManager.mode = EILIndoorLocationManagerMode.light
        startInstructions()
        setLoggedState(state: true)
    }
    
    func profilePic(){
        //img
        profileIMG.layer.borderWidth = 0
        profileIMG.layer.masksToBounds = false
        profileIMG.layer.borderColor = UIColor.black.cgColor
        profileIMG.layer.cornerRadius = profileIMG.frame.height/2
        profileIMG.clipsToBounds = true

    }
    @IBAction func qrBTN(_ sender: Any) {
        self.navigationController?.pushViewController(QRView(), animated: true)
    }
    @IBAction func settingBTN(_ sender: Any) {
        self.navigationController?.pushViewController(Setting(), animated: true)
    }
    @IBAction func logoutBTN(_ sender: Any) {
        GIDSignIn.sharedInstance().signOut()
        setLoggedState(state: false)
        self.navigationController?.pushViewController(Welcome(), animated: true)
    }
    @IBAction func imgPicker(_ sender: Any) {
        checkPermission()
        imagePickerController.sourceType = UIImagePickerController.SourceType.photoLibrary
        imagePickerController.allowsEditing = true
        self.present(imagePickerController, animated: true, completion: nil)
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
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
    }
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        coachMarksController.stop(immediately: true)
    }
    //MARK :- Savestate
    func setLoggedState(state: Bool){
        if state == true{
            UserDefaults.standard.set(true, forKey: "Senior_is_authenticated") // save true flag to UserDefaults
        }
        else{
        }
    }
    func getLoggedState() -> Bool {
        if UserDefaults.standard.bool(forKey: "Senior_is_authenticated") != nil{
            return UserDefaults.standard.bool(forKey: "Senior_is_authenticated")
        }
        return false
    }
    func saveHealthData(){
        
        getTodaySteps{ (result) in
            DispatchQueue.main.async {
                let Daily = "\(result)"
                self.ref.child("User/Senior/\(SeniorUID)/HealthData/DailySteps").setValue(Daily)
            }
        }
        getWeekSteps{ (result) in
            DispatchQueue.main.async {
                let Weekly = "\(result)"
                self.ref.child("User/Senior/\(SeniorUID)/HealthData/WeeklySteps").setValue(Weekly)
            }
        }
        heartRate{ (result) in
            DispatchQueue.main.async {
                self.ref.child("User/Senior/\(SeniorUID)/HealthData/Heartrate").setValue(result)
            }
        }
        flightsClimbedWeekly{ (result) in
            DispatchQueue.main.async {
                let flightsClimbed = "\(result)"
                self.ref.child("User/Senior/\(SeniorUID)/HealthData/flightsClimbedWeekly").setValue(flightsClimbed)
            }}
        flightsClimbedToday{ (result) in
            DispatchQueue.main.async {
                let flightsClimbed = "\(result)"
                self.ref.child("User/Senior/\(SeniorUID)/HealthData/flightsClimbedToday").setValue(flightsClimbed)
            }}
    }
    func getTodaySteps(completion: @escaping (Double) -> Void) {
        
        let stepsQuantityType = HKQuantityType.quantityType(forIdentifier: .stepCount)!
        
        let now = Date()
        let startOfDay = Calendar.current.startOfDay(for: now)
        let fromDate = NSDate(timeIntervalSinceNow: -86400 * 7)
        //week
        let week = HKQuery.predicateForSamples(withStart: fromDate as Date, end: now, options: .strictStartDate)
        //day
        let day = HKQuery.predicateForSamples(withStart: startOfDay, end: now, options: .strictStartDate)
        
        let query = HKStatisticsQuery(quantityType: stepsQuantityType, quantitySamplePredicate: day, options: .cumulativeSum) { (_, result, error) in
            var resultCount = 0.0
            guard let result = result else {
                print("Failed to fetch steps rate")
                completion(resultCount)
                return
            }
            if let sum = result.sumQuantity() {
                resultCount = sum.doubleValue(for: HKUnit.count())
            }
            
            DispatchQueue.main.async {
                completion(resultCount)
            }
        }
        healthStore.execute(query)
        
    }
    //flightclimbed Weekly
    func flightsClimbedWeekly(completion: @escaping (Double) -> Void) {
        
        let stepsQuantityType = HKQuantityType.quantityType(forIdentifier: .flightsClimbed)!
        
        let now = Date()
        let startOfDay = Calendar.current.startOfDay(for: now)
        let fromDate = NSDate(timeIntervalSinceNow: -86400 * 7)
        //week
        let week = HKQuery.predicateForSamples(withStart: fromDate as Date, end: now, options: .strictStartDate)
        
        let query = HKStatisticsQuery(quantityType: stepsQuantityType, quantitySamplePredicate: week, options: .cumulativeSum) { (_, result, error) in
            var resultCount = 0.0
            guard let result = result else {
                print("Failed to fetch flight Climbed")
                completion(resultCount)
                return
            }
            if let sum = result.sumQuantity() {
                resultCount = sum.doubleValue(for: HKUnit.count())
            }
            
            DispatchQueue.main.async {
                completion(resultCount)
            }
        }
        healthStore.execute(query)
        
    }
    //flightclimbed Today
    func flightsClimbedToday(completion: @escaping (Double) -> Void) {
        
        
        let stepsQuantityType = HKQuantityType.quantityType(forIdentifier: .flightsClimbed)!
        
        let now = Date()
        let startOfDay = Calendar.current.startOfDay(for: now)
        let fromDate = NSDate(timeIntervalSinceNow: -86400 * 7)
        //week
        
        let week = HKQuery.predicateForSamples(withStart: fromDate as Date, end: now, options: .strictStartDate)
        //day
        let day = HKQuery.predicateForSamples(withStart: startOfDay, end: now, options: .strictStartDate)
        
        let query = HKStatisticsQuery(quantityType: stepsQuantityType, quantitySamplePredicate: day, options: .cumulativeSum) { (_, result, error) in
            var resultCount = 0.0
            guard let result = result else {
                print("Failed to fetch flight Climbed")
                completion(resultCount)
                return
            }
            if let sum = result.sumQuantity() {
                resultCount = sum.doubleValue(for: HKUnit.count())
            }
            
            DispatchQueue.main.async {
                completion(resultCount)
            }
        }
        healthStore.execute(query)
        
    }
    func getWeekSteps(completion: @escaping (Double) -> Void) {
        
        let stepsQuantityType = HKQuantityType.quantityType(forIdentifier: .stepCount)!
        
        let now = Date()
        let startOfDay = Calendar.current.startOfDay(for: now)
        let fromDate = NSDate(timeIntervalSinceNow: -86400 * 7)
        //week
        let week = HKQuery.predicateForSamples(withStart: fromDate as Date, end: now, options: .strictStartDate)
        
        let query = HKStatisticsQuery(quantityType: stepsQuantityType, quantitySamplePredicate: week, options: .cumulativeSum) { (_, result, error) in
            var resultCount = 0.0
            guard let result = result else {
                print("Failed to fetch steps rate")
                completion(resultCount)
                return
            }
            if let sum = result.sumQuantity() {
                resultCount = sum.doubleValue(for: HKUnit.count())
            }
            
            DispatchQueue.main.async {
                completion(resultCount)
            }
        }
        healthStore.execute(query)
        
    }
    func heartRate(completion: @escaping (String) -> Void) {
        
        // 1. Create a heart rate BPM Sample
        let heartRateType = HKQuantityType.quantityType(forIdentifier: HKQuantityTypeIdentifier.heartRate)!
        let heartRateQuantity = HKQuantity(unit: HKUnit(from: "count/min"),
                                           doubleValue: Double(arc4random_uniform(80) + 100))
        let currentDate = Date()
        let dateStringFormatter = DateFormatter()
        //dateStringFormatter.calendar = Calendar(identifier: .iso8601)
        dateStringFormatter.dateFormat = "dd/MM/yyyy"
        let currentDay = dateStringFormatter.string(from: currentDate)
        print("1. \(currentDay)")
        
        let startDateString: String = "\(currentDay) 00:00:00"
        let endDateString: String = "\(currentDay) 23:59:59"
        print("2 start: \(startDateString)")
        print("2 end: \(endDateString)")
        
        let dateFormatter = DateFormatter()
        //dateFormatter.calendar = Calendar(identifier: .iso8601)
        //dateFormatter.timeZone = TimeZone(abbreviation: "UTC")
        dateFormatter.dateFormat = "dd/MM/yyyy HH:mm:ss"
        let startDate = dateFormatter.date(from: startDateString)
        let endDate = dateFormatter.date(from: endDateString)
        print("3 start: \(startDate)")
        print("3 end: \(endDate)")
        
        let heartSample = HKQuantitySample(type: heartRateType,
                                           quantity: heartRateQuantity, start: startDate!, end: endDate!)
        
        // 2. Save the sample in the store
        healthStore.save(heartSample, withCompletion: { (success, error) -> Void in
            if let error = error {
                print("Error saving heart sample: \(error.localizedDescription)")
            } else{
                //healthStore.execute(heartSample)
                completion("\(heartSample.quantity)")
            }
        })
    }
    
}
//MARK: indoorbackground
extension SeniorHome: UIImagePickerControllerDelegate{
    @objc
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        
        if let pickedImage = info[UIImagePickerController.InfoKey.originalImage] as? UIImage {
            let imageData = pickedImage.jpegData(compressionQuality: 1.0)
            let imageName = "\(SeniorUID)"
            let docDir = try! FileManager.default.url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: true)
            let imageURL = docDir.appendingPathComponent(imageName)
            try! imageData!.write(to: imageURL)
            let metadata = StorageMetadata()
            metadata.contentType = "image/jpg"
            let uploadTask = storageRef.child("images").child("\(imageName)").putFile(from: imageURL, metadata: metadata)
            let dd = storageRef.child("images").child("\(imageName)")
            
            uploadTask.observe(.success){
                snapshot in print(snapshot.reference.fullPath)
                dd.downloadURL { url, error in
                    if let error = error {
                        // Handle any errors
                    } else { self.ref.child("User/Senior/\(SeniorUID)/ProfileURL").setValue([
                            "URL": "\(url!)"])
                    }
                }
            }
            uploadTask.observe(.failure){
                snapshot in
                if let error = snapshot.error as? NSError{
                    print(error)}
            }
            uploadTask.observe(.progress){
                snapshot in
                let percentCom = 100.0 * Double(snapshot.progress!.completedUnitCount) / Double(snapshot.progress!.totalUnitCount)
                print(percentCom)
            }
            self.profileIMG.contentMode = .scaleToFill
            //self.profileImg.contentModepickedImage = .scaleToFill
            self.profileIMG.image = pickedImage
        }
        dismiss(animated: true, completion: nil)
    }
    func checkPermission() {
        let photoAuthorizationStatus = PHPhotoLibrary.authorizationStatus()
        switch photoAuthorizationStatus {
        case .authorized: print("Access is granted by user")
        case .notDetermined: PHPhotoLibrary.requestAuthorization({
            (newStatus) in print("status is \(newStatus)")
            if newStatus == PHAuthorizationStatus.authorized {
                print("success")
            }
        })
        case .restricted:
            print("User do not have access to photo album.")
        case .denied:
            print("User has denied the permission.")
        }
    }
    
}
extension SeniorHome: EILBackgroundIndoorLocationManagerDelegate{
    func fetchLocationAndStartPositioninig() {
        UIApplication.shared.beginBackgroundTask {
            print("can't fetch location")
            UIApplication.shared.endBackgroundTask(self.fetchLocationTask)
            self.fetchLocationTask = UIBackgroundTaskIdentifier.invalid
        }
        let fetchLocation = EILRequestFetchLocation(locationIdentifier: API.Estimote_API_locaionID)
        fetchLocation.sendRequest { (location, error) in
            if let location = location {
                self.location = location
                self.backgroundIndoorLocationManager.startPositionUpdates(for: location)
                self.locationManager.startPositionUpdates(for: self.location)
            } else {
                print("can't fetch location: \(error!)")
            }
            UIApplication.shared.endBackgroundTask(self.fetchLocationTask)
            self.fetchLocationTask = UIBackgroundTaskIdentifier.invalid
        }
    }
    
    func backgroundIndoorLocationManager(_ locationManager: EILBackgroundIndoorLocationManager, didFailToUpdatePositionWithError error: Error) {
        print("failed to update position: \(error)")
    }
    
    func backgroundIndoorLocationManager(_ locationManager: EILBackgroundIndoorLocationManager, didUpdatePosition position: EILOrientedPoint, with positionAccuracy: EILPositionAccuracy, in location: EILLocation) {
        xPoint = position.x
        yPoint = position.y
        //location
        self.ref.child("User/Senior/\(SeniorUID)/Location").setValue([
            "LocationX": "\(xPoint ?? 0.0)",
            "LocationY": "\(yPoint ?? 0.0)",
            "LocationID": "\(API.Estimote_API_locaionID)"
            ])
    }
}
extension SeniorHome: EILIndoorLocationManagerDelegate{
    func indoorLocationManager(_ manager: EILIndoorLocationManager, didFailToUpdatePositionWithError error: Error) {
        print("failed to update position: \(error)")
        JSSAlertView().show(self,title: "ไม่สามารถอัปเดตตำแหน่งคุณได้")
    }
    
    func indoorLocationManager(_ manager: EILIndoorLocationManager, didUpdatePosition position: EILOrientedPoint, with positionAccuracy: EILPositionAccuracy, in location: EILLocation) {
        xPoint = position.x
        yPoint = position.y
        //location
        self.ref.child("User/Senior/\(SeniorUID)/Location").setValue([
            "LocationX": "\(xPoint ?? 0.0)",
            "LocationY": "\(yPoint ?? 0.0)",
            "LocationID": "\(API.Estimote_API_locaionID)"
            ])
    }
}

extension SeniorHome: CoachMarksControllerDelegate , CoachMarksControllerDataSource{
    func startInstructions() {
        coachMarksController.start(in: .window(over: self))
    }
    func numberOfCoachMarks(for coachMarksController: CoachMarksController) -> Int {
        return 4
    }
    func coachMarksController(_ coachMarksController: CoachMarksController, coachMarkAt index: Int) -> CoachMark {
        switch(index) {
        case 0:
            return coachMarksController.helper.makeCoachMark(for: self.qrBTN)
        case 1:
            return coachMarksController.helper.makeCoachMark(for: self.imgPicker)
        case 2:
            return coachMarksController.helper.makeCoachMark(for: self.SettingBTN)
        case 3:
            return coachMarksController.helper.makeCoachMark(for: self.LogoutBTN)
        default:
            return coachMarksController.helper.makeCoachMark()
        }
    }
    
    
    
    func coachMarksController(_ coachMarksController: CoachMarksController, coachMarkViewsAt index: Int, madeFrom coachMark: CoachMark) -> (bodyView: CoachMarkBodyView, arrowView: CoachMarkArrowView?) {
        
        var hintText = ""
        
        switch(index) {
        case 0:
            hintText = "QR อยู่ตรงนี้จ้า"
        case 1:
            hintText = "เปลี่ยนรูปโปรไฟล์ให้สวย ๆ เลยจ้า"
        case 2:
            hintText = "ถ้าอยากจะเปลี่ยนชื่อให้มาตรงนี้"
        case 3:
            hintText = "อยากออกจากระบบ ไม่ยากเลยจ้าแค่จิ้มตรงนี้👇🏻"
        default: break
        }
        
        let coachViews = coachMarksController.helper.makeDefaultCoachViews(withArrow: true, arrowOrientation: coachMark.arrowOrientation, hintText: hintText, nextText: nil)
        
        return (bodyView: coachViews.bodyView, arrowView: coachViews.arrowView)
    }
}
