//
//  VPDeviceContactsViewController.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2023/3/23.
//  Copyright © 2023 veepoo. All rights reserved.
//

import UIKit

class VPDeviceContactsViewController: UIViewController {
    let CellId = "VPDeviceContactsViewControllerID"
    
    private var tableView : UITableView!
    private var mArr:[VPDeviceContactsModel] = []
    
    private var supportSOS:Bool!

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "联系人"
        view.backgroundColor = .white
        addSubViews()
        
        let contactType = VPBleCentralManage.sharedBleManager().peripheralModel.contactType
                
        let unsupported = contactType == 0
        if unsupported {
            _ = AppDelegate.showHUD(message: "设备不支持该功能", hudModel: MBProgressHUDModeText, showView: self.view)
            return
        }
        
        supportSOS = contactType == 2
        
        commonFunc(opCode: .read, opModel: nil, toID: 0)
        let addItem:UIBarButtonItem = .init(barButtonSystemItem: .add, target: self, action: #selector(add))
        if supportSOS {
            let sosItem:UIBarButtonItem = .init(title: "SOS", style: .plain, target: self, action: #selector(readSOSInfo))
            navigationItem.rightBarButtonItems = [addItem, sosItem]
        } else {
            navigationItem.rightBarButtonItems = [addItem]
        }
    }
    
    @objc func add() {
        let model:VPDeviceContactsModel = VPDeviceContactsModel.init()
        model.nickName = "test"
        model.phoneNumber = "10086"
        model.contactID = Int32(mArr.count + 1)
        model.isSOS = true
        commonFunc(opCode: .add, opModel: model, toID: 0)
    }
    
    func move(model:VPDeviceContactsModel, toID:Int32) {
        commonFunc(opCode: .move, opModel: model, toID: toID)
    }
        
    func delete(model:VPDeviceContactsModel) {
        commonFunc(opCode: .delete, opModel: model, toID: 0)
    }
    
    private func commonFunc(opCode:VPDeviceContactsOpCode, opModel:VPDeviceContactsModel?, toID:Int32) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceContacts(with: opCode, opModel: opModel, toID: toID) { [self]state, models in
            if (state == .complete) {
                if (opCode == .add) {
                    if let opModel = opModel {
                        mArr.append(opModel)
                        tableView.reloadData()
                    }
                } else {
                    if let models = models {
                        mArr = models
                        tableView.reloadData()
                    }
                }
                _ = AppDelegate.showHUD(message: "操作成功", hudModel: MBProgressHUDModeText, showView: self.view)
            }
        }
    }
    
    @objc func changeSOSContact(_ indexPath: IndexPath, _ didOpen: Bool) {
        let model = mArr[indexPath.row]
        model.isSOS = didOpen
        model.phoneNumber = "12345"
        commonFunc(opCode: .edit, opModel: model, toID: 0)
    }
    
    @objc func readSOSInfo() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceContactsSOSInfo(withOpCode: .read, times: 0) { (state, curTime, timesMin, timesMax) in
            if state == .complete {
                print("curTime:\(curTime), timesMin:\(timesMin), timesMax:\(timesMax)")
            }
        }
        
//        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSettingDeviceContactsSOSInfo(withOpCode: .setting, times: 2) { (state, curTime, timesMin, timesMax) in
//            if state == .complete {
//                print("curTime:\(curTime), timesMin:\(timesMin), timesMax:\(timesMax)")
//            }
//        }
    }
}

extension VPDeviceContactsViewController {
    func addSubViews(){
        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView.delegate = self
        tableView.dataSource = self
        tableView.isEditing = true
        tableView.register(UINib(nibName: "VPContactCell", bundle: Bundle.main), forCellReuseIdentifier: CellId)
        view.addSubview(tableView)
    }
}

extension VPDeviceContactsViewController: UITableViewDelegate, UITableViewDataSource {
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return mArr.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell:VPContactCell = tableView.dequeueReusableCell(withIdentifier: CellId, for: indexPath) as! VPContactCell
        let model = mArr[indexPath.row]
        cell.nickNameLabel.text = model.nickName
        cell.phoneNumberLabel.text = model.phoneNumber
        cell.sosSwitch.isHidden = !supportSOS
        cell.sosLabel.isHidden = !supportSOS
        if supportSOS {
            cell.sosSwitch.isOn = model.isSOS
            cell.output = { [weak self] didOpen in
                guard let weakSelf = self else {
                    return
                }
                weakSelf.changeSOSContact(indexPath, didOpen)
            }
        }
        return cell
    }
    
    // 移动
    func tableView(_ tableView: UITableView, moveRowAt sourceIndexPath: IndexPath, to destinationIndexPath: IndexPath) {
        if sourceIndexPath.compare(destinationIndexPath) == .orderedSame {
            return
        }
        let model = mArr[sourceIndexPath.row]
        let toID = Int32(destinationIndexPath.row + 1)
        move(model: model, toID: toID)
    }
    
    // 编辑
    func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if (editingStyle == .delete) {
            let model = mArr[indexPath.row]
            mArr.remove(at: indexPath.row)
            delete(model: model)
        }
        tableView.reloadData()
    }
    
    func tableView(_ tableView: UITableView, targetIndexPathForMoveFromRowAt sourceIndexPath: IndexPath, toProposedIndexPath proposedDestinationIndexPath: IndexPath) -> IndexPath {
        if (proposedDestinationIndexPath.section == 1) {
            return IndexPath.init(row: 0, section: 1)
        }
        return proposedDestinationIndexPath
    }
    
    // 编辑状态为删除
    func tableView(_ tableView: UITableView, editingStyleForRowAt indexPath: IndexPath) -> UITableViewCellEditingStyle {
        return .delete
    }
    
    // 可以编辑
    func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        return true
    }
    
    // 可以移动
    func tableView(_ tableView: UITableView, canMoveRowAt indexPath: IndexPath) -> Bool {
        return true
    }
}
