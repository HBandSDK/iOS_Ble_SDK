//
//  VPBloodPrivateSettingController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/17.
//  Copyright © 2017年 zc.All rights reserved.
//

/*
 SDK1.7之后对此模块进行修改，因设备区别，有的是直接设置私人模式，有的需要动态校准，如果需要动态校准的设备，在动态校准过程中要保持正确的佩戴姿势，动态校准时间比较长，如果快的话30秒之内，如果慢的话大概要1-2分钟
 */

import UIKit

class VPBloodPrivateSettingController: UIViewController {

    @IBOutlet weak var systolicLabel: UILabel!
    
    @IBOutlet weak var diastolicLabel: UILabel!
    
    @IBOutlet weak var modeLabel: UILabel!
    
    @IBOutlet weak var systolicSlider: UISlider!
    
    @IBOutlet weak var diastolicSlider: UISlider!
    
    @IBOutlet weak var bloodModeSegControl: UISegmentedControl!
    
    @IBOutlet weak var bloodSettingBtn: UIButton!
    
    @IBOutlet weak var calibrationProgressLabel: UILabel!
    
    var isNew:Bool = false //是否是动态校准
    
    var privateBloodModel: VPDevicePrivateBloodModel?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "血压私人模式设置"
        
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[1] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有此功能", hudModel: MBProgressHUDModeText, showView: view)
            bloodSettingBtn.isEnabled = false
            return
        }
        
        if tbyte[16] == 1 {//如果等于一就是要使用动态校准，否则就是普通模式设置
            bloodSettingBtn.setTitle("动态校准", for: .normal)
            bloodSettingBtn.setTitle("动态校准中", for: .disabled)
            calibrationProgressLabel.isHidden = false
            isNew = true
        }
        
        //要先读取一下手环的数据，这个App显示一般以手环为主
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingPersonalBlood(with: VPDevicePrivateBloodModel(), settingMode: .readFunctionState, successResult: { (devicePrivateModel) in
            weakSelf.privateBloodModel = devicePrivateModel
            if devicePrivateModel?.systolicPressure == 0 && devicePrivateModel?.diastolicPressure == 0 {
                _ = AppDelegate.showHUD(message: "手环还没有设置此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }else {//展示给用户当前手环的值
                _ = AppDelegate.showHUD(message: "读取血压私人模式成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                weakSelf.systolicSlider.value = Float((devicePrivateModel?.systolicPressure)!)
                weakSelf.diastolicSlider.value = Float((devicePrivateModel?.diastolicPressure)!)
                weakSelf.bloodModeSegControl.selectedSegmentIndex = Int((devicePrivateModel?.privateMode)!)
                weakSelf.systolicLabel.text = "高压:" + String((devicePrivateModel?.systolicPressure)!)
                weakSelf.diastolicLabel.text = "低压:" + String((devicePrivateModel?.diastolicPressure)!)
                weakSelf.modeLabel.text = devicePrivateModel?.privateMode == 0 ? "模式:通用" : "模式:私人"
            }
        }) { 
            _ = AppDelegate.showHUD(message: "读取血压私人模式失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }

    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        if isNew == false {//如果没有就不用取消
            return
        }
        //退出界面的时候取消动态校准，校准过程中也可以取消
//        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingPersonalBlood(with: privateBloodModel, settingMode: .settingFunctionCancel, successResult: { (devicePrivateModel) in
//            guard let devicePrivateModel = devicePrivateModel else {
//                return
//            }
            
        }) {
        }
    }

    @IBAction func settingBloodValueAction(_ sender: UISlider) {
        let bloodValue = UInt16(sender.value)
        if sender.tag == 0 {
            systolicLabel.text = "高压:" + String(bloodValue)
        }else {
            diastolicLabel.text = "低压:" + String(bloodValue)
        }
    }
    
    @IBAction func choiceBloodTestModeAction(_ sender: UISegmentedControl) {
        modeLabel.text = bloodModeSegControl.selectedSegmentIndex == 0 ? "模式:通用" : "模式:私人"
    }
    
    @IBAction func startSettingBloodModeAction(_ sender: UIButton) {
        sender.isEnabled = false
        privateBloodModel?.systolicPressure = UInt(systolicSlider.value)
        privateBloodModel?.diastolicPressure = UInt(diastolicSlider.value)
        privateBloodModel?.privateMode = UInt(bloodModeSegControl.selectedSegmentIndex)
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingPersonalBlood(with: privateBloodModel, settingMode: .settingFunction, successResult: { (devicePrivateModel) in
            guard let devicePrivateModel = devicePrivateModel else {
                return
            }
            if devicePrivateModel.settingState == 1 {//普通私人设置
                _ = AppDelegate.showHUD(message: "设置血压私人模式成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                sender.isEnabled = true
            }else if devicePrivateModel.settingState == 6 {//动态校准中
                weakSelf.calibrationProgressLabel.text = "动态校准进度:" + String(describing: devicePrivateModel.calibrationProgress) + "%"
            }else if devicePrivateModel.settingState == 7 {//动态校准中
                _ = AppDelegate.showHUD(message: "动态校准失败，请重试", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                sender.isEnabled = true
            }else if devicePrivateModel.settingState == 8 {//动态校准中
                _ = AppDelegate.showHUD(message: "动态校准成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                weakSelf.calibrationProgressLabel.text = "动态校准进度:100%"
                sender.isEnabled = true
            }else if devicePrivateModel.settingState == 9 {//设备端正在操作，校准失败
                sender.isEnabled = true
                _ = AppDelegate.showHUD(message: "校准失败，校准中请勿操作设备", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
            
        }) {
            sender.isEnabled = true
            _ = AppDelegate.showHUD(message: "设置血压私人模式失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }
    
}








