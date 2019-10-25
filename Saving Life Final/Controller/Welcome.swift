//
//  Welcome.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 2/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit

class Welcome: UIViewController {

    @IBAction func startBTN(_ sender: Any) {
        self.navigationController?.pushViewController(Input(), animated: true)

    }
    override func viewDidLoad() {
        super.viewDidLoad()
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
