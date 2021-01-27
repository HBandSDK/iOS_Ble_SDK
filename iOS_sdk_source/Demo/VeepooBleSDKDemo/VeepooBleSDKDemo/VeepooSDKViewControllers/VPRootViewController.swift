//
//  VPRootViewController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/16.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

//动态获取命名空间(CFBundleExecutable这个键对应的值就是项目名称,也就是命名空间)
let nameSpace = Bundle.main.infoDictionary!["CFBundleExecutable"] as! String

class VPRootViewController: UIViewController {
    
    //先初始化VPBleCentralManage
    let veepooBleManager: VPBleCentralManage = VPBleCentralManage.sharedBleManager()
    
    /// 主界面下边按钮的子控制器
    let controllers = ["VPTestHeartController","VPTestBloodController","VPTestOxygenController","VPTestFatigueController","VPTestSleepController","VPTestStepController","VPMessageRemindViewController","VPBaseFunctionRemindController","VPDFUController" ,"VPOterFunctionSettingController","VPPTTTestController"
        ,"VPSOSViewController"]
    
    @IBOutlet weak var vpScanDeviceButton: UIButton!
    
    @IBOutlet weak var vpDisconnectDeviceButton: UIButton!
    
    @IBOutlet weak var vpDeviceNameLabel: UILabel!
    
    @IBOutlet weak var vpDeviceAddressLabel: UILabel!
    
    @IBOutlet weak var vpDeviceVersionLabel: UILabel!
    
    @IBOutlet weak var vpDeviceBatteryLevelLabel: UILabel!
    
    @IBOutlet weak var vpDeviceCurrentStepLabel: UILabel!
    
    
    /// demo的版本
    let AppVersion: String = Bundle.main.object(forInfoDictionaryKey: "CFBundleShortVersionString") as! String
    
    /// 获取实时计步的定时器
    var stepTimer: Timer!
    
    let curveView: VPOxygenAnalysisSectionFourView = VPAnalysisViewFactory.createSectionFourView()
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        curveView.showType = 0;
        curveView.update(withConnectState: true)
        curveView.frame = CGRect(x: 0, y: 150, width: Width, height: 100)
//        self.view.addSubview(curveView)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "VeepooBleSDK" + String(VeepooBleSDKVersion)//sdk的版本
        self.navigationController?.navigationBar.isTranslucent = false
        //设置导航栏上的UI
        self.setRootViewControllerNaviItemUI()
        
        //从2.0之后，要多加一步操作,下边两句任选其一，第一个是已经封装了SDK的，第二种是没有封装到数据库的，优点是自己对数据进行操作比较灵活
        VPBleCentralManage.sharedBleManager().isLogEnable = true
        VPBleCentralManage.sharedBleManager().peripheralManage = VPPeripheralManage.shareVPPeripheralManager()
//        VPBleCentralManage.sharedBleManager().peripheralManage = VPPeripheralAddManage.shareVPPeripheralManager()
//        VPBleCentralManage.sharedBleManager()?.automaticConnection = false
        
