//
//  VPRRIntervalDataViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/11/29.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPRRIntervalDataViewController: UIViewController {

    @IBOutlet weak var startPackageTextField: UITextField!
    @IBOutlet weak var textView: UITextView!
    var startPackage:Int = 1
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "RR逐跳数据"
    }

    @IBAction func readData(_ sender: UIButton) {
        startPackage = Int(startPackageTextField.text!) ?? 1
        if startPackage < 1 {
            return
        }
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readRRIntervalData(withDayNumber: 0, blockNumber: startPackage, result: { model, progress, error in
            if error == nil {
                self.printData(model: model as Any, progress: progress!)
            }
        })
    }
    
    @IBAction func readData1(_ sender: UIButton) {
        startPackage = Int(startPackageTextField.text!) ?? 1
        if startPackage < 1 {
            return
        }
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readRRIntervalData(withDayNumber: 1, blockNumber: startPackage, result: { model, progress, error in
            if error == nil {
                self.printData(model: model as Any, progress: progress!)
            }
        })
    }
    
    @IBAction func readData2(_ sender: UIButton) {
        startPackage = Int(startPackageTextField.text!) ?? 1
        if startPackage < 1 {
            return
        }
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readRRIntervalData(withDayNumber: 2, blockNumber: startPackage, result: { model, progress, error in
            if error == nil {
                self.printData(model: model as Any, progress: progress!)
            }
        })
    }
    @IBAction func clearBtn(_ sender: UIButton) {
        self.textView.text = ""
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        view.endEditing(true)
    }
    
    func printData(model:Any, progress: Progress) -> Void {
        let model = model as! VPRRIntervalDataModel
        let progress = progress as Progress
        let str = "块:\(model.blockNumber),长度:\(model.dataStream),读取进度:\(progress.localizedDescription!))"
        self.printText(str)
        print(str)
    }
    
    private func printText(_ str: String){
        self.textView.text.append(str)
        self.textView.insertText("\n")
        self.textView.scrollRangeToVisible(NSMakeRange(self.textView.text.count, 1))
    }
    
}
