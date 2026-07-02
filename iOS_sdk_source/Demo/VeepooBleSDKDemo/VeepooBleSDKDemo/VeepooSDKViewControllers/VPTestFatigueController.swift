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
    
    private var fatigueLevelType = VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel.fatigueLevelType
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    @IBAction func startTestFatigueAction(_ sender: UIButton) {
        if VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel.fatigueLevelType == 0 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有疲劳度功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            fatigueStateLabel.text = "疲劳度状态: "
            testFatigueProgressLabel.text = "测试进度:0%"
        }
        
        if fatigueLevelType == 1 {
            /// 旧的疲劳度测量返回的测量结果是疲劳度的结论 0x00: 测试无效（佩戴不通过，算法结果无效）0x01：不疲劳 0x02：轻度疲劳 0x03：一般疲劳 0x04：重度疲劳
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestFatigueStart(sender.isSelected) {[weak self]
                (testFatigueState, progress, fatigueValue) in
                guard let weakSelf = self else { return }
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
        } else if fatigueLevelType == 2 {
            /// 新的疲劳度测量返回的测量结果是疲劳度的数值 con 1:开启 2关闭
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_fatigueLevelTest(sender.isSelected) {[weak self] con, ack, progress, value in
                guard let weakSelf = self else { return }
                print(con,ack, progress,value)
                if ack == .testing {
                    if con == 1 {
                        weakSelf.testFatigueProgressLabel.text = "测试进度:" + String(progress) + "%"
                        if progress == 100 {
                            weakSelf.fatigueStateLabel.text = "疲劳度值: " + String(value)
                        }
                    }
                } else {
                    
                }
            }
        }
        
        
    }
    
    deinit {//销毁的时候关闭疲劳度测试
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestFatigueStart(false, testResult: nil)
    }
}






