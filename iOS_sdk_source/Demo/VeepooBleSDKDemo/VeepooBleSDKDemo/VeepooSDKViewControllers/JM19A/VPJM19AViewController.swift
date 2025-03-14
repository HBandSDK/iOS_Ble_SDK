//
//  VPJM19AViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2025/3/14.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPJM19AViewController: UIViewController {
    
    @IBOutlet weak var testBtn: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "中医诊断定制"
        
        let typeArr:[String] = ["ppg1", "ppg2", "ppg3"]
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JM19AProjectTCMPPGADCSubscribe { type, dataArr in
            let typeInt = Int(type)
            if let dataArr = dataArr {
                print("类型：\(typeArr[typeInt]), dataArr count: \(dataArr.count)")
            }
        }
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        // 取消订阅
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JM19AProjectTCMPPGADCSubscribe(nil)
    }
    
    @IBAction func testBtnAction(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        
        VPBleCentralManage.sharedBleManager().peripheralManage
            .veepooSDK_JM19AProjectTCMTest(withStart: sender.isSelected) { [weak self] (state, progress, model) in
                guard let `self` = self else {
                    return
                }
                print("类型：\(state), progress: \(progress)")
                if state == .testing, let model = model {
                    print("testing, adc_count: \(model.filterSignals.count)")
                }
                
                if state == .complete, let model = model {
                    self.getResult(model: model)
                }
            }
    }
    
    private func getResult(model: VPTCMTestDataModel) {
        let report = VPECGTestResutHandle.resultReport(withTCMModel: model)
        print("\(report.diseaseRisk)")
    }
}
