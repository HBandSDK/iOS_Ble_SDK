//
//  VPSNCodeVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/9/23.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPSNCodeVC: UIViewController {

    private var snTextField: UITextField!
    private var tipLabel: UILabel!
    private var resultLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
    }
}

extension VPSNCodeVC {
    private func setupSubViews() {
        title = "SN码"
        view.backgroundColor = .white
        
        let screenWidth = UIScreen.main.bounds.width
        
        // 输入框
        snTextField = UITextField(frame: CGRect(x: 20, y: 40, width: screenWidth - 40, height: 40))
        snTextField.borderStyle = .roundedRect
        snTextField.placeholder = "请输入SN码"
        snTextField.keyboardType = .numberPad
        view.addSubview(snTextField)
        
        tipLabel = UILabel(frame: CGRect(x: 20, y: 88, width: screenWidth - 40, height: 20))
        tipLabel.textColor = .gray
        tipLabel.font = UIFont.systemFont(ofSize: 12)
        tipLabel.text = "说明：SN码只能为数字，长度固定 10 位"
        view.addSubview(tipLabel)
        
        resultLabel = UILabel(frame: CGRect(x: 20, y: 116, width: screenWidth - 40, height: 30))
        resultLabel.textColor = .darkGray
        resultLabel.font = UIFont.systemFont(ofSize: 14)
        resultLabel.text = "结果："
        view.addSubview(resultLabel)
        
        let buttonTitles = ["设置", "修改", "查询", "删除"]
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
            btn.addTarget(self, action: #selector(snButtonClicked(_:)), for: .touchUpInside)
            view.addSubview(btn)
        }
    }
    
    private func handleResult(_ errorCode: VPJH76SNCodeErrorCode, action: String) {
        if errorCode == .success {
            resultLabel.text = "\(action)成功"
        } else {
            resultLabel.text = "\(action)失败：\(VPJH76SNCodeErrorDescription(errorCode))"
        }
    }
    
    @objc func snButtonClicked(_ sender: UIButton) {
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        switch sender.tag {
        case 0: // 设置
            peripheralManage?.veepooSDK_JH76SetSNCode(snTextField.text) { [weak self] errorCode in
                self?.handleResult(errorCode, action: "设置")
            }
        case 1: // 修改
            peripheralManage?.veepooSDK_JH76ModifySNCode(snTextField.text) { [weak self] errorCode in
                self?.handleResult(errorCode, action: "修改")
            }
        case 2: // 查询
            peripheralManage?.veepooSDK_JH76ReadSNCode { [weak self] isSet, string in
                self?.resultLabel.text = isSet ? "查询结果：\(string ?? "")" : "未设置SN码"
            }
        case 3: // 删除
            peripheralManage?.veepooSDK_JH76DeleteSNCode { [weak self] errorCode in
                self?.handleResult(errorCode, action: "删除")
            }
        default:
            break
        }
    }
}