        unowned let weakSelf = self
        //监听手机系统蓝牙状态改变
        veepooBleManager.vpBleCentralManageChangeBlock = {(centralManagerState: VPCentralManagerState) -> Void
            in
            switch centralManagerState {
            case .poweredOff: //系统蓝牙关闭
                _ = AppDelegate.showHUD(message: "检测到系统蓝牙关闭", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .poweredOn://系统蓝牙打开
                _ = AppDelegate.showHUD(message: "检测到系统蓝牙打开", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .unknown://未知
                _ = AppDelegate.showHUD(message: "未检测到系统蓝牙状态", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            default:
                _ = AppDelegate.showHUD(message: "其他情况", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
        
        //监听设备连接状态改变
        veepooBleManager.vpBleConnectStateChangeBlock = {(deviceConnectState: VPDeviceConnectState) -> Void
            in
            switch deviceConnectState {
            case .connectStateDisConnect: //断开连接
                weakSelf.deviceDidDisConnect()
            case .connectStateConnect://连接成功
                _ = AppDelegate.showHUD(message: "连接成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .connectStateVerifyPasswordSuccess://验证密码成功
                _ = AppDelegate.showHUD(message: "验证密码成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
                weakSelf.deviceVerifyPasswordSuccessful()
            case .connectStateVerifyPasswordFailure://验证密码失败
                _ = AppDelegate.showHUD(message: "验证密码失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .discoverNewUpdateFirm://发现新固件
                //可以给出用户弹窗询问用户是否前去升级
                _ = AppDelegate.showHUD(message: "发现新固件", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
        VPPeripheralManage.shareVPPeripheralManager()?.receiveDeviceSOSCommand = {() -> Void in
            print("sos")
        }
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        startRealTimeStep()
        
        
//        let curveView = VPOxygenCurveView(vpOxygenCurveType: VPOxygenCurveTypeHypoxiaTime)
//        curveView?.frame = CGRect(x: 0, y: 100, width: Width, height: 200)
//        curveView?.oneDayOxygens = nil
//        self.view.addSubview(curveView ?? UIView())
//        let resultView = VPAnalysisViewFactory.createSectionTwoView();
//        resultView?.frame = CGRect(x: 0, y: 100, width: Width, height: 500)
//        view.addSubview(resultView!)
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        DestroyStepTimer()
    }
    
    /// 创建navi的item
    func setRootViewControllerNaviItemUI() {
        let rightNaviButton: UIButton = UIButton(type: .custom)
        rightNaviButton.frame = CGRect(x: 0, y: 0, width: 40, height: 38)
        rightNaviButton.setTitle("V" + AppVersion, for: .normal)
        rightNaviButton.setTitleColor(UIColor.black, for: .normal)
        navigationItem.rightBarButtonItem = UIBarButtonItem(customView: rightNaviButton)
        
        let textLabel = UILabel(frame: CGRect(x: 0, y: 0, width: 100, height: 100))
        textLabel.backgroundColor = UIColor.red
        textLabel.zc_x = 200
        textLabel.zc_y = 200
        textLabel.zc_width = 50
        textLabel.zc_height = 50
        textLabel.zc_centerX = 50
        textLabel.zc_centerY = 300
//        view.addSubview(textLabel)
        
    }

    
    /// 设备验证密码成功后的操作
    func deviceVerifyPasswordSuccessful() {//设备验证密码成功
        
        if VPBleCentralManage.sharedBleManager().vpBleDFUConnectStateChangeBlock != nil {//正在固件升级，自己也可以加判断条件
            return
        }
        //验证密码之后如果不是在DFU模式，第一步一定要先同步一下信息，最主要的是身高，同时App端修改个人信息后也一定要同步给设备，设置成功后在做其他事情，也可以向我这没写，因为一定会设置成功
        VPPeripheralManage.shareVPPeripheralManager().veepooSDKSynchronousPersonalInformation(withStature: 175, weight: 60, birth: 1995, sex: 0, targetStep: 10000) { (settingResult) in
            
        }
        _ = navigationController?.popViewController(animated: true)
        vpDisconnectDeviceButton.isEnabled = true
        vpDeviceNameLabel.text = "设备名称:" + veepooBleManager.peripheralModel.deviceName
        
        vpDeviceAddressLabel.text = "MAC地址:" + veepooBleManager.peripheralModel.deviceAddress
        
        vpDeviceVersionLabel.text = "固件版本:" + veepooBleManager.peripheralModel.deviceVersion + "-" + String(veepooBleManager.peripheralModel.deviceNumber)
        
        unowned let weakSelf = self
        veepooBleManager.peripheralManage.veepooSDKReadDeviceBatteryPower { (batteryLevel) in
            weakSelf.vpDeviceBatteryLevelLabel.text = "电池电压:" + String(batteryLevel)
        }
        
        if veepooBleManager.isDFULangMode == true {//如果处于DFULang模式则不再读取数据
            return
        }
        
        //获取实时计步
        startRealTimeStep()
        
        //密码验证后一般要读取基本数据（这个是所有设备必须读取的，每个设备都有的包含计步，睡眠、心率、血压的数据）、如果有运动数据读取运动数据，如果有血氧数据读取血氧数据，三者读取的时候不能同步进行，要一个读取完毕在读取其他的
        let hud: MBProgressHUD = AppDelegate.showHUDNoHide(message: "", hudModel: MBProgressHUDModeText, showView: view)
        return
            
        
        //验证密码成功后开始读取手环的数据（睡眠、计步、心率、血压等基本数据）
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSdkStartReadDeviceAllData {[weak self] (readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress) in
            switch readDeviceBaseDataState {
            case .start: //开始读取数据
                hud.show(true)
                hud.labelText = "开始读取"
            case .reading://正在读取数据
                let progressString: String = String(currentReadDayNumber) + "/" + String(totalDay) + "  " + String(readCurrentDayProgress) + "%"
                hud.labelText = progressString
            case .complete://读取数据完成
                hud.labelText = "读取完成"
                hud.hide(true, afterDelay: 1.0)
                self?.readOxygenData()
            default:
                break
            }
        }
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readSleepData(withDayNumber: 1) { (sleepArray) in
            guard  let sleepArray = sleepArray  else {
                return
            }
            print(sleepArray)
        }
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readBasicData(withDayNumber: 1, maxPackage: 1) { (heartArray, totalPackage, currentPackage) in
            guard  let heartArray = heartArray  else {
                return
            }
            print(heartArray)
        }
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_readDeviceRunningData(withBlockNumber: 0) { (deviceRunningDict, totalPackage, currentPackage) in
            if currentPackage >= totalPackage {
                print(deviceRunningDict ?? "没有运动数据")
            }else {
                print("totalPackage:\(totalPackage) currentPackage:\(currentPackage)")
            }
        }
    }
    
    /// 确认设备已经断开连接后的操作
    func deviceDidDisConnect() {//设备已经断开连接
        DestroyStepTimer()
        vpDisconnectDeviceButton.isEnabled = false
        vpDeviceNameLabel.text = "设备名称:"
        vpDeviceAddressLabel.text = "MAC地址:"
        vpDeviceVersionLabel.text = "固件版本:"
        vpDeviceBatteryLevelLabel.text = "电池电压:"
        vpDeviceCurrentStepLabel.text = "实时步数:"
        
        if VPBleCentralManage.sharedBleManager().vpBleDFUConnectStateChangeBlock == nil {//如果没有固件升级断开连接返回到主界面
            _ = AppDelegate.showHUD(message: "断开连接", hudModel: MBProgressHUDModeText, showView: UIApplication.shared.keyWindow!)
            _ = navigationController?.popToRootViewController(animated: true)
        }
    }
    
    /// 获取手环当前的计步数据，与设备的显示的计步数据同步
    @objc func startRealTimeStep() {
        if veepooBleManager.isConnected == false {
            return
        }
        if stepTimer == nil {
            stepTimer = Timer.scheduledTimer(timeInterval: 5.0, target: self, selector: #selector(self.startRealTimeStep), userInfo: nil, repeats: true)
        }
        unowned let weakSelf = self
        VPDataBaseOperation .veepooSDKGetStepData(withDate: 0.getOneDayDateString(), andTableID: veepooBleManager.peripheralModel.deviceAddress, changeUserStature: veepooBleManager.peripheralModel.deviceStature) { (stepDict) in
            
            guard  let deviceStepDict = stepDict  else {
                return
            }
            if deviceStepDict["Step"] != nil && deviceStepDict["Dis"] != nil && deviceStepDict["Cal"] != nil {
                weakSelf.vpDeviceCurrentStepLabel.text = "实时步数:" + (deviceStepDict["Step"] as! String) + "  " + (deviceStepDict["Dis"] as! String) + "km  " + (deviceStepDict["Cal"] as! String) + "kcal  "
            }
        }
    }
    
    
    /// 进入扫面界面
    ///
    /// - Parameter sender: ——
    @IBAction func enterScanDeviceController(_ sender: UIButton) {
        if veepooBleManager.isConnected == true {
            _ = AppDelegate.showHUD(message: "请先断开设备", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        let scanController = VPScanDeviceViewController()
        self.navigationController?.pushViewController(scanController, animated: true)
    }
    
    
    /// 断开设备连接
    ///
    /// - Parameter sender: ——
    @IBAction func disconnectDeviceAction(_ sender: UIButton) {
        veepooBleManager.veepooSDKDisconnectDevice()
    }
    
    
    /// 进去各项功能界面
    ///
    /// - Parameter sender: 通过sender的tag去判断应该进入哪个控制器
    @IBAction func enterDetailedFunctionViewControllerAction(_ sender: UIButton) {
//        let testController = VPOxygenDetailController.init()
//        testController.showType = 9;
//        self
//            .navigationController?.pushViewController(testController, animated: true)
        if veepooBleManager.isConnected == false {
            _ = AppDelegate.showHUD(message: "设备没有连接", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        let controllerName = controllers[sender.tag - 1]

        let controllerClass: AnyClass? = NSClassFromString(nameSpace + "." + controllerName)

        let controller = controllerClass as! UIViewController.Type
        self
            .navigationController?.pushViewController(controller.init(), animated: true)
        
        
    }

    /// 销毁定时器操作
    func DestroyStepTimer() {
        guard let stepTimer1 = stepTimer else {
            return
        }
        stepTimer1.invalidate()
        stepTimer = nil
    }
    
    func readOxygenData() {
       let hud: MBProgressHUD = AppDelegate.showHUDNoHide(message: "", hudModel: MBProgressHUDModeText, showView: view)
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSdkStartReadDeviceOxygenData {[weak self] (readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress) in
            switch readDeviceBaseDataState {
            case .start: //开始读取数据
                hud.show(true)
                hud.labelText = "开始读取血氧"
            case .reading://正在读取数据
                let progressString: String = String(currentReadDayNumber) + "/" + String(totalDay) + "  " + String(readCurrentDayProgress) + "%"
                hud.labelText = progressString
            case .complete://读取数据完成
                hud.labelText = "读取完成"
//                hud.hide(true, afterDelay: 1.0)
                self?.readHrvData()
            default:
                break
                }
            }
        }
    func readHrvData() {
        let hud: MBProgressHUD = AppDelegate.showHUDNoHide(message: "", hudModel: MBProgressHUDModeText, showView: view)
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSdkStartReadDeviceHrvData { (readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress) in
            switch readDeviceBaseDataState {
            case .start: //开始读取数据
                hud.show(true)
                hud.labelText = "开始读取HRV"
            case .reading://正在读取数据
                let progressString: String = String(currentReadDayNumber) + "/" + String(totalDay) + "  " + String(readCurrentDayProgress) + "%"
                hud.labelText = progressString
            case .complete://读取数据完成
                hud.labelText = "读取完成"
                hud.hide(true, afterDelay: 1.0)
            default:
                break
                }
            }
        }
}
