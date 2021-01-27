//
//  VPTestBloodController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/22.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPTestBloodController: UIViewController,UITableViewDelegate, UITableViewDataSource {
    
    @IBOutlet weak var systolicLabel: UILabel!
    
    @IBOutlet weak var diastolicLabel: UILabel!
    
    @IBOutlet weak var testProgressLabel: UILabel!
    

    @IBOutlet weak var bloodDateLabel: UILabel!
    
    @IBOutlet weak var testBloodTableView: UITableView!
    
    var bloodArray:Array<[String: String]> = [[String: String]()]
    
    var bloodDayIndex = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "血压"
        // Do any additional setup after loading the view.
        obtainOneDayBloodData()
    }
    
    @IBAction func obtainLastDataAction(_ sender: UIButton) {
        bloodDayIndex = bloodDayIndex - 1
        obtainOneDayBloodData()
    }
    
    @IBAction func obtainNextDataAction(_ sender: UIButton) {
        bloodDayIndex = bloodDayIndex + 1
        obtainOneDayBloodData()
    }
    
    @IBAction func startTestBloodAction(_ sender: UIButton) {
        
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[1] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有血压功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            systolicLabel.text = "高压:0"
            diastolicLabel.text = "低压:0"
            testProgressLabel.text = "测试进度:0%"
        }
        
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBloodStart(sender.isSelected, testMode: 0) { (testBloodState, progress, systolic, diastolic) in
            if sender.isSelected {
                weakSelf.testProgressLabel.text = "测试进度:" + String(progress) + "%"
                weakSelf.systolicLabel.text = "高压:" + String(systolic)
                weakSelf.diastolicLabel.text = "低压:" + String(diastolic)
                switch testBloodState {
                case .testing://正在测试中
                    print("正在测试中")
                case .deviceBusy:
                    _ = AppDelegate.showHUD(message: "设备正忙，结束测试", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .testFail:
                    _ = AppDelegate.showHUD(message: "测试失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .testInterrupt:
                    _ = AppDelegate.showHUD(message: "人为结束测试", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .complete:
                    _ = AppDelegate.showHUD(message: "测试已经完成", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .noFunction:
                    _ = AppDelegate.showHUD(message: "设备暂时没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                }
            }
        }
    }
    
    /// 获取某一天的血压历史数据
    func obtainOneDayBloodData() {
        self.bloodDateLabel.text = bloodDayIndex.getOneDayDateString()
        let bloodDataBaseArray = VPDataBaseOperation.veepooSDKGetBloodData(withDate: self.bloodDateLabel.text, andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        
        guard let bloodDataArray = bloodDataBaseArray else {
            self.bloodArray = [[String: String]]()
            testBloodTableView.reloadData()
            return
        }
        
        self.bloodArray = bloodDataArray as! Array<[String : String]>
        
        testBloodTableView.reloadData()
    }
    
    //MARK: tableView的代理
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return bloodArray.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "Cell")
        if cell == nil {
            cell = UITableViewCell(style: .value1, reuseIdentifier: "Cell")
        }
        
        let bloodDict = bloodArray[indexPath.row]
        
        
        cell?.textLabel?.text = bloodDict["Time"]
        
    
        cell?.detailTextLabel?.text =  bloodDict["systolic"]! + "/" + bloodDict["diastolic"]!
        
        return cell!
    }
    
    deinit {//销毁的时候关闭血压测试
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBloodStart(false, testMode: 0, testResult: nil)
    }
}



