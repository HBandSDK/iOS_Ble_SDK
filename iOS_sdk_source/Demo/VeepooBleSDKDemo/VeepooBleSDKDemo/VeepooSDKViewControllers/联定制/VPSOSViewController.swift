//
//  VPSOSViewController.swift
//  VeepooBleSDKDemo
//
//  Created by zhangchong on 2020/6/16.
//  Copyright © 2020 zc.All rights reserved.
//

import UIKit

class VPSOSViewController: UIViewController {

    @IBOutlet weak var stateLabel: UILabel!
    
    @IBOutlet weak var messageTextField: UITextField!
    
    let bleManager: VPBleCentralManage = VPBleCentralManage.sharedBleManager()
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        title = "SOS调试"
        bleManager.peripheralManage.receiveSoldierFeedback = {[weak self] in
            self?.stateLabel.text = "收到设备发送的SOS求救信息"
        }
    }
    
    @IBAction func sendCommand(_ sender: UIButton) {
        if bleManager.isConnected == false {
            _ = AppDelegate.showHUD(message: "设备未连接", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        bleManager.peripheralManage.veepooSDKSend {[weak self] (success) in
            self?.stateLabel.text = success ? "发送成功" : "发送失败"
        }
    }
    
    @IBAction func sendMessage(_ sender: UIButton) {
        if bleManager.isConnected == false {
            _ = AppDelegate.showHUD(message: "设备未连接", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        if messageTextField.text?.count == 0 {
            _ = AppDelegate.showHUD(message: "请输入发送信息", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        bleManager.peripheralManage.veepooSDKSend(toSoldierSpecialTask: 0xFF, taskMessage: messageTextField.text) {[weak self] (success) in
            self?.stateLabel.text = success ? "发送成功" : "发送失败"
        }
    }
    
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        view.endEditing(true)
    }

}
