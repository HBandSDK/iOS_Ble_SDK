//
//  VPHeartAlarmController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/18.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPHeartAlarmController: UIViewController {

    @IBOutlet weak var heartMaxLabel: UILabel!
    
    @IBOutlet weak var heartMinLabel: UILabel!
    
    @IBOutlet weak var heartAlarmStateLabel: UILabel!
    
    @IBOutlet weak var heartMaxSlider: UISlider!
    
    @IBOutlet weak var heartMinSlider: UISlider!
    
    @IBOutlet weak var heartStateSegControl: UISegmentedControl!
    
    var heartAlarmModel: VPDeviceHeartAlarmModel = VPDeviceHeartAlarmModel(heartMaxValue: 80, heartMinValue: 30, openState: false)
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "心率报警"
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[10] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有心率报警功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        //心率报警功能先读取
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceHeartAlarm(with: VPDeviceHeartAlarmModel(), settingMode: 2, successResult: { (heartAlarmModel) in
            _ = AppDelegate.showHUD(message: "读取成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            weakSelf.heartAlarmModel = heartAlarmModel!
            weakSelf.showDeviceHeartAlarmValue()
        }) {
            _ = AppDelegate.showHUD(message: "读取失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }
    
    @IBAction func heartSliderChangeValueAction(_ sender: UISlider) {
        let sliderValue = UInt(sender.value)
        
        if sender.tag == 0 {
           heartAlarmModel.heartMaxValue = sliderValue
        }else {
            heartAlarmModel.heartMinValue = sliderValue
        }
        showDeviceHeartAlarmValue()
    }
    
    @IBAction func heartStateChangeAction(_ sender: UISegmentedControl) {
        heartAlarmModel.isOpen = sender.selectedSegmentIndex == 1
        showDeviceHeartAlarmValue()
    }
    
    @IBAction func startSettingHeartAlarmAction(_ sender: UIButton) {
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceHeartAlarm(with: heartAlarmModel, settingMode: UInt(heartStateSegControl.selectedSegmentIndex), successResult: { (heartAlarmModel) in
            _ = AppDelegate.showHUD(message: "设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            //下边不执行也可以
            weakSelf.heartAlarmModel = heartAlarmModel!
            weakSelf.showDeviceHeartAlarmValue()
        }) {
            _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }
    
    
    func showDeviceHeartAlarmValue()  {
        heartMaxLabel.text = "心率上限:" + String(heartAlarmModel.heartMaxValue < 80 ? 80 : heartAlarmModel.heartMaxValue)
        heartMinLabel.text = "心率下限:" + String( heartAlarmModel.heartMinValue < 30 ? 30 : heartAlarmModel.heartMinValue)
        heartAlarmStateLabel.text = heartAlarmModel.isOpen ? "状态:开" : "状态:关"
        
        heartMaxSlider.value = Float(heartAlarmModel.heartMaxValue < 80 ? 80 : heartAlarmModel.heartMaxValue)
        heartMinSlider.value = Float( heartAlarmModel.heartMinValue < 30 ? 30 : heartAlarmModel.heartMinValue)
        heartStateSegControl.selectedSegmentIndex = heartAlarmModel.isOpen ? 1 : 0
    }
    
}







