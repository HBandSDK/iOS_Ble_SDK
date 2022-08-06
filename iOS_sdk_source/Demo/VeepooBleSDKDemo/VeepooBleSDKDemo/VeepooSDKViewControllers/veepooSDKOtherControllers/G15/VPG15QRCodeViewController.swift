//
//  VPG15QRCodeViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2022/2/14.
//  Copyright © 2022 veepoo. All rights reserved.
//

import UIKit

class VPG15QRCodeViewController: UIViewController {

    @IBOutlet weak var typeSegment: UISegmentedControl!
    @IBOutlet weak var contentTextField: UITextField!
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var groupIdTextField: UITextField!
    @IBOutlet weak var numberTextField: UITextField!
    @IBOutlet weak var textView: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "G15二维码"
    }

    @IBAction func buttonAction(_ sender: Any) {
        if !contentTextField.hasText {
            _ = AppDelegate.showHUD(message: "请输入二维码内容", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        if !nameTextField.hasText {
            _ = AppDelegate.showHUD(message: "请输入二维码姓名", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        if !groupIdTextField.hasText {
            _ = AppDelegate.showHUD(message: "请输入二维码组别", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        if !numberTextField.hasText {
            _ = AppDelegate.showHUD(message: "请输入二维码编号", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        
        let contentData = contentTextField.text!.data(using: .utf8)
        let nameData = nameTextField.text!.data(using: .utf8)
        let groupIdData = groupIdTextField.text!.data(using: .utf8)
        let numberData = numberTextField.text!.data(using: .utf8)
        
        if contentData == nil || contentData!.count > 50 {
            _ = AppDelegate.showHUD(message: "二维码内容不能大于50个字节", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        if nameData == nil || nameData!.count > 30 {
            _ = AppDelegate.showHUD(message: "二维码姓名不能大于30个字节", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        if groupIdData == nil || groupIdData!.count > 30 {
            _ = AppDelegate.showHUD(message: "二维码组别不能大于30个字节", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        if numberData == nil || numberData!.count > 30 {
            _ = AppDelegate.showHUD(message: "二维码编号不能大于30个字节", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        
        let model = VPG15QRCodeInfoModel()
        model.qrcodeType = VPG15QRCodeType.init(rawValue: UInt(typeSegment.selectedSegmentIndex))!
        model.content = contentTextField.text!
        model.name = nameTextField.text!
        model.groupId = groupIdTextField.text!
        model.number = numberTextField.text!
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_G15QRCodeInfo(with: model) { [weak self](success, error) in
            _ = AppDelegate.showHUD(message: success ? "设置成功" : "设置失败", hudModel: MBProgressHUDModeText, showView: (self?.view)!)
        }
    }
    
    @IBAction func ecgValueCallBack(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            self.textView.text = ""
            VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_G15ECGValueMonitor { [weak self](ecgValue, dateStr) in
                self?.updateTextView("时间：\(dateStr ?? "x")，值:\(ecgValue) \n")
            } ecgDataResult: { ecgDatas in
                print(ecgDatas as Any)
            }
        }
    }
    
    private func updateTextView(_ str: String){
        self.textView.text.append(str)
        self.textView.scrollRangeToVisible(NSMakeRange(self.textView.text.count, 1))
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        view.endEditing(true)
    }

}
