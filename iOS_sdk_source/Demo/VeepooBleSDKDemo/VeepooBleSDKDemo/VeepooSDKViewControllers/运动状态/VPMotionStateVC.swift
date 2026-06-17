//
//  VPMotionStateVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/6/13.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPMotionStateVC: UIViewController {

    private var isSupport: Bool = VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel.isSupportMotionState
    
    private var dateL: UILabel!
    
    private var tableView: UITableView!
    
    var dayIndex = 0
    
    var dataDict = [String : [String: Any]]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        createMainView()
        // Do any additional setup after loading the view.
    }
    

    func createMainView() {
        self.title = "运动状态"
        view.backgroundColor = .white
        
        let titleLab = UILabel(frame: CGRect(x: 20, y: 20, width: 250, height: 40))
        titleLab.text = "是否支持运动状态:\(isSupport ? "支持" : "不支持")"
        self.view.addSubview(titleLab)
        
        let contentView = UIView()
        contentView.isHidden = !isSupport
        contentView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(contentView)
        NSLayoutConstraint.activate([
            contentView.bottomAnchor.constraint(equalTo: view.bottomAnchor),
            contentView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            contentView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            contentView.topAnchor.constraint(equalTo: titleLab.bottomAnchor, constant: 10)
        ])
        
        dateL = .init()
        dateL.translatesAutoresizingMaskIntoConstraints = false
        dateL.text = dayIndex.getOneDayDateString()
        contentView.addSubview(dateL)
        
        NSLayoutConstraint.activate([
            dateL.centerXAnchor.constraint(equalTo: contentView.centerXAnchor),
            dateL.topAnchor.constraint(equalTo: contentView.topAnchor, constant: 10)
        ])
        
        let preBtn = UIButton()
        preBtn.setTitle("前一天", for: .normal)
        preBtn.setTitleColor(.gray, for: .normal)
        preBtn.translatesAutoresizingMaskIntoConstraints = false
        preBtn.addTarget(self, action: #selector(preAction), for: .touchUpInside)
        contentView.addSubview(preBtn)
        NSLayoutConstraint.activate([
            preBtn.centerYAnchor.constraint(equalTo: dateL.centerYAnchor),
            preBtn.trailingAnchor.constraint(equalTo: dateL.leadingAnchor, constant: -10),
        ])
        
        
        let nextBtn = UIButton()
        nextBtn.setTitle("后一天", for: .normal)
        nextBtn.setTitleColor(.gray, for: .normal)
        nextBtn.translatesAutoresizingMaskIntoConstraints = false
        nextBtn.addTarget(self, action: #selector(nextAction), for: .touchUpInside)
        contentView.addSubview(nextBtn)
        NSLayoutConstraint.activate([
            nextBtn.centerYAnchor.constraint(equalTo: dateL.centerYAnchor),
            nextBtn.leadingAnchor.constraint(equalTo: dateL.trailingAnchor, constant: 10),
        ])
        
        tableView = .init(frame: CGRectZero, style: .plain)
        tableView.translatesAutoresizingMaskIntoConstraints = false
        tableView.delegate = self
        tableView.dataSource = self
        contentView.addSubview(tableView)
        NSLayoutConstraint.activate([
            tableView.bottomAnchor.constraint(equalTo: contentView.bottomAnchor),
            tableView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor),
            tableView.trailingAnchor.constraint(equalTo: contentView.trailingAnchor),
            tableView.topAnchor.constraint(equalTo: dateL.bottomAnchor, constant: 10)
        ])
        obtainOneDayData()
    }
    
    @objc func preAction() {
        dayIndex = dayIndex - 1
        obtainOneDayData()
    }
    
    @objc func nextAction() {
        dayIndex = dayIndex + 1
        obtainOneDayData()
    }
    

    func obtainOneDayData() {
        self.dateL.text = dayIndex.getOneDayDateString()
        let onedayData = VPDataBaseOperation.veepooSDKGetOriginalData(withDate: self.dateL.text, andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress)
        if onedayData == nil {
            dataDict = [String : [String: String]]()
        }else {
            dataDict = onedayData as! [String : [String : Any]]
        }
        tableView.reloadData()
    }
}

extension VPMotionStateVC: UITableViewDelegate, UITableViewDataSource {
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        
        return dataDict.keys.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "Cell")
        if cell == nil {
            cell = UITableViewCell(style: .value1, reuseIdentifier: "Cell")
        }
        
        let allkeys = Array(dataDict.keys)
        
        let keys = allkeys.sorted(by: { (n1: String, n2: String) -> Bool in
            //进行从小到大的排序
            return n2 < n1
        })
        
        cell?.textLabel?.text = keys[indexPath.row]
        
        let subDict = dataDict[(cell?.textLabel?.text)!]
        
        guard let subHeartDict = subDict else {
            return cell!
        }
        if let array = subHeartDict["motionState"] as? [String] {
            cell?.detailTextLabel?.text = array.map { getMontionStateTypeString(Int($0) ?? 0) }.joined(separator: ", ")
        }
        
        cell?.detailTextLabel?.adjustsFontSizeToFitWidth = true
        
        return cell!
    }
    
    func getMontionStateTypeString(_ num: Int) -> String {
        if num == 1 {
            return "走路"
        } else if num == 2 {
            return "跑步"
        } else if num == 3 {
            return "静息"
        }
        return "未知"
    }
}
