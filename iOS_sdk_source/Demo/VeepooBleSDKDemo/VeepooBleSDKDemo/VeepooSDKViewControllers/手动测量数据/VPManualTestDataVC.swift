//
//  VPManualTestDataVC.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2025/6/11.
//  Copyright © 2025 veepoo. All rights reserved.
//

import Foundation
import VeepooBleSDK

class VPManualTestDataVC: UIViewController {
    
    var readBtn: UIButton!
    // 新增 UITextView 用于展示日志内容
    var logTextView: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
    }
    
    @objc private func readBtnClick() {
        readBtn.isEnabled = false
        // 可以从DB中获取当前设备最近的同步过的时间戳
        let timestamp: UInt32 = 0
        VPBleCentralManage.sharedBleManager().peripheralManage.readManualTestData(withTimestamp: timestamp,
                                                                                  dataType: .bloodPressure) { [weak self] model in
            guard let someModel = model else {
                return
            }
            self?.readBtn.isEnabled = true
            // 将日志内容输出到 UITextView 中
            let logText = "someModel = \(someModel.bloodPressureArr)"
            if let existingText = self?.logTextView.text {
                self?.logTextView.text = existingText + "\n" + logText
            } else {
                self?.logTextView.text = logText
            }
        }
    }
}

extension VPManualTestDataVC {
    private func setupSubViews() {
        title = "手动测量数据"
        view.backgroundColor = UIColor.white
        
        readBtn = .init(type: .system)
        readBtn.frame = CGRect(origin: .init(x: 100, y: 50), size: .init(width: 100, height: 40))
        readBtn.addTarget(self, action: #selector(readBtnClick), for: .touchUpInside)
        readBtn.setTitle("读取", for: .normal)
        view.addSubview(readBtn)
        
        // 初始化 UITextView
        logTextView = UITextView()
        let screenWidth = UIScreen.main.bounds.width
        logTextView.frame = CGRect(x: 0, y: 100, width: screenWidth, height: 400)
        logTextView.isEditable = false
        logTextView.backgroundColor = .lightGray
        view.addSubview(logTextView)
    }
}
