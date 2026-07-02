//
//  VPEmotionVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/6/23.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPEmotionVC: UIViewController {

    private var isSupTest: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupportEmotionTest
    }
    
    private var testBtn: UIButton!
    
    private var valueLab: UILabel!
    
    private var progressLab: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }

}

extension VPEmotionVC {
    private func setupSubViews() {
        view.backgroundColor = .white
        title = "情绪测量"
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupTest ? "是" : "否")
        
        testBtn = UIButton(frame: CGRect(x: 30, y: 90, width: 100, height: 40))
        testBtn.setTitle("开始测量", for: .normal)
        testBtn.setTitle("关闭测试", for: .selected)
        testBtn.isHidden = !self.isSupTest
        view.addSubview(testBtn)
        testBtn.backgroundColor = .blue
        testBtn.addTarget(self, action: #selector(testAction), for: .touchUpInside)
        
        progressLab = UILabel(frame: CGRect(x: 150, y: 90, width: 100, height: 30))
        view.addSubview(progressLab)
        progressLab.text = ""
        
        valueLab = UILabel(frame: CGRect(x: 260, y: 90, width: 100, height: 30))
        view.addSubview(valueLab)
        valueLab.text = ""
    }
    
    private func metTest(_ state: Bool) {
       
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_emotionTest(state) {[weak self] con, ack, progress, value in
            print(con,ack, progress,value)
            guard let self = self else { return }
            if ack == .testing {
                if con == 1 {
                    self.progressLab.text = "进度:\(progress)%"
                    if progress == 100 {
                        self.valueLab.text = "结果:\(value)"
                        self.testBtn.isSelected = !self.testBtn.isSelected
                    }
                }
            } else {
                
            }
        }
    }
    
    
    @objc func testAction() {
        testBtn.isSelected = !testBtn.isSelected
        metTest(testBtn.isSelected)
        if testBtn.isSelected {
            self.valueLab.text = ""
        }
    }
}

