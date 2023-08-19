//
//  VPTestDeviceSportViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/8/19.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPTestDeviceSportViewController: UIViewController {
    private var opButton: UIButton!
    private var readButton: UIButton!
        
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        VPBleCentralManage.sharedBleManager().peripheralManage.deviceSportDidFinishBlock = { [weak self]success in
            print("1 - success:\(success)")
            self?.readButton.sendActions(for: .touchUpInside)
            self?.opButton.isSelected = false
        }
    }
        
    @objc func operateDeviceSport(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        let settingType:Int32 = sender.isSelected ? 1 : 0
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceRunning(settingType, run: VPDeviceRuningMode.outdoorRun ) { type, success in
            print("2 - type:\(type), success:\(success)")
        }
    }
    
    @objc func readDeviceSportData() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKStartReadDeviceRunningData { [weak self]state, totalTimes, currentReadTimes, readCurrentTimesProgress in
            switch state {
            case .start:
                print(">> readDeviceSportData 开始")
            case .reading:
                print(">> readDeviceSportData 读取中")
            case .complete:
                print(">> readDeviceSportData 完成")
                self?.getDatas()
            case .invalid:
                print(">> readDeviceSportData 不支持")
            }
        }
    }
    
    private func getDatas() -> Void {
        let arr = VPDataBaseOperation.veepooSDKGetDeviceRunningData(withDate: 0.getOneDayDateString(), andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        guard let arr = arr else {
            print("没有数据")
            return
        }
        print(arr)
    }
}

// MARK: - setupSubViews
extension VPTestDeviceSportViewController {
    private func setupSubViews() {
        title = "手环运动"
        view.backgroundColor = UIColor.white
        opButton = .init(type: .system)
        opButton.setTitle("开始运动", for: .normal)
        opButton.setTitle("结束运动", for: .selected)
        opButton.frame = CGRect(x: 30, y: 100, width: 80, height: 38)
        opButton.addTarget(self, action: #selector(operateDeviceSport(_:)), for: .touchUpInside)
        view.addSubview(opButton)
        
        readButton = .init(type: .system)
        readButton.setTitle("读取数据", for: .normal)
        readButton.frame = CGRect(x: 130, y: 100, width: 80, height: 38)
        readButton.addTarget(self, action: #selector(readDeviceSportData), for: .touchUpInside)
        view.addSubview(readButton)
    }
}
