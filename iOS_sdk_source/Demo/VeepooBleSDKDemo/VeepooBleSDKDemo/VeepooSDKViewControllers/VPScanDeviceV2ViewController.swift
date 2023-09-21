//
//  VPScanDeviceV2ViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/8/9.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit
import CoreBluetooth

/// 不使用SDK的扫描
class VPScanDeviceV2ViewController: UIViewController {
    
    private var selfScanBtn:UIButton!
    private var systemBtn:UIButton!
    private var disconnectBtn:UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "自定义扫描"
        setupSubViews()
        
        VPCustomScanManage.sharedInstance.initDelegate()
        
        view.backgroundColor = UIColor.white
    }
    
    @objc func startScanDevices() -> Void {
        VPCustomScanManage.sharedInstance.startScanDevices()
    }
    
    @objc func systemConnectDevice() -> Void {
        VPCustomScanManage.sharedInstance.connectFromSystem()
    }
    
    @objc func disconnectBtnAction() -> Void {
        VPCustomScanManage.sharedInstance.disconnectDevice()
    }
}

extension VPScanDeviceV2ViewController {
    
    private func setupSubViews() {
        selfScanBtn = .init(type: .system)
        selfScanBtn.frame = CGRect(x: 40, y: 100, width: 80, height: 40)
        selfScanBtn.backgroundColor = .lightGray
        selfScanBtn.setTitle("自扫描", for: .normal)
        selfScanBtn.addTarget(self, action: #selector(startScanDevices), for: .touchUpInside)
        view.addSubview(selfScanBtn)
                
        systemBtn = .init(type: .system)
        systemBtn.frame = CGRect(x: 40, y: 160, width: 80, height: 40)
        systemBtn.backgroundColor = .lightGray
        systemBtn.setTitle("系统", for: .normal)
        systemBtn.addTarget(self, action: #selector(systemConnectDevice), for: .touchUpInside)
        view.addSubview(systemBtn)
        
        disconnectBtn = .init(type: .system)
        disconnectBtn.frame = CGRect(x: 40, y: 220, width: 80, height: 40)
        disconnectBtn.backgroundColor = .lightGray
        disconnectBtn.setTitle("断开连接", for: .normal)
        disconnectBtn.addTarget(self, action: #selector(disconnectBtnAction), for: .touchUpInside)
        view.addSubview(disconnectBtn)
    }
}
