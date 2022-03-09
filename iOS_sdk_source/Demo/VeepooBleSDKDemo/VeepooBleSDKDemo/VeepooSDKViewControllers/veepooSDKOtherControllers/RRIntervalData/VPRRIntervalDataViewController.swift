//
//  VPRRIntervalDataViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/11/29.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit

class VPRRIntervalDataViewController: UIViewController {

    var allModels:[VPRRIntervalDataModel] = []
    
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
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readRRIntervalData(withDayNumber: sender.tag, blockNumber: startPackage, result: { [self] model, progress, error in
            if error == nil {
                guard let model = model else {
                    return
                }
                self.printData(model: model as Any, progress: progress!)
                allModels.append(model as! VPRRIntervalDataModel)
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
        var valueStr = ""
        let bytes = [UInt8](model.dataStream)
        var validationCount = 0
        for i in 0..<bytes.count {
            let value = Int(bytes[i])
            var heartValue = 0
            if value != 0 {
//                heartValue = value
                heartValue = 60000/Int(value*20)
            }
            if i == bytes.count - 1 {
                valueStr.append("\(heartValue)\n\n")
            }else{
                valueStr.append("\(heartValue)|")
            }
            if value >= 12 && value <= 120 {
                validationCount += 1
            }
        }
        let str = "时间:\(model.date) \(model.time), 块:\(model.blockNumber), 读取进度:\(progress.localizedDescription!)), 有效数据:\(validationCount)个, 数据:\(valueStr)"
        self.bucketControl(str, finish: progress.isFinished)
//        print(str)
    }
    
    var strs: String = ""
    var strsCount:NSInteger = 0
    
    // 防止太快更新UI
    private func bucketControl(_ str: String, finish: Bool){
        strs.append(str)
        strsCount += 1
        if finish {
            self.updateTextView(strs)
        } else {
            if strsCount > 10 {
                self.updateTextView(strs)
            }
        }
    }
    
    private func updateTextView(_ str: String){
        self.textView.text.append(str)
        strs = ""
        strsCount = 0
        self.textView.scrollRangeToVisible(NSMakeRange(self.textView.text.count, 1))
    }
    
}
