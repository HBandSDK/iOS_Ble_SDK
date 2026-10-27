//
//  VPWearVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/10/27.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPWearVC: UIViewController {

    private var isSupTest: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupportWearSet
    }
    
    private var segControl: UISegmentedControl?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        // Do any additional setup after loading the view.
    }

}

extension VPWearVC {
    private func setupSubViews() {
        view.backgroundColor = .white
        title = "佩戴方式"
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupTest ? "是" : "否")
        
        if !self.isSupTest {
            return
        }
        
    
        let label = UILabel(frame: CGRect(x: 30, y: 90, width: 80, height: 40))
        label.text = "佩戴方式"
        view.addSubview(label)
        
        segControl = .init(items: ["左手","右手"])
        segControl?.frame = CGRect(x: 120, y: 90, width: 120, height: 40)
        view.addSubview(segControl!)
        segControl?.addTarget(self, action: #selector(setWearState), for: .valueChanged)
        
        readWearState()
    }
    
    private func readWearState() {
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.veepooSDK_readWearConfig { [weak self] type in
            if type != 0 {
                self?.segControl?.selectedSegmentIndex = type - 1
            }
        }
    }
    
    @objc func setWearState() {
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        let index = (self.segControl?.selectedSegmentIndex ?? 0) + 1
        peripheralManage?.veepooSDK_setWearConfig(Int32(index)) { success in
            
        }
    }
    
}
