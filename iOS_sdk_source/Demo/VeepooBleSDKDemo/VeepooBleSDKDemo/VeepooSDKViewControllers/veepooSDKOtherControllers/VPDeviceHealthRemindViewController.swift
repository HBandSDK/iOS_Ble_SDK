//
//  VPDeviceHealthRemindViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/3/14.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPDeviceHealthRemindViewController: UIViewController {
    let CellId = "VPDeviceHealthRemindViewControllerID"
    
    private var tableView : UITableView!
    
    private var mArr:[VPDeviceHealthRemindModel] = []
    
    let NameStrArr:[String] = ["所有", "久坐提醒", "喝水提醒", "远眺提醒", "运动提醒", "吃药提醒", "看书提醒", "出行提醒", "洗手提醒"]

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "健康提醒"
        view.backgroundColor = .white
        
        addSubViews()
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingHealthRemind(with: .all, opCode: 2, remindModel: nil) { [self]success, model in
            if (success) {
                if let model = model {
                    let index = Int(model.type.rawValue)
                    let start = String(format: "%02d:%02d", model.startHour, model.startMinute)
                    let end = String(format: "%02d:%02d", model.endHour, model.endMinute)
                    print("type:\(NameStrArr[index]), 起始:\(start), 结束- \(end), 间隔- \(model.remindInterval), 开启:\(model.open)")
                    mArr.append(model)
                    tableView.reloadData()
                }
            }
        }
        
    }
    
    @objc func healthRemindOpenOrCloseAction(sender: UISwitch)  {//开始设置信息提醒的开关功能
        let model = mArr[sender.tag]
        model.open = sender.isOn
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingHealthRemind(with: model.type, opCode: 1, remindModel: model) {  [self]success, model in
            if (success) {
                if let model = model {
                    let index = Int(model.type.rawValue)
                    let start = String(format: "%02d:%02d", model.startHour, model.startMinute)
                    let end = String(format: "%02d:%02d", model.endHour, model.endMinute)
                    print("type:\(NameStrArr[index]), 起始:\(start), 结束- \(end), 间隔- \(model.remindInterval), 开启:\(model.open)")
//                    mArr.append(model)
                    tableView.reloadData()
                }
            }
        }
    }

}

extension VPDeviceHealthRemindViewController {
    func addSubViews(){
        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView.delegate = self
        tableView.dataSource = self
        view.addSubview(tableView)
    }
}

extension VPDeviceHealthRemindViewController: UITableViewDelegate, UITableViewDataSource {
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return mArr.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {        
        var cell = tableView.dequeueReusableCell(withIdentifier: CellId)
        if cell == nil {
            cell = UITableViewCell(style: .subtitle, reuseIdentifier: CellId)
        }
        let model = mArr[indexPath.row]
        let index = Int(model.type.rawValue)
        
        let start = String(format: "%02d:%02d", model.startHour, model.startMinute)
        let end = String(format: "%02d:%02d", model.endHour, model.endMinute)
        
        cell?.textLabel?.text = "\(NameStrArr[index]) 间隔(分钟): \(model.remindInterval)"
        
        cell?.detailTextLabel?.text = "时间范围: \(start) - \(end)"
        
        let baseFunctionSwitch = UISwitch()
        
        baseFunctionSwitch.isOn = model.open
        baseFunctionSwitch.tag = indexPath.row
        
        baseFunctionSwitch.addTarget(self, action: #selector(healthRemindOpenOrCloseAction(sender:)), for: .touchUpInside)
        cell?.accessoryView = baseFunctionSwitch
        
        return cell!
    }
    
}
