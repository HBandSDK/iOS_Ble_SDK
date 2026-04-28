//
//  VPQX17ViewController.swift
//  VeepooBleSDKDemo
//
//  Created by vp_app_01 on 2026/4/21.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPQX17ViewController: UIViewController {
    let QX17FileHandle = VPFileHandleManager()
    
    private var modeModifyBtn: UIButton?
    private var switchDataAcq: UISwitch?
    // 记录当前设备数据采集开启状态
    private var dataAcqState: VPQX17DataAcqState = .closed
    // 记录当前震动模式
    private var curVibrationMode: VPQX17VibrationMode = .start
    
    override func viewDidLoad() {
        super.viewDidLoad()
        configSource()
        setupSubViews()
        registDataAcquitionState()
        // 首次进入该功能，校验当前设备采集状态是否已开启，触发重传流程
        handleRetransData()
    }

    func configSource() {
        QX17FileHandle.configureFilePath("QX17DataAcquitions")
    }
    
    func setupSubViews() {
        view.backgroundColor = .white
        title = "QX17 功能"
        
        let label1 = UILabel(frame: CGRect(x: 20, y: 10, width: UIScreen.main.bounds.width-40, height: 50))
        label1.text = "点击按钮切换震动模式"
        label1.font = .systemFont(ofSize: 14)
        label1.numberOfLines = 0
        label1.textColor = .red
        view.addSubview(label1)
        
        modeModifyBtn = UIButton(frame: CGRect(x: 30, y: 60, width: 100, height: 40))
        modeModifyBtn!.backgroundColor = .blue
        modeModifyBtn!.addTarget(self, action: #selector(modifyVibrationModeClick(btn:)), for: .touchUpInside)
        view.addSubview(modeModifyBtn!)
        refreshVibrationModeShowName()
        
        let label2 = UILabel(frame: CGRect(x: 20, y: 140, width: UIScreen.main.bounds.width-40, height: 50))
        label2.text = "点击开关按钮，开启或关闭实时数据采集（IMU、GPS、心率）"
        label2.font = .systemFont(ofSize: 14)
        label2.numberOfLines = 0
        label2.textColor = .red
        view.addSubview(label2)
        
        switchDataAcq = UISwitch(frame: CGRect(x: 30, y: 200, width: 0, height: 0))
        view.addSubview(switchDataAcq!)
        switchDataAcq!.addTarget(self, action: #selector(switchSyncAction), for: .valueChanged)
        
        let shareBtn = UIButton(frame: CGRect(x: 20, y: 260, width: 160, height: 50));
        shareBtn.setTitle("导出数据", for: .normal)
        shareBtn.backgroundColor = .blue
        shareBtn.layer.cornerRadius = 4
        view.addSubview(shareBtn)
        shareBtn.addTarget(self, action: #selector(shareAction), for: .touchUpInside)
        
    }
}


/// 数据采集结果监听相关 API
extension VPQX17ViewController {
    
    func registDataAcquisitionCallback() {
        // 监听 IMU 实时数据通知
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17IMUResultSubscribe { [weak self] imuDatas in
            guard let self = self else { return }
            guard let imuResults = imuDatas else {
                return
            }
            print("QX17 IMU 实时数据回调结果:\(imuResults.count)")
            self.writeIMU(datas: imuResults)
        }
        
        // 监听 GPS 实时数据通知
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17GPSResultSubscribe { [weak self] gpsDatas in
            guard let self = self else { return }
            guard let gpsResults = gpsDatas else {
                return
            }
            print("QX17 GPS 实时数据回调结果:\(gpsResults.count)")
            self.writeGPS(datas: gpsResults)
        }
        
        // 监听心率实时数据通知
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17HeartRateResultSubscribe { [weak self] heartRateDatas in
            guard let self = self else { return }
            guard let hRateResults = heartRateDatas else {
                return
            }
            print("QX17 心率实时数据回调结果:\(hRateResults.count)")
            self.writeHeartRate(datas: hRateResults)
        }
        
    }
    
    func registDataAcquitionState() {
        // 监听设备数据采集开启状态修改通知
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17DataAcquitionStateSubscribe { [weak self] dataAcquitionState in
            guard let self = self else { return }
            self.dataAcqState = dataAcquitionState
            if dataAcquitionState == .opening {
                print("QX17 更新监听到的，设备数据采集开关状态，已开启")
                self.switchDataAcq?.isOn = true
            } else {
                print("QX17 更新监听到的，设备数据采集开关状态，已关闭")
                self.switchDataAcq?.isOn = false
            }
        }
    }
    
}

/// 数据采集相关 API
extension VPQX17ViewController {
    // 开启数据采集
    func handleStartDataAcq() {
        print("QX17 上层调用开始数据采集接口")
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17StartDataAcquisition { [weak self] result in
            guard let self = self else { return }
            let isSucc = result == .setResultSucc
            print("QX17 数据采集开启结果:\(isSucc)")
            if isSucc {
                print("QX17 监听数据采集结果")
                self.registDataAcquisitionCallback()
            }
        }
    }
    
    // 关闭数据采集
    func handleStopDataAcq() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17StopDataAcquisition { result in
            let isSucc = result == .setResultSucc
            print("QX17 数据采集关闭结果:\(isSucc)")
        }
    }
    
    // 继续数据采集
    func handleContinueDataAcq() {
        print("QX17 开始触发继续采集数据")
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17ContinueDataAcquisition { [weak self] result in
            guard let self = self else { return }
            let isSucc = result == .setResultSucc
            print("QX17 继续采集数据结果:\(isSucc)")
            if isSucc {
                print("QX17 重新监听数据采集结果")
                self.registDataAcquisitionCallback()
            }
        }
    }
    
}

/// 振动马达控制相关 API
extension VPQX17ViewController {
    // 修改振动马达模式
    func handleModifyVibrationMode(mode: VPQX17VibrationMode, duration: Int = 0) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QX17SetVibrationMode(mode, duration: duration) { [weak self] resultCode in
            guard let self = self else { return }
            print("QX17 修改震动等模式 resultCode:\(resultCode.rawValue)")
            if resultCode == .succ {
                // 更新震动模式
                self.updateVibrationMode()
            }
        }
    }

}

