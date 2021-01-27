//
//  VPLongSeatSettingController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/17.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPLongSeatSettingController: UIViewController {

    @IBOutlet weak var startHourLabel: UILabel!
    
    @IBOutlet weak var startMinuteLabel: UILabel!
    
    @IBOutlet weak var endHourLabel: UILabel!
    
    @IBOutlet weak var endMinuteLabel: UILabel!
    
    @IBOutlet weak var howLongRemindLabel: UILabel!
    
    @IBOutlet weak var stateLabel: UILabel!
    
    @IBOutlet weak var startHourSlider: UISlider!
    
    @IBOutlet weak var startMinuteSlider: UISlider!
    
    @IBOutlet weak var endHourSlider: UISlider!
    
    @IBOutlet weak var endMinuteSlider: UISlider!
    
    @IBOutlet weak var howLongRemindSlider: UISlider!
    
    @IBOutlet weak var stateSegControl: UISegmentedControl!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "久坐提醒设置"
        
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[3] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有久坐功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        //开始要先读取手环的，App上展示以手环为准,读取也要有个模型，模型只要有就可以，不能为nil
        let longSeatModel = VPDeviceLongSeatModel()
        //开始读取
        unowned let weakSelf = self;
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceLongSeat(with: longSeatModel, settingMode: 2, successResult: { (longSeatModel) in
            
            guard let readLongSeatModel = longSeatModel else {
                print("error")
                return
            }
            _ = AppDelegate.showHUD(message: "读取成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            weakSelf.startHourLabel.text = "起始小时:" + String(describing: readLongSeatModel.longSeatStartHour)
            
            weakSelf.startMinuteLabel.text = "起始分钟:" + String(describing: readLongSeatModel.longSeatStartMinute)
           
            weakSelf.endHourLabel.text = "结束小时:" + String(describing: readLongSeatModel.longSeatEndHour)
            
            weakSelf.endMinuteLabel.text = "结束分钟:" + String(describing: readLongSeatModel.longSeatEndMinute)
           
            weakSelf.howLongRemindLabel.text = "多久提醒:" + String(describing: readLongSeatModel.longSeatGateValue)
            
            weakSelf.stateLabel.text = readLongSeatModel.longSeatState == 0 ? "状态:关闭" : "状态:开启"
            
            weakSelf.startHourSlider.value = Float(readLongSeatModel.longSeatStartHour)
            
            weakSelf.startMinuteSlider.value = Float(readLongSeatModel.longSeatStartMinute)
            
            weakSelf.endHourSlider.value = Float(readLongSeatModel.longSeatEndHour)
            
            weakSelf.endMinuteSlider.value = Float(readLongSeatModel.longSeatEndMinute)
            
            weakSelf.howLongRemindSlider.value = Float(readLongSeatModel.longSeatGateValue) / 30
            
            weakSelf.stateSegControl.selectedSegmentIndex = Int(readLongSeatModel.longSeatState)
            
        }) {
            _ = AppDelegate.showHUD(message: "读取失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
        
        // Do any additional setup after loading the view.
    }

    @IBAction func sliderValueChangedAction(_ sender: UISlider) {
        let sliderValue = UInt16(sender.value)
        switch sender.tag {
        case 0:
            startHourLabel.text = "起始小时:" + String(sliderValue)
        case 1:
            startMinuteLabel.text = "起始分钟:" + String(sliderValue)
        case 2:
            endHourLabel.text = "结束小时:" + String(sliderValue)
        case 3:
            endMinuteLabel.text = "结束分钟:" + String(sliderValue)
        case 4:
            howLongRemindLabel.text = "多久提醒:" + String(sliderValue * 30)
        default:
            print("error")
        }
    }
    
    @IBAction func stateChangedAction(_ sender: UISegmentedControl) {
        stateLabel.text = stateSegControl.selectedSegmentIndex == 0 ? "状态:关闭" : "状态:开启"
    }
    
    @IBAction func startSettingLongseatAction(_ sender: UIButton) {
        //建立久坐模型
        let longSeatModel = VPDeviceLongSeatModel(longSeatStartHour: UInt(startHourSlider.value), longSeatStartMinute: UInt(startMinuteSlider.value), longSeatEndHour: UInt(endHourSlider.value), longSeatEndMinute: UInt(endMinuteSlider.value), longSeatGateValue: UInt(howLongRemindSlider.value) * 30, longSeatState: UInt(stateSegControl.selectedSegmentIndex))
        
        //开始设置
        unowned let weakSelf = self;
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceLongSeat(with: longSeatModel, settingMode: UInt(stateSegControl.selectedSegmentIndex), successResult: { (longSeatModel) in
            _ = AppDelegate.showHUD(message: "久坐设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }) {
            _ = AppDelegate.showHUD(message: "久坐设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }
}




