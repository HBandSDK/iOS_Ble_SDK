//
//  VPHRVTestVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/4/23.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPHRVTestVC: UIViewController {

    private var isSupHRVTest: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupportHRVTest
    }
    
    private var timer: Timer?
    
    private var testBtn: UIButton!
    
    private var valueLab: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        endTestTimer()
        hrvTest(false)
    }
    
}

extension VPHRVTestVC {
    private func setupSubViews() {
        view.backgroundColor = .white
        title = "HRV测量"
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupHRVTest ? "是" : "否")
        
        testBtn = UIButton(frame: CGRect(x: 30, y: 90, width: 100, height: 30))
        testBtn.setTitle("开始测量", for: .normal)
        testBtn.setTitle("关闭测试", for: .selected)
        testBtn.isHidden = !self.isSupHRVTest
        view.addSubview(testBtn)
        testBtn.backgroundColor = .blue
        testBtn.addTarget(self, action: #selector(hrvTestAction), for: .touchUpInside)
        
        valueLab = UILabel(frame: CGRect(x: 150, y: 90, width: 100, height: 30))
        view.addSubview(valueLab)
        valueLab.text = ""
    }
    
    private func hrvTest(_ state: Bool) {
        // *HRV测量是持续测量,设备端不会主动关闭测量,所以需要App主动关闭测量*
        if state {
            print("开始测试")
            self.startTestTimer()
        } else {
            print("关闭测试")
            self.endTestTimer()
        }
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_HRVTest(state) {[weak self] con, ack, hrvValue in
            print(con,ack,hrvValue)
            if ack == .testing {
                if con == 1 {
                    self?.valueLab.text = "\(hrvValue)"
                }
            } else {
                
            }
        }
    }
    
    private func startTestTimer() {
        endTestTimer()
        var count = 0
        timer = Timer.scheduledTimer(withTimeInterval: 1, repeats: true, block: {[weak self] timer in
            if count > 60 {
                self?.endTestTimer()
                self?.hrvTest(false)
                self?.testBtn.isSelected = false
            }
            count += 1
        })
    }
    
    private func endTestTimer() {
        timer?.invalidate()
        timer = nil
    }
    
    
    @objc func hrvTestAction() {
        testBtn.isSelected = !testBtn.isSelected
        hrvTest(testBtn.isSelected)
    }
}
