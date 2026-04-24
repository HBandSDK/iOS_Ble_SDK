//
//  VPJE136PTCMVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/4/22.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPJE136PTCMVC: UIViewController {
    
    // MARK: - 诊断选项定义
    private let diagnosisOptions: [String] = [
        "血瘀", "湿热", "特禀", "阳虚",
        "阴虚", "痰湿", "平和","气郁",
        "气虚", "大肠", "胆", "肝",
        "脾", "肺","小肠", "三焦膀胱",
        "肾", "胃", "心脏"
    ]
    
    private let options: [JE136PTCMOption] = [
        .bloodStasis,
        .dampHeat,
        .specialAllergy,
        .yangDeficiency,
        .yinDeficiency,
        .phlegmDampness,
        .balanced,
        .qiStagnation,
        .qiDeficiency,
        .largeIntestine,
        .gallbladder,
        .liver,
        .spleen,
        .lung,
        .smallIntestine,
        .sanjiaoBladder,
        .kidney,
        .stomach,
        .heart,
    ]
    
    // MARK: - UI 组件
    private let scrollView = UIScrollView()
    private let contentView = UIView()
    private var steppers: [UIStepper] = []
    private var valueLabels: [UILabel] = []
    private var switchControls: [UISwitch] = []
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
    }
    
    // MARK: - UI Setup
    private func setupUI() {
        view.backgroundColor = .systemBackground
        title = "JE136P定制中医数据下发"
        
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .save, target: self, action: #selector(sendTCMData))
        
        scrollView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(scrollView)
        
        contentView.translatesAutoresizingMaskIntoConstraints = false
        scrollView.addSubview(contentView)
        
        NSLayoutConstraint.activate([
            scrollView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            scrollView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            scrollView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            scrollView.bottomAnchor.constraint(equalTo: view.bottomAnchor),
            
            contentView.topAnchor.constraint(equalTo: scrollView.topAnchor),
            contentView.leadingAnchor.constraint(equalTo: scrollView.leadingAnchor),
            contentView.trailingAnchor.constraint(equalTo: scrollView.trailingAnchor),
            contentView.bottomAnchor.constraint(equalTo: scrollView.bottomAnchor),
            contentView.widthAnchor.constraint(equalTo: scrollView.widthAnchor)
        ])
        
        createOptionRows()
    }
    
    private func createOptionRows() {
        var lastView: UIView = contentView
        
        for (index, option) in diagnosisOptions.enumerated() {
            let containerView = UIView()
            containerView.translatesAutoresizingMaskIntoConstraints = false
            containerView.backgroundColor = .systemGray6
            containerView.layer.cornerRadius = 8
            contentView.addSubview(containerView)
            
            // Switch
            let switchControl = UISwitch()
            switchControl.translatesAutoresizingMaskIntoConstraints = false
            switchControl.tag = index
            switchControl.isOn = true
            switchControl.addTarget(self, action: #selector(switchChanged(_:)), for: .valueChanged)
            switchControls.append(switchControl)
            containerView.addSubview(switchControl)
            
            // 名称标签
            let nameLabel = UILabel()
            nameLabel.text = option
            nameLabel.font = .systemFont(ofSize: 16, weight: .medium)
            nameLabel.translatesAutoresizingMaskIntoConstraints = false
            containerView.addSubview(nameLabel)
            
            // Stepper
            let stepper = UIStepper()
            stepper.translatesAutoresizingMaskIntoConstraints = false
            stepper.tag = index
            stepper.minimumValue = 0
            stepper.maximumValue = 65535
            stepper.value = Double.random(in: 0...100)
            stepper.stepValue = 10
            stepper.isEnabled = true
            stepper.addTarget(self, action: #selector(stepperValueChanged(_:)), for: .valueChanged)
            steppers.append(stepper)
            containerView.addSubview(stepper)
            
            // 值标签
            let valueLabel = UILabel()
            valueLabel.text = "\(Int(stepper.value))"
            valueLabel.font = .monospacedSystemFont(ofSize: 14, weight: .medium)
            valueLabel.textAlignment = .right
            valueLabel.translatesAutoresizingMaskIntoConstraints = false
            valueLabels.append(valueLabel)
            containerView.addSubview(valueLabel)
            
            NSLayoutConstraint.activate([
                containerView.topAnchor.constraint(equalTo: lastView == contentView ? contentView.topAnchor : lastView.bottomAnchor, constant: 10),
                containerView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 20),
                containerView.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -20),
                containerView.heightAnchor.constraint(equalToConstant: 60),
                
                switchControl.centerYAnchor.constraint(equalTo: containerView.centerYAnchor),
                switchControl.leadingAnchor.constraint(equalTo: containerView.leadingAnchor, constant: 15),
                
                nameLabel.centerYAnchor.constraint(equalTo: containerView.centerYAnchor),
                nameLabel.leadingAnchor.constraint(equalTo: switchControl.trailingAnchor, constant: 15),
                nameLabel.widthAnchor.constraint(equalToConstant: 80),
                
                valueLabel.centerYAnchor.constraint(equalTo: containerView.centerYAnchor),
                valueLabel.trailingAnchor.constraint(equalTo: stepper.leadingAnchor, constant: -10),
                valueLabel.widthAnchor.constraint(equalToConstant: 50),
                
                stepper.centerYAnchor.constraint(equalTo: containerView.centerYAnchor),
                stepper.trailingAnchor.constraint(equalTo: containerView.trailingAnchor, constant: -15)
            ])
            
            lastView = containerView
        }
        
        // 底部间距
        let bottomSpacer = UIView()
        bottomSpacer.translatesAutoresizingMaskIntoConstraints = false
        contentView.addSubview(bottomSpacer)
        
        NSLayoutConstraint.activate([
            bottomSpacer.topAnchor.constraint(equalTo: lastView.bottomAnchor, constant: 20),
            bottomSpacer.leadingAnchor.constraint(equalTo: contentView.leadingAnchor),
            bottomSpacer.trailingAnchor.constraint(equalTo: contentView.trailingAnchor),
            bottomSpacer.bottomAnchor.constraint(equalTo: contentView.bottomAnchor),
            bottomSpacer.heightAnchor.constraint(equalToConstant: 20)
        ])
    }
    
    // MARK: - Actions
    @objc private func switchChanged(_ sender: UISwitch) {
        let index = sender.tag
        steppers[index].isEnabled = sender.isOn
    }
    
    @objc private func stepperValueChanged(_ sender: UIStepper) {
        let index = sender.tag
        valueLabels[index].text = "\(UInt16(sender.value))"
    }
    
    @objc func sendTCMData() {
        let model = VPJE136PTCMModel()
        let sendTime = UInt32(Date().timeIntervalSince1970)
        model.timestamp = sendTime
        var support: UInt32 = 0
        for (index, step) in steppers.enumerated() {
            if step.isEnabled {
                support = support | options[index].rawValue
            }
            let val = UInt16(valueLabels[index].text!)!
            switch index {
            case 0: model.bloodStasis = val
            case 1: model.dampHeat = val
            case 2: model.specialAllergy = val
            case 3: model.yangDeficiency = val
            case 4: model.yinDeficiency = val
            case 5: model.phlegmDampness = val
            case 6: model.balanced = val
            case 7: model.qiStagnation = val
            case 8: model.qiDeficiency = val
            case 9: model.largeIntestine = val
            case 10: model.gallbladder = val
            case 11: model.liver = val
            case 12: model.spleen = val
            case 13: model.lung = val
            case 14: model.smallIntestine = val
            case 15: model.sanjiaoBladder = val
            case 16: model.kidney = val
            case 17: model.stomach = val
            case 18: model.heart = val
            default:
                break
            }
        }
        
        model.option = support
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_JE136PSendTCMCustomData(model) {[weak self] time in
            guard let self = self else { return }
            AppDelegate.showHUD(message: sendTime == time ? "成功" : "失败", hudModel: MBProgressHUDModeText, showView: self.view)
        }
    }
}

