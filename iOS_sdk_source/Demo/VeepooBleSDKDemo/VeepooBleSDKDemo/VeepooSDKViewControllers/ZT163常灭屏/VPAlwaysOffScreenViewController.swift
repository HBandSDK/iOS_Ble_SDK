//
//  VPAlwaysOffScreenViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/12/24.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPAlwaysOffScreenViewController: UIViewController {

    private var sw: UISwitch!
    
    private var titleLab: UILabel!
    
    private var state: VPZT163AlwaysOffScreenState?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        getState()
        // Do any additional setup after loading the view.
    }
    
    private func setupSubViews() {
        self.title = "常灭屏"
        view.backgroundColor = .white
        titleLab = UILabel(frame: CGRect(x: 20, y: 80, width: 150, height: 40))
        titleLab.text = "常灭屏功能:不支持"
        self.view.addSubview(titleLab)
        
        sw = UISwitch(frame: CGRect(x: 220, y: 80, width: 0, height: 0))
        self.view.addSubview(sw)
        sw.addTarget(self, action: #selector(swAction), for: .valueChanged)
        sw.isHidden = true
        
        
    }

    
    private func getState() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_ZT163GetDeviceAlwaysOffScreenState {[weak self] state in
            guard let self = self else { return }
            self.state = state
            if state != .noSup {
                self.sw.isHidden = false
                self.sw.isOn = state == .open ? true : false
                self.titleLab.text = state == .open ? "常灭屏功能:开启" : "常灭屏功能:关闭"
            }
        }
        
    }
    
    @objc func swAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_ZT163SetDeviceAlwaysOffScreen(sw.isOn) {[weak self] success in
            print(success ? "成功" : "失败")
            guard let self = self else { return }
            if success {
                self.state = self.state == .close ? .open : .close
                self.titleLab.text = self.state == .open ? "常灭屏功能:开启" : "常灭屏功能:关闭"
            }else{
                self.sw.isOn = !self.sw.isOn
            }
        }
    }
    
}
