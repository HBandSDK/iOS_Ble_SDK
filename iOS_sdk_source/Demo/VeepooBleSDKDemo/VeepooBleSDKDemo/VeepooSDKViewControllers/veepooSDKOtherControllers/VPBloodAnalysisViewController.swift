//
//  VPBloodAnalysisViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/10/11.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPBloodAnalysisViewController: UIViewController {
    private var support: Bool! = false
    private var supportL: UILabel!
    private var opButton: UIButton!
    private var readButton: UIButton!
    private var privateModeButton: UIButton!
        
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
    }
    
    @objc func opButtonAction(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBloodAnalysisStart(sender.isSelected, isPersonalModel: false, progress: { progress in
            if let progress = progress {
                print("progress = \(progress)")
            }
        }, testResult: { [weak self]state, model in
            if state == .complete {
                if let model = model {
                    print(model)
                }
            }
            if state == .failure {
                print("测量失败")
            }
            if state == .over {
                print("手动结束")
            }
            self?.opButton.isSelected = false
        })
    }
    
    @objc func readButtonAction() {
        let tableID = VPBleCentralManage.sharedBleManager()?.peripheralModel.deviceAddress;
        let arr = VPDataBaseOperation.veepooSDKGetDeviceBloodAnalysisData(withDate: "2023-10-18", andTableID: tableID)
        
        guard let arr = arr else {
            print("当日没有血液成分数据")
            return
        }
        
        print(arr)
    }
    
    @objc func privateModeButtonAction() {
//        let setModel:VPBloodAnalysisResultModel = .init()
//        setModel.uricAcidValue = 9.4
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKBloodAnalysisPersonal(withOpCode: 2, open: false, model: nil) { success, openState, model in
            if let model = model {
                print(model)
            }
        }
    }
}

// MARK: - setupSubViews
extension VPBloodAnalysisViewController {
    private func setupSubViews() {
        title = "血液成分"
        view.backgroundColor = UIColor.white
        
        let type = VPBleCentralManage.sharedBleManager().peripheralModel.bloodAnalysisType
        support = type != 0
        supportL = .init()
        supportL.text = "是否支持: " + (support ? "是" : "否")
        supportL.frame = CGRect(x: 30, y: 40, width: 120, height: 38)
        view.addSubview(supportL)
        
        opButton = .init(type: .system)
        opButton.setTitle("手动测试", for: .normal)
        opButton.frame = CGRect(x: 30, y: 100, width: 100, height: 38)
        opButton.addTarget(self, action: #selector(opButtonAction(_:)), for: .touchUpInside)
        view.addSubview(opButton)
        
        readButton = .init(type: .system)
        readButton.setTitle("读取数据", for: .normal)
        readButton.frame = CGRect(x: 150, y: 100, width: 80, height: 38)
        readButton.addTarget(self, action: #selector(readButtonAction), for: .touchUpInside)
        view.addSubview(readButton)
        
        privateModeButton = .init(type: .system)
        privateModeButton.setTitle("校准操作", for: .normal)
        privateModeButton.frame = CGRect(x: 250, y: 100, width: 80, height: 38)
        privateModeButton.addTarget(self, action: #selector(privateModeButtonAction), for: .touchUpInside)
        view.addSubview(privateModeButton)
    }
}

