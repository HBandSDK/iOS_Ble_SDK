//
//  VPTemperatureViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/6/5.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPTemperatureViewController: UIViewController {

    @IBOutlet weak var supportFunctionLabel: UILabel!
    @IBOutlet weak var readAutoTestDataBtn: UIButton!
    @IBOutlet weak var manualTestDataBtn: UIButton!
    @IBOutlet weak var monitorSwitch: UISwitch!
    
    var support: Bool = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "体温数据读取"
        support = VPBleCentralManage.sharedBleManager()?.peripheralModel.temperatureType != 0
        supportFunctionLabel.text = support ? "是" : "否"
        
        if support {
            VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingBaseFunctionType(VPSettingBaseFunctionSwitchType.automaticTemperatureTest, settingState: .readFunctionState, complete: { [weak self](state) in
                let open = state == VPSettingFunctionCompleteState.functionCompleteOpen
                self?.monitorSwitch.setOn(open, animated: true)
            })
        }
    }

    // 读取自动测量数据
    @IBAction func readAutoTestDataBtnClick(_ sender: UIButton) {
        // 读取数据完成后存储在数据库中，直接从数据库中拿数据
        // 注意⚠️不要与hrv/血氧/日常数据等并发读取
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSdkStartReadDeviceTemperatureData({ [weak self] (readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress) in
            switch readDeviceBaseDataState {
            case .start:
                break
            case .reading:
                break
            case .complete:
                self?.getDataFromDatabase()
                break
            case .invalid:
                // 设备不支持
                break
            default:
                break
            }
        })
        // 如果自行设计数据库存储，用下面这种方式读
//        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readDeviceAutoTestTemperatureData(withDayNumber: 0, maxPackage: 1, result: { (tempDataArray, totalPackage, currentReadPackage) in
//            guard  let tempDataArray = tempDataArray  else {
//                return
//            }
//            print(tempDataArray)
//        })
    }
    
    func getDataFromDatabase() -> Void {
        let tableID = VPBleCentralManage.sharedBleManager()?.peripheralModel.deviceAddress;
        let arr = VPDataBaseOperation.veepooSDKGetDeviceTemperatureData(withDate: "2021-06-08", andTableID: tableID)
        print(arr as Any)
        let arr1 = VPDataBaseOperation.veepooSDKGetDeviceTemperatureData(withDate: "2021-06-07", andTableID: tableID)
        print(arr1?.count as Any)
        let arr2 = VPDataBaseOperation.veepooSDKGetDeviceTemperatureData(withDate: "2021-06-06", andTableID: tableID)
        print(arr2?.count as Any)
    }
    
    // 手动测量体温
    @IBAction func manualTestDataBtnClick(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_temperatureTestStart(sender.isSelected, result: { [weak self](state, enable, progress, tempValue) in
            if state == .unsupported {
                _ = AppDelegate.showHUD(message: "设备不支持该功能", hudModel: MBProgressHUDModeText, showView: self!.view)
            }
            if state == .close {
                print("结束测量")
            }
            if state == .open {
                if enable {
                    print("进度:\(progress), 体温:\(Double(tempValue)/Double(10))°C")
                    if progress == 100 {
                        _ = AppDelegate.showHUD(message: "测量结束，体温为:\(Double(tempValue)/Double(10))°C", hudModel: MBProgressHUDModeText, showView: self!.view)
                        self!.manualTestDataBtn.isSelected = false
                    }
                }else{
                    print("设备正忙")
                }
            }
        })
    }
    
    @IBAction func monitorSwitchAction(_ sender: UISwitch) {
        if support {
            // 单位设置
//            VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingBaseFunctionType(VPSettingBaseFunctionSwitchType.temperatureUnit, settingState: sender.isOn ? .settingFunctionOpen : .settingFunctionClose, complete: nil)
            // 体温自动监测开关
            VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingBaseFunctionType(VPSettingBaseFunctionSwitchType.automaticTemperatureTest, settingState: sender.isOn ? .settingFunctionOpen : .settingFunctionClose, complete: { [weak self](state) in
                switch state {
                case .functionCompleteUnknown:
                    break
                case .functionCompleteOpen:
                    _ = AppDelegate.showHUD(message: "功能已开启", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
                    break
                case .functionCompleteClose:
                    _ = AppDelegate.showHUD(message: "功能已关闭", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
                    break
                case .functionCompleteFailure:
                    break
                case .functionCompleteComplete:
                    break
                }
            })
        }else{
            _ = AppDelegate.showHUD(message: "设备不支持该功能", hudModel: MBProgressHUDModeText, showView: self.view)
        }
    }
}
