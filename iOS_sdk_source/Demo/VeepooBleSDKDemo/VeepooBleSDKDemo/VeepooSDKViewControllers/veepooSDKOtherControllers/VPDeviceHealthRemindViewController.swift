//
//  VPDeviceHealthRemindViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/3/14.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

let NameStrArr:[String] = ["所有",
                           "久坐提醒",
                           "喝水提醒",
                           "远眺提醒",
                           "运动提醒",
                           "吃药提醒",
                           "看书提醒",
                           "出行提醒",
                           "洗手提醒"]

class VPDeviceHealthRemindCell: UITableViewCell {
    
    var saveButtonClickEvent: ((VPDeviceHealthRemindModel) -> Void)?
    
    var titleLabel: UILabel!
    private var remindIntervalLabel: UILabel!
    var remindIntervalTextField: UITextField!
    
    private var timeLabel: UILabel!
    var sTimeHourTextField: UITextField!
    var sTimeMinuteTextField: UITextField!
    
    var eTimeHourTextField: UITextField!
    var eTimeMinuteTextField: UITextField!
    
    private var openSwitch: UISwitch!
    
    private var saveButton: UIButton!
    
    var model = VPDeviceHealthRemindModel() {
        didSet {
            let index = Int(model.type.rawValue)
            titleLabel.text = NameStrArr[index]
            remindIntervalTextField.text = String(model.remindInterval)
            sTimeHourTextField.text = String(format: "%02d", model.startHour)
            sTimeMinuteTextField.text = String(format: "%02d", model.startMinute)
            eTimeHourTextField.text = String(format: "%02d", model.endHour)
            eTimeMinuteTextField.text = String(format: "%02d", model.endMinute)
            openSwitch.isOn = model.open
        }
    }
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        selectionStyle = .none
        setupSubview()
    }
    
    @objc func saveButtonClick() {
        model.open = openSwitch.isOn
        model.remindInterval = UInt8(remindIntervalTextField.text ?? "0")!
        model.startHour = UInt8(sTimeHourTextField.text ?? "0")!
        model.startMinute = UInt8(sTimeMinuteTextField.text ?? "0")!
        model.endHour = UInt8(eTimeHourTextField.text ?? "0")!
        model.endMinute = UInt8(eTimeMinuteTextField.text ?? "0")!
        
        saveButtonClickEvent?(model)
    }
        
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}

extension VPDeviceHealthRemindCell {
    
    private func setupSubview() {
        titleLabel = UILabel.init(frame: CGRect(x: 5, y: 5, width: 120, height: 20))
        contentView.addSubview(titleLabel)
        
        remindIntervalLabel = UILabel.init(frame: CGRect(x: 5, y: 30, width: 90, height: 20))
        remindIntervalLabel.text = "间隔(分钟):"
        contentView.addSubview(remindIntervalLabel)
        
        remindIntervalTextField = UITextField.init(frame: CGRect(x: 100, y: 30, width: 50, height: 20))
        remindIntervalTextField.keyboardType = .numberPad
        remindIntervalTextField.borderStyle = .roundedRect
        contentView.addSubview(remindIntervalTextField)
        
        
        timeLabel = UILabel.init(frame: CGRect(x: 5, y: 55, width: 90, height: 20))
        timeLabel.text = "时间范围:"
        contentView.addSubview(timeLabel)
        
        sTimeHourTextField = UITextField.init(frame: CGRect(x: 100, y: 55, width: 40, height: 20))
        sTimeHourTextField.keyboardType = .numberPad
        sTimeHourTextField.borderStyle = .roundedRect
        contentView.addSubview(sTimeHourTextField)
        
        let label1 = UILabel.init(frame: CGRect(x: 140, y: 55, width: 5, height: 20))
        label1.text = ":"
        contentView.addSubview(label1)
        
        sTimeMinuteTextField = UITextField.init(frame: CGRect(x: 145, y: 55, width: 40, height: 20))
        sTimeMinuteTextField.keyboardType = .numberPad
        sTimeMinuteTextField.borderStyle = .roundedRect
        contentView.addSubview(sTimeMinuteTextField)
        
        let label2 = UILabel.init(frame: CGRect(x: 185, y: 55, width: 10, height: 20))
        label2.text = "-"
        label2.textAlignment = .center
        contentView.addSubview(label2)
                
        eTimeHourTextField = UITextField.init(frame: CGRect(x: 195, y: 55, width: 40, height: 20))
        eTimeHourTextField.keyboardType = .numberPad
        eTimeHourTextField.borderStyle = .roundedRect
        contentView.addSubview(eTimeHourTextField)
        
        let label3 = UILabel.init(frame: CGRect(x: 235, y: 55, width: 5, height: 20))
        label3.text = ":"
        contentView.addSubview(label3)
        
        eTimeMinuteTextField = UITextField.init(frame: CGRect(x: 240, y: 55, width: 40, height: 20))
        eTimeMinuteTextField.keyboardType = .numberPad
        eTimeMinuteTextField.borderStyle = .roundedRect
        contentView.addSubview(eTimeMinuteTextField)
        
        let label4 = UILabel.init(frame: CGRect(x: 155, y: 20, width: 48, height: 20))
        label4.text = "开关："
        contentView.addSubview(label4)
        
        openSwitch = UISwitch.init(frame: CGRect(x: 203, y: 13, width: 60, height: 40))
        contentView.addSubview(openSwitch)
        
        saveButton = UIButton(type: .system)
        saveButton.frame = CGRect(x: 280, y: 15, width: 60, height: 40)
        saveButton.setTitle("保存", for: .normal)
        saveButton.addTarget(self, action: #selector(saveButtonClick), for: .touchUpInside)
        contentView.addSubview(saveButton)
    }
    
}

class VPDeviceHealthRemindViewController: UIViewController {
    let CellId = "VPDeviceHealthRemindViewControllerID"
    
