//
//  VPHNordic54LDFUVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/4/15.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPHNordic54LDFUVC: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    private let stateLabel: UILabel = UILabel()
    
    private var isSupport: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupportNordic
    }
    
    lazy var nordicDfuManager: VPHNordic54LDFUManager = {
        let nordic = VPHNordic54LDFUManager()
        nordic.delegate = self
        return nordic
    }()
    
}

extension VPHNordic54LDFUVC {
    private func setupSubViews() {
        self.title = "Nordic固件升级"
        view.backgroundColor = .white
        
        let titleLab = UILabel(frame: CGRect(x: 20, y: 20, width: 250, height: 40))
        titleLab.text = "是否支持Nordic升级:\(isSupport ? "支持" : "不支持")"
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
        startNordicOTA()
    }
    
    
}

extension VPHNordic54LDFUVC: VPHNordic54LDFUManagerDelegate {
    
    private func startNordicOTA() {
        let fileName = "xxxxxxxx.bin"
        let filePath = Bundle.main.path(forResource: fileName, ofType: nil)
        if (filePath == nil) {
            stateLabel.text = "没找到升级固件"
            return
        }
        let fileURL = URL(fileURLWithPath: filePath!)
        self.nordicDfuManager.setFileInfo(fileURL)
        self.nordicDfuManager.startOTA()
    }
    
    func nordicOtaDidStart() {
        print("nordicOtaDidStart")
        stateLabel.text = "Start"
    }
    
    func nordicOtaStateDidChange(from previousState: String, to newState: String) {
        print("nordicOtaStateDidChange\(previousState)")
        
    }
    
    func nordicOtaDidComplete() {
        print("nordicOtaDidComplete")
        stateLabel.text = "Complete"
    }
    
    func nordicOtaDidFail(inState state: String, error: NSError) {
        print("nordicOtaDidFail")
        stateLabel.text = "Fail"
    }
    
    func nordicOtaUploadProgress(bytesSent: Int, imageSize: Int, progress: Float) {
        print("nordicOtaUploadProgress\(progress)")
        stateLabel.text = "Progress:\(Int(progress*100))"
    }
    
    
}


