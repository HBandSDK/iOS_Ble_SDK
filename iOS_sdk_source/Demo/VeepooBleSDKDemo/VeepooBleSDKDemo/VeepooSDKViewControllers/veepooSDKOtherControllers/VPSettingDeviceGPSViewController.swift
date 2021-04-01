//
//  VPSettingDeviceGPSViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/3/11.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPSettingDeviceGPSViewController: UIViewController {
    
    @IBOutlet weak var longitudeField: UITextField!
    @IBOutlet weak var latitudeField: UITextField!
    @IBOutlet weak var timezoneField: UITextField!
    @IBOutlet weak var timestampField: UITextField!
    @IBOutlet weak var altitudeTextField: UITextField!
    
    @IBOutlet weak var textView: UITextView!
    var deviceGPSModel: VPDeviceGPSModel!
    
    @IBOutlet weak var timestampField2: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        deviceGPSModel = VPDeviceGPSModel.init()
        // Do any additional setup after loading the view.
        timestampField.text = String(format: "%.0f", Date().toGlobalTime().timeIntervalSince1970)
        timestampField2.text = String(format: "%.0f", Date().timeIntervalSince1970)
    }

    @IBAction func sendCommandBtnClick(_ sender: UIButton) {
        if longitudeField!.text!.isEmpty ||
            latitudeField!.text!.isEmpty ||
            timezoneField!.text!.isEmpty ||
            timestampField!.text!.isEmpty ||
            altitudeTextField!.text!.isEmpty {
            _ = AppDelegate.showHUD(message: "参数不能为空", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        // 判断时区是否是15的倍数
        if (Int16(timezoneField.text!) ?? 0) % 15 != 0 {
            _ = AppDelegate.showHUD(message: "时区只能是15分钟的倍数", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        // 自行加上经纬度的范围验证
        
        deviceGPSModel.longitude = Int32((Double(longitudeField.text!) ?? 0) * 100000)
        deviceGPSModel.latitude = Int32((Double(latitudeField.text!) ?? 0) * 100000)
        deviceGPSModel.timezone = Int16(timezoneField.text!) ?? 0
        deviceGPSModel.timestamp = Int(timestampField.text!) ?? 0
        deviceGPSModel.altitude = Int16(altitudeTextField.text!) ?? 0
        
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_setDeviceGPSAndTimezone(with: deviceGPSModel, result: { [weak self](state) in
            _ = AppDelegate.showHUD(message: state == 1 ? "设置成功" : "设置失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
        })
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
    }
    
    // 诵经计数读取
    @IBAction func hadjCountReadBtn(_ sender: UIButton) {
//        let timeFormatter = DateFormatter()
//        //日期显示格式，可按自己需求显示
//        timeFormatter.dateFormat = "yyyy-MM-dd"
//        let strNowTime = timeFormatter.date(from: timeFormatter.string(from: Date()))
//        // 当天开始时间戳
//        let toDayTimestamp = Int(UInt64.init(strNowTime!.timeIntervalSince1970))
        // 当前时间戳
//        let currentTimestamp = Int(UInt64.init(Date().timeIntervalSince1970))
        let timestamp = Int(timestampField2.text!) ?? 0
        // timestamp 读取哪个时间戳之后的数据，返回结束时间戳大于下发的这个时间戳的数据 诵经通道最多纪录31天的数据
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readHadjCount(withTimestamp: timestamp, result: { [weak self](model) in
            let model = model! as VPDeviceHadjCountModel
            let str = "当前包诵经次数:\(model.currentCount) 开始时间戳:\(model.startTimestamp) 结束时间戳:\(model.endTimestamp)"
            self?.textView.text.append(str)
            self?.textView.insertText("\n\n")
        })
    }
}

extension Date {

    // Convert local time to UTC (or GMT)
    func toGlobalTime() -> Date {
        let timezone = TimeZone.current
        let seconds = -TimeInterval(timezone.secondsFromGMT(for: self))
        return Date(timeInterval: seconds, since: self)
    }

    // Convert UTC (or GMT) to local time
    func toLocalTime() -> Date {
        let timezone = TimeZone.current
        let seconds = TimeInterval(timezone.secondsFromGMT(for: self))
        return Date(timeInterval: seconds, since: self)
    }

}

