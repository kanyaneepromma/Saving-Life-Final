//
//  QRView.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 21/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import EFQRCode
import Firebase
class QRView: UIViewController {
    var ref: DatabaseReference!
    @IBOutlet weak var QRview: UIImageView!
    override func viewDidLoad() {
        super.viewDidLoad()
        ref = Database.database().reference()
        ref.child("User/Senior/\(SeniorUID)").observeSingleEvent(of: .value, with: { snapshot in
            let SLID = "Senior_\(SeniorUID)"
            self.generateQRCode(content: SLID)
        })
        
    }
    func generateQRCode(content: String) {
        let generator = EFQRCodeGenerator(content: "\(content)", size: EFIntSize(width: 1000, height: 1000))
        generator.setContent(content: "\(content)")
        generator.setMode(mode: .none)
        generator.setWatermark(watermark: UIImage(named: "iCON2")?.toCGImage(), mode: .scaleToFill)
        generator.setAllowTransparent(allowTransparent: false)
        if let tryImage = generator.generate() {
            print("Create QRCode image success: \(tryImage)")
            
            let tryImage = UIImage(cgImage: tryImage)
            
            self.QRview.image = tryImage
        } else {
            print("Create QRCode image failed!")
        }
        
    }
    //MARK: - Hidden Navigation
    override func viewWillAppear(_ animated: Bool) {
        //super.viewWillAppear(animated)
        navigationItem.title = "คิวอาร์โค้ด"
        let nav = self.navigationController?.navigationBar
        nav?.barStyle = UIBarStyle.default
        nav?.barTintColor = UIColor(red: 185/255, green: 220/255, blue: 255/255, alpha: 1.0)
        nav?.tintColor = UIColor.white
        nav?.shadowColor = UIColor.black
    }
    /*
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        navigationController?.setNavigationBarHidden(false, animated: animated)
    }*/
    
}
