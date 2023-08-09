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
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "自定义扫描"
        
        VPCustomScanManage.sharedInstance.initDelegate()
        
        view.backgroundColor = UIColor.white
        navigationItem.rightBarButtonItem = UIBarButtonItem(title: "测试", style: .plain, target: self, action: #selector(startScanDevices))
    }
    
    @objc func startScanDevices() -> Void {
        VPCustomScanManage.sharedInstance.startScanDevices()
    }
    
}
