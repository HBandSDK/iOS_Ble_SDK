//
//  VPDFUController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/23.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPDFUController: UIViewController {

    @IBOutlet weak var dfuProgressLabel: UILabel!
    
    @IBOutlet weak var currentVersionLabel: UILabel!
    
    @IBOutlet weak var updateVersionLabel: UILabel!
    
    @IBOutlet weak var updateDesTextView: UITextView!
    
    
    
    //要声明一个全局属性，固件升级过程中请不要操作手机
    let dufOperationManager: VPDFUOperation = VPDFUOperation.dfuOperationShare()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "固件升级"
        // Do any additional setup after loading the view.
        currentVersionLabel.text = "当前版本: " + VPBleCentralManage.sharedBleManager().peripheralModel.deviceVersion
        
        if (VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion == nil) {
            updateVersionLabel.text = "升级版本: " + "没有新版本"
        }else {
            //下边是升级版本和升级新固件描述
            updateVersionLabel.text = "升级版本: " + VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion
            updateDesTextView.text = VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersionDes.replacingOccurrences(of: "$", with: "\n")
        }
    }

    @IBAction func startDFUAction(_ sender: UIButton) {
        if sender.isSelected {
            return
        }
        if (VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion == nil) {
            dfuProgressLabel.text = "没有新固件，暂时不用升级"
            return
        }
        
        dfuProgressLabel.text = "准备升级"
        sender.isSelected = true
        unowned let weakSelf = self
        dufOperationManager.veepooSDKStartDfu { (dfuProgress, deviceDFUState) in
            switch deviceDFUState {
            case .fileNotExist:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级文件不存在，不能升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .start:
                _ = AppDelegate.showHUD(message: "开始升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .updating:
                weakSelf.dfuProgressLabel.text = "升级进度: " + String(dfuProgress) + "%"
            case .success:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .failure:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
