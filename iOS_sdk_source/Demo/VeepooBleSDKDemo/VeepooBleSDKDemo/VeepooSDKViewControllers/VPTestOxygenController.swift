//
//  VPTestOxygenController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/3/3.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPTestOxygenController: UIViewController {

    @IBOutlet weak var currentOxygenValueLabel: UILabel!
    @IBOutlet weak var currentRateValueLabel: UILabel!
    
    @IBOutlet weak var testOxygenBtn: UIButton!
    @IBOutlet weak var testRateBtn: UIButton!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
//        let arr = VPDataBaseOperation.veepooSDKGetDeviceOxygenData(withDate: "2019-06-18", andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        let arr = VPDataBaseOperation.veepooSDKGetDeviceOxygenData(withDate: "2020-05-27", andTableID: "FF:E4:71:43:BC:D9")
        
        let oxygenCurview = VPOxygenCurveView(vpOxygenCurveType:VPOxygenCurveTypeOxygen)
        
        oxygenCurview?.frame = CGRect(x: 0, y: 200, width: 300, height: 300)
        
        oxygenCurview?.oneDayOxygens = arr
        
        
        view .addSubview(oxygenCurview!)
        
        // Do any additional setup after loading the view.
    }

    @IBAction func startTestOxygenAction(_ sender: UIButton) {
//        sender.isSelected = !sender.isSelected
//        VPBleCentralManage.sharedBleManager()
//            .peripheralManage.veepooSDKTestECGStart(sender.isSelected) { (state, progress1, model) in
//
//        }
//
//        return
        
        if VPBleCentralManage.sharedBleManager().peripheralModel.oxygenType == 0 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有血氧功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            currentOxygenValueLabel.text = "当前血氧值: "
        }
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestOxygenStart(sender.isSelected) { (testOxygenState, oxygenValue) in
            if  sender.isSelected {
                switch testOxygenState {
                case .start:
                    _ = AppDelegate.showHUD(message: "正在做测试准备，请保持正确姿势", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                case .testing: //正在检测血氧，已经测出血氧值
                    weakSelf.currentOxygenValueLabel.text = "当前血氧值:" + String(oxygenValue) + "%"
                case .notWear: //佩戴检测没有通过，测试已经结束
                    _ = AppDelegate.showHUD(message: "佩戴检测未通过", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .deviceBusy: //设备正忙不能测试了，测试已经结束
                    _ = AppDelegate.showHUD(message: "设备端正在操作", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .over: //测试正常结束，人为结束
                    _ = AppDelegate.showHUD(message: "测试结束", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .noFunction: //设备没有此功能
                    _ = AppDelegate.showHUD(message: "设备没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .calibration: //校准中
                    weakSelf.currentOxygenValueLabel.text = "校准进度:" + String(oxygenValue) + "%"
                case .calibrationComplete: //校准完成
                    weakSelf.currentOxygenValueLabel.text = "校准进度:" + String(oxygenValue) + "%"
                default:
                    break
                }
            }else {
                if testOxygenState == .over {
                    _ = AppDelegate.showHUD(message: "测试结束", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                }
            }
        }
    }
    
    @IBAction func startTestRateAction(_ sender: UIButton) {//开始测试呼吸率
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionDataTwo.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[7] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有呼吸率功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        sender.isSelected = !sender.isSelected
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBreathingRateStart(sender.isSelected) { (testBreathingRateState, testProgress, testValue) in
            if  sender.isSelected {
                switch testBreathingRateState {
                case .start:
                    _ = AppDelegate.showHUD(message: "正在做测试准备，请保持正确姿势", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                case .testing: //正在检测呼吸率
                    weakSelf.currentRateValueLabel.text = "测试进度:" + String(testProgress) + "%"
                case .notWear: //佩戴检测没有通过，测试已经结束
                    weakSelf.currentOxygenValueLabel.text = "佩戴检测未通过"
                    sender.isSelected = false
                case .deviceBusy: //设备正忙不能测试了，测试已经结束
                    weakSelf.currentRateValueLabel.text = "设备端正在操作"
                    sender.isSelected = false
                case .over: //测试正常结束，人为结束
                    weakSelf.currentRateValueLabel.text = "测试结束"
                    sender.isSelected = false
                case .complete: //正常完成
                    weakSelf.currentRateValueLabel.text = "呼吸率:" + String(testValue) + "%" + "次/分"
                    sender.isSelected = false
                case .failure: //测试无效
                    weakSelf.currentRateValueLabel.text = "测试无效"
                    sender.isSelected = false
                case .noFunction: //设备没有此功能
                    weakSelf.currentRateValueLabel.text = "设备没有此功能"
                    sender.isSelected = false
                }
            }else {
                if testBreathingRateState == .over {
                    weakSelf.currentRateValueLabel.text = "测试结束"
                }
            }
        }
    }
    
    deinit {//销毁的时候关闭血氧测试
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestOxygenStart(false, testResult: nil)
    }

}
