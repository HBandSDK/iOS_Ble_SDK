//
//  VPDeviceCountDownController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/15.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPDeviceCountDownController: UIViewController {

    @IBOutlet weak var currentCountDownLabel: UILabel!

    @IBOutlet weak var countDownBtn: UIButton!

    @IBOutlet weak var showSwitch: UISwitch!

    @IBOutlet weak var permanentTimeBackView: UIView!

    @IBOutlet weak var permanentSelectTimeBtn: UIButton!
    
    @IBOutlet weak var permanentTimeDetailLabel: UILabel!
    
    var countDownModel: VPDeviceCountDownModel = VPDeviceCountDownModel()
    
    var selectView:VPCountDownSelectView {
        let selectView = VPCountDownSelectView(frame: UIScreen.main.bounds)
        selectView.isHidden = true
        UIApplication.shared.keyWindow?.addSubview(selectView)
        unowned let weakSelf = self
        selectView.callBackBlock = {(value:Bool) -> Void in
            if value == true {
                weakSelf.readOrSettingCountDownWithCountDownModel(countDownModel: weakSelf.countDownModel, settingMode: 1)
            }
            selectView.isHidden = true
        }
        return selectView
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "倒计时设置"
        view.backgroundColor = UIColor.white
        //所有判断有无的这个里边，自己都可以做个封装，因开发者需求不同，我们就没对其封装效果不一定好
        if VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionDataTwo == nil {
            _ = AppDelegate.showHUD(message: "手环没有倒计时功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionDataTwo.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[1] != 1 {//先判断一下是否有这个功能
            _ = AppDelegate.showHUD(message: "手环没有倒计时功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        self.readOrSettingCountDownWithCountDownModel(countDownModel: countDownModel, settingMode: 2)
    }
    
    @IBAction func beginCountDownAction(_ sender: UIButton) {//开始或者取消当前设备正在进行的倒计时
        if sender.isSelected == true {//取消倒计时 SDK中支持取消，但是设备暂时不支持这个取消功能，做的时候让产品经理考虑一下如何设计，此功能呢暂时无用，SDK只是为了后期需求扩展先加进去了
            self.readOrSettingCountDownWithCountDownModel(countDownModel: countDownModel, settingMode: 0)
        }else {
            self.showSelectView(selectViewTitle: "倒计时时长")
        }
    }

    @IBAction func permanentSwitchAction(_ sender: UISwitch) {//常驻界面 显示或者隐藏
        if countDownModel.countDownState == 3 {
            _ = AppDelegate.showHUD(message: "设备正常进行倒计时", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        if sender.isOn == false {
            countDownModel.settingOperation = 0
            self.readOrSettingCountDownWithCountDownModel(countDownModel: countDownModel, settingMode: 1)
        }else {
            self.showSelectView(selectViewTitle: "常驻倒计时时长")
        }
        
    }
    
    @IBAction func selectPermanentTimeAction(_ sender: UIButton) {//选择常驻倒计时时长
        if countDownModel.countDownState == 3 {
            _ = AppDelegate.showHUD(message: "设备正常进行倒计时", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        self.showSelectView(selectViewTitle: "常驻倒计时时长")
    }

    func readOrSettingCountDownWithCountDownModel(countDownModel: VPDeviceCountDownModel, settingMode:UInt) {//设置、读取或者监听倒计时
        unowned let weakSelf = self;
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceCountDown(with: countDownModel, settingMode: settingMode, successResult: { (deviceCountDownModel) in
            var tip = "读取成功"
            if settingMode == 0 {
                tip = "取消成功"
            }else if settingMode == 1 {
                tip = "设置成功"
            }
            if deviceCountDownModel?.countDownState == 4 {
                tip = "倒计时结束"
            }
            if deviceCountDownModel?.countDownState != 3 {
                _ = AppDelegate.showHUD(message: tip, hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
            weakSelf.countDownModel = deviceCountDownModel!
            weakSelf.updateUIShow()
        }) {
            var tip = "读取失败"
            if settingMode == 0 {
                tip = "取消失败"
            }else if settingMode == 1 {
                tip = "设置失败"
            }
            _ = AppDelegate.showHUD(message: tip, hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }

    func updateUIShow() {//根据model改变界面显示
        currentCountDownLabel.text = String(countDownModel.currentCountDownTime)
        countDownBtn.isSelected = countDownModel.countDownState == 3
        showSwitch.isOn = countDownModel.isShow
        
        permanentTimeBackView.isHidden = !showSwitch.isOn
        
        permanentTimeDetailLabel.text = String(countDownModel.repeatTime)
    }

    func showSelectView(selectViewTitle: String)  {
        let selectView = VPCountDownSelectView(frame: UIScreen.main.bounds)
        selectView.selectViewTitle = selectViewTitle
        selectView.countDownModel = countDownModel
        UIApplication.shared.keyWindow?.addSubview(selectView)
        unowned let weakSelf = self
        selectView.callBackBlock = {(value:Bool) -> Void in
            if value == true {
                weakSelf.readOrSettingCountDownWithCountDownModel(countDownModel: weakSelf.countDownModel, settingMode: 1)
            }
            selectView.removeFromSuperview()
        }
    }

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
