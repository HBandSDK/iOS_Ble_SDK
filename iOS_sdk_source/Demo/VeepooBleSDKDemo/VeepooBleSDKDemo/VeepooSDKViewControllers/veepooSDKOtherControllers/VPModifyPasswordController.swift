//
//  VPModifyPasswordController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/3/2.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPModifyPasswordController: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var currentPassword: UITextField!
    
    @IBOutlet weak var modifyPassword: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        view.endEditing(true)
    }
    
    @IBAction func modifyDevicePassword(_ sender: UIButton) {
        if currentPassword.text != VPBleCentralManage.sharedBleManager().peripheralModel.devicePassword {
            _ = AppDelegate.showHUD(message: "当前密码不匹配", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        if modifyPassword.text?.count != 4 {//这里要在加个是否全部是数字组成，才严谨，开发者自己写吧
            _ = AppDelegate.showHUD(message: "密码必须为4位数字组成", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().veepooSDKSynchronousPassword(with: .SettingPasswordType, password: modifyPassword.text) { (resultType) in
            switch resultType {
            case .resetSuccess:
                _ = AppDelegate.showHUD(message: "设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            default:
                _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
    }
}









