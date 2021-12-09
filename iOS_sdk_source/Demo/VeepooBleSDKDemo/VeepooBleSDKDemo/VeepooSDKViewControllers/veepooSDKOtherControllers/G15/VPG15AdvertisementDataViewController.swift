//
//  VPG15AdvertisementDataViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/9/16.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit
import CoreBluetooth

class VPG15AdvertisementDataViewController: UIViewController {

    var centralManager : CBCentralManager?
    
    let service1 = CBUUID(string: "FFFF")
    let service2 = CBUUID(string: "FEE7")
    let service3 = CBUUID(string: "0001")
    let service4 = CBUUID(string: "180D")
    
    @IBOutlet weak var filterDeviceNameTextField: UITextField!
    @IBOutlet weak var logTextView: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "赛米加广播包测试"
        centralManager = CBCentralManager.init(delegate: self, queue: nil)
    }

    @IBAction func startScanBtn(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            let options = [CBCentralManagerScanOptionAllowDuplicatesKey: true]
            centralManager?.scanForPeripherals(withServices: [service1, service2, service3, service4], options: options)
        }else{
            centralManager?.stopScan()
        }
        
    }
    @IBAction func clearTextView(_ sender: UIButton) {
        self.logTextView.text = "";
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        view.endEditing(true)
    }
    
    private func printText(_ str: String){
        self.logTextView.text.append(str)
        self.logTextView.insertText("\n")
//        self.logTextView.scrollRangeToVisible(NSMakeRange(self.logTextView.text.count, 1))
    }

}


extension VPG15AdvertisementDataViewController: CBCentralManagerDelegate {
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        switch central.state {
        case .poweredOn:
            break
        default:
            break
        }
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        let name = advertisementData["kCBAdvDataLocalName"] as? String
//        print(advertisementData)
        let addressData: NSData? = (advertisementData["kCBAdvDataManufacturerData"]) as? NSData
        if filterDeviceNameTextField.text?.lowercased() == name?.lowercased() {
            print("设备名:\((name ?? "nil")) 广播包内容: \(addressData as Any)")
            // 解析广播包内容，并log出来
            if addressData!.length >= 0x12 {
                var header:UInt16 = 0
                let nameText = "设备名: \((name ?? "nil"))\n"
                let macText = "MAC地址: \(getMacText(data: addressData))\n"
                
                addressData!.getBytes(&header, range: NSRange(location: 8, length: 1))
                let adTag = "广播内容标志: \(header)\n"
                
                addressData!.getBytes(&header, range: NSRange(location: 9, length: 1))
                let spo2 = "血氧: \(header)\n"
                
                addressData!.getBytes(&header, range: NSRange(location: 10, length: 1))
                let ecgHeart = "心率ECG: \(header)\n"
                
                addressData!.getBytes(&header, range: NSRange(location: 11, length: 1))
                let heart = "脉率: \(header)\n"
                
                addressData!.getBytes(&header, range: NSRange(location: 12, length: 2))
                let step = "步数: \(header)\n"
                
                addressData!.getBytes(&header, range: NSRange(location: 14, length: 2))
                let sleep = "睡眠时长: \(header) 分钟\n"
                
                addressData!.getBytes(&header, range: NSRange(location: 16, length: 2))
                let temp = "目标体温: \(header) (10倍)\n"
                
                self.printText("\(nameText)\(macText)\(adTag)\(spo2)\(ecgHeart)\(heart)\(step)\(sleep)\(temp)")
            }
        }
    }
    
    private func getMacText(data: NSData?) -> String {
        var mac: String? = ""//初始化mac地址 默认为空
        var byteArray:[UInt8] = [UInt8]()
        let startIndex:Int = 2
        for i in (startIndex...(startIndex+5)).reversed() {
            var temp:UInt8 = 0
            data!.getBytes(&temp, range: NSRange(location: i,length:1))
            byteArray.append(temp)
            var tempSp: String = ""
            if temp > 15 {
                tempSp = String(temp,radix:16)
            }else{//小于15转换成16进制为1位，所以补个零
                tempSp = "0" + String(temp,radix:16)
            }
            if i == startIndex {
                mac = mac! + tempSp
            }else {
                mac = mac! + tempSp + ":"
            }
        }
        mac = mac?.uppercased()
        return mac ?? "nil"
    }
    
}

extension VPG15AdvertisementDataViewController: CBPeripheralDelegate {
    
}
