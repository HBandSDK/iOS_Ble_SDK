//
//  VPAGPSViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/8/27.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPAGPSViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    

    private var isSupTest: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.agpsFunction != 0
    }
    
    private var stateLab: UILabel!

    private var progressLab: UILabel!
}

extension VPAGPSViewController {
    func setupSubViews() {
        
        view.backgroundColor = .white
        title = "星历"
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupTest ? "是" : "否")
        
        if !self.isSupTest {
            return
        }
        
        stateLab = .init(frame: CGRect(x: 30, y: 80, width: 340, height: 30))
        stateLab.font = UIFont .systemFont(ofSize: 16)
        view.addSubview(stateLab)
        
        
        let readBtn = UIButton.init(frame: CGRect(x: 30, y: 120, width: 120, height: 40))
        view.addSubview(readBtn)
        readBtn.setTitle("读取星历信息", for: .normal)
        readBtn.backgroundColor = .blue
        readBtn.addTarget(self, action: #selector(readAGPSAction), for: .touchUpInside)
        
        let downlondBtn = UIButton.init(frame: CGRect(x: 30, y: 180, width: 120, height: 40))
        view.addSubview(downlondBtn)
        downlondBtn.setTitle("下载并传输", for: .normal)
        downlondBtn.backgroundColor = .blue
        downlondBtn.addTarget(self, action: #selector(downlondBtnAction), for: .touchUpInside)
        
        progressLab = .init(frame: CGRect(x: 30, y: 240, width: 220, height: 30))
        view.addSubview(progressLab)
    }
    
    @objc func readAGPSAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readDeviceAGPSDataResult {[weak self] model in
            guard let weakSelf = self, let m = model else { return }
            let validDay = String(format: "%.1f", Double(m.validMin) / 1440.0)
            weakSelf.stateLab.text = "星历有效总时长\(m.validDay)天,星历剩余时长\(validDay)天"
        }
    }
    
    @objc func downlondBtnAction() {
        let timestamp = Int(Date().timeIntervalSince1970) /// veepooSDK_getAGPSFileUrl 是网络请求 需要网络权限
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_getAGPSFileUrl { url, respone, error  in
            if error == nil && url != nil {
                VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_AGPSTransformV1(withFileUrl: url, timestamp: timestamp) { error in
                    
                } transformProgress: { [weak self] progress in
                    guard let weakSelf = self else { return }
                    weakSelf.progressLab.text = "传输进度:\(Int(progress * 100))%"
                } transformCompleted: { [weak self] in
                    guard let weakSelf = self else { return }
                    weakSelf.readAGPSAction()// 传输完成后重新读取星历信息
                }
            }
        }
    }
    
}

