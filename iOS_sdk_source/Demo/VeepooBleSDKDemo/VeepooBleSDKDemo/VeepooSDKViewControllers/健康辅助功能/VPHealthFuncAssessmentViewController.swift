//
//  VPHealthFuncAssessmentViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/12/29.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPHealthFuncAssessmentViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        readFuns()
        // Do any additional setup after loading the view.
    }
    
    private var supportLab: UILabel?
    
    private func setupSubViews() {
        view.backgroundColor = .white
        title = "健康辅助功能"
        supportLab = .init(frame: CGRect(x: 30, y: 50, width: 120, height: 40))
        view.addSubview(supportLab!)
        supportLab?.text = "是否支持: 否"
    }
    
    private func setupFunView(funs: [VPHealthFunctionModel]) {
        for (ind, fun) in funs.enumerated() {
            let view = UIView(frame: CGRect(x: 30, y: 100+40*ind, width: 240, height: 40))
            let lab = UILabel(frame: CGRect(x: 0, y: 0, width: 80, height: 40))
            let sw = UISwitch(frame: CGRect(x: 120, y: 0, width: 0, height: 0))
            sw.center.y = lab.center.y
            if fun.type == .bloodGlucose {
                lab.text = "血糖"
            }else if fun.type == .bloodComp {
                lab.text = "血液成分"
            }else if fun.type == .bodyComp {
                lab.text = "身体成分"
            }
            sw.tag = 1000 + fun.type.rawValue
            sw.isOn = fun.open
            sw.addTarget(self, action: #selector(setFunState(sw:)), for: .touchUpInside)
            view.addSubview(lab)
            view.addSubview(sw)
            self.view.addSubview(view)
        }
    }
    
    private func readFuns() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readFuncAssessment {[weak self] models in
            guard let self = self, let funs = models else { return }
            self.supportLab?.text = "是否支持: 是"
            self.setupFunView(funs: funs)
        }
    }
    
    @objc func setFunState(sw: UISwitch) {
        var type: VPFuncAssessmentType = .bloodComp
        if sw.tag - 1000 == VPHealthFunctionType.bloodGlucose.rawValue {
            type = .bloodGlucose
        }else if sw.tag - 1000 == VPHealthFunctionType.bloodComp.rawValue {
            type = .bloodComp
        }else if sw.tag - 1000 == VPHealthFunctionType.bodyComp.rawValue {
            type = .bodyComp
        }
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_setFuncAssessment(with: type, open: sw.isOn) { state in
            print(state ? "成功" : "失败")
        }
    }
}
