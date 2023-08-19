//
//  VPDFUController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/23.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPDFUController: UIViewController {

    @IBOutlet weak var dfuProgressLabel: UILabel!
    
    @IBOutlet weak var currentVersionLabel: UILabel!
    
    @IBOutlet weak var updateVersionLabel: UILabel!
    
    @IBOutlet weak var updateDesTextView: UITextView!
    
    
    
    //要声明一个全局属性，固件升级过程中请不要操作手机
    let dfuOperationManager: VPDFUOperation = VPDFUOperation.dfuOperationShare()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "固件升级"
        // Do any additional setup after loading the view.
        currentVersionLabel.text = "当前版本: " + VPBleCentralManage.sharedBleManager().peripheralModel.deviceVersion
        
        reloadData()
    }
    
    func reloadData() -> Void {
        if (VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion == nil) {
            updateVersionLabel.text = "升级版本: " + "没有新版本"
        }else {
            //下边是升级版本和升级新固件描述
            updateVersionLabel.text = "升级版本: " + VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion
            updateDesTextView.text = VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersionDes.replacingOccurrences(of: "$", with: "\n")
        }
    }
    
    @IBAction func checkNetDeviceVersion(_ sender: UIButton) {
        
        /// 注意⚠️，生产环境 debug 参数请勿传 true
        dfuOperationManager.checkDeviceOTAInfo(withDebug: true) { progress in
            guard let progress = progress else {
                return
            }
            print("OTA固件下载中>>> \(progress.completedUnitCount)----\(progress.totalUnitCount)")
        } completionHandler: { [weak self]newVersion, describe, error in
            // 请求成功
            guard let error = error else {
                if let newVersion = newVersion {
                    print("升级版本:\(newVersion)")
                    self?.reloadData()
                } else {
                    print("没有新固件")
                }
                return
            }
            
            // 请求失败
            print(error)
        }
    }
    
    @IBAction func startDFUAction(_ sender: UIButton) {
        if sender.isSelected {
            return
        }
        if (VPBleCentralManage.sharedBleManager().peripheralModel.deviceNetVersion == nil) {
            dfuProgressLabel.text = "没有新固件，暂时不用升级"
            return
        }
        
        dfuProgressLabel.text = "准备升级"
        sender.isSelected = true
        unowned let weakSelf = self
        dfuOperationManager.veepooSDKStartDfu { (dfuProgress, deviceDFUState) in
            switch deviceDFUState {
            case .fileNotExist:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级文件不存在，不能升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .start:
                _ = AppDelegate.showHUD(message: "开始升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .updating:
                weakSelf.dfuProgressLabel.text = "升级进度: " + String(format: "%.2f", dfuProgress) + "%"
            case .success:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .failure:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .prepared:
                _ = AppDelegate.showHUD(message: "校验文件完成(K)", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .reboot:
                _ = AppDelegate.showHUD(message: "设备即将重启(K)", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
    }
    
    @IBAction func localTest(_ sender: UIButton) {
        if sender.isSelected {
            return
        }
        dfuProgressLabel.text = "准备升级"
        sender.isSelected = true
        unowned let weakSelf = self
        let fileName = "KH31_9638_00310433_OTA_UI_23-0303.zip"
        var filePath = Bundle.main.path(forResource: fileName, ofType: nil)
        if (filePath == nil) {
            return
        }
        // 拷贝到沙盒中，并返回路径
        filePath = copyToSandbox(bundlePath: filePath!)
        
        dfuOperationManager.veepooSDKStartDfu(withFilePath: filePath) { (dfuProgress, deviceDFUState) in
            switch deviceDFUState {
            case .fileNotExist:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级文件不存在，不能升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .start:
                _ = AppDelegate.showHUD(message: "开始升级", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .updating:
                weakSelf.dfuProgressLabel.text = "升级进度: " + String(format: "%.2f", dfuProgress) + "%"
            case .success:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级成功", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .failure:
                sender.isSelected = false
                _ = AppDelegate.showHUD(message: "升级失败", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .prepared:
                _ = AppDelegate.showHUD(message: "校验文件完成(K)", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            case .reboot:
                _ = AppDelegate.showHUD(message: "设备即将重启(K)", hudModel: MBProgressHUDModeText, showView: weakSelf.view)
            }
        }
    }
    
    func copyToSandbox(bundlePath:String) -> String {
        let bundleURL = URL(string: bundlePath)
        let fileName = bundleURL?.lastPathComponent
        let document = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first
        let destURL = document!.appendingPathComponent(fileName!, isDirectory: false)
        let fileManager = FileManager.default
        do {
            if fileManager.fileExists(atPath: destURL.path) {
                try fileManager.removeItem(at: destURL)
            }
            try fileManager.copyItem(atPath: bundlePath, toPath: destURL.path)
        } catch let error as NSError {
            print("Error : \(error.localizedDescription)")
        }
        return destURL.path
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
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
