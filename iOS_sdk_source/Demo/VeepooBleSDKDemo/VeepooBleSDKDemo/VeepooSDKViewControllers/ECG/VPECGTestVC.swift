//
//  VPECGTestVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/7/20.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

class VPECGTestVC: UIViewController, UITableViewDelegate, UITableViewDataSource {

    private var dateLabel: UILabel!
    private var testBtn: UIButton!
    private var progressLabel: UILabel!
    private var tableView: UITableView!
    private var dataSource: [VPECGTestDataModel] = []
    private var dayIndex = 0

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white

        guard VPBleCentralManage.sharedBleManager().peripheralManage.peripheralModel.ecgType != 0 else {
            let tipLabel = UILabel()
            tipLabel.text = "不支持ECG功能"
            tipLabel.textAlignment = .center
            tipLabel.textColor = .gray
            tipLabel.font = UIFont.systemFont(ofSize: 16)
            tipLabel.translatesAutoresizingMaskIntoConstraints = false
            view.addSubview(tipLabel)
            NSLayoutConstraint.activate([
                tipLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor),
                tipLabel.centerYAnchor.constraint(equalTo: view.centerYAnchor)
            ])
            return
        }

        setupUI()
        loadData()
        /// 监听设备测量结束上报,App测量不会触发
        VPBleCentralManage.sharedBleManager().peripheralManage.deviceTestOffStoreECGDidFinishBlock = { [weak self] in
            self?.reReadAllData()
        }
    }

    private func reReadAllData() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSdkStartReadDeviceAllData { [weak self] readDeviceBaseDataState, totalDay, currentReadDayNumber, readCurrentDayProgress in
            if readDeviceBaseDataState == .complete {
                self?.loadData()
            }
        }
    }

    deinit {
        VPBleCentralManage.sharedBleManager().peripheralManage.deviceTestOffStoreECGDidFinishBlock = nil
    }
    
    

    private func setupUI() {
        title = "ECG"
        
        // 顶部日期区域
        let topContainer = UIView()
        topContainer.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(topContainer)

        let prevBtn = UIButton(type: .system)
        prevBtn.setTitle("前一天", for: .normal)
        prevBtn.addTarget(self, action: #selector(prevDayAction), for: .touchUpInside)
        prevBtn.translatesAutoresizingMaskIntoConstraints = false
        topContainer.addSubview(prevBtn)

        let nextBtn = UIButton(type: .system)
        nextBtn.setTitle("后一天", for: .normal)
        nextBtn.addTarget(self, action: #selector(nextDayAction), for: .touchUpInside)
        nextBtn.translatesAutoresizingMaskIntoConstraints = false
        topContainer.addSubview(nextBtn)

        dateLabel = UILabel()
        dateLabel.textAlignment = .center
        dateLabel.font = UIFont.systemFont(ofSize: 16, weight: .medium)
        dateLabel.translatesAutoresizingMaskIntoConstraints = false
        topContainer.addSubview(dateLabel)

        // 测量按钮和进度
        testBtn = UIButton(type: .system)
        testBtn.setTitle("开始测量", for: .normal)
        testBtn.setTitle("停止测量", for: .selected)
        testBtn.addTarget(self, action: #selector(testAction), for: .touchUpInside)
        testBtn.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(testBtn)

        progressLabel = UILabel()
        progressLabel.textAlignment = .center
        progressLabel.font = UIFont.systemFont(ofSize: 14)
        progressLabel.textColor = .gray
        progressLabel.text = ""
        progressLabel.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(progressLabel)

        // 列表
        tableView = UITableView(frame: .zero, style: .plain)
        tableView.delegate = self
        tableView.dataSource = self
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "Cell")
        tableView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(tableView)

        NSLayoutConstraint.activate([
            topContainer.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            topContainer.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            topContainer.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            topContainer.heightAnchor.constraint(equalToConstant: 50),

            prevBtn.leadingAnchor.constraint(equalTo: topContainer.leadingAnchor, constant: 16),
            prevBtn.centerYAnchor.constraint(equalTo: topContainer.centerYAnchor),

            dateLabel.centerXAnchor.constraint(equalTo: topContainer.centerXAnchor),
            dateLabel.centerYAnchor.constraint(equalTo: topContainer.centerYAnchor),

            nextBtn.trailingAnchor.constraint(equalTo: topContainer.trailingAnchor, constant: -16),
            nextBtn.centerYAnchor.constraint(equalTo: topContainer.centerYAnchor),

            testBtn.topAnchor.constraint(equalTo: topContainer.bottomAnchor, constant: 12),
            testBtn.centerXAnchor.constraint(equalTo: view.centerXAnchor),

            progressLabel.topAnchor.constraint(equalTo: testBtn.bottomAnchor, constant: 8),
            progressLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            progressLabel.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),

            tableView.topAnchor.constraint(equalTo: progressLabel.bottomAnchor, constant: 8),
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            tableView.bottomAnchor.constraint(equalTo: view.bottomAnchor)
        ])
    }

    @objc private func prevDayAction() {
        dayIndex -= 1
        loadData()
    }

    @objc private func nextDayAction() {
        dayIndex += 1
        loadData()
    }

    private func loadData() {
        dateLabel.text = dayIndex.getOneDayDateString()
        if let ecgArr = VPDataBaseOperation.veepooSDKGetDeviceOffStoreECG(withDate: dayIndex.getOneDayDateString(), andTableID: VPBleCentralManage.sharedBleManager().peripheralModel.deviceAddress) {
            dataSource = ecgArr
        } else {
            dataSource = []
        }
        tableView.reloadData()
    }

    @objc private func testAction(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        if sender.isSelected {
            progressLabel.text = "测量中..."
        }
        /// App测量数据自行存储
        VPBleCentralManage.sharedBleManager()
            .peripheralManage.veepooSDKTestECGStart(sender.isSelected) {[weak self] (state, progress, model) in
                guard let model = model, let self = self else { return }
                self.progressLabel.text = "进度: \(progress)"
                if state == .complete {
                    self.progressLabel.text = "测量完成"
                    sender.isSelected = false
                    if self.dayIndex == 0 {
                        self.dataSource.insert(model, at: 0)
                        self.tableView.reloadData()
                    }
                }
        }
    }

    // MARK: - UITableViewDelegate

    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "共 \(dataSource.count) 条数据"
    }

    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        let model = dataSource[indexPath.row]
        let message = """
        type: \(model.type ?? "")
        ecgType: \(model.ecgType ?? "")
        date: \(model.date ?? "")
        testTime: \(model.testTime ?? "")
        duration: \(model.duration ?? "")
        aveHeart: \(model.aveHeart ?? "")
        aveHrv: \(model.aveHrv ?? "")
        aveQT: \(model.aveQT ?? "")
        avePWV: \(model.avePWV ?? "")
        frequency: \(model.frequency ?? "")
        uploadFrequency: \(model.uploadFrequency ?? "")
        """
        let alert = UIAlertController(title: "ECG 详情", message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "确定", style: .default))
        present(alert, animated: true)
    }

    // MARK: - UITableViewDataSource

    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return dataSource.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath)
        let model = dataSource[indexPath.row]
        cell.textLabel?.text = "测量时间:" + model.testTime + " ECG类型:" + model.ecgType
        return cell
    }
}
