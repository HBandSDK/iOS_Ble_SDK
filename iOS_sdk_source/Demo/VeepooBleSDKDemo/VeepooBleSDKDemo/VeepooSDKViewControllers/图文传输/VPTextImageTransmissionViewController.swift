//
//  VPTextImageTransmissionViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/10/23.
//  Copyright © 2025 veepoo. All rights reserved.
//

import UIKit

class VPTextImageTransmissionViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        creatMainView()
        title = "图文传输"
        checkSupportImageSize()
        // Do any additional setup after loading the view.
    }
    
    let textField: UITextField = {
        let textField = UITextField(frame: CGRect(x: 30, y: 30, width: UIScreen.main.bounds.size.width - 60, height: 50))
        textField.placeholder = "输入文本"
        textField.borderStyle = .roundedRect
        return textField
    }()
    
    let progressLabel: UILabel = {
        let label = UILabel()
        return label
    }()
    
    let segControl: UISegmentedControl = {
        let seg = UISegmentedControl(items: ["图片1","图片2"])
        seg.selectedSegmentIndex = 0
        return seg
    }()
    
    var selectImage :String = "test_390_450_1"
    
    var hud: MBProgressHUD?
    
    func creatMainView(){
        
        view.backgroundColor = .white;
        view.addSubview(self.textField);
        let textBtn = UIButton(frame: CGRect(x: CGRectGetMinX(self.textField.frame), y: CGRectGetMaxY(self.textField.frame) + 20, width: CGRectGetWidth(self.textField.frame), height: CGRectGetHeight(self.textField.frame)))
        textBtn.layer.cornerRadius = 4
        textBtn.backgroundColor = .orange
        textBtn.setTitle("文本传输", for: .normal)
        textBtn.addTarget(self, action: #selector(textTransmissionAction), for: .touchUpInside)
        view.addSubview(textBtn)
        
        
        
        self.segControl.frame = CGRect(x: CGRectGetMinX(self.textField.frame), y: CGRectGetMaxY(textBtn.frame) + 20, width: 120, height: 50)
        segControl.addTarget(self, action: #selector(selectImageAction), for: .valueChanged)
        view.addSubview(self.segControl)
        
        self.progressLabel.frame = CGRect(x: CGRectGetMaxX(self.segControl.frame)+20, y: CGRectGetMinY(self.segControl.frame), width: 200, height: 50)
        view.addSubview(self.progressLabel)
        
        let imageBtn = UIButton(frame: CGRect(x: CGRectGetMinX(self.textField.frame), y: CGRectGetMaxY(self.progressLabel.frame) + 20, width: CGRectGetWidth(self.textField.frame), height: CGRectGetHeight(self.textField.frame)))
        imageBtn.layer.cornerRadius = 4
        imageBtn.backgroundColor = .orange
        imageBtn.setTitle("图片传输", for: .normal)
        imageBtn.addTarget(self, action: #selector(imageTransmissionAction), for: .touchUpInside)
        view.addSubview(imageBtn)
        
        self.hud=AppDelegate.showHUDNoHide(message: "", hudModel: MBProgressHUDModeText, showView: self.view)
    }

    func checkSupportImageSize(){
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSendCheckDeviceSupportImageInfoAndResult { model in
            print("可传输的图片的最大长度:" + String(model.dataLength) + "可传输的图片的宽:" + String(model.width) + "可传输的图片的高:" + String(model.height))
        }
    }
    
    
    @objc func textTransmissionAction(){
        self.textField.resignFirstResponder()
        guard let text = self.textField.text,text != "" else { return }
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSendStartTransmissionMessage(text) {[weak self] error in
            guard let weakSelf = self else {return}
            weakSelf.hud?.show(true)
            if let error = error as? NSError {
                if let str = error.userInfo["NSLocalizedDescription"] as? String{
                    weakSelf.hud?.labelText = str
                }
            }else{
                weakSelf.hud?.labelText = "Success"
            }
            weakSelf.hud?.hide(true, afterDelay: 1.0)
        }
    }
    
    @objc func selectImageAction(){
        self.selectImage = self.segControl.selectedSegmentIndex == 0 ? "test_390_450_1" : "test_390_450"
    }
    
    @objc func imageTransmissionAction(){
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSendStartTransmissionImage(UIImage(named: self.selectImage)) { error in
            guard let er = error as? NSError else {return}
            print(er)
        } andProgress: { [weak self] progress in
            guard let weakself = self else { return }
            DispatchQueue.main.async {
                weakself.progressLabel.text = "传输进度:" + String(format: "%.0f", progress*100) + "%"
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
