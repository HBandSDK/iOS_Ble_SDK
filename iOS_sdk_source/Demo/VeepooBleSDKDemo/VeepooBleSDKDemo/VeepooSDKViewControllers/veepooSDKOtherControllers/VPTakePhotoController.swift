//
//  VPTakePhotoController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/23.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPTakePhotoController: UIViewController {

    @IBOutlet weak var takePhotoTypeLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "拍照功能"
        
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[6] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有拍照功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        // Do any additional setup after loading the view.
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        //退出界面后退出拍照模式
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingCameraType(.exit, settingAndMonitorResult: nil)
        
    }
    
    @IBAction func takePhotoAction(_ sender: UIButton) {
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingCameraType(sender.tag == 1 ? .exit : .enter) { (cameraType) in
            switch cameraType {
            case .exit:
                weakSelf.takePhotoTypeLabel.text = "当前手环模式:退出拍照模式"
            case .enter://这里接收到进入拍照指令后，App可以调用相机，进入拍照模式
                weakSelf.takePhotoTypeLabel.text = "当前手环模式:进入拍照模式，可以调用相机了"
            case .photo://这里接收到拍照指令后，App调用的相机可以调用拍照功能，进行拍照，进入拍照模式后，手环摇一摇就会收到这个回调
                _ = AppDelegate.showHUD(message: "收到拍照指令，可以拍照了", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
    }

}
