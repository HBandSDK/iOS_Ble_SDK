//
//  VPChangeDeviceNameViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/4/23.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPChangeDeviceNameViewController: UIViewController {

    private var textField: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
    }
    
    

}

extension VPChangeDeviceNameViewController {
    private func setupSubViews() {
        title = "修改蓝牙名"
        view.backgroundColor = .white
        textField = UITextField(frame: CGRect(x: 20, y: 40, width: 200, height: 40))
        textField.borderStyle = .roundedRect
        textField.text = VPBleCentralManage.sharedBleManager().peripheralModel.deviceName
        view.addSubview(textField)
        
        let btn = UIButton(frame: CGRect(x: 20, y: 100, width: 70, height: 40))
        btn.setTitle("发送", for: .normal)
        btn.backgroundColor = .blue
        view.addSubview(btn)
        btn.addTarget(self, action: #selector(changeDeviceName), for: .touchUpInside)
    }
    
    @objc func changeDeviceName() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceName(with: textField.text) { state in
            print(state)
        }
    }
}
