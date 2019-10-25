//
//  naviView.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 22/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import Navigation_Toolbar

class naviView: UIViewController {

    @IBOutlet weak var navigationView: NavigationView!
    override func viewDidLoad() {
        super.viewDidLoad()
        naviItem()
    }
    func naviItem(){
        navigationView = NavigationView.init(frame: view.bounds,
                                             middleView: MiddleView(),
                                             screens: [
                                                ScreenObject(title: "ตำแหน่งผู้สูงอายุ",
                                                             startColor: .red,
                                                             endColor: .blue,
                                                             image: UIImage(named : "Icon3")!,
                                                             controller: CareHome()),
                                                
                                                ScreenObject(title: "ข้อมูลสุขภาพ",
                                                             startColor: .black,
                                                             endColor: .white,
                                                             image: #imageLiteral(resourceName: "old"),
                                                             controller: viewData())
            ],
                                             backgroundImage: #imageLiteral(resourceName: "63860"))
        
        navigationView?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        view.addSubview(navigationView!)
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
    func saveLoggedState() {
        
        let careState = UserDefaults.standard
        careState.set(true, forKey: "Caregiver_is_authenticated") // save true flag to UserDefaults
        careState.synchronize()
        
    }

}

