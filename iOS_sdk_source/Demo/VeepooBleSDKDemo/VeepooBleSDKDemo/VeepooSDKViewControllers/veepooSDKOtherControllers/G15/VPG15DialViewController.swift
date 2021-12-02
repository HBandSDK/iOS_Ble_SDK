//
//  VPG15DialViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/9/16.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPG15DialViewController: UIViewController {
    @IBOutlet weak var imageView1: UIImageView!
    @IBOutlet weak var imageView2: UIImageView!
    @IBOutlet weak var imageView3: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "G15表盘"
        imageView1.image = imageWithUIColor(color: .red)
        imageView2.image = imageWithUIColor(color: .green)
        imageView3.image = imageWithUIColor(color: .blue)
    }
    
    @IBAction func transformBtn1(_ sender: UIButton) {
        let imageView = UIImageView.init(frame: CGRect.init(origin: .zero, size: .init(width: 240, height: 240)))
        imageView.image = imageWithUIColor(color: .red)
        let label = UILabel.init(frame: .init(x: 0, y: 0, width: 240, height: 240))
        label.text = "个人信息"
        label.textColor = .white
        imageView.addSubview(label)
        sendImageDataToDevice(imageView: imageView, type: .personalProfile)
    }
    
    @IBAction func transformBtn2(_ sender: UIButton) {
        let imageView = UIImageView.init(frame: CGRect.init(origin: .zero, size: .init(width: 240, height: 240)))
        imageView.image = imageWithUIColor(color: .green)
        let label = UILabel.init(frame: .init(x: 0, y: 0, width: 240, height: 240))
        label.text = "主题1"
        label.textColor = .white
        imageView.addSubview(label)
        sendImageDataToDevice(imageView: imageView, type: .pictureTheme1)
    }
    
    @IBAction func transformBtn3(_ sender: UIButton) {
        let imageView = UIImageView.init(frame: CGRect.init(origin: .zero, size: .init(width: 240, height: 240)))
        imageView.image = imageWithUIColor(color: .blue)
        let label = UILabel.init(frame: .init(x: 0, y: 0, width: 240, height: 240))
        label.text = "主题2"
        label.textColor = .white
        imageView.addSubview(label)
        sendImageDataToDevice(imageView: imageView, type: .pictureTheme2)
    }
    
    @IBAction func transformBtn4(_ sender: UIButton) {
        let imageView = UIImageView.init(frame: CGRect.init(origin: .zero, size: .init(width: 240, height: 240)))
        imageView.image = imageWithUIColor(color: .cyan)
        let label = UILabel.init(frame: .init(x: 0, y: 0, width: 240, height: 240))
        label.text = "二维码"
        label.textColor = .black
        imageView.addSubview(label)
        sendImageDataToDevice(imageView: imageView, type: .appQRCode)
    }
    
    func sendImageDataToDevice(imageView:UIImageView, type:VPG15DialViewTransformType) -> Void {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_G15Transform(with: transformView(imageView: imageView), type: type, result: { (obj, error) in
            if error != nil {
                print(error! as NSError)
            }
        }, transformProgress: { progress in
            print("进度：\(progress)")
        })
    }
    
    func imageWithUIColor(color:UIColor) -> UIImage {
        let rect = CGRect.init(x: 0, y: 0, width: 1, height: 1)
        UIGraphicsBeginImageContext(rect.size)
        let context = UIGraphicsGetCurrentContext()!
        context.setFillColor(color.cgColor)
        context.fill(rect)
        let image = UIGraphicsGetImageFromCurrentImageContext()!
        UIGraphicsEndImageContext()
        return image
    }
    
    func transformView(imageView:UIImageView) -> UIImage {
        UIGraphicsBeginImageContextWithOptions(CGSize.init(width: 240, height: 240), false, 1)
        imageView.layer.render(in: UIGraphicsGetCurrentContext()!)
        let image = UIGraphicsGetImageFromCurrentImageContext()!
        return image
    }

}
