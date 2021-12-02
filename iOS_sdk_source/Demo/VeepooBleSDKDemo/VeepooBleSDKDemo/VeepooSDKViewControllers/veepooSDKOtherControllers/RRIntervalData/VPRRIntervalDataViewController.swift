//
//  VPRRIntervalDataViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/11/29.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPRRIntervalDataViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "RR逐跳数据"
    }

    @IBAction func readData(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readRRIntervalData(withDayNumber: 0, blockNumber: 379, result: { model, progress, error in
            if error == nil {
                print("model = \(model as Any), progress = \(progress as Any)")
            }
        })
    }
    
    @IBAction func readData1(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readRRIntervalData(withDayNumber: 1, blockNumber: 0xD0, result: { model, progress, error in
            if error == nil {
                print("model = \(model as Any), progress = \(progress as Any)")
            }
        })
    }
    
    @IBAction func readData2(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readRRIntervalData(withDayNumber: 2, blockNumber: 1, result: { model, progress, error in
            if error == nil {
                print("model = \(model as Any), progress = \(progress as Any)")
            }
        })
    }

}
