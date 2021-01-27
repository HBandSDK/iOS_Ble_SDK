//
//  VPScanDeviceViewController.swift
//  VeepooBleSDKDemo
//
//  Created by 张冲 on 17/2/16.
//  Copyright © 2017年 zc.All rights reserved.
//

import UIKit

class VPScanDeviceViewController: UIViewController , UITableViewDelegate , UITableViewDataSource {

    let cellID = "scanCell"
    
    var scanTableView: UITableView?
    
    /// 保存设备的可变数据
    var deviceArray: Array<VPPeripheralModel> = [VPPeripheralModel]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "扫描设备"
        view.backgroundColor = UIColor.white
        setScanDeviceViewControllerUI()
        
        unowned let weakSelf: VPScanDeviceViewController = self
        //开始扫描设备，并接收扫描到的设备
        VPBleCentralManage.sharedBleManager().veepooSDKStartScanDeviceAndReceiveScanningDevice { (peripheralModel) in
            weakSelf.addPeripheralToDeviceArray(peripheralModel: peripheralModel!)
        }
        
        // Do any additional setup after loading the view.
    }

    func setScanDeviceViewControllerUI() {
        scanTableView = UITableView(frame: view.bounds, style: .plain)
        scanTableView?.delegate = self
        scanTableView?.dataSource = self;
        view.addSubview(scanTableView!)
    }
    
    /// 判断获取的设备在数组内是否存在，如果不存在则插入，并按照信号进行排序
    ///
    /// - Parameter peripheralModel: 设备的模型
    func addPeripheralToDeviceArray(peripheralModel: VPPeripheralModel) {
        var isExist = false
        for i in (0..<deviceArray.count) {
            let p = deviceArray[i]
            if p.deviceAddress == peripheralModel.deviceAddress {
                isExist = true
                break
            }
        }
        if isExist == false {
            deviceArray.append(peripheralModel)
            //按照信号进行排序
            deviceArray = deviceArray.sorted(by: { (p1, p2) -> Bool in
                return p1.rssi.intValue > p2.rssi.intValue
            })
            
            scanTableView?.reloadData()
        }
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
        }
    }
    
    //MARK: tableView的代理方法
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return deviceArray.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: cellID)
        if cell == nil {
            cell = UITableViewCell(style: .value1, reuseIdentifier: cellID)
        }
        let p = deviceArray[indexPath.row]
        cell?.textLabel?.text = p.deviceName
        
        cell?.detailTextLabel?.text = p.deviceAddress
        
        guard let rssi = p.rssi else {
            return cell!
        }
        
        cell?.detailTextLabel?.text = p.deviceAddress + "/" + String(describing: rssi)
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let p = deviceArray[indexPath.row]
        
        unowned let weakSelf: VPScanDeviceViewController = self
        //连接设备
        VPBleCentralManage.sharedBleManager().veepooSDKConnectDevice(p) { (connectState) in
            weakSelf.handleConnectEvent(connectState: connectState)
        }
    }
    
    //MARK: 销毁控制器前执行
    deinit {
        VPBleCentralManage.sharedBleManager().veepooSDKStopScanDevice()
    }

}
