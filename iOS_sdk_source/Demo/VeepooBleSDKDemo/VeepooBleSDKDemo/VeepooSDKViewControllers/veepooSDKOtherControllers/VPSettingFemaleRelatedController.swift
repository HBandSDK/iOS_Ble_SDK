//
//  VPSettingFemaleRelatedController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/6/13.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPSettingFemaleRelatedController: UIViewController , UITableViewDelegate , UITableViewDataSource {

    let cellID = "FemaleCell"

    var femaleRelatedTableView: UITableView?
    
    var femaleModel = VPDeviceFemaleModel()
    
    var femaleTitleArray = Array<String>()
    var femaleDetailArray = Array<String>()
    
    var selectView:VPFemaleSelectView {
        let selectView = VPFemaleSelectView(frame: UIScreen.main.bounds)
        selectView.isHidden = true
        UIApplication.shared.keyWindow?.addSubview(selectView)
        unowned let weakSelf = self
        selectView.callBackBlock = {(value:Bool) -> Void in
            if value == true {
                weakSelf.femaleRelatedTableView?.reloadData()
            }
            selectView.isHidden = true
        }
        return selectView
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor.white
        title = "女性项目设置"
        // Do any additional setup after loading the view.
        var tbyte:[UInt8] = Array(repeating: 0x00, count: 20)
        VPBleCentralManage.sharedBleManager().peripheralModel.deviceFuctionData.copyBytes(to: &tbyte, count: tbyte.count)
        if tbyte[12] == 0 {//先判断一下是否有这个功能,1是App端只是所有语言，2是App端只是支持中英文，这个是产品设计问题，手环上没有区别，原因是手环上只做了中文和英文
            _ = AppDelegate.showHUD(message: "手环没有女性功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        self.setFemaleRelateControllerUI()
        //开始要先读取手环的，App上展示以手环为准,读取也要有个模型，模型只要有就可以，不能为nil
        let femaleModel = VPDeviceFemaleModel()
        //开始读取
        unowned let weakSelf = self;
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceFemale(with: femaleModel, settingMode: 2, successResult: { (deviceFemaleModel) in
            guard let deviceFemaleModel = deviceFemaleModel else {
                return
            }
            weakSelf.femaleModel = deviceFemaleModel
            weakSelf.femaleRelatedTableView?.reloadData()
            _ = AppDelegate.showHUD(message: "读取成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }) {
            _ = AppDelegate.showHUD(message: "读取失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }

    func setFemaleRelateControllerUI() {
        femaleRelatedTableView = UITableView(frame: view.bounds , style: .plain)
        femaleRelatedTableView?.dataSource = self
        femaleRelatedTableView?.delegate = self
        
        let footView = UIView(frame: CGRect(x: 0, y: 0, width: view.bounds.size.width, height: 60))
        let footBtn = UIButton(type: .custom)
        footBtn.frame = CGRect(x: 15, y: 7, width: footView.frame.size.width - 30, height: footView.frame.size.height - 14)
        footBtn.addTarget(self, action: #selector(startSettingFemaleAction), for: .touchUpInside)
        footBtn.backgroundColor = UIColor.lightGray
        footBtn.setTitle("设置", for: .normal)
        footBtn.setTitleColor(UIColor.brown, for: .normal)
        footView.addSubview(footBtn)
        femaleRelatedTableView?.tableFooterView = footView
        view.addSubview(femaleRelatedTableView!)
    }

    @objc func startSettingFemaleAction() {
        unowned let weakSelf = self;
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceFemale(with: femaleModel, settingMode: 1, successResult: { (deviceFemaleModel) in
            guard let deviceFemaleModel = deviceFemaleModel else {
                return
            }
            weakSelf.femaleModel = deviceFemaleModel
            _ = AppDelegate.showHUD(message: "设置成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }) {
            _ = AppDelegate.showHUD(message: "设置失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
        }
    }

    func obtainUIShowMessage() -> Int {
        if self.femaleModel.femaleState == VPDeviceFemaleState(rawValue:0) {//没有生理期
            self.femaleTitleArray = ["生理期选择"]
            self.femaleDetailArray = ["暂无"]
            return 1
        }else if self.femaleModel.femaleState == VPDeviceFemaleState(rawValue:1) || self.femaleModel.femaleState == VPDeviceFemaleState(rawValue:2) {//经期或者备孕期
            self.femaleTitleArray = ["生理期选择","最后经期日期","经期周期","经期正常持续天数"]
            self.femaleDetailArray = [self.femaleModel.femaleState == VPDeviceFemaleState(rawValue:1) ? "经期" : "备孕期",self.femaleModel.lastMenstrualDate ?? "",String(self.femaleModel.menstrualCircle),String(self.femaleModel.menstrualDays)]
            return 4
        }else if self.femaleModel.femaleState == VPDeviceFemaleState(rawValue:3) {//预产期，换孕期
            self.femaleTitleArray = ["生理期选择","预产期"]
            self.femaleDetailArray = ["预产",self.femaleModel.expectedDateOfChildbirth ?? ""]
            return 2
        }else if self.femaleModel.femaleState == VPDeviceFemaleState(rawValue:4) {//预产期，换孕期
            self.femaleTitleArray = ["生理期选择","最后经期日期","经期周期","经期正常持续天数","宝宝生日","宝宝性别"]
            self.femaleDetailArray = ["宝妈",self.femaleModel.lastMenstrualDate ?? "",String(self.femaleModel.menstrualCircle),String(self.femaleModel.menstrualDays),self.femaleModel.babyBirthday ?? "",self.femaleModel.isGirl ? "女" : "男"]
            return 6
        }
        self.femaleTitleArray = ["生理期选择"]
        self.femaleDetailArray = ["暂无"]
        return 1
    }

    //MARK: tableView的代理方法
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.obtainUIShowMessage()
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: cellID)
        if cell == nil {
            cell = UITableViewCell(style: .value1, reuseIdentifier: cellID)
        }
        
        cell?.accessoryType = .disclosureIndicator
        
        cell?.textLabel?.text = self.femaleTitleArray[indexPath.row]
        
        cell?.detailTextLabel?.text = self.femaleDetailArray[indexPath.row]
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let selectView = VPFemaleSelectView(frame: UIScreen.main.bounds)
        selectView.selectViewTitle = self.femaleTitleArray[indexPath.row]
        selectView.femaleModel = femaleModel
        UIApplication.shared.keyWindow?.addSubview(selectView)
        unowned let weakSelf = self
        selectView.callBackBlock = {(value:Bool) -> Void in
            if value == true {
                weakSelf.femaleRelatedTableView?.reloadData()
            }
            selectView.removeFromSuperview()
        }
    }
    
    //MARK: 销毁控制器前执行
    deinit {
        VPBleCentralManage.sharedBleManager().veepooSDKStopScanDevice()
    }
}
