//
//  VPMicroTestViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/10/29.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPMicroTestViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        creatMainUI()
        // Do any additional setup after loading the view.
    }
    
    lazy var resultLabel: UILabel = {

        return UILabel()
    }()
    
    lazy var progressLabel: UILabel = {

        return UILabel()
    }()
    
    lazy var heartRateLabel: UILabel = {

        return UILabel()
    }()
    
    lazy var textView: UITextView = {

        return UITextView()
    }()
    
    var checkTimeInterval:TimeInterval = 0
    
    func creatMainUI(){
        self.title = "微体检"
        view.backgroundColor = .white
        let startBtn = UIButton(frame: CGRect(x: 20, y: 30, width: 160, height: 50));
        startBtn.tag = 1000
        startBtn.setTitle("开始测量", for: .normal)
        startBtn.backgroundColor = .blue
        startBtn.layer.cornerRadius = 4
        view.addSubview(startBtn)
        startBtn.addTarget(self, action: #selector(startAction), for: .touchUpInside)
        
        let endBtn = UIButton(frame: CGRect(x: 0, y: CGRectGetMinY(startBtn.frame), width: CGRectGetWidth(startBtn.frame), height: CGRectGetHeight(startBtn.frame)));
        endBtn.tag = 1001
        endBtn.center.x = UIScreen.main.bounds.width - CGRectGetMinX(startBtn.frame)-CGRectGetWidth(startBtn.frame)/2
        endBtn.setTitle("结束测量", for: .normal)
        endBtn.backgroundColor = .orange
        endBtn.layer.cornerRadius = 4
        view.addSubview(endBtn)
        endBtn.addTarget(self, action: #selector(startAction), for: .touchUpInside)
        
        self.heartRateLabel.frame = CGRect(x: CGRectGetMinX(startBtn.frame), y: CGRectGetMaxY(startBtn.frame), width: CGRectGetWidth(startBtn.frame), height: CGRectGetHeight(startBtn.frame))
        self.heartRateLabel.text = "心率:0"
        view.addSubview(heartRateLabel)
        
        self.progressLabel.frame = CGRect(x: CGRectGetMinX(endBtn.frame), y: CGRectGetMaxY(endBtn.frame), width: CGRectGetWidth(startBtn.frame), height: CGRectGetHeight(startBtn.frame))
        view.addSubview(self.progressLabel)
        
        self.resultLabel.frame = CGRect(x: 20, y: CGRectGetMaxY(heartRateLabel.frame), width: UIScreen.main.bounds.size.width-30, height: 60)
        self.resultLabel.numberOfLines = 0
        view.addSubview(self.resultLabel)
        
        let getBtn = UIButton(frame: CGRect(x: CGRectGetMinX(startBtn.frame), y: CGRectGetMaxY(resultLabel.frame), width: CGRectGetWidth(startBtn.frame), height: CGRectGetHeight(startBtn.frame)));
        getBtn.setTitle("获取手动测量数据", for: .normal)
        getBtn.backgroundColor = .orange
        getBtn.layer.cornerRadius = 4
        view.addSubview(getBtn)
        getBtn.addTarget(self, action: #selector(manualMeasurementAction), for: .touchUpInside)
        
        let timePicker = UIDatePicker(frame: CGRect(x: CGRectGetMinX(getBtn.frame), y: CGRectGetMaxY(getBtn.frame)+20, width: CGRectGetWidth(getBtn.frame), height: CGRectGetWidth(getBtn.frame)))
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
        
        textView.frame = CGRect(x: 20, y: CGRectGetMaxY(timePicker.frame), width: UIScreen.main.bounds.width-40, height: UIScreen.main.bounds.height - CGRectGetMaxY(timePicker.frame))
        textView.isEditable = false
        view.addSubview(textView)
    }
    
    @objc func manualMeasurementAction(){
        self.textView.text = ""
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKMicroTestManualMeasurement(self.checkTimeInterval) {[weak self] array in
            guard let weakSelf = self else {return}
            if let array = array {
                for model in array {
                    if let resultModel = model as? VPManualMeasurementMicroTestModel {
                        weakSelf.textView.text = weakSelf.textView.text + "\n" + weakSelf.timestampToDateString(resultModel.timestamp) + String(format: " 心率:%d 血氧:%d 压力:%d 血糖:%.1f 体温:%.1f 表皮温度:%.1f 高压:%d 低压:%d HRV:%d", resultModel.heartRate,resultModel.bloodOxygen,resultModel.pressure,resultModel.bloodSugar,resultModel.bodyTemperature,resultModel.skinTemperature,resultModel.systolicBloodPressure,resultModel.diastolicBloodPressure,resultModel.hrv)
                    }
                }
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
    
    func timestampToDateString(_ timestamp: TimeInterval) -> String {
        let date = Date(timeIntervalSince1970: timestamp)
        let formatter = DateFormatter()
        formatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
        formatter.timeZone = TimeZone.current
        return formatter.string(from: date)
    }
    
    @objc func startAction(btn: UIButton){
        self.progressLabel.text = ""
        self.resultLabel.text = ""
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKMicroTestOpenState(btn.tag == 1000 ? true : false) { [weak self] progress in
            guard let self = self else {return}
            self.progressLabel.text = "测量进度:" + progress.description + "%"
        } andFail: { error in
            
        } andSuccess: { [weak self] endState, model in
            guard let self = self else {return}
            if let resultModel = model {
                self.resultLabel.text = String(format: "心率:%d-血氧:%d-压力:%d-血糖:%.1f-体温:%.1f-高压:%d-低压:%d-HRV:%d", resultModel.heartRate,resultModel.bloodOxygen,resultModel.pressure,resultModel.bloodSugar,resultModel.bodyTemperature,resultModel.systolicBloodPressure,resultModel.diastolicBloodPressure,resultModel.hrv)
            }
        } andHeartRate: { [weak self] heart in
            guard let self = self else {return}
            self.heartRateLabel.text = "心率:" + String(heart)
        } andPPG: { ppgArray in
            
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
