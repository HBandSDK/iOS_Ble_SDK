//
//  VPAutoMonitSwitchVC.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2025/6/11.
//  Copyright © 2025 veepoo. All rights reserved.
//

import Foundation
import VeepooBleSDK

class VPAutoMonitSwitchVC: UIViewController {
    
    private var dataSource: [VPAutoMonitTestModel] = []
    
    private var tableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        bindViewModel()
    }
}

extension VPAutoMonitSwitchVC {
    private func bindViewModel() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKReadAutoMonitSwitchInfo { [weak self] models in
            guard let someModels = models else {
                return
            }
            self?.dataSource = someModels
            print(">>> \(someModels.count)")
            self?.tableView.reloadData()
        }
    }
}

extension VPAutoMonitSwitchVC {
    private func setupSubViews() {
        title = "自动测量时间间隔设置"
        view.backgroundColor = UIColor.white
        
        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView.dataSource = self
        tableView.delegate = self
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "AutoMonitCell")
        view.addSubview(tableView)
    }
}

// 扩展类以实现 UITableViewDataSource 协议
extension VPAutoMonitSwitchVC: UITableViewDataSource, UITableViewDelegate {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return dataSource.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "AutoMonitCell", for: indexPath)
        let model = dataSource[indexPath.row]
        cell.textLabel?.text = model.displayText + " " + model.onStr
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        let model = dataSource[indexPath.row]
        model.on = !model.on
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSetAutoMonitSwitch(with: model) { [weak self] success, model in
            if success {
                self?.tableView.reloadData()
            }
        }
    }
}

extension VPAutoMonitTestModel {
    var displayText: String {
        switch self.type {
        case .heartRate:
            return "心率自动监测"
        case .bloodPressure:
            return "血压自动监测"
        case .bloodGlucose:
            return "血糖自动监测"
        case .stress:
            return "压力自动监测"
        case .bloodOxygen:
            return "血氧自动监测"
        case .bodyTemperature:
            return "体温自动监测"
        case .lorentz:
            return "洛伦兹散点图"
        case .HRV:
            return "HRV自动监测"
        case .bloodComponents:
            return "血液成分监测"
        }
    }
    
    var onStr: String {
        on ? "开启" : "关闭"
    }
}
