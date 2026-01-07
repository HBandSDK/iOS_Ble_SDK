//
//  VP4GViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/1/4.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VP4GViewController: UIViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        readDeviceInfo()
        // Do any additional setup after loading the view.
    }
    
    var isSup4G: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupport4GType != 0 ? true : false
    }
    
    private var switch4g: UISwitch?
    
    private var switchSync: UISwitch?
    
    private var intervalTimeLab: UILabel?
    
    private var hostTextFiled: UITextField?
    
    private var portTextField: UITextField?
    
    private var accountTextFiled: UITextField?
    
    private var passwordTextField: UITextField?
    
    private func setupSubViews() {
        
        view.backgroundColor = .white
        title = "4G功能"
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSup4G ? "是" : "否")
        
        if self.isSup4G {
//            let readBtn = UIButton(frame: CGRect(x: 30, y: 80, width: 120, height: 45))
//            readBtn.setTitle("读取设备信息", for: .normal)
//            readBtn.backgroundColor = .orange
//            view.addSubview(readBtn)
//            readBtn.addTarget(self, action: #selector(readDeviceInfo), for: .touchUpInside)
            
            let (hTextField, hostFieldView) = setupTextFiledView(text: "Host")
            hostFieldView.frame = CGRect(x: CGRectGetMinX(suplab.frame), y: CGRectGetMaxY(suplab.frame) + 10, width: 150, height: 65)
            hostTextFiled = hTextField
            view.addSubview(hostFieldView)
            
            let (pTextField, portFieldView) = setupTextFiledView(text: "端口")
            portFieldView.frame = CGRect(x: CGRectGetMinX(hostFieldView.frame), y: CGRectGetMaxY(hostFieldView.frame) + 10, width: CGRectGetWidth(hostFieldView.frame), height: CGRectGetHeight(hostFieldView.frame))
            portTextField = pTextField
            view.addSubview(portFieldView)
            
            let (accTextField, accFieldView) = setupTextFiledView(text: "账号")
            accFieldView.frame = CGRect(x: CGRectGetMaxX(hostFieldView.frame) + 20, y: CGRectGetMinY(hostFieldView.frame), width: 150, height: 65)
            accountTextFiled = accTextField
            view.addSubview(accFieldView)
            
            let (passTextField, passFieldView) = setupTextFiledView(text: "密码")
            passFieldView.frame = CGRect(x: CGRectGetMaxX(portFieldView.frame) + 20, y: CGRectGetMinY(portFieldView.frame), width: CGRectGetWidth(hostFieldView.frame), height: CGRectGetHeight(hostFieldView.frame))
            passwordTextField = passTextField
            view.addSubview(passFieldView)
            
            let configBtn = UIButton(frame: CGRect(x: CGRectGetMinX(portFieldView.frame), y: CGRectGetMaxY(portFieldView.frame) + 10, width: 120, height: 40))
            configBtn.setTitle("配置MQTT", for: .normal)
            configBtn.backgroundColor = .blue
            view.addSubview(configBtn)
            configBtn.addTarget(self, action: #selector(configMQTTInfo), for: .touchUpInside)
            
            let accountConfigBtn = UIButton(frame: CGRect(x: CGRectGetMinX(passFieldView.frame), y: CGRectGetMinY(configBtn.frame), width: CGRectGetWidth(configBtn.frame), height: CGRectGetHeight(configBtn.frame)))
            accountConfigBtn.setTitle("配置账号", for: .normal)
            accountConfigBtn.backgroundColor = .blue
            view.addSubview(accountConfigBtn)
            accountConfigBtn.addTarget(self, action: #selector(configAccountInfo), for: .touchUpInside)
            
            let lab4g = UILabel(frame: CGRect(x: 30, y: CGRectGetMaxY(configBtn.frame) + 10, width: 140, height: 40))
            lab4g.text = "启动移动网络:"
            view.addSubview(lab4g)
            
            let syncLab = UILabel(frame: CGRect(x: CGRectGetMinX(lab4g.frame), y: CGRectGetMaxY(lab4g.frame) + 10, width: 160, height: 40))
            syncLab.text = "使用移动数据同步:"
            view.addSubview(syncLab)
            
            switch4g = UISwitch(frame: CGRect(x: CGRectGetMaxX(lab4g.frame)+10, y: 0, width: 0, height: 0))
            view.addSubview(switch4g!)
            switch4g?.center.y = lab4g.center.y
            switch4g?.addTarget(self, action: #selector(switch4gAction), for: .valueChanged)
            
            switchSync = UISwitch(frame: CGRect(x: CGRectGetMaxX(syncLab.frame)+10, y: 0, width: 0, height: 0))
            view.addSubview(switchSync!)
            switchSync?.center.y = syncLab.center.y
            switchSync?.addTarget(self, action: #selector(switchSyncAction), for: .valueChanged)
            
            intervalTimeLab = UILabel(frame: CGRect(x: CGRectGetMinX(lab4g.frame), y: CGRectGetMaxY(syncLab.frame) + 10, width: 140, height: 40))
            view.addSubview(intervalTimeLab!)
            
            let seg = UISegmentedControl(items: ["5分钟", "10分钟", "15分钟"])
            seg.frame = CGRect(x: CGRectGetMaxX(intervalTimeLab!.frame) + 10, y: CGRectGetMinY(intervalTimeLab!.frame), width: 160, height: 40)
            view.addSubview(seg)
            seg.addTarget(self, action: #selector(setIntervalTimeAction(seg:)), for: .valueChanged)
            
            navigationItem.rightBarButtonItem = UIBarButtonItem.init(title: "隐藏键盘", style: .plain, target: self, action: #selector(hiddenKeyboard))
            
            let clearAccBtn = UIButton(frame: CGRect(x: CGRectGetMinX(lab4g.frame), y: CGRectGetMaxY(intervalTimeLab!.frame) + 10, width: CGRectGetWidth(configBtn.frame), height: CGRectGetHeight(configBtn.frame)))
            clearAccBtn.backgroundColor = .orange
            clearAccBtn.setTitle("清除账号", for: .normal)
            clearAccBtn.addTarget(self, action: #selector(clearAction), for: .touchUpInside)
            view.addSubview(clearAccBtn)
        }
        
    }
    
    @objc func hiddenKeyboard() {
        view.endEditing(true)
    }
    
    private func setupTextFiledView(text: String) -> (textField: UITextField, bottomView: UIView){
        let view = UIView()
        
        let titleLab = UILabel(frame: CGRect(x: 0, y: 0, width: 150, height: 30))
        titleLab.text = text
        view.addSubview(titleLab)
        
        let textField = UITextField(frame: CGRect(x: 0, y: 30, width: 150, height: 35))
        textField.borderStyle = .roundedRect
        view.addSubview(textField)
        
        return (textField: textField, bottomView: view)
    }
    
    @objc func clearAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_modifyAccountValidState(0) {[weak self] success in
            print(success ? "成功" : "失败")
            guard let self = self else { return }
            accountTextFiled?.text = ""
            passwordTextField?.text = ""
        }
    }
    
    @objc func configMQTTInfo() {
        guard let host = hostTextFiled?.text, let port = portTextField?.text, let p = Int(port) else { return }
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_modifyMQTTConfig(host, port: p) { success in
            print(success ? "成功" : "失败")
        }
    }
    
    @objc func configAccountInfo() {
        guard let acc = accountTextFiled?.text, let pass = passwordTextField?.text else { return }
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_bind4GDeviceAccount(acc, password: pass) { success in
            print(success ? "设备同意绑定新的账号" : "设备拒绝绑定新的账号")
            if success {
                VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_sendVerifyInfoSucc()
            }
        }
    }
    
    @objc func setIntervalTimeAction(seg: UISegmentedControl) {
        let times = [5,10,15]
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_modifySyncTimeInterval(times[seg.selectedSegmentIndex]) {[weak self] success in
            print(success ? "成功" : "失败")
            let title = seg.titleForSegment(at: seg.selectedSegmentIndex) ?? ""
            self?.intervalTimeLab?.text = "同步频率:\(title)"
            
        }
    }
    
    @objc func switch4gAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_modify4GSwitchEnableState(switch4g!.isOn ? 1 : 0) { success in
            
        }
    }
    
    @objc func switchSyncAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_modify4GSyncSwitchEnableState(switchSync!.isOn ? 1 : 0) { success in
            
        }
    }
    
    @objc func readDeviceInfo() {
        if !self.isSup4G {
            return
        }
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_read4GDeviceConfigInfoSubscribe {[weak self] state, config in
            guard let self = self, let config = config else { return }
            print("host:\(config.deviceHost),port:\(config.devicePort),账号:\(config.account),密码:\(config.password)")
            switch4g?.isOn = config.is4GSwitchEnable
            switchSync?.isOn = config.isSyncDataSwitchEnable
            intervalTimeLab?.text = "同步频率:\(config.intervalTime)分钟"
            hostTextFiled?.text = config.deviceHost
            portTextField?.text = "\(config.devicePort)"
            accountTextFiled?.text = config.account
            passwordTextField?.text = config.password
        }
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
