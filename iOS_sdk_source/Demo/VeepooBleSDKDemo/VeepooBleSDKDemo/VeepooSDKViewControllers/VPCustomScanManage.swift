//
//  VPCustomScanManage.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/8/9.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

/*
 注意⚠️，自扫描连接的方式，需要自行实现重连机制，包括被系统配对的情况，也需要自行实现。
 因为 CBPeripheral
 */

class VPCustomScanManage: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate {
        
    static let sharedInstance = VPCustomScanManage()
    
    var centralManager: CBCentralManager?
    
    var mPeripheral: CBPeripheral!
    
    public func initDelegate() {
        centralManager = CBCentralManager.init(delegate: self, queue: nil)
    }
    
    public func startScanDevices() -> Void {
        let service1 = CBUUID(string: "FFFF")
        let service2 = CBUUID(string: "FEE7")
        let service3 = CBUUID(string: "0001")
        let service4 = CBUUID(string: "180D")

        let options = [CBCentralManagerScanOptionAllowDuplicatesKey: true]
        centralManager?.scanForPeripherals(withServices: [service1, service2, service3, service4], options: options)
//        retrieveConnected()
    }
    
    public func cancel() {
        if let mPeripheral = mPeripheral {
            centralManager?.cancelPeripheralConnection(mPeripheral)
        }
    }
    
    public func connectDevice(peripheral :CBPeripheral) {
        centralManager?.stopScan()
        mPeripheral = peripheral
        centralManager?.connect(mPeripheral)
    }
    
    /// 获取系统蓝牙中已配对的外部设备
    public func retrieveConnected() {
        let serverStr = "F0020001-0451-4000-B000-000000000000"
        let peripherals = centralManager?.retrieveConnectedPeripherals(withServices: [CBUUID(string: serverStr)])
        
        guard let peripherals = peripherals else {
            return
        }
        
        if peripherals.count < 1 {
            return
        }
        
        // 直接连接第一个
        let peripheral = peripherals.first!
        
        connectDevice(peripheral: peripheral)
    }
    
    /// 系统蓝牙状态监听
    /// - Parameter central: 中央管理器
    public func centralManagerDidUpdateState(_ central: CBCentralManager) {
        print(">>centralManagerDidUpdateState")
        VPBleCentralManage.sharedBleManager()?.veepooSDKUpdate(central.state)
    }
        
    /// 扫描到的外设
    /// - Parameters:
    ///   - central: 中央管理器
    ///   - peripheral: 外设对象
    ///   - advertisementData: 广播包数据
    ///   - RSSI: 信号量
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if RSSI.intValue < 0 && RSSI.intValue >= -75 {
            let name = advertisementData["kCBAdvDataLocalName"] as? String
            // 这里只是举例：扫到"W8"的设备就连接
            if let name = name {
                print(name)
                if name == "W8" {
                    print("2")
                    connectDevice(peripheral: peripheral)
                }
            }
        }
    }
    
    /// 外部设备被连接上后会被触发
    /// - Parameters:
    ///   - central: 中央管理器
    ///   - peripheral: 外部设备
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        print("didConnect")
        peripheral.delegate = self
        peripheral.discoverServices(nil)
    }
    
    /// 外部设备连接断开后会被触发
    /// - Parameters:
    ///   - central: 中央管理器
    ///   - peripheral: 外部设备
    ///   - error: 异常
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        print("didDisconnectPeripheral")
        VPBleCentralManage.sharedBleManager().veepooSDKDisconnectPeripheral(peripheral)
    }
        
    /// 外部设备的服务被发现
    /// - Parameters:
    ///   - peripheral: 外部设备对象
    ///   - error: 错误
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        guard let services = peripheral.services else {
            return
        }
        // 遍历每个服务下的特征
        for service in services {
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }
        
    /// 外部设备每个服务下的特征被发现
    /// - Parameters:
    ///   - peripheral: 外部设备对象
    ///   - service: 所属服务
    ///   - error: 错误
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        print("didDiscoverCharacteristicsFor")
        VPBleCentralManage.sharedBleManager().veepooSDKDiscoverCharacteristics(for: service, peripheral: peripheral)
    }
}
