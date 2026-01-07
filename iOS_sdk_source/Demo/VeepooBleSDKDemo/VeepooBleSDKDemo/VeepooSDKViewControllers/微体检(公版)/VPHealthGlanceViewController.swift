//
//  VPHealthGlanceViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/12/30.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPHealthGlanceViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    
    var isSupHG: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.healthGlanceType > 1 ? true : false
    }
    
    private var progressLabel: UILabel!
    
    private var resultLabel: UILabel!
    
    private func setupSubViews() {
        view.backgroundColor = .white
        title = "微体检(公版)"
        let lab = UILabel(frame: CGRect(x: 30, y: 50, width: 100, height: 40))
        view.addSubview(lab)
        lab.text = "是否支持:" + (self.isSupHG ? "是" : "否")
        
        let testBtn = UIButton(frame: CGRect(x: 30, y: 120, width: 100, height: 40))
        testBtn.backgroundColor = .blue
        testBtn.setTitle("开启测试", for: .normal)
        testBtn.setTitle("关闭测试", for: .selected)
        testBtn.isHidden = !self.isSupHG
        testBtn.addTarget(self, action: #selector(startTest(btn:)), for: .touchUpInside)
        view.addSubview(testBtn)
        
        progressLabel = UILabel(frame: CGRect(x: 30, y: 180, width: 100, height: 40))
        view.addSubview(progressLabel)
        
        resultLabel = UILabel(frame: CGRect(x: 30, y: 240, width: CGRectGetWidth(self.view.frame)-60, height: 80))
        resultLabel.numberOfLines = 0
        view.addSubview(resultLabel)
    }
    
    @objc func startTest(btn: UIButton) {
        btn.isSelected = !btn.isSelected
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_healthGlanceTestStart(btn.isSelected) {[weak self] progress in
            guard let self = self else { return }
            self.progressLabel.text = "进度:\(progress)%"
        } andResult: {[weak self] state, resultModel in
            guard let self = self else { return }
            if state == .complete {
                guard let res = resultModel else { return }
                var result = "测量完成 "
                //支持心率,其他以此类推,判断微体检结果是否包含这项功能,支持输出对应结果,不支持不输出.
                if res.functionSupport & VPHealthGlanceType.heartValue.rawValue != 0 {
                    print("心率:\(res.heartRate)")
                    let str = "心率:\(res.heartRate)"
                    result += str
                }
                if res.functionSupport & VPHealthGlanceType.bloodOxy.rawValue != 0 {
                    let str = "血氧:\(res.bloodOxygen)"
                    result += str
                }
                //其他结果参考上述实现
                self.resultLabel.text = result + " *其他结果参考心率,血氧实现*"
            }else if state == .over {
                self.resultLabel.text = "人为测量结束"
            }else {
                self.resultLabel.text = "异常参考VPDeviceHealthGlanceState枚举类型查看原因"
            }
        }
    }
}
