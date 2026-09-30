//
//  VPQH15SecurityProtectionViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/1/7.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit
import CoreLocation

class VPQH15SecurityProtectionViewController: UIViewController, CLLocationManagerDelegate {

    override func viewDidLoad() {
        super.viewDidLoad()
        bindViewModel()
        setupSubViews()
        if isSupSP {
            requestLocationAuthorization()
        }
    }
    
    var isSupSP: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.securityProtection != 0 ? true : false
    }
    
    private var stateSwitch: UISwitch?
    
    private var locationLabel: UILabel?
    
    private var locationManager: CLLocationManager?
    
    private var reqRssiRaw: Int = 0
    
    private func setupSubViews() {
        
        view.backgroundColor = .white
        title = "QH15安全守护"
        
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupSP ? "是" : "否")
        
        if isSupSP {
            let label = UILabel(frame: CGRect(x: 30, y: 90, width: 100, height: 40))
            label.text = "安全守护"
            view.addSubview(label)
            
            stateSwitch = UISwitch(frame: CGRect(x: 150, y: 90, width: 0, height: 0))
            view.addSubview(stateSwitch!)
            stateSwitch?.addTarget(self, action: #selector(setProtectionAction(sw:)), for: .touchUpInside)
            
            locationLabel = UILabel(frame: CGRect(x: 30, y: 150, width: CGRectGetWidth(view.frame) - 60, height: 60))
            view.addSubview(locationLabel!)
            locationLabel?.numberOfLines = 0
            locationLabel?.text = "位置信息"
        }
        
    }
    
    @objc func setProtectionAction(sw: UISwitch) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SetProtectionOpen(sw.isOn) { ack in
            if ack == .success {
                print("成功")
            }
        }
    }
    
    private func bindViewModel() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15ProtectionResultSubscribe {[weak self] open, time in
            print(open, time)
            guard let weakSelf = self else { return }
            weakSelf.stateSwitch?.isOn = open
            
        }
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SecurityProtectionLocationResultSubscribe {[weak self] (type, model) in
            guard let weakSelf = self, let model = model else { return }
            if type == .req {
                weakSelf.reqRssiRaw = Int(model.rssi)
                let status = CLLocationManager.authorizationStatus()
                if status == .authorizedAlways || status == .authorizedWhenInUse {
                    weakSelf.locationManager?.requestLocation()
                } else {
                    let sendModel = VPQH15SecurityProtectionModel()
                    sendModel.rssi = Int32(weakSelf.reqRssiRaw)
                    sendModel.gnssState = VPQH15SecurityProtectionState(rawValue: 0x04)!
                    VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SendSecurityProtectionLocation(sendModel)
                }
            } else {
                weakSelf.locationLabel?.text = "位置信息: latitude(\(model.location.latitude)) longitude(\(model.location.longitude))"
            }
        }
    }

    private func requestLocationAuthorization() {
        let manager = CLLocationManager()
        manager.delegate = self
        manager.desiredAccuracy = kCLLocationAccuracyBest
        self.locationManager = manager
        manager.requestWhenInUseAuthorization()
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        guard let loc = locations.last else { return }
        var stateRaw: UInt8 = 0x01
        if loc.horizontalAccuracy < 0 {
            stateRaw = 0x02
        } else if loc.horizontalAccuracy > 30 {
            stateRaw = 0x03
        }
        let model = VPQH15SecurityProtectionModel()
        model.rssi = Int32(reqRssiRaw)
        model.gnssState = VPQH15SecurityProtectionState(rawValue: stateRaw)!
        model.location = CLLocationCoordinate2D(latitude: round(loc.coordinate.latitude * 100000) / 100000.0,
                                                longitude: round(loc.coordinate.longitude * 100000) / 100000.0)
        model.alt = Int32(Int(loc.altitude))
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SendSecurityProtectionLocation(model)
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        var stateRaw: UInt8 = 0x02
        if let clErr = error as? CLError, clErr.code == .denied {
            stateRaw = 0x04
        }
        let model = VPQH15SecurityProtectionModel()
        model.rssi = Int32(reqRssiRaw)
        model.gnssState = VPQH15SecurityProtectionState(rawValue: stateRaw)!
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_QH15SendSecurityProtectionLocation(model)
    }

}
