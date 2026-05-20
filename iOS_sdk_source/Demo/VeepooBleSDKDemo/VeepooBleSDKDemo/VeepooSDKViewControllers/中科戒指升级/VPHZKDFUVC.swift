//
//  VPHZKDFUVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/5/20.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPHZKDFUVC: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    private let stateLabel: UILabel = UILabel()
    
    private var isSupport: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupportZKOTA
    }
    
    lazy var zkDfuManager: VPHZKDFUManager = {
        let nordic = VPHZKDFUManager(peripheral: VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel.peripheral)
        nordic.delegate = self
        return nordic
    }()
    
}

extension VPHZKDFUVC {
    private func setupSubViews() {
        self.title = "中科固件升级"
        view.backgroundColor = .white
        
        let titleLab = UILabel(frame: CGRect(x: 20, y: 20, width: 250, height: 40))
        titleLab.text = "是否支持中科升级:\(isSupport ? "支持" : "不支持")"
        self.view.addSubview(titleLab)
        
        let otaBtn = UIButton(frame: CGRect(x: CGRectGetMinX(titleLab.frame), y: CGRectGetMaxY(titleLab.frame) + 20, width: 100, height: 30))
        otaBtn.setTitle("固件升级", for: .normal)
        otaBtn.backgroundColor = .blue
        self.view.addSubview(otaBtn)
        otaBtn.isHidden = !isSupport
        otaBtn.addTarget(self, action: #selector(otaAction), for: .touchUpInside)
        
        stateLabel.frame = CGRect(x: CGRectGetMaxX(otaBtn.frame) + 20, y: CGRectGetMinY(otaBtn.frame), width: 180, height: 30)
        view.addSubview(stateLabel)
        
        let tip = UILabel(frame: CGRect(x: CGRectGetMinX(otaBtn.frame), y: CGRectGetMaxY(otaBtn.frame) + 20, width: UIScreen.main.bounds.size.width - CGRectGetMinX(otaBtn.frame), height: 100))
        tip.numberOfLines = 0
        view.addSubview(tip)
        tip.text = "**固件升级流程,我们只提供固件传输方法,不提供检测是否可以升级和固件下载的方法,这需要使用者自行实现.**"
    }
    
    @objc func otaAction() {
        zkOtaAction()
    }
    
    
}

extension VPHZKDFUVC: VPHZKDFUManagerDelegate {
    func zkOtaStatusReady() {
        print("zkOtaStatusReady")
    }
    
    func zkOtaStatusStart() {
        print("zkOtaStatusStart")
    }
    
    func zkOtaStatusUpdating(progress: UInt) {
        print("zkOtaStatusUpdating\(progress)")
    }
    
    func zkOtaStatuSuccess() {
        print("zkOtaStatuSuccess")
    }
    
    func zkOtaStatusFail(errorCode: Int) {
        print("zkOtaStatusFail\(errorCode)")
    }
    
    @objc func zkOtaAction() {
        let fileName = "xx.bin"
        let filePath = Bundle.main.path(forResource: fileName, ofType: nil)
        if (filePath == nil) {
            stateLabel.text = "没找到升级固件"
            return
        }
        let fileURL = URL(fileURLWithPath: filePath!)
        zkDfuManager.zkDeinitialize()
        zkDfuManager.setFileInfo(fileURL)
        zkDfuManager.enterDfu()
    }
    
}



