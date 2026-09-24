//
//  VPYM23ProVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/9/24.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

/// YM23PRO 佩戴状态上报与检测/修复状态定制协议演示
/// 包头 0x02 0x06（不使用 A7 标志位），FUCTION 区分：0x01=佩戴状态 0x02=测试状态
class VPYM23ProVC: UIViewController {

    private var wearResultLabel: UILabel!
    private var wearReportLabel: UILabel!
    private var testResultLabel: UILabel!
    private var statusSegment: UISegmentedControl!

    /// 测试状态区整体（标题 + 分段控件 + 下发按钮 + 结果），统一显示/隐藏
    private var testSectionViews: [UIView] = []

    /// 佩戴实时上报累计次数（每次开启佩戴上报时清零）
    private var wearReportCount = 0

    /// 测试状态下拉项文字（下标 = 对应 `testStatusTitles` / `testStatusValues` 的数字）
    ///
    /// 数字与文字对应关系：
    /// 0 退出 / 1 检测中 / 2 修复中 / 3 检测完成 / 4 修复完成 / 5 检测暂停 / 6 修复暂停
    private let testStatusNames = ["退出", "检测中", "修复中", "检测完成", "修复完成", "检测暂停", "修复暂停"]

    /// 分段控件显示的文字（太长，改成数字；数字对应 `testStatusNames` 的文字）
    ///
    /// 0=退出 / 1=检测中 / 2=修复中 / 3=检测完成 / 4=修复完成 / 5=检测暂停 / 6=修复暂停
    private let testStatusTitles = ["0", "1", "2", "3", "4", "5", "6"]

    /// 下拉项对应的实际协议枚举值（下标与 `testStatusTitles` 的数字一一对应，
    /// 与 `testStatusNames` 也是同序，故 `selectedSegmentIndex` 可直接作为下标取用）。
    private let testStatusValues: [VPM23ProTestStatus] = [.idle, .detecting, .repairing, .detectComplete, .repairComplete, .detectPaused, .repairPaused]

    /// 分段控件下方展示的「数字 → 状态文字」对应关系
    /// 由 `testStatusNames` 自动拼接生成（改名字自动同步，避免手写不一致）
    private var statusMapText: String {
        testStatusNames.enumerated().map { "\($0.offset):\($0.element)" }.joined(separator: "  ")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        setupWearReportCallback()
        // 默认隐藏测试状态区，开启佩戴状态上报成功后再显示
        setTestSectionHidden(true)
    }

    deinit {
        // 退出时取消持续上报监听，避免回调到已释放页面
        VPBleCentralManage.sharedBleManager().peripheralManage?.ym23ProWearReportResult = nil
    }
}

extension VPYM23ProVC {

