//
//  VPECGMultiLeadViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/11/1.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPECGMultiLeadViewController: UIViewController {
    
    var leadIArr:[NSNumber] = []
    var leadIIArr:[NSNumber] = []
    var leadIIIArr:[NSNumber] = []
    var leadAVRArr:[NSNumber] = []
    var leadAVLArr:[NSNumber] = []
    var leadAVFArr:[NSNumber] = []
    
    var timerSource:DispatchSourceTimer?
    
    var lastIndex:Int = 0
    
    private var chartView: VPECGMultiLeadChartReportView!
    
    private var opButton: UIButton!
    private var infoLable: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()        
        setupSubViews()
        VPBleCentralManage.sharedBleManager().peripheralManage.ecgMultiLeadBLEDelegate = self
    }
    
    
    @objc func opButtonAction(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            chartView.reset()
        }
        lastIndex = 0
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_ECGMultiLeadTest(withStart: sender.isSelected)
    }
}

extension VPECGMultiLeadViewController {
    private func setupSubViews() {
        title = "多导心电"
        view.backgroundColor = UIColor.white
        
        opButton = .init(type: .system)
        opButton.setTitle("开始测试", for: .normal)
        opButton.setTitle("结束测试", for: .selected)
        opButton.frame = CGRect(x: 10, y: 10, width: 100, height: 38)
        opButton.addTarget(self, action: #selector(opButtonAction(_:)), for: .touchUpInside)
        view.addSubview(opButton)
        
        let width:Int = Int(UIScreen.main.bounds.width)
        
        infoLable = .init(frame: CGRect(x: 0, y: 40, width: width, height: 38))
        infoLable.textAlignment = .center
        infoLable.text = "progress: 0%, heart:0, qt:0, hrv:0"
        view.addSubview(infoLable)
        
        chartView = .init(frame: CGRect(x: 0, y: 78, width: width, height: 120))
        view.addSubview(chartView)
    }
}

extension VPECGMultiLeadViewController: VPECGMultiLeadBLEDelegate {
    
    /// 前置信息响应触发
    /// - Parameters:
    ///   - frequency: 频率 固定 250
    ///   - leads: 导联数量 固定 6 路
    func vpecgMultiLeadDidResponsePreInfoFrequency(_ frequency: UInt16, leads: UInt8) {
        print("frequency = \(frequency), leads = \(leads)")
        leadIArr = []
        leadIIArr = []
        leadIIIArr = []
        leadAVRArr = []
        leadAVLArr = []
        leadAVFArr = []
    }
    
    /// 每秒信息包返回
    /// - Parameter infoModel: 信息包对象
    func vpecgMultiLeadDidResponseProgressInfo(_ infoModel: VPECGMultiLeadProgressInfoModel) {
        let str:String = "progress: \(infoModel.progress)%, heart:\(infoModel.heart), qt:\(infoModel.qt), hrv:\(infoModel.hrv)"
        print(str)
        infoLable.text = str
    }
    
    /// 6路波形返回
    /// - Parameter waveFormModel: 每路波形的对象
    func vpecgMultiLeadDidResponseWaveFormData(_ waveFormModel: VPECGMultiLeadWaveFormModel) {
        if waveFormModel.leadType == .typeI {
            waveFormModel.waveFormArr.forEach { v in
                leadIArr.append(v)
            }
        }
        if waveFormModel.leadType == .typeII {
            waveFormModel.waveFormArr.forEach { v in
                leadIIArr.append(v)
            }
        }
        if waveFormModel.leadType == .typeIII {
            waveFormModel.waveFormArr.forEach { v in
                leadIIIArr.append(v)
            }
        }
        if waveFormModel.leadType == .typeaVR {
            waveFormModel.waveFormArr.forEach { v in
                leadAVRArr.append(v)
            }
        }
        if waveFormModel.leadType == .typeaVL {
            waveFormModel.waveFormArr.forEach { v in
                leadAVLArr.append(v)
            }
        }
        if waveFormModel.leadType == .typeaVF {
            waveFormModel.waveFormArr.forEach { v in
                leadAVFArr.append(v)
            }
        }
    }
    
    /// 测量完成后的诊断结果返回
    /// - Parameter diagnosisResultModel: 诊断结果对象
    func vpecgMultiLeadDidResponseDiagnosisResult(_ diagnosisResultModel: VPECGMultiLeadDiagnosisResultModel) {
        print(diagnosisResultModel)
    }
    
    /// 测量成功并且波形返回结束
    func vpecgMultiLeadDidResponseSuccess() {
        print(">> vpecgMultiLeadDidResponseSuccess")
        if opButton.isSelected {
            opButton.isSelected = false
            print("leadIArr = \(leadIArr.count)")
            print("leadIIArr = \(leadIIArr.count)")
            print("leadIIIArr = \(leadIIIArr.count)")
            print("leadAVRArr = \(leadAVRArr.count)")
            print("leadAVLArr = \(leadAVLArr.count)")
            print("leadAVFArr = \(leadAVFArr.count)")
        }
        if leadIArr.count > 0 {
            chartView.dataArr = leadIArr
        }
    }
    
    /// 指令响应测量结束
    func vpecgMultiLeadDidResponseEndTest() {
        print(">> vpecgMultiLeadDidResponseEndTest")
        if opButton.isSelected {
            opButton.isSelected = false
        }
    }
    
    /// 测量失败时触发
    func vpecgMultiLeadTestFailure() {
        print(">> vpecgMultiLeadTestFailure")
        if opButton.isSelected {
            opButton.isSelected = false
        }
    }
}
