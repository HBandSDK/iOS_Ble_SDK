//
//  VPBodyCompositionViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/10/11.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPBodyCompositionViewController: UIViewController {
    private var support: Bool! = false
    private var supportL: UILabel!
    private var opButton: UIButton!
    private var readButton: UIButton!
        
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        subscribe()
    }
    
    @objc func opButtonAction(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKTestBodyCompositionStart(sender.isSelected) { lead, progress in
            if let progress = progress {
                print("lead = \(lead), progress = \(progress)")
            }
        } testResult: { [weak self]state, model in
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
        }
    }
    
    @objc func readButtonAction() {
        let tableID = VPBleCentralManage.sharedBleManager()?.peripheralModel.deviceAddress;
        var date = "2023-09-22"
        date = "2023-10-13"
        let arr = VPDataBaseOperation.veepooSDKGetDeviceOffStoreBodyComposition(withDate: date, andTableID: tableID)
        
        guard let arr = arr else {
            print("没有数据")
            return
        }
        if arr.isEmpty {
            print("没有数据")
            return
        }
        print(arr)
    }
}

// MARK: - setupSubViews
extension VPBodyCompositionViewController {
    private func setupSubViews() {
        title = "身体成分"
        view.backgroundColor = UIColor.white
        
        let type = VPBleCentralManage.sharedBleManager().peripheralModel.bodyCompositionType
        support = type != 0
        supportL = .init()
        supportL.text = "是否支持: " + (support ? "是" : "否")
        supportL.frame = CGRect(x: 30, y: 40, width: 120, height: 38)
        view.addSubview(supportL)
                
        opButton = .init(type: .system)
        opButton.setTitle("开始手动测试", for: .normal)
        opButton.setTitle("结束手动测试", for: .selected)
        opButton.frame = CGRect(x: 30, y: 100, width: 100, height: 38)
        opButton.addTarget(self, action: #selector(opButtonAction(_:)), for: .touchUpInside)
        view.addSubview(opButton)
        
        readButton = .init(type: .system)
        readButton.setTitle("读取数据", for: .normal)
        readButton.frame = CGRect(x: 150, y: 100, width: 80, height: 38)
        readButton.addTarget(self, action: #selector(readButtonAction), for: .touchUpInside)
        view.addSubview(readButton)
    }
}

extension VPBodyCompositionViewController {
    private func subscribe() {
        // 订阅设备端身体成分测量完成事件
        VPBleCentralManage.sharedBleManager().peripheralManage.deviceTestBodyCompositionDidFinishBlock = {[weak self] in
            // 这里调用读取全部日常数据即可
            self?.reReadAllData()
        }
    }
    
    private func reReadAllData() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSdkStartReadDeviceAllData {
            [weak self] (readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress) in
            if readDeviceBaseDataState == .complete {
                print("读取成功")
                self?.readButton.sendActions(for: .touchUpInside)
            }
        }
    }
}
