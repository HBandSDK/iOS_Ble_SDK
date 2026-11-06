//
//  VPGameControlVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/11/5.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

/// 游戏控制简易演示
/// SDK不做持久化, 本页面用两个内存变量充当宿主侧状态(会话级):
/// 每次操作前先改本地状态再下发, 失败后回滚
class VPGameControlVC: UIViewController {

    /// 设备是否支持游戏控制, 非0即支持
    private var isSupTest: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.gameType != 0
    }

    /// 总开关状态, nil表示从未同步过
    private var mainSwitchState: Int?

    /// 当前持有的时段列表(下发时用于与设备端数据一致性校验)
    private var clockList: [VPGameClockModel] = []

    private var mainSwitch: UISwitch?
    private var stateLabel: UILabel?
    private var logTextView: UITextView?

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        if isSupTest {
            readGameClock()
        }
    }
}

// MARK: - UI
extension VPGameControlVC {

    private func setupSubViews() {
        view.backgroundColor = .white
        title = "游戏控制"
        let screenWidth = UIScreen.main.bounds.width

        let supLab = UILabel(frame: CGRect(x: 30, y: 40, width: 200, height: 30))
        supLab.text = "是否支持:" + (isSupTest ? "是" : "否")
        view.addSubview(supLab)

        guard isSupTest else {
            return
        }

        let switchLab = UILabel(frame: CGRect(x: 30, y: 80, width: 200, height: 30))
        switchLab.text = "总开关(游戏限制)"
        view.addSubview(switchLab)

        let switchControl = UISwitch(frame: CGRect(x: 250, y: 76, width: 60, height: 36))
        switchControl.addTarget(self, action: #selector(mainSwitchChanged(_:)), for: .valueChanged)
        view.addSubview(switchControl)
        mainSwitch = switchControl

        let stateLabel = UILabel(frame: CGRect(x: 30, y: 120, width: screenWidth - 60, height: 60))
        stateLabel.numberOfLines = 0
        stateLabel.font = UIFont.systemFont(ofSize: 13)
        stateLabel.textColor = .darkGray
        view.addSubview(stateLabel)
        self.stateLabel = stateLabel

        let addButton = UIButton(type: .system)
        addButton.frame = CGRect(x: 30, y: 190, width: (screenWidth - 70) / 2, height: 40)
        addButton.setTitle("添加示例时段", for: .normal)
        addButton.backgroundColor = UIColor(red: 0.95, green: 0.95, blue: 0.95, alpha: 1)
        addButton.addTarget(self, action: #selector(addSampleClock), for: .touchUpInside)
        view.addSubview(addButton)

        let deleteButton = UIButton(type: .system)
        deleteButton.frame = CGRect(x: 40 + (screenWidth - 70) / 2, y: 190, width: (screenWidth - 70) / 2, height: 40)
        deleteButton.setTitle("删除全部时段", for: .normal)
        deleteButton.backgroundColor = UIColor(red: 0.95, green: 0.95, blue: 0.95, alpha: 1)
        deleteButton.addTarget(self, action: #selector(deleteAllClocks), for: .touchUpInside)
        view.addSubview(deleteButton)

        let sampleDescLabel = UILabel(frame: CGRect(x: 30, y: 238, width: screenWidth - 60, height: 20))
        sampleDescLabel.text = "示例时段: 每天重复, 12:00:00 开始, 持续30分钟, 状态开启"
        sampleDescLabel.font = UIFont.systemFont(ofSize: 12)
        sampleDescLabel.textColor = .lightGray
        view.addSubview(sampleDescLabel)

        let logTextView = UITextView(frame: CGRect(x: 30, y: 266, width: screenWidth - 60, height: view.frame.size.height - 316))
        logTextView.layer.borderWidth = 0.5
        logTextView.layer.borderColor = UIColor.lightGray.cgColor
        logTextView.font = UIFont.systemFont(ofSize: 12)
        logTextView.isEditable = false
        view.addSubview(logTextView)
        self.logTextView = logTextView

        appendLog("进入页面, 读取游戏控制信息...")
    }

    private func refreshStateLabel() {
        var text = "总开关: " + (mainSwitchState == nil ? "未同步" : (mainSwitchState == 1 ? "开" : "关"))
        text += "\n时段列表(\(clockList.count)/10):"
        for model in clockList {
            text += String(format: "\n[id%d] %@ %02d:%02d:%02d起 %d分钟 %@",
                           model.clockID,
                           clockTypeText(model.clockType),
                           model.clockHour, model.clockMinute, model.clockSecond,
                           model.clockDuration,
                           model.clockState == 1 ? "开" : "关")
        }
        stateLabel?.text = text
    }

    private func clockTypeText(_ type: VPGameClockType) -> String {
        switch type {
        case .weeklyRepeat: return "周重复"
        case .single: return "单次"
        case .temporary: return "临时"
        @unknown default: return "未知"
        }
    }

    private func appendLog(_ line: String) {
        let formatter = DateFormatter()
        formatter.dateFormat = "HH:mm:ss.SSS"
        logTextView?.text.append("\n[\(formatter.string(from: Date()))] \(line)")
        let end = NSRange(location: (logTextView?.text.count ?? 0) - 1, length: 1)
        logTextView?.scrollRangeToVisible(end)
    }

    private func showToast(_ message: String) {
        _ = AppDelegate.showHUD(message: message, hudModel: MBProgressHUDModeText, showView: view)
    }
}

// MARK: - 事件
extension VPGameControlVC {

    /// 读取游戏控制信息: 传入宿主当前持有的总开关与列表用于一致性校验
    private func readGameClock() {
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        let mainSwitchNumber = mainSwitchState.map { NSNumber(value: $0) }
        peripheralManage?.veepooSDK_ZT79ReadGameClock(mainSwitchNumber, clockArr: clockList) { [weak self] readState, mainSwitch, clockArr in
            guard let self = self else { return }
            switch readState {
            case .fullData:
                self.mainSwitchState = mainSwitch
                self.clockList = clockArr
                self.appendLog("读取成功(设备回传全量): 总开关=\(mainSwitch), \(clockArr.count)条时段")
            case .synced:
                // 设备数据与本地一致, 沿用宿主传入的数据
                self.appendLog("读取成功(设备数据一致): 沿用本地数据, \(self.clockList.count)条时段")
            case .empty:
                self.mainSwitchState = mainSwitch
                self.clockList = []
                self.appendLog("读取成功(设备无时段数据): 总开关=\(mainSwitch)")
            @unknown default:
                self.appendLog("读取返回未知应答类型")
            }
            self.refreshStateLabel()
            self.mainSwitch?.setOn(self.mainSwitchState == 1, animated: false)
        }
    }

    /// 切换总开关: 先改本地状态再下发, 失败回滚
    @objc private func mainSwitchChanged(_ sender: UISwitch) {
        let newState = sender.isOn ? 1 : 0
        let oldState = mainSwitchState
        mainSwitchState = newState
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.veepooSDK_ZT79SetGameClockMainSwitch(sender.isOn, temporary: nil, crcClockArr: clockList) { [weak self] success in
            guard let self = self else { return }
            if success {
                self.appendLog("设置总开关=\(newState == 1 ? "开" : "关") 成功")
            } else {
                self.mainSwitchState = oldState
                self.mainSwitch?.setOn(oldState == 1, animated: false)
                self.appendLog("设置总开关 失败, 已回滚")
                self.showToast("设置失败")
            }
            self.refreshStateLabel()
        }
    }

    /// 添加一条示例时段(周重复, 每天12:00:00起30分钟, 开启)
    @objc private func addSampleClock() {
        guard clockList.count < 10 else {
            showToast("时段已达上限10条")
            return
        }
        let model = VPGameClockModel()
        model.clockID = minMissingID()
        model.clockType = .weeklyRepeat
        model.clockRepeat = .everyDay
        model.clockHour = 12
        model.clockMinute = 0
        model.clockSecond = 0
        model.clockDuration = 30
        model.clockState = 1

        // 先改本地状态(操作生效后的全量列表)再下发, 失败回滚
        let previousList = clockList
        clockList.append(model)
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.veepooSDK_ZT79SetGameClocks([model], mainSwitch: mainSwitchState.map { NSNumber(value: $0) }, crcClockArr: clockList) { [weak self] success in
            guard let self = self else { return }
            if success {
                self.appendLog(String(format: "添加时段成功: [id%d] 每天12:00 30分钟", model.clockID))
            } else {
                self.clockList = previousList
                self.appendLog("添加时段 失败, 已回滚")
                self.showToast("添加失败")
            }
            self.refreshStateLabel()
        }
        refreshStateLabel()
    }

    /// 删除全部时段
    @objc private func deleteAllClocks() {
        guard !clockList.isEmpty else {
            showToast("当前没有时段")
            return
        }
        let ids = clockList.map { NSNumber(value: $0.clockID) }
        // 先改本地状态(删除后的剩余列表)再下发, 失败恢复
        let previousList = clockList
        clockList = []
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.veepooSDK_ZT79DeleteGameClocks(withIDs: ids, mainSwitch: mainSwitchState.map { NSNumber(value: $0) }, crcClockArr: clockList) { [weak self] success in
            guard let self = self else { return }
            if success {
                self.appendLog("删除全部时段成功")
            } else {
                self.clockList = previousList
                self.appendLog("删除时段 失败, 已恢复")
                self.showToast("删除失败")
            }
            self.refreshStateLabel()
        }
        refreshStateLabel()
    }

    /// 取1~10中最小的空缺clockID
    private func minMissingID() -> UInt8 {
        let usedIDs = Set(clockList.map { Int($0.clockID) })
        for id in 1...10 where !usedIDs.contains(id) {
            return UInt8(id)
        }
        return 1
    }
}
