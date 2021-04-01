//
//  VPFindDeviceViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/3/8.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPFindDeviceViewController: UIViewController {
    @IBOutlet weak var supportLabel: UILabel!
    @IBOutlet weak var rssiValueLabel: UILabel!
    @IBOutlet weak var searchDeviceBtn: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        // 1. 判断是否支持 手机查找手环功能
        let support = VPBleCentralManage.sharedBleManager()?.peripheralModel.searchDeviceFunction == 1
        print("是否支持: \(support)")
        supportLabel.text = support ? "支持" : "不支持"
        searchDeviceBtn.isEnabled = support
    }
    
    // 2. 已连接设备信号量监听 开启手环查找后，自行创建定时器循环读取设备的信号量
    // 信号量参考: [非常好，好，中，差] 可以自行划分等级
    // (-60,   ∞) 信号非常好
    // (-70, -60] 信号好
    // (-85, -70] 信号中
    // (-∞ , -85] 信号差
    @IBAction func readConnectedDeviceRSSIValue(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.veepooSDKReadConnectedPeripheralRSSIValue({ [weak self](rssiValue) in
            print("rssiValue: \(rssiValue)")
            self?.rssiValueLabel.text = "当前信号值:\(rssiValue)"
        })
    }
    
    // 3. 查找手环指令协议 设备未增加相关协议则无返回值
    @IBAction func startSearchDeviceClick(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_searchDeviceFuntion(withState: !sender.isSelected, result: { [weak self](start, state) in
            print("state: \(state.rawValue)")
            if state.rawValue == 2 || state.rawValue == 3 {//设备主动退出或查找超时
                self?.searchDeviceBtn.isSelected = false
            }
        })
        sender.isSelected = !sender.isSelected
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
