//
//  VPHealthLightVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/6/30.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPHealthLightVC: UIViewController {

    private var isSupTest: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.healthLightType != 0
    }
    
    private var stateLab: UILabel!
    
    private var setBtn: UIButton!
    
    private var readBtn: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }
    
    private var statusType: VPHealthLightStatusType = .off;

}

extension VPHealthLightVC {
    private func setupSubViews() {
        
        view.backgroundColor = .white
        title = "健康灯"
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupTest ? "是" : "否")
        
        if !self.isSupTest {
            return
        }
        
        stateLab = .init(frame: CGRect(x: 30, y: suplab.frame.maxY + 10, width: 220, height: 50))
        view.addSubview(stateLab)
        stateLab.text = "健康灯状态:"
        
        setBtn = .init(frame: CGRect(x: 30, y: stateLab.frame.maxY + 10, width: 120, height: 40))
        setBtn.titleLabel?.font = .systemFont(ofSize: 14)
        setBtn.setTitle("设置健康灯状态", for: .normal)
        view.addSubview(setBtn)
        setBtn.backgroundColor = .systemBlue
        setBtn.layer.cornerRadius = 4
        setBtn.layer.masksToBounds = true
        setBtn.addTarget(self, action: #selector(setAction), for: .touchUpInside)
        
        readBtn = .init(frame: CGRect(x: setBtn.frame.maxX + 20, y: setBtn.frame.minY, width: setBtn.frame.width, height: 40))
        readBtn.titleLabel?.font = .systemFont(ofSize: 14)
        readBtn.setTitle("读取健康灯状态", for: .normal)
        view.addSubview(readBtn)
        readBtn.backgroundColor = .systemOrange
        readBtn.layer.cornerRadius = 4
        readBtn.layer.masksToBounds = true
        readBtn.addTarget(self, action: #selector(readAction), for: .touchUpInside)
        readAction()
        listenChange()
    }
    
    @objc func setAction() {
        let val = self.statusType.rawValue + 1
        if val > VPHealthLightStatusType.stayOn.rawValue {
            self.statusType = VPHealthLightStatusType.off
        } else {
            self.statusType = VPHealthLightStatusType(rawValue: val) ?? .off
        }
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSetHealthLightStatus(self.statusType) {[weak self] state, type in
            guard let self = self else { return }
            if state {
                self.statusType = type
                self.stateLab.text = self.getHealthLightState()
            }
        }
    }
    
    private func listenChange() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKListenHealthLightStatus {[weak self] type in
            guard let self = self else { return }
            self.statusType = type
            self.stateLab.text = self.getHealthLightState()
        }
    }
    
    
    @objc func readAction() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKReadHealthLightStatus {[weak self] type in
            guard let self = self else { return }
            self.statusType = type
            self.stateLab.text = self.getHealthLightState()
        }
    }
    
    private func getHealthLightState() -> String {
        let text = "健康灯状态:"
        var stateText = ""
        switch statusType {
        case .off: stateText = "关闭"
        case .slowFlash: stateText = "慢闪"
        case .stayOn: stateText = "常亮"
        case .continuousFlashing: stateText = "连续闪"
        }
        return text + stateText
    }
}
