//
//  VPTestFatigueController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/3/3.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPTestFatigueController: UIViewController {

    @IBOutlet weak var fatigueStateLabel: UILabel!
    
    @IBOutlet weak var testFatigueProgressLabel: UILabel!
    
    @IBOutlet weak var testFatigueBtn: UIButton!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    @IBAction func startTestFatigueAction(_ sender: UIButton) {
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[7] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有疲劳度功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            fatigueStateLabel.text = "疲劳度状态: "
            testFatigueProgressLabel.text = "测试进度:0%"
        }
        
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestFatigueStart(sender.isSelected) { (testFatigueState, progress, fatigueValue) in
            if sender.isSelected {
                weakSelf.testFatigueProgressLabel.text = "测试进度:" + String(progress) + "%"
                weakSelf.fatigueStateLabel.text = "疲劳度状态: " + String(fatigueValue)
                switch testFatigueState {
                case .testing://正在测试中
                    print("正在测试中")
                case .deviceBusy:
                    _ = AppDelegate.showHUD(message: "设备正忙，结束测试", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .testFail:
                    _ = AppDelegate.showHUD(message: "测试失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .testInterrupt:
                    _ = AppDelegate.showHUD(message: "人为结束测试", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .complete:
                    _ = AppDelegate.showHUD(message: "测试已经完成", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .noFunction:
                    _ = AppDelegate.showHUD(message: "设备暂时没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                }
            }
        }
    }
    
    deinit {//销毁的时候关闭疲劳度测试
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestFatigueStart(false, testResult: nil)
    }
}






