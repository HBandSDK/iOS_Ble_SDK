//
//  VPDevicePulseViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2024/6/20.
//  Copyright © 2024 veepoo. All rights reserved.
//

import UIKit

class VPDevicePulseViewController: UIViewController {
    
    @IBOutlet weak var typeSegControl: UISegmentedControl!
    @IBOutlet weak var minuteSlider: UISlider!
    @IBOutlet weak var levelSlider: UISlider!
    @IBOutlet weak var openSegControl: UISegmentedControl!
    @IBOutlet weak var durationL: UILabel!
    @IBOutlet weak var levelL: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let strArr = ["null", "操作成功", "未知失败", "设备正忙", "充电中", "佩戴检测未通过", "设备端低电"]
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_pulseResultSubscribe { [weak self] state, isDeviceChange, respType, type, level in
            guard let `self` = self else {
                return
            }
            if state == .noFunction {
                _ = AppDelegate.showHUD(message: "不支持该功能", hudModel: MBProgressHUDModeText, showView: self.view)
                return
            }
            if isDeviceChange {
                if state == .open {
                    _ = AppDelegate.showHUD(message: "设备端开启", hudModel: MBProgressHUDModeText, showView: self.view)
                    self.typeSegControl.selectedSegmentIndex = Int(type)
                    self.levelL.text = "\(level)"
                    self.levelSlider.value = Float(level)
                } else {
                    _ = AppDelegate.showHUD(message: "设备端关闭", hudModel: MBProgressHUDModeText, showView: self.view)
                }
            } else {
                _ = AppDelegate.showHUD(message: strArr[Int(respType.rawValue)], hudModel: MBProgressHUDModeText, showView: self.view)
            }
        }
    }

    @IBAction func sendCmdToDeviceAction(_ sender: UIButton) {
        let type:Int32 = Int32(typeSegControl.selectedSegmentIndex)
        let minute:Int32 = Int32(minuteSlider.value)
        let level:Int32 = Int32(levelSlider.value)
        let open:Bool = openSegControl.selectedSegmentIndex == 0
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_setPulseAction(open, type: type, minute: minute, level: level)
    }
    
    @IBAction func durationValueDidChange(_ sender: UISlider) {
        let sliderValue = UInt(sender.value)
        durationL.text = "\(sliderValue)分钟"
    }
    
    @IBAction func levelValueDidChange(_ sender: UISlider) {
        let sliderValue = UInt(sender.value)
        levelL.text = "\(sliderValue)"
    }
    
}
