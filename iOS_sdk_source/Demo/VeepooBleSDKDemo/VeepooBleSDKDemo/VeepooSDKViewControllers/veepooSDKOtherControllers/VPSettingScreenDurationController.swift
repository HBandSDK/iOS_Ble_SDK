//
//  VPSettingScreenDurationController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 2018/9/14.
//  Copyright © 2018年 zc.All rights reserved.
//

import UIKit

class VPSettingScreenDurationController: UIViewController {

    @IBOutlet var pickerView: UIPickerView!
    
    var durationModel: VPScreenDurationModel = VPScreenDurationModel()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //1.先判断有没有此功能
        let type = VPBleCentralManage
            .sharedBleManager().peripheralModel.screenDurationType
        if type == 0 {
            _ = AppDelegate.showHUD(message: "该设备没有亮屏时长设置功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        //2.读取当前设备亮屏时长的信息
        VPBleCentralManage.sharedBleManager()
            .peripheralManage.veepooSDKSettingScreenDuration(VPScreenDurationModel(), settingMode: 2, successResult: {[weak self] (durationModel) in
                _ = AppDelegate.showHUD(message: "读取信息成功", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
                self?.durationModel = durationModel!
                self?.updateUI()
        }) {[weak self] in
                _ = AppDelegate.showHUD(message: "读取信息失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
        }
    }

    func updateUI() {
        pickerView.reloadAllComponents()
        var selectRow = durationModel.currentDuration - durationModel.minDuration
        if selectRow < 0 {
            selectRow = 0
        }
        pickerView.selectRow(selectRow, inComponent: 0, animated: true)
    }
    
    //开始设置
    @IBAction func startSetting(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()
            .peripheralManage.veepooSDKSettingScreenDuration(durationModel, settingMode: 1, successResult: {[weak self] (durationModel) in
                _ = AppDelegate.showHUD(message: "设置成功", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            }) {[weak self] in
                _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
        }
    }
}

extension VPSettingScreenDurationController: UIPickerViewDataSource,UIPickerViewDelegate {
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        var rows = durationModel.maxDuration - durationModel.minDuration + 1
        if rows < 0 {
            rows = 0
        }
        return rows
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        if row == durationModel.defaultDuration - durationModel.minDuration {
            return String(row + durationModel.minDuration) + "(default)"
        }
        return String(row + durationModel.minDuration)
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        durationModel.currentDuration = row + durationModel.minDuration
    }
    
}

