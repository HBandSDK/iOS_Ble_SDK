//
//  VPSyncPersonalInformationController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/17.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPSyncPersonalInformationController: UIViewController {

    @IBOutlet weak var statureLabel: UILabel!
    
    @IBOutlet weak var weightLabel: UILabel!
    
    @IBOutlet weak var birthLabel: UILabel!
    
    @IBOutlet weak var sexLabel: UILabel!
    
    @IBOutlet weak var stepTargetLabel: UILabel!
    
    @IBOutlet weak var statureSlider: UISlider!
    
    @IBOutlet weak var weightSlider: UISlider!
    
    @IBOutlet weak var sexSegControl: UISegmentedControl!
    
    @IBOutlet weak var birthSlider: UISlider!
    
    @IBOutlet weak var stepTargetSlider: UISlider!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //同步个人信息，一般是在手环连接或者个人资料信息该表的时候同步，现在没有读取功能，只要设置成功就可以了，这个资料一般都是以App个人资料为准，所以只有设置，根据下边的设置自己可以参考
        title = "同步个人资料"
    }

    @IBAction func sliderAction(_ sender: UISlider) {
        let changeValue = UInt16(sender.value)
        switch sender.tag {
        case 0:
            statureLabel.text = "身高:" + String(changeValue)
        case 1:
            weightLabel.text = "体重:" + String(changeValue)
        case 2:
            birthLabel.text = "出生:" + String(changeValue)
        case 3:
            stepTargetLabel.text = "目标:" + String(changeValue)
        default:
            print("error")
        }
    }

    
    @IBAction func sexSegControlAction(_ sender: UISegmentedControl) {
        sexLabel.text = sender.selectedSegmentIndex == 0 ? "性别:女" : "性别:男"
    }
    
    @IBAction func startSyncAction(_ sender: UIButton) {//开始同步个人数据
        unowned let weakSelf = self
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSynchronousPersonalInformation(withStature: UInt(statureSlider.value), weight: UInt(weightSlider.value), birth: UInt(birthSlider.value), sex: UInt(sexSegControl.selectedSegmentIndex), targetStep: UInt(stepTargetSlider.value)) { (syncState) in
            if syncState == 1 {
                _ = AppDelegate.showHUD(message: "设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }else {
                _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
    }
}






