//
//  ScanQRViewController.swift
//  Savinglife
//
//  Created by Kanyanee P on 14/1/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import UIKit
import GoogleSignIn
import AVFoundation
import Firebase
import JSSAlertView

protocol QRCodeDelegate: class {
    func scanResult(value: String)
}

class ScanQRViewController: UIViewController,  GIDSignInUIDelegate, AVCaptureMetadataOutputObjectsDelegate {
    var ref: DatabaseReference!
    var text:String = ""
    let screenWidth = UIScreen.main.bounds.width
    let screenHeight = UIScreen.main.bounds.height
    
    //@IBOutlet weak var messageLabel:UILabel!
    var cancelButton = UIButton()
    
    let isGetQRCode = UserDefaults.standard
    var captureSession:AVCaptureSession?
    var videoPreviewLayer:AVCaptureVideoPreviewLayer?
    var qrCodeFrameView:UIView?
    
    weak var delegate: QRCodeDelegate?
    
    // Added to support different barcodes
    let supportedBarCodes: [AVMetadataObject.ObjectType] = [.qr, .code128, .code93, .code39, .upce, .pdf417, .ean13, .ean8, .aztec, .dataMatrix, .itf14, .interleaved2of5, .code39Mod43]
    
    override var supportedInterfaceOrientations : UIInterfaceOrientationMask {
        return UIInterfaceOrientationMask.portrait
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Get an instance of the AVCaptureDevice class to initialize a device object and provide the video
        // as the media type parameter.
        guard let captureDevice = AVCaptureDevice.default(for: .video) else { return }
        
        do {
            // Get an instance of the AVCaptureDeviceInput class using the previous device object.
            let input = try AVCaptureDeviceInput(device: captureDevice)
            
            // Initialize the captureSession object.
            captureSession = AVCaptureSession()
            // Set the input device on the capture session.
            captureSession?.addInput(input)
            
            // Initialize a AVCaptureMetadataOutput object and set it as the output device to the capture session.
            let captureMetadataOutput = AVCaptureMetadataOutput()
            captureSession?.addOutput(captureMetadataOutput)
            
            // Set delegate and use the default dispatch queue to execute the call back
            captureMetadataOutput.setMetadataObjectsDelegate(self, queue: DispatchQueue.main)
            
            // Detect all the supported bar code
            captureMetadataOutput.metadataObjectTypes = supportedBarCodes
            
            // Initialize the video preview layer and add it as a sublayer to the viewPreview view's layer.
            videoPreviewLayer = AVCaptureVideoPreviewLayer(session: captureSession!)
            videoPreviewLayer?.videoGravity = AVLayerVideoGravity.resizeAspectFill
            videoPreviewLayer?.frame = view.layer.bounds
            view.layer.addSublayer(videoPreviewLayer!)
            
            // Start video capture
            captureSession?.startRunning()
            
            // Move the message label to the top view
            //view.bringSubviewToFront(messageLabel)
            
            // Initialize QR Code Frame to highlight the QR code
            qrCodeFrameView = UIView()
            
            if let qrCodeFrameView = qrCodeFrameView {
                qrCodeFrameView.layer.borderColor = UIColor.green.cgColor
                qrCodeFrameView.layer.borderWidth = 2
                view.addSubview(qrCodeFrameView)
                view.bringSubviewToFront(qrCodeFrameView)
            }
            
        } catch {
            print("got error")
            print(error)
            return
        }
        
        self.cancelButton.frame = CGRect(x: 0, y: self.screenHeight-40, width: self.screenWidth, height: 40)
        self.cancelButton.setTitle("Cancel", for: UIControl.State())
        self.cancelButton.backgroundColor = UIColor.black
        self.cancelButton.tintColor = UIColor.white
        self.cancelButton.addTarget(self, action: #selector(cancelScan(_:)), for: .touchUpInside)
        self.view.addSubview(self.cancelButton)
        view.bringSubviewToFront(cancelButton)
        
    }
    
    func metadataOutput(_ output: AVCaptureMetadataOutput, didOutput metadataObjects: [AVMetadataObject], from connection: AVCaptureConnection) {
        //captureSession!.stopRunning()
        
        if let metadataObject = metadataObjects.first {
            guard let readableObject = metadataObject as? AVMetadataMachineReadableCodeObject else { return }
            guard let stringValue = readableObject.stringValue else { return }
            // print(stringValue)
            
            //send
            if stringValue.prefix(7) == "Senior_"{
                //check if true in db?
               let result = String(stringValue.dropFirst(7))
                print("มี: \(result)")
                
                self.dismiss(animated: true) {
                    self.delegate?.scanResult(value: result)
                    
                }
                captureSession!.stopRunning()
            }
                //ถ้าไม่ใช่ของSL
            else{
                
                var alertview = JSSAlertView().danger(
                    self,
                    title: "ไม่พบข้อมูลผู้ใช้",
                    text: "ไม่ใช่ QR สำหรับแอพพลิเคชั่นนี้!")
                
                captureSession!.startRunning()
                print("not")
            }
            
        } else {
            //self.dismiss(animated: true) { }
        }
    }
    
    @objc func cancelScan(_ sender: UIButton) {
        self.dismiss(animated: true, completion: {})
        
        //self.present(ChoiceViewController(), animated: true, completion: nil)
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }



}
