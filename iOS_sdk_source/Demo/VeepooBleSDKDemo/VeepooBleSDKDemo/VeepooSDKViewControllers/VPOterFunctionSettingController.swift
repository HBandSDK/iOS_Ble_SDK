//
//  VPOterFunctionSettingController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/17.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

struct VPFunctionVCObject {
    public var funcName:String
    public var vcName:String
    
    public init(_ funcName: String,_ vcName: String) {
        self.funcName = funcName
        self.vcName = vcName
    }
}

class VPOterFunctionSettingController: UIViewController   , UITableViewDelegate , UITableViewDataSource{

    let otherFunctionSettingCellID = "otherFunctionSettingCellID"
    
    var otherFunctionSettingTableView: UITableView?
    
    let otherFuncAndVCs:[VPFunctionVCObject] = [
        .init("同步个人信息", "VPSyncPersonalInformationController"),
        .init("闹钟设置","VPAlarmClockSettingController"),
        .init("血压私人模式设置","VPBloodPrivateSettingController"),
        .init("久坐提醒设置","VPLongSeatSettingController"),
        .init("心率报警设置","VPHeartAlarmController"),
        .init("拍照功能","VPTakePhotoController"),
        .init("与手机配对","与手机配对"),
        .init("翻腕亮屏","VPRaiseHandSettingController"),
        .init("修改密码","VPModifyPasswordController"),
        .init("亮度调节","VPSettingBrightController"),
        .init("女性设置","VPSettingFemaleRelatedController"),
        .init("倒计时功能","VPDeviceCountDownController"),
        .init("新闹钟设置","VPDeviceNewAlarmController"),
        .init("文字闹钟","VPTextAlarmClockSettingController"),
        .init("彩屏样式设置","VPSettingScreenStyleController"),
        .init("亮屏时长","VPSettingScreenDurationController"),
        .init("敲击测试","VPTapTestViewController"),
        .init("照片表盘","VPPhotoDialViewController"),
        .init("市场表盘","VPMarketDialViewController"),
        .init("手环查找手机","VPFindPhoneViewController"),
        .init("手机查找手环","VPFindDeviceViewController"),
        .init("GPS与时区设置","VPSettingDeviceGPSViewController"),
        .init("体温数据读取","VPTemperatureViewController"),
        .init("G15表盘","VPG15DialViewController"),
        .init("G15二维码","VPG15QRCodeViewController"),
        .init("RR逐跳数据","VPRRIntervalDataViewController"),
        .init("健康提醒","VPDeviceHealthRemindViewController"),
        .init("联系人","VPDeviceContactsViewController"),
        .init("身体成分","VPBodyCompositionViewController"),
        .init("血液成分","VPBloodAnalysisViewController"),
        .init("G08W项目","VPG08WViewController"),
        .init("脉冲磁疗功能","VPDevicePulseViewController"),
        .init("中医诊断定制","VPJM19AViewController"),
    ]
    
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
        return otherFuncAndVCs.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCell(withIdentifier: otherFunctionSettingCellID)
        if cell == nil {
            cell = UITableViewCell(style: .default, reuseIdentifier: otherFunctionSettingCellID)
        }
        cell?.textLabel?.text = otherFuncAndVCs[indexPath.row].funcName
        
        cell?.accessoryType = .disclosureIndicator
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        let controllerName = otherFuncAndVCs[indexPath.row].vcName
        
        if controllerName == "与手机配对" {//手机配对，如果已经配对了点击没有反应，如果没有配对，系统会有弹窗询问用户是否需要配对
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSendPairedWithIphoneCommand()
            return
        }
        
        let controllerClass: AnyClass? = NSClassFromString(nameSpace + "." + controllerName)
        
        let controller = controllerClass as! UIViewController.Type
        
        self.navigationController?.pushViewController(controller.init(), animated: true)
    }
}






