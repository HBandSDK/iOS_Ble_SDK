//
//  VPDeviceNewAlarmController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/16.
//  Copyright © 2017年 zc.All rights reserved.
//

/*
  新闹钟最多可设置20组，自己在做的时候，超过20组的时候提示用户不要继续添加，设
  备上存储闹钟排序方式是按照model的ID进行排序的，SDK中返回的是用户设置先后的顺序（如果用户卸载App了，第一次读取排序和设备端一致）
  
  我这边显示的是没有区分单次和重复星期的，开发的时候可以把重复的和单次的分两个区显示，可以参考我们的H Band，重新分开的时候，在对返回的数组进行处理一下就可以了，这里就不多说了
 */

//此demo编写了所有闹钟的逻辑，包括增 删 改 查，侧滑可以删除，1.7版本单次日期选择那里我偷懒了，先只写个随机的，开发者明白啥意思就行了，有点写累了😰，下个版本有时间在把逻辑写全吧，看心情😀

import UIKit

class VPDeviceNewAlarmController: UIViewController,UITableViewDelegate,UITableViewDataSource {

    let deviceNewAlarmCellID = "newAlarmCellID"
    
    var deviceNewAlarmTableView: UITableView?
    
    var deviceAlarmArray = Array<Any>()

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "新闹钟设置"
        view.backgroundColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        
        self.setDeviceNewAlarmControllerUI()
        
        if VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData == nil {
            _ = AppDelegate.showHUD(message: "手环没有新闹钟功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if !(tbyte[17] != 1 || tbyte[17] != 2 || tbyte[17] != 3 || tbyte[17] != 4) {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有新闹钟功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        //先读取一下设备的闹钟
        self.readOrSettingAlarmClock(settingAlarmModel: VPDeviceNewAlarmModel(), settingMode: 2)
    }

    func setDeviceNewAlarmControllerUI() {
        deviceNewAlarmTableView = UITableView(frame: view.bounds, style: .plain)
        deviceNewAlarmTableView?.delegate = self
        deviceNewAlarmTableView?.dataSource = self
        deviceNewAlarmTableView?.tableFooterView = UIView()
        view.addSubview(deviceNewAlarmTableView!)
        
        deviceNewAlarmTableView?.register(UINib.init(nibName: "VPNewAlarmCell", bundle: Bundle.main), forCellReuseIdentifier: deviceNewAlarmCellID)
        
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(addAlarmClock))
    }
    
    @objc func openOrCloseAlarmClock(sender: UISwitch) {//对单组闹钟进行开或者关，只对重复星期的闹钟有效
        let alarmModel = deviceAlarmArray[sender.tag] as? VPDeviceNewAlarmModel
        //下边copy一个模型，以免设置失败后，Model改变，页面不能刷新到正确状态
        let settingModel = alarmModel?.copy() as? VPDeviceNewAlarmModel
        settingModel?.alarmState = sender.isOn ? "1" : "0"
        
        self.readOrSettingAlarmClock(settingAlarmModel: settingModel!, settingMode: 1)
    }
    
    @objc func addAlarmClock()  {//
        if deviceAlarmArray.count >= 20 {
            _ = AppDelegate.showHUD(message: "设备最多支持20组闹钟", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        let editController = VPEditNewAlarmController(nibName: "VPEditNewAlarmController", bundle: Bundle.main)
        editController.isAdd = true
        //初始化的Model，SDK中时间和ID都已经给默认好了
        let addAlarmModel = VPDeviceNewAlarmModel()
        editController.alarmModel = addAlarmModel
        unowned let weakSelf = self
        editController.callBackBlock = {() -> Void in
            weakSelf.readOrSettingAlarmClock(settingAlarmModel: addAlarmModel, settingMode: 1)
        }
        navigationController?.pushViewController(editController, animated: true)
    }

    func readOrSettingAlarmClock(settingAlarmModel: VPDeviceNewAlarmModel, settingMode:UInt) {//设置或者读取新闹钟
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceNewAlarm(with: settingAlarmModel, settingMode: settingMode, successResult: { (alarmArray) in
            print(alarmArray?.count ?? "")
            weakSelf.deviceAlarmArray = alarmArray!
            weakSelf.deviceNewAlarmTableView?.reloadData()
            var tip = "读取成功"
            if settingMode == 0 {
                tip = "删除成功"
            }else if settingMode == 1 {
                tip = "设置成功"
            }
            _ = AppDelegate.showHUD(message: tip, hudModel: MBProgressHUDModeText, showView: UIApplication.shared.keyWindow!)
            if weakSelf.navigationController?.topViewController is VPEditNewAlarmController {
                _ = weakSelf.navigationController?.popViewController(animated: true)
            }
        }) {
            var tip = "读取失败"
            if settingMode == 0 {
                tip = "删除失败"
            }else if settingMode == 1 {
                tip = "设置失败"
            }
            _ = AppDelegate.showHUD(message: tip, hudModel: MBProgressHUDModeText, showView: UIApplication.shared.keyWindow!)
            weakSelf.deviceNewAlarmTableView?.reloadData()
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
        let cell: VPNewAlarmCell = tableView.dequeueReusableCell(withIdentifier: deviceNewAlarmCellID, for: indexPath) as! VPNewAlarmCell
        cell.alarmModel = deviceAlarmArray[indexPath.row] as? VPDeviceNewAlarmModel
        cell.alarmSwitch.addTarget(self, action: #selector(openOrCloseAlarmClock(sender:)), for: .valueChanged)
        cell.alarmSwitch.tag = indexPath.row
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        let editController = VPEditNewAlarmController(nibName: "VPEditNewAlarmController", bundle: Bundle.main)
        let modifyAlarmModel = deviceAlarmArray[indexPath.row] as? VPDeviceNewAlarmModel
        let copyModel = modifyAlarmModel?.copy() as! VPDeviceNewAlarmModel?
        editController.alarmModel = copyModel
        unowned let weakSelf = self
        editController.callBackBlock = {() -> Void in
            weakSelf.readOrSettingAlarmClock(settingAlarmModel: copyModel!, settingMode: 1)
        }
        navigationController?.pushViewController(editController, animated: true)
    }
    

    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 60
    }
    
    func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            let delectAlarmModel = deviceAlarmArray[indexPath.row] as? VPDeviceNewAlarmModel
            let copyModel = delectAlarmModel?.copy() as! VPDeviceNewAlarmModel?
            self.readOrSettingAlarmClock(settingAlarmModel: copyModel!, settingMode: 0)
        }
    }
    
    func tableView(_ tableView: UITableView, canMoveRowAt indexPath: IndexPath) -> Bool {
        return true
    }
    
    func tableView(_ tableView: UITableView, editingStyleForRowAt indexPath: IndexPath) -> UITableViewCellEditingStyle {
        return .delete
    }

}
