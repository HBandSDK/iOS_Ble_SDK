//
//  VPManualTestDataVC.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2025/6/11.
//  Copyright © 2025 veepoo. All rights reserved.
//

import Foundation
import VeepooBleSDK

class VPManualTestDataVC: UIViewController {
    
    let veepooBleManager: VPBleCentralManage = VPBleCentralManage.sharedBleManager()
    
    // 新增 UITextView 用于展示日志内容
    var logTextView: UITextView!
    
    var checkTimeInterval:TimeInterval = 0
    
    let mmTypes: [VPManualTestDataType] = [.heartRate , .bloodPressure, .bloodOxygen, .bloodSugar, .bloodComponents, .temperature, .all]
    
    var allViews: [UIButton] = []
    
    var supportType: VPManualTestDataType {
        get {
            return veepooBleManager.peripheralManage.supportManualTestType
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
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
    
    @objc private func readBtnClick(btn: UIButton) {
        let type = mmTypes[btn.tag]
        if btn.tag != mmTypes.count - 1 {
            guard supportType.contains(type) else {
                AppDelegate.showHUD(message: "设备不支持该功能", hudModel: MBProgressHUDModeText, showView: view)
                return
            }
        }
        readDataForType(dataType: type)
    }
    
    func btnEnabled(_ enable: Bool) {
        allViews.forEach { $0.isEnabled = enable }
    }
    
    func readDataForType(dataType: VPManualTestDataType) {
        btnEnabled(false)
        // 可以从DB中获取当前设备最近的同步过的时间戳 设备端每种类型最多存储10条手动测量数据
        let timestamp: UInt32 = UInt32(self.checkTimeInterval)
        VPBleCentralManage.sharedBleManager().peripheralManage.readManualTestData(withTimestamp: timestamp,
                                                                                  dataType: dataType) { [weak self] model in
            self?.btnEnabled(true)
            guard let someModel = model else {
                self?.logTextView.text += "\n" + "无数据"
                return
            }
            
            // 将日志内容输出到 UITextView 中
            var logText = ""
            if !someModel.bloodPressureArr.isEmpty {
                logText += "\n" + "血压 = \(someModel.bloodPressureArr)"
            }
            
            if !someModel.bodyTempArr.isEmpty {
                logText += "\n" + "体温 = \(someModel.bodyTempArr)"
            }
            
            if !someModel.bloodCompArr.isEmpty {
                logText += "\n" + "血液成分 = \(someModel.bloodCompArr)"
            }
            
            if !someModel.heartRateArr.isEmpty {
                logText += "\n" + "心率 = \(someModel.heartRateArr)"
            }
            
            if !someModel.bloodOxygenArr.isEmpty {
                logText += "\n" + "血氧 = \(someModel.bloodOxygenArr)"
            }
            
            if !someModel.bloodSugarArr.isEmpty {
                logText += "\n" + "血糖 = \(someModel.bloodSugarArr)"
            }
            
            if let existingText = self?.logTextView.text {
                self?.logTextView.text = existingText + logText
            } else {
                self?.logTextView.text = logText
            }
        }
    }
}

extension VPManualTestDataVC {
    private func setupSubViews() {
        title = "手动测量数据"
        view.backgroundColor = UIColor.white
        
        let texts = ["读取心率","读取血压","读取血氧","读取血糖","读取血液成分","读取体温","读取所有"]
        
        let height = 40
        let rowNum = 4
        // 计算起始X位置（居中显示）
        let totalWidth = view.bounds.width
        let width = totalWidth / CGFloat(rowNum)

        for (ind, type) in mmTypes.enumerated() {
            var sup = supportType.contains(type)
            if ind == mmTypes.count - 1 {
                sup = supportType.rawValue != 0
            }
            if sup {
                let row = ind / rowNum
                let line = ind % rowNum
                
                let x = CGFloat(line) * CGFloat(width)
                let y = CGFloat(row) * CGFloat(height)
                
                let btn = UIButton(type: .system)
                btn.frame = CGRect(x: x, y: y, width: CGFloat(width), height: CGFloat(height))
                btn.addTarget(self, action: #selector(readBtnClick(btn:)), for: .touchUpInside)
                btn.setTitle(texts[ind], for: .normal)  // 使用对应的标题
                btn.setTitleColor(.black, for: .normal)
                btn.tag = ind  // 可以设置tag来区分按钮
                view.addSubview(btn)
                allViews.append(btn)
            }
        }
        
        // 初始化 UITextView
        logTextView = UITextView()
        let screenWidth = UIScreen.main.bounds.width
        logTextView.frame = CGRect(x: 0, y: 100, width: screenWidth, height: 400)
        logTextView.isEditable = false
        logTextView.backgroundColor = .lightGray
        view.addSubview(logTextView)
        
        if supportType.rawValue == 0 {
            AppDelegate.showHUD(message: "设备不支持该功能", hudModel: MBProgressHUDModeText, showView: view)
        }
        
        let timePicker = UIDatePicker(frame: CGRect(x: CGRectGetMinX(logTextView.frame), y: CGRectGetMaxY(logTextView.frame)+20, width: 120, height: 40))
        timePicker.datePickerMode = .dateAndTime // 设置为时间模式[citation:5]
        timePicker.timeZone = TimeZone.current
        let calendar = Calendar.current
        let today = Date()
        if let startOfDay = calendar.date(bySettingHour: 0, minute: 0, second: 0, of: today) {
            timePicker.date = startOfDay
            self.checkTimeInterval = startOfDay.timeIntervalSince1970;
        }
        // 添加值变化监听
        timePicker.addTarget(self, action: #selector(timeChanged(picker:)), for: .valueChanged)
        // 将时间选择器添加到视图中
        view.addSubview(timePicker)
    }
}
