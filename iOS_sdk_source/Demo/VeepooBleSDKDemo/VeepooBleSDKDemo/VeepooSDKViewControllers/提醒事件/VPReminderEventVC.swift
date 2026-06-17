//
//  VPReminderEventVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/6/12.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPReminderEventVC: UIViewController {

    
    private var textView: UITextView!
    
    private var isSupport: Bool = VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel.isSupportReminderEvent
    
    var checkTimeInterval:TimeInterval = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        createMainView()
        // Do any additional setup after loading the view.
    }
    
    func createMainView() {
        self.title = "提醒事件"
        view.backgroundColor = .white
        
        let titleLab = UILabel(frame: CGRect(x: 20, y: 20, width: 250, height: 40))
        titleLab.text = "是否支持提醒事件:\(isSupport ? "支持" : "不支持")"
        self.view.addSubview(titleLab)
        
        let otaBtn = UIButton(frame: CGRect(x: CGRectGetMinX(titleLab.frame), y: CGRectGetMaxY(titleLab.frame) + 20, width: 120, height: 30))
        otaBtn.setTitle("读取历史数据", for: .normal)
        otaBtn.backgroundColor = .blue
        self.view.addSubview(otaBtn)
        otaBtn.isHidden = !isSupport
        otaBtn.addTarget(self, action: #selector(readAction), for: .touchUpInside)
        
        let timePicker = UIDatePicker(frame: CGRect(x: CGRectGetMaxX(otaBtn.frame) + 10, y: CGRectGetMinY(otaBtn.frame), width: 120, height: 40))
        timePicker.datePickerMode = .dateAndTime // 设置为时间模式[citation:5]
        timePicker.timeZone = TimeZone.current
        let calendar = Calendar.current
        let today = Date()
        if let startOfDay = calendar.date(bySettingHour: 0, minute: 0, second: 0, of: today) {
            timePicker.date = startOfDay
            self.checkTimeInterval = startOfDay.timeIntervalSince1970;
        }
        timePicker.isHidden = !isSupport
        timePicker.addTarget(self, action: #selector(timeChanged(picker:)), for: .valueChanged)
        view.addSubview(timePicker)
        
        
        textView = UITextView(frame: CGRect(x: 20, y: Int(otaBtn.frame.maxY) + 30, width: Int(view.bounds.size.width) - 40, height: 200))
        textView.backgroundColor = .lightGray
        view.addSubview(textView)
        textView.isHidden = !isSupport
        
        let testBtn = UIButton(frame: CGRect(x: CGRectGetMinX(textView.frame), y: CGRectGetMaxY(textView.frame) + 20, width: 220, height: 40))
        testBtn.setTitle("主动触发事件(仅用于测试)", for: .normal)
        testBtn.backgroundColor = .blue
        self.view.addSubview(testBtn)
        testBtn.isHidden = !isSupport
        testBtn.addTarget(self, action: #selector(triggerAction), for: .touchUpInside)
        
        listenCallBack()
    }
    
    
    
    func listenCallBack() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_listenReminderEventReport {[weak self] array in
            guard let self = self, let array = array else { return }
            self.textView.text += "主动上报:\n"
            for model in array {
                self.textView.text += "时间戳\(model.timestamp),事件类型:\(model.type == .fall ? "跌倒" : "久坐")\n"
            }
        }
    }
    
    @objc func triggerAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_triggerReminderEvent()
    }
    
    
    @objc func readAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readHistoricalDataReminderEvents(.all, andTime: UInt32(self.checkTimeInterval)) {[weak self] array in
            guard let self = self, let array = array else { return }
            self.textView.text += "主动读取:\n"
            for model in array {
                self.textView.text += "时间戳\(model.timestamp),事件类型:\(model.type == .fall ? "跌倒" : "久坐")\n"
            }
        }
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
}
