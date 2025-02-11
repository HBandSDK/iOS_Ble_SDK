//
//  VPCustomScanManage.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/8/9.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

/*
 注意⚠️，自扫描连接的方式，因为CBPeripheral底层机制原因，SDK内部需要再扫描一遍，故自扫描的连接会比SDK扫描要慢一些。
 */

class VPCustomScanManage: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate {
        
    static let sharedInstance = VPCustomScanManage()
    
    var centralManager: CBCentralManager?
    
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
    }
    
    public func connectFromSystem() -> Void {
        retrieveConnected()
    }
    
    public func disconnectDevice() -> Void {
        VPBleCentralManage.sharedBleManager().veepooSDKDisconnectDevice()
    }
    
    /// 蓝牙连接过程中的状态变化
    ///
    /// - Parameter connectState: 蓝牙过程中的状态
    func handleConnectEvent(connectState: DeviceConnectState) {
        switch connectState {
        case .BlePoweredOff://蓝牙没有打开
            print("手机蓝牙没有打开")
        case .BleConnecting://蓝牙连接中
            print("蓝牙连接中")
        case .BleConnectSuccess://蓝牙连接成功
            print("蓝牙连接成功")
        case .BleConnectFailed://蓝牙连接失败
            print("蓝牙连接失败")
        case .BleVerifyPasswordSuccess://验证密码成功,返回上一级
            print("验证密码成功")
        case .BleVerifyPasswordFailure://验证密码失败
            print("验证密码失败")
        case .BleConnectTimeout://连接超时
            print("连接超时")
        }
    }
    
    public func connectDevice(peripheral :CBPeripheral) {
        centralManager?.stopScan()
//        VPBleCentralManage.sharedBleManager().veepooSDKSelfScanConnectDevice(peripheral, deviceConnect: { [weak self](connectState) in
//            self?.handleConnectEvent(connectState: connectState)
//        })
        VPBleCentralManage.sharedBleManager().veepooSDKSelfScanConnectDevice(peripheral, deviceConnect: nil)
    }
    
    /// 系统蓝牙状态监听
    /// - Parameter central: 中央管理器
    public func centralManagerDidUpdateState(_ central: CBCentralManager) {
        print(">>centralManagerDidUpdateState")
    }
        
    /// 扫描到的外设
    /// - Parameters:
    ///   - central: 中央管理器
    ///   - peripheral: 外设对象
    ///   - advertisementData: 广播包数据
    ///   - RSSI: 信号量
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral,
                        advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if RSSI.intValue < 0 && RSSI.intValue >= -55 {
            let name = advertisementData["kCBAdvDataLocalName"] as? String
            // 这里只是举例：扫到"W8"的设备就连接
            if let name = name {
                print(name)
                if name == "itel ISW-42" {
                    print("2")
                    connectDevice(peripheral: peripheral)
                }
            }
        }
    }
}

extension VPCustomScanManage {
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
}
