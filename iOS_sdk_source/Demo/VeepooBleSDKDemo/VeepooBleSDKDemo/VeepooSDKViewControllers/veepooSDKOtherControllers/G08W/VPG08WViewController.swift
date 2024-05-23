//
//  VPG08WViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2024/5/23.
//  Copyright © 2024 veepoo. All rights reserved.
//

import UIKit

public enum DataType: Int {
    case heart = 0
    case blood = 1
    case temp = 2
    case bloodOxygen = 3
}

class VPG08WViewController: UIViewController {
    
    @IBOutlet weak var typeSegment: UISegmentedControl!
    @IBOutlet weak var upperSlider: UISlider!
    @IBOutlet weak var floorSlider: UISlider!
    @IBOutlet weak var upperL: UILabel!
    @IBOutlet weak var floorL: UILabel!
    @IBOutlet weak var openSegment: UISegmentedControl!
    @IBOutlet weak var setBtn: UIButton!
    @IBOutlet weak var tipL: UILabel!
    
    private var dataType: DataType! = .heart
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        title = "G08W项目"
        
        // PPG订阅
        let typeArr:[String] = ["绿光", "红光", "红外"]
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_G08WProjectPPGSubscribe { type, dataArr in
            let typeInt = Int(type)
            if let dataArr = dataArr {
                print("类型：\(typeArr[typeInt]), dataArr: \(dataArr)")
            }
        }
        
        let dataTypeArr:[String] = ["心率报警", "血压报警", "体温过高", "血氧过低"]
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_G08WProjectDataAlertSubscribe { [weak self] type, upper, floor, open, error in
            guard let `self` = self else { return }
            if error == nil {
                print("\(dataTypeArr[Int(type)]) - 上限:\(upper), 下限:\(floor), 开启:\(open)")
                self.openSegment.selectedSegmentIndex = open ? 1 : 0
                self.upperSlider.value = Float(upper)
                self.floorSlider.value = Float(floor)
                self.upperL.text = "\(upper)"
                self.floorL.text = "\(floor)"
                _ = AppDelegate.showHUD(message: "读取或设置成功", hudModel: MBProgressHUDModeText, showView: self.view)
            } else {
                _ = AppDelegate.showHUD(message: error?.localizedDescription ?? "操作失败", hudModel: MBProgressHUDModeText, showView: self.view)
            }
        }
        
        // 进来先读心率报警的
        setDefaultUIValue(type: .heart)
        readDeviceDataTypeValue(type: .heart)
    }

    @IBAction func typeChange(_ sender: UISegmentedControl) {
        let dataType = DataType(rawValue: sender.selectedSegmentIndex)
        guard let dataType = dataType else {
            return
        }
        self.dataType = dataType
        setDefaultUIValue(type: dataType)
        readDeviceDataTypeValue(type: dataType)
    }
    
    @IBAction func setBtnAction(_ sender: UIButton) {
        let upper:Int32 = Int32(upperSlider.value)
        let floor:Int32 = Int32(floorSlider.value)
        let opCode:Int32 = Int32(openSegment.selectedSegmentIndex)
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_G08WProjectDataAlert(withOpCode: opCode, type: Int32(dataType.rawValue), upper: upper, floor: floor)
    }
    
    @IBAction func upperSliderValueChange(_ sender: UISlider) {
        let sliderValue = UInt(sender.value)
        upperL.text = "\(sliderValue)"
    }
    
    @IBAction func floorSliderValueChange(_ sender: UISlider) {
        let sliderValue = UInt(sender.value)
        floorL.text = "\(sliderValue)"
    }
}

extension VPG08WViewController {
    private func setDefaultUIValue(type: DataType) {
        switch type {
        case .heart:
            upperSlider.minimumValue = 30
            upperSlider.maximumValue = 250
            floorSlider.minimumValue = 30
            floorSlider.maximumValue = 250
            upperSlider.isEnabled = true
            floorSlider.isEnabled = true
            tipL.isHidden = true
        case .blood:
            upperSlider.minimumValue = 80
            upperSlider.maximumValue = 210
            floorSlider.minimumValue = 80
            floorSlider.maximumValue = 210
            upperSlider.isEnabled = true
            floorSlider.isEnabled = true
            tipL.isHidden = true
        case .temp:
            upperSlider.minimumValue = 120
            upperSlider.maximumValue = 480
            upperSlider.isEnabled = true
            floorSlider.isEnabled = false
            tipL.isHidden = false
        case .bloodOxygen:
            floorSlider.minimumValue = 70
            floorSlider.maximumValue = 99
            upperSlider.isEnabled = false
            floorSlider.isEnabled = true
            tipL.isHidden = true
        }
    }
    
    private func readDeviceDataTypeValue(type: DataType) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_G08WProjectDataAlert(withOpCode: 2, type: Int32(type.rawValue), upper: 0, floor: 0)
    }
}
