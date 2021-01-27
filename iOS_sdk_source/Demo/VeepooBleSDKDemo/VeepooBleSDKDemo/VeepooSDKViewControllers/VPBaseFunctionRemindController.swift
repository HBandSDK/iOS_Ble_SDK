//
//  VPBaseFunctionRemindController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/17.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPBaseFunctionRemindController: UIViewController  , UITableViewDelegate , UITableViewDataSource {

    let baseFunctionRemindCellID = "baseFunctionRemindCellID"
    
    var baseFunctionRemindTableView: UITableView?
    
    //血氧自动检测功能无用，LED档位如果有1代表正常肤色档位 2代表黑色皮肤档位
    let baseFunctions = ["夜间抬手亮屏","设备防丢失","佩戴检测","公制","24小时制","心率自动检测","血压自动检测","运动量过量提醒","心率血氧血压语音播报","手机查找","秒表功能","血氧过低通知","LED档位","HRV夜间自动检测","来电免接听","蓝牙断链提醒","SOS页面显示","PPG(脉率)自动监测","血氧自动检测"]
    
    let baseTwoFunctions = ["长按解锁", "消息亮屏"]
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "基本开关"
        view.backgroundColor = UIColor.white
        baseFunctionRemindTableView = UITableView(frame: view.bounds, style: .plain)
        baseFunctionRemindTableView?.contentInset = UIEdgeInsetsMake(0, 0, 80, 0)
        baseFunctionRemindTableView?.delegate = self
        baseFunctionRemindTableView?.dataSource = self
        view.addSubview(baseFunctionRemindTableView!)
        // Do any additional setup after loading the view.
        
//        VPBleCentralManage.sharedBleManager()?.peripheralManage
//            .veepooSDKSettingBaseFunctionType(.longpressUnlock, settingState: .readFunctionState, complete: { (state) in
//                switch state {
//                case .functionCompleteClose:
//                    print("close")
//                case .functionCompleteOpen:
//                    print("open")
//                default:
//                    print("unkown")
//                }
//        })
    }
    
    @objc func baseFunctionOpenOrCloseRemindAction(sender: UISwitch)  {//开始设置信息提醒的开关功能
        if VPBleCentralManage.sharedBleManager().isConnected == false {
            print();
            _ = AppDelegate.showHUD(message: "设备未连接,设置失败", hudModel: MBProgressHUDModeText, showView: view)
            self.perform(#selector(settingBaseFunctionRemindFarilure(sender:)), with: sender, afterDelay: 0.5)
            return
        }
         VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingBaseFunctionType(VPSettingBaseFunctionSwitchType(rawValue: sender.tag)!, settingState: VPSettingFunctionState(rawValue: sender.isOn ? 1 : 2)!) {[weak self] (settingFunctionCompleteState) in
            if self == nil {
                return
            }
            switch settingFunctionCompleteState {
            case .functionCompleteUnknown:
                _ = AppDelegate.showHUD(message: "没有此功能", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
                fallthrough
            case .functionCompleteFailure:
                self?.perform(#selector(self?.settingBaseFunctionRemindFarilure(sender:)), with: sender, afterDelay: 0.5)
                _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            case .functionCompleteOpen:
                _ = AppDelegate.showHUD(message: "设置成功，已经开启", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            case .functionCompleteClose:
                _ = AppDelegate.showHUD(message: "设置成功，已经关闭", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            case .functionCompleteComplete:
                _ = AppDelegate.showHUD(message: "设置完成闭", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            }
        }
    }
    
    ///设置失败
    @objc func settingBaseFunctionRemindFarilure(sender: UISwitch) {
        sender.isOn = !sender.isOn
    }

    //MARK: tableView的代理
    func numberOfSections(in tableView: UITableView) -> Int {
        return 2
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section == 0 {
            return baseFunctions.count
        }else {
            return baseTwoFunctions.count
        }
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCell(withIdentifier: baseFunctionRemindCellID)
        if cell == nil {
            cell = UITableViewCell(style: .default, reuseIdentifier: baseFunctionRemindCellID)
        }
        cell?.selectionStyle = .none
        let baseFunctionSwitch = UISwitch()
        
        if indexPath.section == 1 {
            cell?.textLabel?.text = baseTwoFunctions[indexPath.row]
            baseFunctionSwitch.tag = indexPath.row + 22;
            var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
            VPBleCentralManage.sharedBleManager()
                .peripheralModel.deviceSwitchTwoData.copyBytes(to: &tbyte, count: 20)
            let header = tbyte[indexPath.row + 2]//header == 0即为没有此功能，1是开启，2是关闭
            baseFunctionSwitch.isEnabled = header != 0//为1即为开
            baseFunctionSwitch.isOn = header == 1//为1即为开
        }else {//section == 0
            cell?.textLabel?.text = baseFunctions[indexPath.row]
            baseFunctionSwitch.tag = indexPath.row
            if (baseFunctions.count - 1 == indexPath.row) {//兼容血氧自动检测开关
                baseFunctionSwitch.tag = 1000
            }
            if indexPath.row == 0 {//抬手亮屏幕
                baseFunctionSwitch.isEnabled = VPBleCentralManage.sharedBleManager().peripheralModel.raiseHandState != 0//为0即为没有此功能
                baseFunctionSwitch.isOn = VPBleCentralManage.sharedBleManager().peripheralModel.raiseHandState == 1//为1即为开
                var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
                VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
                if tbyte[11] == 1 {//先判断一下是否有翻腕亮屏幕的功能，如果有翻腕亮屏的这个则视为没有
                    baseFunctionSwitch.isEnabled = false //为0即为没有此功能
                    baseFunctionSwitch.isOn = false //为1即为开
                }
            }else if indexPath.row == 1 {//设备防丢失
                baseFunctionSwitch.isEnabled = VPBleCentralManage.sharedBleManager().peripheralModel.lostRemindState != 0//为0即为没有此功能
                baseFunctionSwitch.isOn = VPBleCentralManage.sharedBleManager().peripheralModel.lostRemindState == 1//为1即为开
            }else if indexPath.row == 2 {//佩戴检测
                baseFunctionSwitch.isEnabled = VPBleCentralManage.sharedBleManager().peripheralModel.wearMonitoringState != 0//为0即为没有此功能
                baseFunctionSwitch.isOn = VPBleCentralManage.sharedBleManager().peripheralModel.wearMonitoringState == 1//为1即为开
            }else if indexPath.row == baseFunctions.count - 1 {//血氧自动检测
                baseFunctionSwitch.isEnabled = VPBleCentralManage.sharedBleManager().peripheralModel.oxygenType != 0//为0即为没有此功能
                baseFunctionSwitch.isOn = VPBleCentralManage.sharedBleManager().peripheralModel.oxygenAutoDetectType == 1//为1即为开
            }else {
                var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
                VPBleCentralManage.sharedBleManager()
                    .peripheralModel.deviceSwitchData.copyBytes(to: &tbyte, count: 20)
                let header = tbyte[indexPath.row - 1]//header == 0即为没有此功能，1是开启，2是关闭
                baseFunctionSwitch.isEnabled = header != 0//为1即为开
                baseFunctionSwitch.isOn = header == 1//为1即为开
            }
        }
        baseFunctionSwitch.addTarget(self, action: #selector(baseFunctionOpenOrCloseRemindAction(sender:)), for: .touchUpInside)
        cell?.accessoryView = baseFunctionSwitch
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        
    }

    deinit {
        print("deinit")
    }
    
}
