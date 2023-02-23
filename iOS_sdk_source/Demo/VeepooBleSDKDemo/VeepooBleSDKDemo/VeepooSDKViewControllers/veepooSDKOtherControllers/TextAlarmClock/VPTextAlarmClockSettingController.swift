//
//  VPTextAlarmClockSettingController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/9/17.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPTextAlarmClockSettingController: UIViewController,UITableViewDelegate,UITableViewDataSource {
    
    let deviceTextAlarmCellID = "textAlarmCellID"
    
    var deviceTextAlarmTableView: UITableView?
    
    var deviceAlarmArray = Array<Any>()

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "文字闹钟设置"
        view.backgroundColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        
        self.setDeviceTextAlarmControllerUI()
        
        if VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData == nil {
            _ = AppDelegate.showHUD(message: "手环没有新闹钟功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[17] != 0x05 && tbyte[17] != 0x06 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有文字闹钟功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        //先读取一下设备的闹钟
        self.readOrSettingAlarmClock(settingAlarmModel: VPDeviceTextAlarmModel(), settingMode: .read)
    }

    func setDeviceTextAlarmControllerUI() {
        deviceTextAlarmTableView = UITableView(frame: view.bounds, style: .plain)
        deviceTextAlarmTableView?.delegate = self
        deviceTextAlarmTableView?.dataSource = self
        deviceTextAlarmTableView?.tableFooterView = UIView()
        view.addSubview(deviceTextAlarmTableView!)
        
        deviceTextAlarmTableView?.register(UINib.init(nibName: "VPTextAlarmCell", bundle: Bundle.main), forCellReuseIdentifier: deviceTextAlarmCellID)
                
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(addAlarmClock))
    }
    
    @objc func openOrCloseAlarmClock(sender: UISwitch) {//对单组闹钟进行开或者关，只对重复星期的闹钟有效
        let alarmModel = deviceAlarmArray[sender.tag] as? VPDeviceTextAlarmModel
        //下边copy一个模型，以免设置失败后，Model改变，页面不能刷新到正确状态
        let settingModel = alarmModel?.copy() as? VPDeviceTextAlarmModel
        settingModel?.alarmState = sender.isOn ? "1" : "0"
        
        self.readOrSettingAlarmClock(settingAlarmModel: settingModel!, settingMode: .addOrChange)
    }
    
    @objc func addAlarmClock()  {//
        if deviceAlarmArray.count >= 10 {
            _ = AppDelegate.showHUD(message: "设备最多支持10组闹钟", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        let editController = VPEditTextAlarmViewController(nibName: "VPEditTextAlarmViewController", bundle: Bundle.main)
        editController.isAdd = true
        //初始化的Model，SDK中时间和ID都已经给默认好了
        let addAlarmModel = VPDeviceTextAlarmModel()
        editController.alarmModel = addAlarmModel
        unowned let weakSelf = self
        editController.callBackBlock = {() -> Void in
            weakSelf.readOrSettingAlarmClock(settingAlarmModel: addAlarmModel, settingMode: .addOrChange)
        }
        navigationController?.pushViewController(editController, animated: true)
    }

    func readOrSettingAlarmClock(settingAlarmModel: VPDeviceTextAlarmModel, settingMode:VPDeviceTextAlarmSettingModel) {//设置或者读取新闹钟
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceTextAlarm(with: settingAlarmModel, settingMode: settingMode, successResult: { (alarmArray) in
            print(alarmArray?.count ?? "")
            weakSelf.deviceAlarmArray = alarmArray!
            weakSelf.deviceTextAlarmTableView?.reloadData()
            var tip = "读取成功"
            if settingMode == .delete {
                tip = "删除成功"
            }else if settingMode == .addOrChange {
                tip = "设置成功"
            }
            _ = AppDelegate.showHUD(message: tip, hudModel: MBProgressHUDModeText, showView: UIApplication.shared.keyWindow!)
            if weakSelf.navigationController?.topViewController is VPEditTextAlarmViewController {
                _ = weakSelf.navigationController?.popViewController(animated: true)
            }
        }) {
            var tip = "读取失败"
            if settingMode == .delete {
                tip = "删除失败"
            }else if settingMode == .addOrChange {
                tip = "设置失败"
            }
            _ = AppDelegate.showHUD(message: tip, hudModel: MBProgressHUDModeText, showView: UIApplication.shared.keyWindow!)
            weakSelf.deviceTextAlarmTableView?.reloadData()
        }
    }

    //MARK: tableView的代理
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return deviceAlarmArray.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell: VPTextAlarmCell = tableView.dequeueReusableCell(withIdentifier: deviceTextAlarmCellID, for: indexPath) as! VPTextAlarmCell
        cell.alarmModel = deviceAlarmArray[indexPath.row] as? VPDeviceTextAlarmModel
        cell.alarmSwitch.addTarget(self, action: #selector(openOrCloseAlarmClock(sender:)), for: .valueChanged)
        cell.alarmSwitch.tag = indexPath.row
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        let editController = VPEditTextAlarmViewController(nibName: "VPEditTextAlarmViewController", bundle: Bundle.main)
        let modifyAlarmModel = deviceAlarmArray[indexPath.row] as? VPDeviceTextAlarmModel
        let copyModel = modifyAlarmModel?.copy() as! VPDeviceTextAlarmModel?
        editController.alarmModel = copyModel
        unowned let weakSelf = self
        editController.callBackBlock = {() -> Void in
            weakSelf.readOrSettingAlarmClock(settingAlarmModel: copyModel!, settingMode: .addOrChange)
        }
        navigationController?.pushViewController(editController, animated: true)
    }
    

    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 80
    }
    
    func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            let delectAlarmModel = deviceAlarmArray[indexPath.row] as? VPDeviceTextAlarmModel
            let copyModel = delectAlarmModel?.copy() as! VPDeviceTextAlarmModel?
            self.readOrSettingAlarmClock(settingAlarmModel: copyModel!, settingMode: .delete)
        }
    }
    
    func tableView(_ tableView: UITableView, canMoveRowAt indexPath: IndexPath) -> Bool {
        return true
    }
    
    func tableView(_ tableView: UITableView, editingStyleForRowAt indexPath: IndexPath) -> UITableViewCellEditingStyle {
        return .delete
    }

}