    private func setupSubViews() {
        title = "YM23PRO 佩戴/测试状态"
        view.backgroundColor = .white
        let screenWidth = UIScreen.main.bounds.width

        var y: CGFloat = 20
        _ = addSectionTitle("一、佩戴状态上报", y: y, screenWidth: screenWidth)
        y += 34

        let halfWidth = (screenWidth - 60) / 2
        let openBtn = makeButton(title: "开启上报", x: 20, y: y, width: halfWidth)
        openBtn.addTarget(self, action: #selector(openWearClicked), for: .touchUpInside)
        view.addSubview(openBtn)

        let closeBtn = makeButton(title: "关闭上报", x: 40 + halfWidth, y: y, width: halfWidth)
        closeBtn.addTarget(self, action: #selector(closeWearClicked), for: .touchUpInside)
        view.addSubview(closeBtn)
        y += 50

        wearResultLabel = makeLabel(text: "开关结果：")
        wearResultLabel.frame = CGRect(x: 20, y: y, width: screenWidth - 40, height: 30)
        view.addSubview(wearResultLabel)
        y += 36

        wearReportLabel = makeLabel(text: "实时上报：未开启")
        wearReportLabel.numberOfLines = 0
        wearReportLabel.frame = CGRect(x: 20, y: y, width: screenWidth - 40, height: 44)
        view.addSubview(wearReportLabel)
        y += 60

        // 二、测试状态上报（整体默认隐藏）
        let testTitle = addSectionTitle("二、测试状态上报(需先开启佩戴状态上报)", y: y, screenWidth: screenWidth)
        testSectionViews.append(testTitle)
        y += 34

        statusSegment = UISegmentedControl(items: testStatusTitles)
        statusSegment.frame = CGRect(x: 20, y: y, width: screenWidth - 40, height: 32)
        statusSegment.selectedSegmentIndex = 0
        statusSegment.apportionsSegmentWidthsByContent = true
        view.addSubview(statusSegment)
        testSectionViews.append(statusSegment)
        y += 42

        // 数字与状态文字的对应关系说明
        let statusMapLabel = makeLabel(text: statusMapText)
        statusMapLabel.font = UIFont.systemFont(ofSize: 12)
        statusMapLabel.numberOfLines = 0
        statusMapLabel.frame = CGRect(x: 20, y: y, width: screenWidth - 40, height: 40)
        view.addSubview(statusMapLabel)
        testSectionViews.append(statusMapLabel)
        y += 46

        let sendBtn = makeButton(title: "下发测试状态", x: 20, y: y, width: screenWidth - 40)
        sendBtn.addTarget(self, action: #selector(sendTestStatusClicked), for: .touchUpInside)
        view.addSubview(sendBtn)
        testSectionViews.append(sendBtn)
        y += 50

        testResultLabel = makeLabel(text: "应答结果：")
        testResultLabel.frame = CGRect(x: 20, y: y, width: screenWidth - 40, height: 30)
        view.addSubview(testResultLabel)
        testSectionViews.append(testResultLabel)
    }

    /// 测试状态区整体显示/隐藏
    private func setTestSectionHidden(_ hidden: Bool) {
        testSectionViews.forEach { $0.isHidden = hidden }
    }

    private func addSectionTitle(_ title: String, y: CGFloat, screenWidth: CGFloat) -> UILabel {
        let label = UILabel(frame: CGRect(x: 20, y: y, width: screenWidth - 40, height: 24))
        label.font = UIFont.boldSystemFont(ofSize: 15)
        label.textColor = .black
        label.text = title
        view.addSubview(label)
        return label
    }

    private func makeButton(title: String, x: CGFloat, y: CGFloat, width: CGFloat) -> UIButton {
        let btn = UIButton(frame: CGRect(x: x, y: y, width: width, height: 40))
        btn.setTitle(title, for: .normal)
        btn.backgroundColor = .blue
        btn.titleLabel?.font = UIFont.systemFont(ofSize: 14)
        return btn
    }

    private func makeLabel(text: String) -> UILabel {
        let label = UILabel()
        label.font = UIFont.systemFont(ofSize: 14)
        label.textColor = .darkGray
        label.text = text
        return label
    }

    // MARK: - 佩戴状态主动上报（持续监听）

    private func setupWearReportCallback() {
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.ym23ProWearReportResult = { [weak self] reportType, isWear, heartRate in
            let typeDesc = (reportType == 1) ? "佩戴变更" : "每秒上报"
            // 累计上报次数（开启上报时已清零）
            self?.wearReportCount += 1
            let count = self?.wearReportCount ?? 0
            DispatchQueue.main.async {
                self?.updateWearReportLabel(typeDesc: typeDesc, isWear: isWear, heartRate: heartRate, count: count)
            }
        }
    }

    /// 刷新实时上报文案：未佩戴时，「实时上报」后面的内容显示红色；已佩戴显示默认色
    private func updateWearReportLabel(typeDesc: String, isWear: Bool, heartRate: Int, count: Int) {
        let prefix = "实时上报[\(typeDesc)]："
        let tail = "佩戴=\(isWear ? "已佩戴" : "未佩戴")，心率=\(heartRate)bpm"
        let countText = "，上报次数=\(count)"
        let defaultColor = UIColor.darkGray
        let tailColor = isWear ? defaultColor : UIColor.systemRed

        let attr = NSMutableAttributedString(string: prefix, attributes: [
            .foregroundColor: defaultColor,
            .font: UIFont.systemFont(ofSize: 14)
        ])
        attr.append(NSAttributedString(string: tail, attributes: [
            .foregroundColor: tailColor,
            .font: UIFont.systemFont(ofSize: 14)
        ]))
        // 次数用默认色，避免跟着"未佩戴"一起变红
        attr.append(NSAttributedString(string: countText, attributes: [
            .foregroundColor: defaultColor,
            .font: UIFont.systemFont(ofSize: 14)
        ]))
        wearReportLabel.attributedText = attr
    }

    // MARK: - 点击事件

    @objc private func openWearClicked() {
        // 每次开启上报时把累计次数清零
        wearReportCount = 0
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.veepooSDK_YM23ProSetWearStatus(true) { [weak self] ack in
            self?.handleWearACK(ack, isOpen: true)
        }
    }

    @objc private func closeWearClicked() {
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.veepooSDK_YM23ProSetWearStatus(false) { [weak self] ack in
            self?.handleWearACK(ack, isOpen: false)
        }
    }

    private func handleWearACK(_ ack: Int, isOpen: Bool) {
        let ackDesc: String
        switch ack {
        case 0: ackDesc = "不支持该协议"
        case 1: ackDesc = "成功"
        case 2: ackDesc = "失败"
        default: ackDesc = "未知(\(ack))"
        }
        // 2.3 开关应答帧只含 CON+ACK，无 Wear/HR；佩戴/心率见实时上报
        DispatchQueue.main.async {
            self.wearResultLabel.text = "开关结果：\(ackDesc)"
            guard ack == 1 else { return }
            // 开启成功才显示测试状态区；关闭成功则隐藏
            self.setTestSectionHidden(!isOpen)
            if !isOpen {
                self.wearReportLabel.textColor = .darkGray
                self.wearReportLabel.text = "实时上报：已关闭"
            }
        }
    }

    @objc private func sendTestStatusClicked() {
        let index = statusSegment.selectedSegmentIndex
        guard index >= 0 && index < testStatusValues.count else { return }
        let status = testStatusValues[index]
        let peripheralManage = VPBleCentralManage.sharedBleManager().peripheralManage
        peripheralManage?.veepooSDK_YM23ProSendTest(status) { [weak self] ack, currentStatus in
            let ackDesc: String
            switch ack {
            case 0: ackDesc = "不支持该协议"
            case 1: ackDesc = "成功"
            case 2: ackDesc = "失败"
            default: ackDesc = "未知(\(ack))"
            }
            let name = self?.testStatusNames[currentStatus] ?? "\(currentStatus)"
            DispatchQueue.main.async {
                self?.testResultLabel.text = "应答结果：\(ackDesc)，设备状态=\(name)"
            }
        }
    }
}
