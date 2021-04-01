//
//  VPMarketDialViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/1/27.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPMarketDialViewController: UIViewController {
    
    @IBOutlet weak var dialTypeLabel: UILabel!
    @IBOutlet weak var readDeviceScreenButton: UIButton!
    @IBOutlet weak var textView: UITextView!
    
    var supportMarketDialFunction = false
    
    var dialModel: VPDialModel!
    
    var deviceMarketDialModel: VPDeviceMarketDialModel!
    var marketDialArray: [VPServerMarketDialModel] = []
    
    var filePath: URL!
    
    var marketDialManager: VPMarketDialManager!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "市场表盘"
        
        // 照片表盘标志位
        supportMarketDialFunction = (VPBleCentralManage.sharedBleManager()?.peripheralModel.marketDialCount)! > 0
        if !supportMarketDialFunction {
            _ = AppDelegate.showHUD(message: "不支持市场表盘功能", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        
        self.readDeviceScreenButton.sendActions(for: .touchUpInside)
//        dialModel = VPBleCentralManage.sharedBleManager()?.peripheralModel.dialModel
//
//        print(dialModel as VPDialModel)
        
        marketDialManager = VPMarketDialManager.share()
    }
    // MARK: - 设备屏幕读取与切换
    
    // 读取设备当前显示的表盘
    // settingMode: 1代表设置，2代表读取
    // dialType: 0 默认表盘 1 市场表盘 2 照片表盘
    // screenStyle 市场表盘/照片表盘从1开始，默认表盘的从0开始
    @IBAction func readDeviceScreenStyleClick(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingDeviceScreenStyle(0, settingMode: 2, dialType: .market, result: { [weak self](dialType, screenStyle, settingSuccess) in
//            print("读取>> screenStyle: \(screenStyle), settingSuccess:\(settingSuccess)")
            self?.dialTypeLabel.text = "\(dialType.rawValue) - \(screenStyle)"
        })
    }

    @IBAction func setDeviceScreenStyleToMarketClick(_ sender: UIButton) {
        let support = self.supportMarketDialFunction
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDKSettingDeviceScreenStyle(1, settingMode: 1, dialType: .market, result: { [weak self](dialType, screenStyle, settingSuccess) in
//            print("设置>> screenStyle: \(screenStyle), settingSuccess:\(settingSuccess)")
            if !settingSuccess && support {
                // 设备支持市场表盘, 但未传输过表盘 先传输一次市场表盘中的表盘
                _ = AppDelegate.showHUD(message: "设备支持市场表盘, 但未传输过表盘", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
            }else{
                self?.readDeviceScreenButton.sendActions(for: .touchUpInside)
            }
        })
    }
    
    // MARK: - 市场表盘信息读取、UI数据传输
    
    @IBAction func readDeviceMarketDialInfoClick(_ sender: UIButton) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_dialChannel(with: .read, dialType: .market, photoDialModel: nil, result: { [weak self](photoDialModel, deviceMarketDialModel, error) in
            if error == nil {
                self?.deviceMarketDialModel = deviceMarketDialModel!
            }
        }, transformProgress: nil)
    }
    
    // 获取服务器关于本设备的所有市场表盘模型对象 fileUrl 为要传输给设备的UI文件，previewUrl 为预览图
    @IBAction func getServerMarketDialsClick(_ sender: UIButton) {
        if deviceMarketDialModel == nil {
            _ = AppDelegate.showHUD(message: "请先获取设备市场表盘信息", hudModel: MBProgressHUDModeText, showView: view)
            return
        }

        marketDialManager.getVeepooServerAllMarketDials(withDeviceInfo: deviceMarketDialModel) { [weak self](marketDialArray) in
            guard  let marketDialArray = marketDialArray  else {
                return
            }
            self?.marketDialArray = marketDialArray
            if marketDialArray.count > 0 {
                var str = ""
                for item in marketDialArray {
                    str = str.appending("\(item.fileUrl) \n")
                }
                self?.textView.text = str
            }
        } failure: { (error, code) in
            
        }
    }
    
    // 下载选择的模型中UI传输文件 download file
    @IBAction func downloadTransferBinFileClick(_ sender: UIButton) {
        if marketDialArray.count == 0 {
            _ = AppDelegate.showHUD(message: "请先获取服务器市场表盘", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        // 测试 第一个 验证效果请自行拿 marketDialArray.first.previewUrl 查看预览图
        marketDialManager.downloadMarketDialBinFile(with: marketDialArray.first!, deviceMarketDialModel: deviceMarketDialModel) { [weak self](filePath) in
            self?.filePath = filePath!
            print("下载成功!")
        } failure: { (error, code) in
            
        }
    }
    
    // 传输下载成功的 bin 文件到设备中
    @IBAction func transferMarketDialToDeviceClick(_ sender: UIButton) {
        if filePath == nil {
           _ = AppDelegate.showHUD(message: "请先下载表盘文件", hudModel: MBProgressHUDModeText, showView: view)
            return
        }
        marketDialManager.startTransfer(withFilePath: filePath) { (progress) in
            print("进度: \(progress * 100) %")
        } failure: { (error) in
            if error != nil{
                print(error! as NSError)
            }
        }

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
