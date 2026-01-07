//
//  VPGSRViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/12/30.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPGSRViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    var isSupGSR: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.gsrType != 0 ? true : false
    }
    
    private var progressLabel: UILabel!
    
    private var resultLabel: UILabel!
    
    private func setupSubViews() {
        view.backgroundColor = .white
        title = "皮电"
        let lab = UILabel(frame: CGRect(x: 30, y: 50, width: 100, height: 40))
        view.addSubview(lab)
        lab.text = "是否支持:" + (self.isSupGSR ? "是" : "否")
        
        let testBtn = UIButton(frame: CGRect(x: 30, y: 120, width: 100, height: 40))
        testBtn.backgroundColor = .blue
        testBtn.setTitle("开启测试", for: .normal)
        testBtn.setTitle("关闭测试", for: .selected)
        testBtn.isHidden = !self.isSupGSR
        testBtn.addTarget(self, action: #selector(startTest(btn:)), for: .touchUpInside)
        view.addSubview(testBtn)
        
        progressLabel = UILabel(frame: CGRect(x: 30, y: 180, width: 200, height: 40))
        view.addSubview(progressLabel)
        
        resultLabel = UILabel(frame: CGRect(x: 30, y: 240, width: CGRectGetWidth(self.view.frame)-60, height: 80))
        resultLabel.numberOfLines = 0
        view.addSubview(resultLabel)
    }
    
    @objc func startTest(btn: UIButton) {
        btn.isSelected = !btn.isSelected
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestGSRStart(btn.isSelected) {[weak self] progress in
            guard let self = self, let pro = progress else { return }
            let value = Double(pro.completedUnitCount) / Double(pro.totalUnitCount)
            self.progressLabel.text = "进度:\(value*100)%"
        } testResult: {[weak self] state, resultModel in
            guard let self = self else { return }
//            /// depression_risk 抑郁症风险 [0,2] 0:低风险 1：中风险 2：高风险
            if state == .complete {
                guard let res = resultModel else { return }
                self.resultLabel.text = "情绪:\(res.emotin_level) 皮肤含水量:\(res.skin_moisture) 抑郁症风险:\(res.depression_risk) 交感神经活跃度:\(res.sns_activation) 皮质醇浓度:\(res.cortisol_value)"
            }else if state == .over {
                self.resultLabel.text = "人为结束"
            }else {
                self.resultLabel.text = "异常参考VPDeviceGSRState枚举类型查看原因"
            }
        }
    }

}


