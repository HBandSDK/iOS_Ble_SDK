//
//  VPPPGAccelerationViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/10/24.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPPPGAccelerationViewController: UIViewController {
    
    override func viewDidLoad() {
        /* 获取原始数据和实时传输数据上报,都会存在文件里,直接导出可以查看 */
        super.viewDidLoad()
        view.backgroundColor = .white
        self.title = "JH58定制PPG和加速度原始数据"
        creatMainView()
        getMeasurementModeState(type: 1)
        // Do any additional setup after loading the view.
    }
    
    let segControl: UISegmentedControl = {
        let seg = UISegmentedControl(items: ["全关","模式1","模式2"])
        seg.selectedSegmentIndex = 0
        return seg
    }()
    
    lazy var textView: UITextView = {

        return UITextView()
    }()
    
    var hud: MBProgressHUD?
    
    var checkTimeInterval:TimeInterval = 0
    
    let ppgAccfileHandle = VPFileHandleManager()
    let realTimePPGfileHandle = VPFileHandleManager()
    let realTimeAccfileHandle = VPFileHandleManager()

    var currentGroup :Int = 0
    var currentText :String = ""
    
    func dataToHexString(_ data: Data) -> String {
        return data.map { String(format: "%02x", $0) }.joined()
    }

    
    func creatMainView(){
        //监听设备请求实时传输上报
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58MonitorDeviceReqRealTimeTransmission {[weak self] open in
            guard let weakSelf = self else {return}
            weakSelf.showDeviceReqRealTimeAlertView(open: open)
        }
        //监听设备修改测量模式上报
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58MonitorMeasurementMode {[weak self] state in
            guard let weakSelf = self else {return}
            weakSelf.segControl.selectedSegmentIndex = Int(state.rawValue - 1)
        }
        //监听实时传输PPG数据上报
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58MonitorRealTimeTransmissionPPGData {[weak self] array in
            guard let weakSelf = self else {return}
            if let str = array?.componentsJoined(by: ",") {
                weakSelf.realTimePPGfileHandle.writeText(str)
            }
        }
        //监听实时传输加速度数据上报
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58MonitorRealTimeTransmissionAccelerationData { [weak self] array in
            guard let weakSelf = self else {return}
            var textArray = [String]()
            if let array = array {
                for model in array {
                    if let accModel = model as? VPAccelerationModel {
                        let str = "加速度x:" + String(accModel.x) + "y:" + String(accModel.y) + "z:" + String(accModel.z)
                        textArray.append(str)
                    }
                }
            }
            let str = String(textArray.joined(separator: " "))
            weakSelf.realTimeAccfileHandle.writeText(str)
        }
        
        ppgAccfileHandle.configureFilePath("PPGAccData")
        realTimePPGfileHandle.configureFilePath("RealTimePPGData")
        realTimeAccfileHandle.configureFilePath("RealTimeAccData")
        
        let label1 = UILabel(frame: CGRect(x: 20, y: 5, width: UIScreen.main.bounds.width-40, height: 50))
        label1.text = "/* 获取原始数据和实时传输数据上报的数据,都会存在文件里,直接导出可以查看 */"
        label1.font = .systemFont(ofSize: 14)
        label1.numberOfLines = 0
        label1.textColor = .red
        view.addSubview(label1)
        
        
        let label = UILabel(frame: CGRect(x: 20, y: 40, width: 80, height: 50))
        label.text = "测量模式:"
        view.addSubview(label)
        
        view.addSubview(self.segControl)
        self.segControl.frame = CGRect(x: CGRectGetMaxX(label.frame) + 10, y: 0, width: 150, height: 40)
        self.segControl.center.y = label.center.y
        self.segControl.addTarget(self, action: #selector(valueChange), for: .valueChanged)
        
        let btn = UIButton(frame: CGRect(x: CGRectGetMaxX(self.segControl.frame) + 20, y: 0, width: 100, height: 40))
        btn.setTitle("重新获取", for: .normal)
        btn.backgroundColor = .orange
        btn.layer.cornerRadius = 4;
        btn.center.y = label.center.y
        btn.addTarget(self, action: #selector(getMeasurementModeAction), for: .touchUpInside)
        view.addSubview(btn)
        
        
        let getModeBtn1 = UIButton(frame: CGRect(x: 20, y: CGRectGetMaxY(self.segControl.frame)+30, width: 160, height: 50));
        getModeBtn1.setTitle("获取模式1数据", for: .normal)
        getModeBtn1.backgroundColor = .blue
        getModeBtn1.layer.cornerRadius = 4
        view.addSubview(getModeBtn1)
        getModeBtn1.addTarget(self, action: #selector(getModeBtn1Action), for: .touchUpInside)
        
        let getModeBtn2 = UIButton(frame: CGRect(x: UIScreen.main.bounds.width-CGRectGetWidth(getModeBtn1.frame)-20, y: CGRectGetMaxY(self.segControl.frame)+30, width: CGRectGetWidth(getModeBtn1.frame), height: CGRectGetHeight(getModeBtn1.frame)));
        getModeBtn2.setTitle("获取模式2数据", for: .normal)
        getModeBtn2.backgroundColor = .green
        getModeBtn2.layer.cornerRadius = 4
        view.addSubview(getModeBtn2)
        getModeBtn2.addTarget(self, action: #selector(getModeBtn2Action), for: .touchUpInside)
        
        
        let timePicker = UIDatePicker(frame: CGRect(x: CGRectGetMinX(getModeBtn1.frame), y: CGRectGetMaxY(getModeBtn1.frame)+20, width: CGRectGetWidth(getModeBtn1.frame), height: CGRectGetWidth(getModeBtn1.frame)))
        timePicker.datePickerMode = .dateAndTime // 设置为时间模式[citation:5]
        timePicker.timeZone = TimeZone.current
        let calendar = Calendar.current
        let today = Date()
        if let startOfDay = calendar.date(bySettingHour: 0, minute: 0, second: 0, of: today) {
            timePicker.date = startOfDay
            self.checkTimeInterval = startOfDay.timeIntervalSince1970;
        }
        timePicker.addTarget(self, action: #selector(timeChanged(picker:)), for: .valueChanged)
        view.addSubview(timePicker)
        
        
        let shareBtn = UIButton(frame: CGRect(x: 20, y: CGRectGetMaxY(timePicker.frame)+30, width: 160, height: 50));
        shareBtn.setTitle("导出数据", for: .normal)
        shareBtn.backgroundColor = .blue
        shareBtn.layer.cornerRadius = 4
        view.addSubview(shareBtn)
        shareBtn.addTarget(self, action: #selector(shareAction), for: .touchUpInside)
        
        let clearBtn = UIButton(frame: CGRect(x: UIScreen.main.bounds.width-CGRectGetWidth(getModeBtn1.frame)-20, y: CGRectGetMinY(shareBtn.frame), width: CGRectGetWidth(getModeBtn1.frame), height: CGRectGetHeight(getModeBtn1.frame)));
        clearBtn.setTitle("清除数据", for: .normal)
        clearBtn.backgroundColor = .green
        clearBtn.layer.cornerRadius = 4
        view.addSubview(clearBtn)
        clearBtn.addTarget(self, action: #selector(clearAction), for: .touchUpInside)
        
        
        let openRealTimeBtn = UIButton(frame: CGRect(x: 20, y: CGRectGetMaxY(shareBtn.frame)+30, width: 160, height: 50));
        openRealTimeBtn.tag = 1000
        openRealTimeBtn.setTitle("开启实时数据传输", for: .normal)
        openRealTimeBtn.backgroundColor = .blue
        openRealTimeBtn.layer.cornerRadius = 4
        view.addSubview(openRealTimeBtn)
        openRealTimeBtn.addTarget(self, action: #selector(realTimeAction(btn:)), for: .touchUpInside)
        
        
        let closeRealTimeBtn = UIButton(frame: CGRect(x: UIScreen.main.bounds.width-CGRectGetWidth(openRealTimeBtn.frame)-20, y: CGRectGetMinY(openRealTimeBtn.frame), width: CGRectGetWidth(openRealTimeBtn.frame), height: CGRectGetHeight(openRealTimeBtn.frame)));
        closeRealTimeBtn.tag = 1001
        closeRealTimeBtn.setTitle("关闭实时数据传输", for: .normal)
        closeRealTimeBtn.backgroundColor = .green
        closeRealTimeBtn.layer.cornerRadius = 4
        view.addSubview(closeRealTimeBtn)
        closeRealTimeBtn.addTarget(self, action: #selector(realTimeAction(btn:)), for: .touchUpInside)
        
        self.hud=AppDelegate.showHUDNoHide(message: "", hudModel: MBProgressHUDModeText, showView: self.view)
        
        textView.frame = CGRect(x: 20, y: CGRectGetMaxY(closeRealTimeBtn.frame)+10, width: UIScreen.main.bounds.width-40, height: CGRectGetHeight(self.view.frame) - CGRectGetMaxY(closeRealTimeBtn.frame)-80)
        textView.isEditable = false
        textView.layoutManager.allowsNonContiguousLayout = false
        view.addSubview(textView)
    }
    
    func showDeviceReqRealTimeAlertView(open :Bool){
        let title = open ? "请求开始实时传输" : "请求关闭实时传输"
        let alert = UIAlertController(title: title, message: "", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "拒绝", style: .cancel, handler: { action in
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58ResDeviceRealTimeTransmission(false)
        }))
        alert.addAction(UIAlertAction(title: "同意", style: .default, handler: { action in
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58ResDeviceRealTimeTransmission(true)
        }))
        self.present(alert, animated: true)
    }
    
    @objc func realTimeAction(btn :UIButton){
        //只有开始测量模式2而且是设备决定是否开启
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58ReqRealTimeTransmission(btn.tag == 1000 ? true : false) {[weak self] success in
            guard let weakSelf = self else {return}
            let str = success ? "成功" : "失败"
            weakSelf.hud?.show(true)
            weakSelf.hud?.labelText = str
            weakSelf.hud?.hide(true, afterDelay: 1.0)
        }
    }
    
    @objc func getModeBtn1Action(){
        getPPGAccelerationData(mode: .modeOne)
    }
    
    @objc func getModeBtn2Action(){
        getPPGAccelerationData(mode: .modeTwo)
    }
    
    
    
    @objc func timeChanged(picker :UIDatePicker){
        let selectedDate = picker.date
        let dateFormatter = DateFormatter()
        dateFormatter.timeZone = TimeZone.current
        dateFormatter.locale = Locale(identifier: "zh_CN")
        // 3. 设置日期和时间格式
        dateFormatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
        self.checkTimeInterval = selectedDate.timeIntervalSince1970
        let formattedDate = dateFormatter.string(from: selectedDate)
        print("选择的日期和时间: \(formattedDate))")
    }
    
    func getPPGAccelerationData(mode :VPJH58MeasurementModeState){
        self.currentText = mode == .modeOne ? "获取模式1数据" : "获取模式2数据"
        self.textView.text = ""
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58GetPPGAndAccelerationRawData(withMeasurementMode: mode, andTimestamp: self.checkTimeInterval){[weak self] group, DT, DTS in
            guard let weakSelf = self else {return}
            weakSelf.currentGroup = group
            weakSelf.textView.text = weakSelf.currentText + "\n" + String(format: "第%d组,(%d/%d)", group+1,DT,DTS)
            if DT == 0 {
                weakSelf.textView.scrollToBottom()
            }
            if DT == DTS {
                weakSelf.currentText = weakSelf.textView.text
            }
        } andResult: {[weak self] error,array in
            guard let array = array,let weakSelf = self else {return}
            weakSelf.hud?.show(true)
            if error == nil {
                if array.count != 0 {
                    for model in array {
                        if let model1 = model as? VPJH58PPGAccelerationModel {
                            let time = weakSelf.timestampToDateString(TimeInterval(model1.timestamp))
                            weakSelf.ppgAccfileHandle.writeText("数据时间:"+time)
                            weakSelf.ppgAccfileHandle.writeText("PPG数据:"+model1.ppgValueArray.componentsJoined(by: " "))
                            var xTextArray = [String]()
                            var yTextArray = [String]()
                            var zTextArray = [String]()
                            if let array = model1.accelerationArray as? Array<Any> {
                                for model in array {
                                    if let accModel = model as? VPAccelerationModel {
                                        let strX = String(accModel.x)
                                        xTextArray.append(strX)
                                        let strY = String(accModel.y)
                                        yTextArray.append(strY)
                                        let strZ = String(accModel.z)
                                        zTextArray.append(strZ)
                                    }
                                }
                            }
                            let str1 = "加速度X:" + String(xTextArray.joined(separator: " "))
                            let str2 = "加速度Y:" + String(yTextArray.joined(separator: " "))
                            let str3 = "加速度Z:" + String(zTextArray.joined(separator: " "))
                            weakSelf.ppgAccfileHandle.writeText(str1)
                            weakSelf.ppgAccfileHandle.writeText(str2)
                            weakSelf.ppgAccfileHandle.writeText(str3)
                        }
                    }
                    weakSelf.hud?.labelText = "获取数据成功"
                    weakSelf.textView.text = weakSelf.currentText + "\n" + "结束"
                    weakSelf.textView.scrollToBottom()
                }else{
                    weakSelf.hud?.labelText = "无数据"
                    weakSelf.textView.text = weakSelf.currentText + "\n" + "无数据"
                    weakSelf.textView.scrollToBottom()
                }
            }else{
                if let error = error as? NSError {
                    if let str = error.userInfo["NSLocalizedDescription"] as? String{
                        weakSelf.hud?.labelText = str
                    }
                }
            }
            weakSelf.hud?.hide(true, afterDelay: 1.0)
        }
    }
    
    func timestampToDateString(_ timestamp: TimeInterval) -> String {
        let date = Date(timeIntervalSince1970: timestamp)
        let formatter = DateFormatter()
        formatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
        formatter.timeZone = TimeZone.current
        return formatter.string(from: date)
    }
    
    @objc func shareAction(){
        let array = ppgAccfileHandle.getFilesWithDetails()
        let cachesURL = FileManager.default.urls(for: .cachesDirectory, in: .userDomainMask).first!

        // 创建归档文件路径
        let archiveURL = cachesURL.appendingPathComponent("PPG加速度数据.zip")
        let newUrl = ppgAccfileHandle.getZipFile(archiveURL, andFilePath: array)
        DispatchQueue.main.async {
            let activityViewController = UIActivityViewController(activityItems: [newUrl], applicationActivities: nil)
            activityViewController.excludedActivityTypes = [.addToReadingList, .assignToContact]
            // 在iPad上需要指定弹出视图的位置
            if let popoverController = activityViewController.popoverPresentationController {
                popoverController.sourceView = self.view // 或者你的按钮
                popoverController.sourceRect = CGRect(x: self.view.bounds.midX, y: self.view.bounds.midY, width: 0, height: 0)
                popoverController.permittedArrowDirections = []
            }

            // 弹出分享视图
            self.present(activityViewController, animated: true) {
                print("完成")
            }
        }
    }
    
    @objc func clearAction(){
        self.ppgAccfileHandle.clearFile()
        self.realTimePPGfileHandle.clearFile()
        self.realTimeAccfileHandle.clearFile()
        self.hud?.show(true)
        self.hud?.labelText = "清除成功"
        self.hud?.hide(true, afterDelay: 1.0)
    }
    
    
    @objc func valueChange(){
        let va = UInt(self.segControl.selectedSegmentIndex+1)
        let state = VPJH58MeasurementModeState.init(rawValue: va) ?? .off
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58SetMeasurementMode(state) { [weak self] error ,backState in
            guard let weakSelf = self else {return}
            if error == nil {
                weakSelf.hud?.show(true)
                weakSelf.hud?.labelText = "Success"
                weakSelf.hud?.hide(true, afterDelay: 1.0)
            }
        }
    }

    @objc func getMeasurementModeAction(){
        getMeasurementModeState()
    }
    
    func getMeasurementModeState(type:Int = 0){
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JH58GetMeasurementMode { [weak self] state in
            guard let weakSelf = self else {return}
            weakSelf.segControl.selectedSegmentIndex = Int(state.rawValue - 1)
            if type == 0 {
                weakSelf.hud?.show(true)
                weakSelf.hud?.labelText = "Success"
                weakSelf.hud?.hide(true, afterDelay: 1.0)
            }
        }
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}

extension UITextView {
    func scrollToBottom(animated: Bool = true) {
        guard !text.isEmpty else { return }
        let bottomRange = NSRange(location: (text as NSString).length - 1, length: 1)
        scrollRangeToVisible(bottomRange)
    }
}
