//
//  VPSettingDeviceGPSViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/3/11.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

typealias SendGPSToDeviceTask = (_ ackState:NSInteger,_ GPSState:NSInteger,_ model:VPDeviceGPSModel) -> ()

class VPSettingDeviceGPSViewController: UIViewController {
    
    @IBOutlet weak var longitudeField: UITextField!
    @IBOutlet weak var latitudeField: UITextField!
    @IBOutlet weak var timezoneField: UITextField!
    @IBOutlet weak var timestampField: UITextField!
    @IBOutlet weak var altitudeTextField: UITextField!
    
    @IBOutlet weak var AGPSButton: UIButton!
    
    @IBOutlet weak var textView: UITextView!
    var deviceGPSModel: VPDeviceGPSModel!
    var KAABAGPSModel: VPDeviceKAABAGPSModel!
    
    @IBOutlet weak var timestampField2: UITextField!
    
    var sendGPSToDeviceTask: SendGPSToDeviceTask!
    var sendTimer: Timer!
    var ackState: NSInteger = 0
    
    @IBOutlet weak var AppSendGPSBtn: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        deviceGPSModel = VPDeviceGPSModel.init()
        KAABAGPSModel = VPDeviceKAABAGPSModel.init()
        // Do any additional setup after loading the view.
        timestampField.text = String(format: "%.0f", Date().timeIntervalSince1970)
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
            self?.printText(str)
            if model.totalCount == model.currentCount {
                self?.printText("诵经次数读取完成")
            }
        })
    }
    
    @IBAction func KAABAGPSSettingBtn(_ sender: UIButton) {
        KAABAGPSModel.longitude = Int32((Double(longitudeField.text!) ?? 0) * 100000)
        KAABAGPSModel.latitude = Int32((Double(latitudeField.text!) ?? 0) * 100000)
        KAABAGPSModel.altitude = Int16(altitudeTextField.text!) ?? 0
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_setKAABAGPS(with: KAABAGPSModel, result: { [weak self](state) in
            _ = AppDelegate.showHUD(message: state == 1 ? "设置成功" : "设置失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
        })
    }
    
    
    /// 设备主动要求App下发GPS数据
    @IBAction func AppSendGPSToDeviceBtn(_ sender: UIButton) {
        _ = AppDelegate.showHUD(message: "已点击", hudModel: MBProgressHUDModeText, showView: view)
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_sendGPSDataToDevice({ [weak self](state, callBack) in
            self?.SendGPSToDeviceControl(state, callBack: callBack!)
        })
    }
    
    private func SendGPSToDeviceControl(_ state: NSInteger, callBack: @escaping SendGPSToDeviceTask){
        // callback 赋值
        sendGPSToDeviceTask = callBack
        ackState = state
        if state == 0x01 {
            AppSendGPSBtn.isEnabled = false
            if sendTimer == nil {
                sendTimer = Timer.scheduledTimer(withTimeInterval: 3.0, repeats: true, block: { [weak self](Timer) in
                    self?.SendTimerAction()
                })
            }
        }
        if state == 0x02 {
            AppSendGPSBtn.isEnabled = true
            // 销毁定时器
            DestroySendTimer()
            // 发结束的 ack 与 结束包
            self.SendTimerAction()
            // 销毁Task闭包（block）
            sendGPSToDeviceTask = nil
            // 销毁block
            self.destroyBlock()
        }
    }
    
    // 销毁block
    private func destroyBlock(){
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_sendGPSDataToDevice(nil)
    }
    
    // 定时器循环操作
    @objc private func SendTimerAction(){
        if (sendGPSToDeviceTask != nil) {
            let gpsModel = VPDeviceGPSModel.init()
            // ... gpsModel 赋值
            gpsModel.longitude = Int32((Double(longitudeField.text!) ?? 0) * 100000)
            gpsModel.latitude = Int32((Double(latitudeField.text!) ?? 0) * 100000)
            gpsModel.timezone = Int16(timezoneField.text!) ?? 0
            gpsModel.timestamp = Int(timestampField.text!) ?? 0
            // GPSState 0x01 表示GPS信号正常， 0x02表示信号弱，0x03表示权限未开启
            let GPSState: NSInteger = 0x01
            sendGPSToDeviceTask(ackState, GPSState, gpsModel)
        }
    }
    
    /// 销毁定时器操作
    func DestroySendTimer() {
        guard let sendTimer1 = sendTimer else {
            return
        }
        sendTimer1.invalidate()
        sendTimer = nil
    }
    
    @IBAction func AGPSBtn(_ sender: UIButton) {
        let apgsFunction = VPBleCentralManage.sharedBleManager()?.peripheralModel.agpsFunction;
        print("是否有AGPS功能: \(apgsFunction == 1 ? "是":"否")")
        
//        let path = Bundle.main.path(forResource: "LTEPH_GPS_1", ofType: "rtcm")
//        let fileUrl = URL(fileURLWithPath: path!)
        
        AGPSButton.isEnabled = false
        
        var fileUrl = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first
        fileUrl?.appendPathComponent("LTEPH_GPS_1-7.rtcm")
        
        let timestamp = Int(timestampField2.text!) ?? 0
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_AGPSTransform(withFileUrl: fileUrl, timestamp: timestamp, result: { [weak self](photoDialModel, marketDialModel, error) in
            self?.AGPSButton.isEnabled = true
            if error != nil {
                print(error! as NSError)
                self?.printText("\(error! as NSError)")
            }
        }, transformProgress: { [weak self](progress) in
            let proVlaue = Int(progress * 100)
            let proStr = "进度: \(proVlaue) %"
            print(proStr)
            if(proVlaue % 2 == 0){
                self?.printText(proStr)
            }
        })
    }
    
    private func printText(_ str: String){
        self.textView.text.append(str)
        self.textView.insertText("\n\n")
        self.textView.scrollRangeToVisible(NSMakeRange(self.textView.text.count, 1))
    }
    
    // 设备主动上报GPS数据
    @IBAction func showGPS(_ sender: UIButton) {
        let vc = VPMapGPSTagViewController.init()
        self.navigationController?.pushViewController(vc, animated: true)
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

