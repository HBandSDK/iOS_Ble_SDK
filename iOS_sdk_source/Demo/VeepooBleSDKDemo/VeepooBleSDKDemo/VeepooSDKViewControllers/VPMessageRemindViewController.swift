//
//  VPMessageRemindViewController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/16.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPMessageRemindViewController: UIViewController , UITableViewDelegate , UITableViewDataSource {
    
    let messageRemindCellID = "messageRemindCellID"
    
    var messageRemindTableView: UITableView?
    
    let messageFunctions = ["来电","短信","微信","QQ","新浪","Facebook","Twitter","Flickr","Linkedln","whatsApp","Line","Instagram","Snapchat","Skype","GMail","DingTalk","WeChat Work","其他应用"]
    let messageFunctionsTwo = ["TikTok","Telegram","Connected2"]
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "信息提醒"
        view.backgroundColor = UIColor.white
        initMessageRemindViewControllerUI()
    }

    func initMessageRemindViewControllerUI() {
        messageRemindTableView = UITableView(frame: CGRect.init(x: 0, y: 0, width: view.bounds.width, height: view.bounds.height - 80), style: .plain)
        messageRemindTableView?.delegate = self
        messageRemindTableView?.dataSource = self
        view.addSubview(messageRemindTableView!)
        
        let headerView = UIView(frame: CGRect(x: 0, y: 0, width: Width, height: 50));
        for i in 1...2 {
            let operationBtn = UIButton(frame: CGRect(x: CGFloat(i - 1) * Width / 2 + 20, y: 5, width: Width / 2 - 40, height: 40))
            operationBtn.backgroundColor = UIColor.brown
            operationBtn.tag = i
            operationBtn.setTitle(i == 1 ? "全开" : "全关", for: .normal)
            operationBtn.addTarget(self, action: #selector(openOrCloseAllFunction(sender:)), for: .touchUpInside)
            headerView.addSubview(operationBtn)
        }
        messageRemindTableView?.tableHeaderView = headerView
    }
    
    @objc func openOrCloseAllFunction(sender: UIButton)  {//开始设置信息提醒的开关功能
        if VPBleCentralManage.sharedBleManager().isConnected == false {
            _ = AppDelegate.showHUD(message: "设备未连接,设置失败", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingMessageType(VPSettingMessageSwitchType.settingAll, settingState: VPSettingFunctionState(rawValue: sender.tag)!) { (settingFunctionCompleteState) in
            switch settingFunctionCompleteState {
            case .functionCompleteUnknown:
                _ = AppDelegate.showHUD(message: "没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .functionCompleteFailure:
                _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .functionCompleteOpen:
                _ = AppDelegate.showHUD(message: "设置成功，已经开启", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                weakSelf.messageRemindTableView?.reloadData()
            case .functionCompleteClose:
                _ = AppDelegate.showHUD(message: "设置成功，已经关闭", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                weakSelf.messageRemindTableView?.reloadData()
            case .functionCompleteComplete:
                _ = AppDelegate.showHUD(message: "设置完成", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                weakSelf.messageRemindTableView?.reloadData()
            }
        }
    }
    
    @objc func messageOpenOrCloseAction(sender: UISwitch)  {//开始设置信息提醒的开关功能
        if VPBleCentralManage.sharedBleManager().isConnected == false {
            _ = AppDelegate.showHUD(message: "设备未连接,设置失败", hudModel: MBProgressHUDModeText, showView: view)
            self.perform(#selector(settingMessageRemindFarilure(sender:)), with: sender, afterDelay: 0.5)
            return
        }
        
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingMessageType(VPSettingMessageSwitchType(rawValue: sender.tag)!, settingState: VPSettingFunctionState(rawValue: sender.isOn ? 1 : 2)!) { (settingFunctionCompleteState) in
            
            switch settingFunctionCompleteState {
            case .functionCompleteUnknown:
                _ = AppDelegate.showHUD(message: "没有此功能", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                fallthrough
            case .functionCompleteFailure:
                weakSelf.perform(#selector(weakSelf.settingMessageRemindFarilure(sender:)), with: sender, afterDelay: 0.5)
                _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .functionCompleteOpen:
                _ = AppDelegate.showHUD(message: "设置成功，已经开启", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .functionCompleteClose:
                _ = AppDelegate.showHUD(message: "设置成功，已经关闭", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .functionCompleteComplete:
                _ = AppDelegate.showHUD(message: "设置完成", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
    }
    
    /// 设置失败@objc @objc
    @objc func settingMessageRemindFarilure(sender: UISwitch) {
        sender.isOn = !sender.isOn
    }
    
    //MARK: tableView的代理
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return messageFunctions.count + messageFunctionsTwo.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: messageRemindCellID)
        if cell == nil {
            cell = UITableViewCell(style: .default, reuseIdentifier: messageRemindCellID)
        }
        
        cell?.selectionStyle = .none
        
        if indexPath.row < messageFunctions.count { // 第一包
            var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
            if VPBleCentralManage.sharedBleManager().peripheralModel.deviceAncsData != nil {
                VPBleCentralManage.sharedBleManager().peripheralModel.deviceAncsData.copyBytes(to: &tbyte, count: 20)
            }
            var header = tbyte[indexPath.row + 2]//header == 0即为没有此功能，1是开启，2是关闭
            
            cell?.textLabel?.text = messageFunctions[indexPath.row]
            
            let messageSwitch = UISwitch()
            messageSwitch.tag = indexPath.row + 2
            
            if  indexPath.row == messageFunctions.count - 1 {//最后一位代表其他应用，中间预留了几位
                header = tbyte[19]
                messageSwitch.tag = 19
            }
            
            messageSwitch.addTarget(self, action: #selector(messageOpenOrCloseAction(sender:)), for: .touchUpInside)
            messageSwitch.isEnabled = header != 0//为0即为没有此功能
            messageSwitch.isOn = header == 1//为1即为开
            
            cell?.accessoryView = messageSwitch
        }
        
        if indexPath.row >= messageFunctions.count { // 第二包
            var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
            if VPBleCentralManage.sharedBleManager().peripheralModel.deviceAncsDataTwo != nil {
                VPBleCentralManage.sharedBleManager().peripheralModel.deviceAncsDataTwo.copyBytes(to: &tbyte, count: 20)
            }
            let header = tbyte[indexPath.row + 2 - messageFunctions.count]//header == 0即为没有此功能，1是开启，2是关闭
            
            cell?.textLabel?.text = messageFunctionsTwo[indexPath.row - messageFunctions.count]
            
            let messageSwitch = UISwitch()
            messageSwitch.tag = indexPath.row + 2
            messageSwitch.addTarget(self, action: #selector(messageOpenOrCloseAction(sender:)), for: .touchUpInside)
//            messageSwitch.isEnabled = header != 0//为0即为没有此功能
            messageSwitch.isOn = header == 1//为1即为开
            
            cell?.accessoryView = messageSwitch
        }
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        
    }
}
