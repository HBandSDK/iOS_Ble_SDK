//
//  VPPhotoDialViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/1/21.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPPhotoDialViewController: UIViewController {
    
    @IBOutlet weak var dialTypeLabel: UILabel!
    @IBOutlet weak var readPhotoDialDetailButton: UIButton!
    @IBOutlet weak var readDeviceScreenButton: UIButton!
    var photoDialModel : VPPhotoDialModel!
    
    @IBOutlet weak var showPhotoDialViewButton: UIButton!
    var photoDialView : VPPhotoDialView!
    
    var supportPhotoDialFunction:Bool!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "照片表盘"
        // 照片表盘标志位
        supportPhotoDialFunction = (VPBleCentralManage.sharedBleManager()?.peripheralModel.photoDialCount)! > 0
        if !supportPhotoDialFunction {
            _ = AppDelegate.showHUD(message: "不支持照片表盘功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        self.readDeviceScreenButton.sendActions(for: .touchUpInside)
        self.readPhotoDialDetailButton.sendActions(for: .touchUpInside)
    }
    // MARK: - 设备屏幕读取与切换
    
    // 读取设备当前显示的表盘
    // dialType: 0 默认表盘 1 市场表盘 2 照片表盘
    // screenStyle 市场表盘/照片表盘从1开始，默认表盘的从0开始
    @IBAction func readDeviceScreenStyleClick(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingDeviceScreenStyle(0, settingMode: 2, dialType: .photo, result: { [weak self](dialType, screenStyle, settingSuccess) in
            print("读取>> screenStyle: \(screenStyle), settingSuccess:\(settingSuccess)")
            self?.dialTypeLabel.text = "\(dialType.rawValue) - \(screenStyle)"
        })
    }
    
    // 设置设备表盘为照片表盘
    @IBAction func setScreenStyleToPhotoDial(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingDeviceScreenStyle(1, settingMode: 1, dialType: .photo, result: { [weak self](dialType, screenStyle, settingSuccess) in
            print("设置>> screenStyle: \(screenStyle), settingSuccess:\(settingSuccess)")
            self?.readDeviceScreenButton.sendActions(for: .touchUpInside)
        })
    }
    
    // MARK: - 照片表盘传输、元素设置、效果View显示
    // 读取照片表盘信息，获取VPPhotoDialModel模型
    // SDK使用者请自行持有该模型，设置与显示效果View都依据读取上来的模型
    @IBAction func readPhotoDialDetailInfo(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_dialChannel(with: .read, dialType: .photo, photoDialModel: nil, result: { [weak self](photoDialModel, deviceMarketDialModel, error) in
            self?.photoDialModel = photoDialModel! as VPPhotoDialModel
        }, transformProgress: nil);
    }
    
    @IBAction func setPhotoDialToDefault(_ sender: UIButton) {
        if self.photoDialModel == nil {
            return
        }
//        self.photoDialModel.timePosition = .top
        self.photoDialModel.setColor = "00FF00"
        self.photoDialModel.isDefaultBG = true
        self.photoDialModel.transformImage = nil // transformImage必须为空
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_dialChannel(with: .setupPhotoDial, dialType: .photo, photoDialModel: self.photoDialModel, result: { (photoDialModel, deviceMarketDialModel, error) in
            if error != nil {
                print(photoDialModel! as VPPhotoDialModel)
            }
            print(error! as NSError)
        }, transformProgress: nil)
    }
    
    @IBAction func setPhotoDialDetailInfo(_ sender: UIButton) {
        if self.photoDialModel == nil {
            return
        }
//        self.photoDialModel.timePosition = .bottom
        self.photoDialModel.setColor = "FF0000"
        // 传输的图片宽高必须与屏幕的宽高一致 请注意⚠️分辨率为显示分辨率，即1x
        // 240*240
        self.photoDialModel.transformImage = UIImage.init(named: "test_240_240")
        // 240*280
//        self.photoDialModel.transformImage = UIImage.init(named: "test_240_280")
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_dialChannel(with: .setupPhotoDial, dialType: .photo, photoDialModel: self.photoDialModel, result: { ( photoDialModel, deviceMarketDialModel, error) in
            print(error! as NSError)
        }, transformProgress: { (progress) in
            print("进度：\(progress * 100) %")
        })
    }
    var timeIndex:UInt = 1
    var topAndBottomIndex:UInt = 0
    
    @IBAction func showPhotoDialViewButtonClick(_ sender: UIButton) {
        if photoDialView != nil {
            photoDialView.removeFromSuperview()
        }
        timeIndex += 1
        // 圆屏 测试
        if timeIndex > 3 {
            timeIndex = 1 // 圆屏 从1 开始
        }
        
        // 方屏 测试
//        if timeIndex > 7 || timeIndex < 4 {
//            timeIndex = 4 // 方屏从 4 开始
//        }
        
        // 元素轮训
        topAndBottomIndex += 1
        if topAndBottomIndex > 8 {
            topAndBottomIndex = 0
        }
        self.photoDialModel.timePosition = VPPhotoDialTimePosition(rawValue: timeIndex)!

        self.photoDialModel.timeTopPosition = VPPhotoDialTimeTopAndBottomElement(rawValue: topAndBottomIndex)!

        self.photoDialModel.timeBottomPosition = VPPhotoDialTimeTopAndBottomElement(rawValue: topAndBottomIndex)!
        
        photoDialView = VPPhotoDialView.init(photoDialModel: self.photoDialModel)
        photoDialView.zc_x = 20
        photoDialView.zc_y = showPhotoDialViewButton.zc_bottom + 40
        
//        photoDialView.setBgImage(UIImage.init(named: "test_240_240")!)
//        photoDialView.setBgImage(UIImage.init(named: "test_240_280")!)
        photoDialView.showDefaultBgImage()
        
        view.addSubview(photoDialView)
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