/// 数据采集数据写入文件
extension VPQX17ViewController {
    func writeIMU(datas: [VPQX17IMUModel]) {
        QX17FileHandle.writeText("------------------------ IMU ------------------------")
        for model in datas {
            let time = model.timestamp
            QX17FileHandle.writeText("数据时间:\(time)")
            let ax = model.accelerometer.ax
            let ay = model.accelerometer.ay
            let az = model.accelerometer.az
            let axStr = "加速度计 ax:\(ax) "
            let ayStr = "加速度计 ay:\(ay) "
            let azStr = "加速度计 az:\(az) \n"
            QX17FileHandle.writeText(axStr)
            QX17FileHandle.writeText(ayStr)
            QX17FileHandle.writeText(azStr)
            
            
            let gx = model.gyroscope.gx
            let gy = model.gyroscope.gy
            let gz = model.gyroscope.gz
            let gxStr = "陀螺仪 gx:\(gx) "
            let gyStr = "陀螺仪 gy:\(gy) "
            let gzStr = "陀螺仪 gz:\(gz) \n"
            QX17FileHandle.writeText(gxStr)
            QX17FileHandle.writeText(gyStr)
            QX17FileHandle.writeText(gzStr)
            
            
            let mx = model.magnetometer.mx
            let my = model.magnetometer.my
            let mz = model.magnetometer.mz
            let mxStr = "磁力计 mx:\(mx) "
            let myStr = "磁力计 my:\(my) "
            let mzStr = "磁力计 mz:\(mz) \n"
            QX17FileHandle.writeText(mxStr)
            QX17FileHandle.writeText(myStr)
            QX17FileHandle.writeText(mzStr)
        }
    }
    
