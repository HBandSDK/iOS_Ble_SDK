//
//  VPStressTestViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/12/27.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPStressTestViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    private var progressLab: UILabel!
    
    private func setupSubViews() {
        view.backgroundColor = .white
        title = "压力测量"
        progressLab = UILabel(frame: CGRect(x: 60, y: 100, width: 200, height: 40))
        progressLab.text = "测量进度"
        self.view.addSubview(progressLab)
        
        let testBtn = UIButton(frame: CGRect(x: 60, y: 160, width: 120, height: 45))
        testBtn.setTitle("开始测量", for: .normal)
        testBtn.setTitle("结束测量", for: .selected)
        testBtn.backgroundColor = .blue
        testBtn.layer.cornerRadius = 4
        self.view.addSubview(testBtn)
        testBtn.addTarget(self, action: #selector(testAction(btn:)), for: .touchUpInside)
    }
    
    @objc func testAction(btn: UIButton) {
        btn.isSelected = !btn.isSelected
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_stressTestStart(btn.isSelected) {[weak self] state, progress, stress in
            guard let self = self else { return }
            print("进度:\(progress),压力\(stress)")
            self.progressLab.text = "测量进度:\(progress)%,压力\(stress)"
            if state == .over {
                self.progressLab.text = "测量结束"
            }
        }
    }

}
