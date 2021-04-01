//
//  VPOterFunctionSettingController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/17.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPOterFunctionSettingController: UIViewController   , UITableViewDelegate , UITableViewDataSource{

    let otherFunctionSettingCellID = "otherFunctionSettingCellID"
    
    var otherFunctionSettingTableView: UITableView?
    
    let otherFunctions = ["同步个人信息","闹钟设置","血压私人模式设置","久坐提醒设置","心率报警设置","拍照功能","与手机配对","翻腕亮屏","修改密码","亮度调节","女性设置","倒计时功能","新闹钟设置","彩屏样式设置","亮屏时长","敲击测试","照片表盘","市场表盘","手机查找手环","GPS与时区设置"]
    
    let otherControllers = ["VPSyncPersonalInformationController","VPAlarmClockSettingController","VPBloodPrivateSettingController","VPLongSeatSettingController","VPHeartAlarmController","VPTakePhotoController","与手机配对","VPRaiseHandSettingController","VPModifyPasswordController","VPSettingBrightController","VPSettingFemaleRelatedController","VPDeviceCountDownController","VPDeviceNewAlarmController","VPSettingScreenStyleController","VPSettingScreenDurationController","VPTapTestViewController","VPPhotoDialViewController","VPMarketDialViewController","VPFindDeviceViewController","VPSettingDeviceGPSViewController"]
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "功能列表"
        view.backgroundColor = UIColor.white
        otherFunctionSettingTableView = UITableView(frame: view.bounds, style: .plain)
        otherFunctionSettingTableView?.autoresizingMask = UIViewAutoresizing.flexibleHeight
        otherFunctionSettingTableView?.delegate = self
        otherFunctionSettingTableView?.dataSource = self
        view.addSubview(otherFunctionSettingTableView!)
        // Do any additional setup after loading the view.
        // Do any additional setup after loading the view.
    }

    func settingBaseFunctionRemindFarilure(sender: UISwitch) {
        sender.isOn = !sender.isOn
    }
    
    //MARK: tableView的代理
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return otherFunctions.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCell(withIdentifier: otherFunctionSettingCellID)
        if cell == nil {
            cell = UITableViewCell(style: .default, reuseIdentifier: otherFunctionSettingCellID)
        }
        cell?.textLabel?.text = otherFunctions[indexPath.row]
        
        cell?.accessoryType = .disclosureIndicator
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        if indexPath.row == 6 {//手机配对，如果已经配对了点击没有反应，如果没有配对，系统会有弹窗询问用户是否需要配对
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSendPairedWithIphoneCommand()
            return
        }
        let controllerName = otherControllers[indexPath.row]
        
        let controllerClass: AnyClass? = NSClassFromString(nameSpace + "." + controllerName)
        
        let controller = controllerClass as! UIViewController.Type
        
        self.navigationController?.pushViewController(controller.init(), animated: true)
    }
}






