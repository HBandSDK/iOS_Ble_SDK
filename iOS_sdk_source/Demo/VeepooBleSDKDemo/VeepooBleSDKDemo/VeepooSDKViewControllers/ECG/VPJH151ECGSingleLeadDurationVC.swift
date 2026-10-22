//
//  VPJH151ECGSingleLeadDurationVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/10/22.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPJH151ECGSingleLeadDurationVC: UIViewController {

    private var durationTextField: UITextField!
    private var tipLabel: UILabel!
    private var resultLabel: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()

        guard VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel.ecgType != 0 else {
            let tipLabel = UILabel()
            tipLabel.text = "不支持ECG功能"
            tipLabel.textAlignment = .center
            tipLabel.textColor = .gray
            tipLabel.font = UIFont.systemFont(ofSize: 16)
            tipLabel.translatesAutoresizingMaskIntoConstraints = false
            view.addSubview(tipLabel)
            NSLayoutConstraint.activate([
                tipLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor),
                tipLabel.centerYAnchor.constraint(equalTo: view.centerYAnchor)
            ])
            return
        }

        setupSubViews()
    }
}

extension VPJH151ECGSingleLeadDurationVC {
    private func setupSubViews() {
        title = "JH151-ECG单导测量时长"
        view.backgroundColor = .white

        let screenWidth = UIScreen.main.bounds.width

        // 输入框
        durationTextField = UITextField(frame: CGRect(x: 20, y: 40, width: screenWidth - 40, height: 40))
        durationTextField.borderStyle = .roundedRect
        durationTextField.keyboardType = .numberPad
        durationTextField.text = "180"
        durationTextField.placeholder = "请输入单导测量时长(秒)"
        view.addSubview(durationTextField)

        tipLabel = UILabel(frame: CGRect(x: 20, y: 88, width: screenWidth - 40, height: 20))
        tipLabel.textColor = .gray
        tipLabel.font = UIFont.systemFont(ofSize: 12)
        tipLabel.text = "说明：单位秒，范围 0~65535，常见值 30/60/180"
        view.addSubview(tipLabel)

        resultLabel = UILabel(frame: CGRect(x: 20, y: 116, width: screenWidth - 40, height: 30))
        resultLabel.textColor = .darkGray
        resultLabel.font = UIFont.systemFont(ofSize: 14)
        resultLabel.text = "结果："
        view.addSubview(resultLabel)

        let buttonTitles = ["设置", "读取"]
        let buttonWidth: CGFloat = 70
        let spacing: CGFloat = 20
        let totalWidth = CGFloat(buttonTitles.count) * buttonWidth + CGFloat(buttonTitles.count - 1) * spacing
        let startX = (screenWidth - totalWidth) / 2
        let buttonY: CGFloat = 166

        for (index, title) in buttonTitles.enumerated() {
            let btn = UIButton(frame: CGRect(x: startX + CGFloat(index) * (buttonWidth + spacing),
                                             y: buttonY,
                                             width: buttonWidth,
                                             height: 40))
            btn.setTitle(title, for: .normal)
            btn.backgroundColor = .blue
            btn.tag = index
            btn.addTarget(self, action: #selector(durationButtonClicked(_:)), for: .touchUpInside)
            view.addSubview(btn)
        }
    }

    @objc func durationButtonClicked(_ sender: UIButton) {
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        switch sender.tag {
        case 0: // 设置
            guard let duration = UInt(durationTextField.text ?? ""), duration <= 65535 else {
                resultLabel.text = "结果：请输入 0~65535 范围内的整数(秒)"
                return
            }
            peripheralManage?.veepooSDK_JH151SetECGSingleLeadTestDuration(duration) { [weak self] success, duration in
                guard let self = self else { return }
                if success {
                    self.resultLabel.text = "结果：设置成功，当前时长：\(duration)秒"
                } else {
                    self.resultLabel.text = "结果：设置失败"
                }
            }
        case 1: // 读取
            peripheralManage?.veepooSDK_JH151ReadECGSingleLeadTestDuration { [weak self] success, duration in
                guard let self = self else { return }
                if success {
                    self.resultLabel.text = "结果：当前时长：\(duration)秒"
                } else {
                    self.resultLabel.text = "结果：读取失败"
                }
            }
        default:
            break
        }
    }
}
