//
//  VPTestSleepController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/22.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPTestSleepController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    
    @IBOutlet weak var sleepLastBtn: UIButton!
    
    @IBOutlet weak var sleepNextBtn: UIButton!
    
    @IBOutlet weak var sleepDateLabel: UILabel!
    
    @IBOutlet weak var sleepTestTableView: UITableView!
    
    var sleepDayIndex = -1 //睡眠一般都是显示前一天，今天显示昨天的睡眠
    
    var sleepTestArray: Array<Any>?
    
    var sleepType = 0;
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "睡眠"
        if VPBleCentralManage
            .sharedBleManager()?.peripheralModel.sleepType == 1 {//精准睡眠
            sleepDayIndex = 0;
            sleepType = 1;
        }
        obtainOneDaySleepData()
    }
    
    @IBAction func sleepLastDayAction(_ sender: UIButton) {
        sleepDayIndex = sleepDayIndex - 1
        obtainOneDaySleepData()
    }

    @IBAction func sleepNextAction(_ sender: UIButton) {
        sleepDayIndex = sleepDayIndex + 1
        obtainOneDaySleepData()
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        guard let sleepArray = sleepTestArray else {
            return 0
        }
        return sleepArray.count
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        guard let sleepArray = sleepTestArray else {
            return 0
        }
//        let sleepDict = sleepArray[section] as! [String : String]
//        return sleepDict.keys.count
        return 6;
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "Cell")
        if cell == nil {
            cell = UITableViewCell(style: .value1, reuseIdentifier: "Cell")
        }
        
        guard let sleepArray = sleepTestArray else {
            return cell!
        }
        
        if sleepType == 1 {//精准睡眠
            let sleepModel = sleepArray[indexPath.section] as! VPAccurateSleepModel
            
            if indexPath.row == 0 {//入睡时间
                cell?.textLabel?.text = "入睡时间"
                cell?.detailTextLabel?.text = sleepModel.sleepTime
            }else if (indexPath.row == 1) {
                cell?.textLabel?.text = "起床时间"
                cell?.detailTextLabel?.text = sleepModel.wakeTime
            }else if (indexPath.row == 2) {//总的睡眠时间就是深睡时间加上浅睡时间
                cell?.textLabel?.text = "深睡时间"
                cell?.detailTextLabel?.text = sleepModel.deepDuration
            }else if (indexPath.row == 3) {
                cell?.textLabel?.text = "浅睡时间"
                cell?.detailTextLabel?.text = sleepModel.lightDuration
            }else if (indexPath.row == 4) {
                cell?.textLabel?.text = "苏醒次数"
                cell?.detailTextLabel?.text = sleepModel.getUpTimes
            }else if (indexPath.row == 5) {//深浅睡眠是由0、1和2组成的字符串，每一个长度代表5分钟，0是表示当时的5分钟是浅睡，1代表深睡，2代表苏醒
                cell?.textLabel?.text = "睡眠曲线"
                cell?.detailTextLabel?.text = sleepModel.sleepLine
            }
            
            return cell!;
        }
        
        
        let sleepDict = sleepArray[indexPath.section] as! [String : String]
        
        if indexPath.row == 0 {//入睡时间
            cell?.textLabel?.text = "入睡时间"
            cell?.detailTextLabel?.text = sleepDict["SLEEP_TIME"]
        }else if (indexPath.row == 1) {
            cell?.textLabel?.text = "起床时间"
            cell?.detailTextLabel?.text = sleepDict["WAKE_TIME"]
        }else if (indexPath.row == 2) {//总的睡眠时间就是深睡时间加上浅睡时间
            cell?.textLabel?.text = "深睡时间"
            cell?.detailTextLabel?.text = sleepDict["DEEP_HOUR"]
        }else if (indexPath.row == 3) {
            cell?.textLabel?.text = "浅睡时间"
            cell?.detailTextLabel?.text = sleepDict["LIGHT_HOUR"]
        }else if (indexPath.row == 4) {
            cell?.textLabel?.text = "苏醒次数"
            cell?.detailTextLabel?.text = sleepDict["WakeUpTime"]
        }else if (indexPath.row == 5) {//深浅睡眠是由0、1和2组成的字符串，每一个长度代表5分钟，0是表示当时的5分钟是浅睡，1代表深睡，2代表苏醒
            cell?.textLabel?.text = "睡眠曲线"
            cell?.detailTextLabel?.text = sleepDict["SLE_LINE"]
        }
        return cell!
    }
    
    func obtainOneDaySleepData() {
        self.sleepDateLabel.text = sleepDayIndex.getOneDayDateString()
        
        if sleepType == 1 {//精准睡眠
            sleepTestArray = VPDataBaseOperation.veepooSDKGetAccurateSleepData(withDate: self.sleepDateLabel.text, andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        } else {
            sleepTestArray = VPDataBaseOperation.veepooSDKGetSleepData(withDate: self.sleepDateLabel.text, andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        }
        
        sleepTestTableView.reloadData()
    }
}







