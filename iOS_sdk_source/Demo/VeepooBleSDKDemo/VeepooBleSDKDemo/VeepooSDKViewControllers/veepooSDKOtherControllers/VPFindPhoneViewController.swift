//
//  VPFindPhoneViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/8/19.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPFindPhoneViewController: UIViewController {

    @IBOutlet weak var textView: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "手环查找手机"
        
        subscribeDeviceDidEnterFindPhone()
        
        // KH70项目定制需求
        subscribeDeviceDidFinishFindPhone()
    }
    
    func subscribeDeviceDidEnterFindPhone() -> Void {
        VPBleCentralManage.sharedBleManager().peripheralManage.receiveDeviceSearchIphoneCommand = {[weak self] in
            self?.printText(">> 收到一次设备查找手机事件")
        }
    }
    
    
    // KH70项目定制需求
    func subscribeDeviceDidFinishFindPhone() -> Void {
        VPBleCentralManage.sharedBleManager().peripheralManage.deviceSearchPhoneDidFinishBlock = {[weak self] in
            self?.printText(">> 收到一次设备退出查找事件")
        }
    }
        
    // KH70项目定制需求
    @IBAction func exitDeviceFindPhone(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceExitSearchPhone()
        self.printText(">> APP主动下发指令，通知设备退出查找")
    }
    
    private func printText(_ str: String){
        self.textView.text.append(str)
        self.textView.insertText("\n")
    }
    
    @IBAction func Clear(_ sender: UIButton) {
        self.textView.text = ""
    }
    
}
