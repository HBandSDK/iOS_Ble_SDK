//
//  VPQH15SecurityProtectionViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/1/7.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPQH15SecurityProtectionViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        bindViewModel()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    var isSupSP: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.securityProtection != 0 ? true : false
    }
    
    private func setupSubViews() {
        
        view.backgroundColor = .white
        title = "QH15安全守护"
        
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupSP ? "是" : "否")
        
        if isSupSP {
            let label = UILabel(frame: CGRect(x: 30, y: 90, width: 100, height: 40))
            label.text = "安全守护"
            view.addSubview(label)
            
            let sw = UISwitch(frame: CGRect(x: 150, y: 90, width: 0, height: 0))
            view.addSubview(sw)
            sw.addTarget(self, action: #selector(setProtectionAction(sw:)), for: .touchUpInside)
        }
        
    }
    
    @objc func setProtectionAction(sw: UISwitch) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SetProtectionOpen(sw.isOn) { ack in
            if ack == .success {
                print("成功")
            }
        }
    }
    
    private func bindViewModel() {
        ///  这里监听只能监听到设备上开启/关闭守护功能的通知,如果想要设备断连重连时接受通知需要自行选择合适的时机实现下面方法
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15ProtectionResultSubscribe { open, time in
            print(open, time)
        }
        
        /// 监听设备请求/推送GNSS位置
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15GNSSLocationResultSubscribe { type, model in
            guard let model = model else { return }
            print(model)
        }
    }

}