    func writeGPS(datas: [VPQX17GPSModel]) {
        QX17FileHandle.writeText("------------------------ GPS ------------------------")
        for model in datas {
            let time = model.timestamp
            QX17FileHandle.writeText("数据时间:\(time)")
            let latitude = model.latitude
            let longitude = model.longitude
            let accuracy = model.accuracy
            let latitudeStr = "纬度:\(latitude) "
            let longitudeStr = "经度:\(longitude) "
            let accuracyStr = "定位精度:\(accuracy) \n"
            QX17FileHandle.writeText(latitudeStr)
            QX17FileHandle.writeText(longitudeStr)
            QX17FileHandle.writeText(accuracyStr)
        }
    }
    
    func writeHeartRate(datas: [VPQX17HeartRateModel]) {
        QX17FileHandle.writeText("------------------------ 心率 ------------------------")
        for model in datas {
            let time = model.timestamp
            QX17FileHandle.writeText("数据时间:\(time)")
            let heartRate = model.heartRate
            let heartRateStr = "心率值:\(heartRate) \n\n"
            QX17FileHandle.writeText(heartRateStr)
        }
    }
    
}

/// 数据采集控制 UI 交互
extension VPQX17ViewController {
    @objc func switchSyncAction() {
        if switchDataAcq!.isOn {
            handleStartDataAcq()
        } else {
            handleStopDataAcq()
        }
    }
    
    func handleRetransData() {
        // 校验设备是否在传输中（IMU、GPS、心率）
        if dataAcqState == .opening {
            // 可以触发继续采集
            handleContinueDataAcq()
        } else{
            print("QX17 上层调用继续采集，设备当前数据采集已关闭，无需继续")
        }
    }
}

/// 振动马达控制 UI 交互
extension VPQX17ViewController {
    @objc func modifyVibrationModeClick(btn: UIButton) {
        handleModifyVibrationMode(mode: curVibrationMode, duration: 0)
    }
    
    func updateVibrationMode() {
        if .error == curVibrationMode {
            curVibrationMode = .start
        } else {
            let nextModeValue = curVibrationMode.rawValue + 1
            if let nextMode = VPQX17VibrationMode(rawValue: nextModeValue) {
                curVibrationMode = nextMode
            }
        }
        refreshVibrationModeShowName()
    }
    
    func refreshVibrationModeShowName() {
        let showTitle = getCurrentModeShowName()
        modeModifyBtn?.setTitle(showTitle, for: .normal)
        modeModifyBtn?.setTitle(showTitle, for: .highlighted)
    }
    
    func getCurrentModeShowName() -> String {
        switch curVibrationMode {
        case .start:
            return "开始"
        case .end:
            return "结束"
        case .notify:
            return "通知"
        case .reminder:
            return "提醒"
        case .ensure:
            return "确认"
        case .beat:
            return "节拍"
        case .connected:
            return "已连接"
        case .error:
            return "错误"
            
        default:
            return ""
        }
    }
}

// 导出数据
extension VPQX17ViewController {
    @objc func shareAction(){
        let array = QX17FileHandle.getFilesWithDetails()
        let cachesURL = FileManager.default.urls(for: .cachesDirectory, in: .userDomainMask).first!

        // 创建归档文件路径
        let archiveURL = cachesURL.appendingPathComponent("QX17实时采集数据.zip")
        let newUrl = QX17FileHandle.getZipFile(archiveURL, andFilePath: array)
        DispatchQueue.main.async {
            let activityViewController = UIActivityViewController(activityItems: [newUrl], applicationActivities: nil)
            activityViewController.excludedActivityTypes = [.addToReadingList, .assignToContact]
          
            if let popoverController = activityViewController.popoverPresentationController {
                popoverController.sourceView = self.view
                popoverController.sourceRect = CGRect(x: self.view.bounds.midX, y: self.view.bounds.midY, width: 0, height: 0)
                popoverController.permittedArrowDirections = []
            }

            // 弹出分享视图
            self.present(activityViewController, animated: true) {
                print("完成")
            }
        }
    }
}
