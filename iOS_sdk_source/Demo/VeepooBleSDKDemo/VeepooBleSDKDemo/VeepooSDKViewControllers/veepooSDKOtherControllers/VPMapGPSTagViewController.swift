//
//  VPMapGPSTagViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2021/5/11.
//  Copyright © 2021 veepoo. All rights reserved.
//

import UIKit
import MapKit

class VPMapGPSTagViewController: UIViewController {

    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var tipLabel: UILabel!
    
    var coordinateChange = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "GPS显示"
        
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readDeviceRTGPSData(withState: true, result: { [weak self](state, model) in
            if state && model != nil {
                let latitude = Double(model!.latitude) / Double(100000)
                let longitude = Double(model!.longitude) / Double(100000)
                print(latitude, longitude, model!.altitude)
                let annotation = MKPointAnnotation()
                var coordinate = CLLocationCoordinate2D(latitude: latitude, longitude: longitude)
                if self?.coordinateChange == true {
                    coordinate = self?.changeCoordinate(coordinate: coordinate) ?? coordinate
                }
                annotation.coordinate = coordinate
                self?.mapView.addAnnotation(annotation)
            }
        })
        
        let item = UIBarButtonItem.init(title: "坐标转换", style: UIBarButtonItemStyle.plain, target: self, action: #selector(GPSChange))
        self.navigationItem.rightBarButtonItem = item
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        VPBleCentralManage.sharedBleManager()?.peripheralManage.veepooSDK_readDeviceRTGPSData(withState: false, result: nil)
    }
    
    @objc func GPSChange() -> Void {
        coordinateChange = !coordinateChange
        tipLabel.text = "转换坐标:  \(coordinateChange ? "是" : "否")"
    }
    
    func changeCoordinate(coordinate : CLLocationCoordinate2D) -> CLLocationCoordinate2D {
        return CLLocationCoordinate2DMake(0, 0)
    }
    
}