    private var tableView : UITableView!
    
    private var mArr:[VPDeviceHealthRemindModel] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "健康提醒"
        view.backgroundColor = .white
        
        addSubViews()
                
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingHealthRemind(with: .all, opCode: 2, remindModel: nil) { [weak self] success, finish, model in
            if (success) {
                if let model = model {
                    let index = Int(model.type.rawValue)
                    let start = String(format: "%02d:%02d", model.startHour, model.startMinute)
                    let end = String(format: "%02d:%02d", model.endHour, model.endMinute)
                    print("type:\(NameStrArr[index]), 起始:\(start), 结束- \(end), 间隔- \(model.remindInterval), 开启:\(model.open)")
                    _ = AppDelegate.showHUD(message: "读取成功", hudModel: MBProgressHUDModeText, showView: self!.view)
                    self!.mArr.append(model)
                    self!.tableView.reloadData()
                }
            }
        } deviceInfoDidChange: { [weak self] model in
            self!.deviceDidChange(model: model)
        }
        navigationItem.rightBarButtonItem = UIBarButtonItem.init(title: "隐藏键盘", style: .plain, target: self, action: #selector(hiddenKeyboard))
    }
    
    @objc func hiddenKeyboard() {
        view.endEditing(true)
    }
    
    private func changeModel(model: VPDeviceHealthRemindModel) { //修改信息提醒
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingHealthRemind(with: model.type, opCode: 1, remindModel: model) { [weak self] success, finish, model in
            if (success) {
                if let model = model {
                    let index = Int(model.type.rawValue)
                    let start = String(format: "%02d:%02d", model.startHour, model.startMinute)
                    let end = String(format: "%02d:%02d", model.endHour, model.endMinute)
                    print("type:\(NameStrArr[index]), 起始:\(start), 结束- \(end), 间隔- \(model.remindInterval), 开启:\(model.open)")
                    _ = AppDelegate.showHUD(message: "操作成功", hudModel: MBProgressHUDModeText, showView: self!.view)
//                    mArr.append(model)
                    self!.tableView.reloadData()
                }
            }
        } deviceInfoDidChange: { [weak self] model in
            self!.deviceDidChange(model: model)
        }
    }
    
    private func deviceDidChange(model: VPDeviceHealthRemindModel?) {
        if let model = model {
            let index = Int(model.type.rawValue) - 1
            mArr[index] = model
            _ = AppDelegate.showHUD(message: "设备端信息变更成功", hudModel: MBProgressHUDModeText, showView: view)
            tableView.reloadData()
        }
    }
}

extension VPDeviceHealthRemindViewController {
    func addSubViews(){
        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView.delegate = self
        tableView.dataSource = self
        tableView.register(VPDeviceHealthRemindCell.self, forCellReuseIdentifier: "CELL")
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
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 100
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell: VPDeviceHealthRemindCell = tableView.dequeueReusableCell(withIdentifier: "CELL", for: indexPath) as! VPDeviceHealthRemindCell
        cell.model = mArr[indexPath.row]
        cell.saveButtonClickEvent = { [self]model in
            changeModel(model: model)
        }
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
    }
}
