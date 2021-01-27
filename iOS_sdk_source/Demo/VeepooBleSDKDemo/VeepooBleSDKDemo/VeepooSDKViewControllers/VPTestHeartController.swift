//
//  VPTestHeartController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/18.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPTestHeartController: UIViewController,UITableViewDelegate, UITableViewDataSource {

    @IBOutlet weak var testHeartTableView: UITableView!
    
    @IBOutlet weak var testHeartCurrentDateLabel: UILabel!
    
    @IBOutlet weak var currentHeartValueLabel: UILabel!
    
    var dayIndex = 0
    
    var heartDict = [String : [String: String]]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "心率"
        obtainOneDayHeartData()
        // Do any additional setup after loading the view.
    }

    @IBAction func selectHeartLastDateAction(_ sender: UIButton) {//上一天
        dayIndex = dayIndex - 1
        obtainOneDayHeartData()
        
    }
    
    @IBAction func selectHeartNextDateAction(_ sender: UIButton) {//下一天
        dayIndex = dayIndex + 1
        obtainOneDayHeartData()
    }
    
    
    @IBAction func startTestHeartAction(_ sender: UIButton) {//测试心率,测试过程中，开发者要考虑一下，蓝牙中断的情况，细节的逻辑要考虑清楚
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            currentHeartValueLabel.text = "当前心率值: "
        }
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestHeartStart(sender.isSelected) { (testHeartState, heartValue) in
            
            if  sender.isSelected {
                switch testHeartState {
                case .start: //测试心率过程中的状态变化 //开始检测心率，还没有测出结果
                    _ = AppDelegate.showHUD(message: "正在做测试准备，请保持正确姿势", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                case .testing: //正在检测心率，已经测出心率值
                    weakSelf.currentHeartValueLabel.text = "当前心率值:" + String(heartValue)
                case .notWear: //佩戴检测没有通过，测试已经结束
                    _ = AppDelegate.showHUD(message: "佩戴检测未通过", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .deviceBusy: //设备正忙不能测试了，测试已经结束
                    _ = AppDelegate.showHUD(message: "设备端正在操作", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                case .over: //测试正常结束，人为结束
                    _ = AppDelegate.showHUD(message: "测试结束", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                    sender.isSelected = false
                }
            }else {
                if testHeartState == .over {
                    _ = AppDelegate.showHUD(message: "测试结束", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                }
            }
        }
        
    }
    
    
    /// 获取某一天的心率历史数据
    func obtainOneDayHeartData() {
        self.testHeartCurrentDateLabel.text = dayIndex.getOneDayDateString()
        let heartOnedayData = VPDataBaseOperation.veepooSDKGetOriginalChangeHalfHourData(withDate: self.testHeartCurrentDateLabel.text, andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        
        if heartOnedayData == nil {
            heartDict = [String : [String: String]]()
        }else {
            heartDict = heartOnedayData as! [String : [String : String]]
        }
        testHeartTableView.reloadData()
    }
    
    //MARK: tableView的代理
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        
        return heartDict.keys.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "Cell")
        if cell == nil {
            cell = UITableViewCell(style: .value1, reuseIdentifier: "Cell")
        }
        
        let allkeys = Array(heartDict.keys)
        
        let keys = allkeys.sorted(by: { (n1: String, n2: String) -> Bool in
            //进行从小到大的排序
            return n2 < n1
        })
        
        cell?.textLabel?.text = keys[indexPath.row]
        
        let subDict = heartDict[(cell?.textLabel?.text)!]
        
        guard let subHeartDict = subDict else {
            return cell!
        }
        
        cell?.detailTextLabel?.text = "心率" + subHeartDict["heartValue"]! + "/运动量" + subHeartDict["sportValue"]! + "/步数" + subHeartDict["stepValue"]! + "/距离" + subHeartDict["disValue"]! + "/卡路里" + subHeartDict["calValue"]!
        cell?.detailTextLabel?.adjustsFontSizeToFitWidth = true
        
        return cell!
    }
    
    deinit {//销毁的时候关闭心率测试
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestHeartStart(false, testResult: nil)
    }
}






