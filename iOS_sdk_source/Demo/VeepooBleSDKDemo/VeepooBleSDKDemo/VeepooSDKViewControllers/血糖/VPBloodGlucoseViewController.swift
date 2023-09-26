//
//  VPBloodGlucoseViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2022/8/5.
//  Copyright © 2022 veepoo. All rights reserved.
//

import UIKit

class VPBloodGlucoseViewController: UIViewController {
    
    @IBOutlet weak var supportFunctionLabel: UILabel!
    
    @IBOutlet weak var privateSingleModelLabel: UILabel!
    @IBOutlet weak var privateMultiModelLabel: UILabel!
    
    @IBOutlet weak var readDataBtn: UIButton!
    @IBOutlet weak var manualTestDataBtn: UIButton!
    
    @IBOutlet weak var privateSingleModelBtn: UIButton!
    @IBOutlet weak var privateMultiModelBtn: UIButton!
    
    var support: Bool = false
    /// 是否支持血糖单校准
    var privateSingleModelSupport: Bool = false
    /// 是否支持血糖多校准
    var privateMultiModelSupport: Bool = false

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "血糖功能"
        support = VPBleCentralManage.sharedBleManager()?.peripheralModel.bloodGlucoseType != 0
        supportFunctionLabel.text = support ? "是" : "否"
        
        let bloodGlucoseType = VPBleCentralManage.sharedBleManager()?.peripheralModel.bloodGlucoseType
        
        // 单校准
        privateSingleModelSupport = bloodGlucoseType == 2
        privateSingleModelLabel.text = privateSingleModelSupport ? "是" : "否"
        privateSingleModelBtn.isEnabled = privateSingleModelSupport
        
        // 多校准
        privateMultiModelSupport = bloodGlucoseType == 4
        privateMultiModelLabel.text = privateMultiModelSupport ? "是" : "否"
        privateMultiModelBtn.isEnabled = privateMultiModelSupport
    }
    
    @IBAction func readDataBtnAction(_ sender: UIButton) {
        let tableID = VPBleCentralManage.sharedBleManager()?.peripheralModel.deviceAddress;
        let dateFormatter = DateFormatter.init()
        dateFormatter.dateFormat = "yyyy-MM-dd"
        dateFormatter.timeZone = TimeZone.init(identifier: "Asia/Shanghai")
        let dateStr = dateFormatter.string(from: Date.init())
        
        let arr = VPDataBaseOperation.veepooSDKGetDeviceBloodGlucoseData(withDate: dateStr, andTableID: tableID)
        print(arr as Any)
    }
    
    @IBAction func manualTestDataBtnAction(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKTestBloodGlucoseStart(sender.isSelected, testResult: { [weak self](state, progress, value) in
            var txt = ""
            
            if state == .unsupported{
                txt = "设备不支持该功能"
            }
            if state == .close {
                txt = "测量结束"
            }
            if state == .lowPower {
                txt = "设备低电"
            }
            if state == .deviceBusy {
                txt = "设备正忙"
            }
            if state == .notWear {
                txt = "设备佩戴检测失败"
            }
            if state == .open {
                txt = "进度：\(progress) % 值：\(value)"
            }
            
            _ = AppDelegate.showHUD(message: txt, hudModel: MBProgressHUDModeText, showView: self!.view)
        });
    }
    
    
    @IBAction func privateSingleModelBtnAction(_ sender: Any) {
        // 设置 setting
//        let testValue = 9.13
//        VPBleCentralManage.sharedBleManager()?.peripheralManage
//            .veepooSDKBloodGlucosePersonal(withOpCode: 1, value: testValue, open: true, result: { [weak self](success, value, isOpen) in
//            _ = AppDelegate.showHUD(message: "设置 \(success), \(value), \(isOpen)", hudModel: MBProgressHUDModeText, showView: self!.view)
//            print("\(success), \(value), \(isOpen)")
//        })
        
        // 读取 read
        VPBleCentralManage.sharedBleManager()?.peripheralManage
            .veepooSDKBloodGlucosePersonal(withOpCode: 2, value: 0, open: true, result: {  [weak self](success, value, isOpen) in
        _ = AppDelegate.showHUD(message: "读取 \(success), \(value), \(isOpen)", hudModel: MBProgressHUDModeText, showView: self!.view)
        })
    }
        
    
    @IBAction func privateMultiModelBtnAction(_ sender: Any) {
        // read 读取
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKBloodGlucoseMultiPersonal(withOpCode: 2, model: nil) { success, model in
            if success {
                guard let model = model else { return }
                print(model)
            }
        }
        
        // setting 设置
//        let model:VPMultiBloodGlucoseModel = .init()
//        model.open = true
//        model.beforeBreakfast = VPMultiBloodGlucoseItemModel(hour: 8, minute: 0, value: 8)
//        // 检查传入的对象是否合理
////        if model.checkAllTimeIsVaild() {
//        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKBloodGlucoseMultiPersonal(withOpCode: 1, model: model) { success, model in
//            if success {
//                guard let model = model else { return }
//                print(model)
//            }
//        }
////        }
    }
    
}

