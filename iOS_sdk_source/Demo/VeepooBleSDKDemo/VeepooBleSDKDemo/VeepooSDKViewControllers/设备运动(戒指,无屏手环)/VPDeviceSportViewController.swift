//
//  VPDeviceSportViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/1/5.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPDeviceSportViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubView()
        bindViewModel()
        // Do any additional setup after loading the view.
    }
    
    private var readTimer: Timer?
    
    private var textView: UITextView?
    
    private func setupSubView() {
        title = "App开启设备运动(戒指,无屏手环)"
        view.backgroundColor = .white
        let screenWidth = UIScreen.main.bounds.width
        let leftPadding: CGFloat = 30
        let topPadding: CGFloat = 40
        textView = UITextView(frame: CGRect(x: leftPadding, y: topPadding, width: screenWidth - leftPadding*2, height: 150))
        textView?.isEditable = false
        textView?.layoutManager.allowsNonContiguousLayout = false
        view.addSubview(textView!)
        
        
        let titles = ["读取当前运动状态", "开始运动", "暂停运动", "继续运动" ,"停止运动", "读取所有运动数据"]
        
        let spacing: CGFloat = 20
        let buttonHeight: CGFloat = 50
        let availableWidth = screenWidth - (leftPadding * 2) - spacing
        let buttonWidth = availableWidth / 2

        for (index, title) in titles.enumerated() {
            let column = index % 2
            let row = index / 2
            
            let button = UIButton(type: .system)
            button.frame = CGRect(
                x: leftPadding + CGFloat(column) * (buttonWidth + spacing),
                y: CGRectGetMaxY(textView!.frame) + CGFloat(row) * (buttonHeight + spacing),
                width: buttonWidth,
                height: buttonHeight
            )
            
            button.backgroundColor = .orange
            button.setTitle(title, for: .normal)
            button.setTitleColor(.white, for: .normal)
            button.layer.cornerRadius = 8
            button.titleLabel?.font = .systemFont(ofSize: 14)
            button.tag = 1000 + index
            view.addSubview(button)
            button.addTarget(self, action: #selector(buttonAction(btn:)), for: .touchUpInside)
        }
        
    }
    
    @objc func buttonAction(btn: UIButton) {
        if btn.tag == 1000 {
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readDeviceSportState()
        } else if btn.tag == 1005 {
            readAllSportCrc()
        }else {
            let opCode = VPDeviceSportControlOpCode(rawValue: UInt(btn.tag - 1000))
            if opCode == .start {
                textView!.text = ""
                startReadTimer()
            } else if opCode == .stop {
                stopReadTimer()
            }
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_deviceSportControl(with: opCode!, type: .outdoorRun)
        }
    }
    
    
    private func readAllSportCrc() {
        textView?.text = ""
        VPBleCentralManage.sharedBleManager().peripheralManage.readDeviceSportCRCArr {[weak self] success, crcs in
            guard let self = self else { return }
            if crcs?.count != 0 {
                VPBleCentralManage.sharedBleManager().peripheralManage.readDeviceSport(withCRC: crcs) {[weak self] sportModels, sportGpsModels in
                    guard let sportModels = sportModels, let sportGpsModels = sportGpsModels, let self = self else { return }
                    print(sportModels)
                    print(sportGpsModels)
                    textView?.text = "有\(sportModels.count + sportGpsModels.count)条运动数据"
                }
            } else {
                textView?.text = "无运动数据"
            }
        }
    }
    
    private func startReadTimer() {
        stopReadTimer()
        readTimer = Timer.scheduledTimer(withTimeInterval: 2, repeats: true, block: { timer in
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readDeviceSportState()
        })
    }
    
    private func stopReadTimer() {
        readTimer?.invalidate()
        readTimer = nil
    }

    private func bindViewModel() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_deviceSportRunninStateSubscribe { state in
            print("veepooSDK_deviceSportRunninStateSubscribe:\(state)")
        }
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_deviceSportInfoSubscribe {[weak self] model in
            guard let self = self, let model = model else { return }
            var runState =  "未开始"
            if model.runState == .paused {
                runState =  "暂停"
            } else if model.runState == .running {
                runState =  "运动中"
            }
            let result = "运动状态:\(runState),时长:\(model.duration),距离:\(model.distance),心率:\(model.heartRate),卡路里:\(model.calories),配速:\(model.pace),速度:\(model.speed)"
            if textView!.text != "" {
                textView!.text = textView!.text + "\n" + result
            } else {
                textView!.text = result
            }
            
            textView!.scrollToBottom()
            print(result)
        }
    }
}
