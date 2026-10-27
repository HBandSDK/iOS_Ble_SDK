//
//  VPAutoMonitSwitchVC.swift
//  VeepooBleSDKDemo
//
//  Created by veepoo-cd on 2025/6/11.
//  Copyright © 2025 veepoo. All rights reserved.
//
import Foundation
import UIKit
import VeepooBleSDK

// MARK: - 时间选择弹窗代理协议
protocol TimePickerDelegate: AnyObject {
    func timePickerDidConfirm(selectedTime: Int)
    func timePickerDidCancel()
}

// MARK: - 时间选择弹窗ViewController
class TimePickerViewController: UIViewController {
    
    // 代理
    weak var delegate: TimePickerDelegate?
    
    // 当前选中的时间
    private var selectedTime: Int = 0
    // 步长值
    private var stepValue: Int = 1
    // 时间数据源
    private var timeOptions: [Int] = []
    
    // UI组件
    private let containerView: UIView = {
        let view = UIView()
        view.backgroundColor = .white
        view.layer.cornerRadius = 12
        view.layer.masksToBounds = true
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    private let titleLabel: UILabel = {
        let label = UILabel()
        label.text = "选择间隔时间"
        label.font = UIFont.boldSystemFont(ofSize: 18)
        label.textAlignment = .center
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()
    
    private let pickerView: UIPickerView = {
        let picker = UIPickerView()
        picker.translatesAutoresizingMaskIntoConstraints = false
        return picker
    }()
    
    private let buttonStackView: UIStackView = {
        let stackView = UIStackView()
        stackView.axis = .horizontal
        stackView.distribution = .fillEqually
        stackView.spacing = 1
        stackView.translatesAutoresizingMaskIntoConstraints = false
        return stackView
    }()
    
    private let cancelButton: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("取消", for: .normal)
        button.setTitleColor(.systemRed, for: .normal)
        button.backgroundColor = UIColor.systemGray6
        button.translatesAutoresizingMaskIntoConstraints = false
        return button
    }()
    
    private let confirmButton: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("确定", for: .normal)
        button.setTitleColor(.systemBlue, for: .normal)
        button.backgroundColor = UIColor.systemGray6
        button.translatesAutoresizingMaskIntoConstraints = false
        return button
    }()
    
    private let separatorLine: UIView = {
        let view = UIView()
        view.backgroundColor = UIColor.systemGray4
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    private let verticalSeparator: UIView = {
        let view = UIView()
        view.backgroundColor = UIColor.systemGray4
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    init(defaultTime: Int = 0, stepValue: Int = 1) {
        self.selectedTime = defaultTime
        self.stepValue = stepValue
        super.init(nibName: nil, bundle: nil)
        modalPresentationStyle = .overFullScreen
        modalTransitionStyle = .crossDissolve
        generateTimeOptions()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        setupPickerView()
        setupActions()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        // 设置背景透明
        view.backgroundColor = UIColor.black.withAlphaComponent(0.4)
        // 动画显示
        containerView.transform = CGAffineTransform(scaleX: 0.8, y: 0.8)
        UIView.animate(withDuration: 0.3) {
            self.containerView.transform = CGAffineTransform.identity
        }
    }
    
    // 生成时间选项
    private func generateTimeOptions() {
        timeOptions.removeAll()
        if stepValue == 0 {
            // stepValue为0，代表时间是0到180连续的
            for i in 0...180 {
                timeOptions.append(i)
            }
        } else {
            // stepValue不为0，从最小值开始按步长递增
            let minValue = stepValue
            for i in stride(from: minValue, through: 180, by: stepValue) {
                timeOptions.append(i)
            }
        }
    }
    
    private func setupUI() {
        view.backgroundColor = .clear
        
        // 添加容器视图
        view.addSubview(containerView)
        
        // 添加子视图
        containerView.addSubview(titleLabel)
        containerView.addSubview(pickerView)
        containerView.addSubview(separatorLine)
        containerView.addSubview(buttonStackView)
        
        buttonStackView.addArrangedSubview(cancelButton)
//        buttonStackView.addArrangedSubview(verticalSeparator)
        buttonStackView.addArrangedSubview(confirmButton)
        
        // 设置约束
        NSLayoutConstraint.activate([
            // 容器视图居中
            containerView.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            containerView.centerYAnchor.constraint(equalTo: view.centerYAnchor),
            containerView.widthAnchor.constraint(equalToConstant: 300),
            containerView.heightAnchor.constraint(equalToConstant: 280),
            
            // 标题
            titleLabel.topAnchor.constraint(equalTo: containerView.topAnchor, constant: 16),
            titleLabel.leadingAnchor.constraint(equalTo: containerView.leadingAnchor, constant: 20),
            titleLabel.trailingAnchor.constraint(equalTo: containerView.trailingAnchor, constant: -20),
            titleLabel.heightAnchor.constraint(equalToConstant: 30),
            
            // PickerView
            pickerView.topAnchor.constraint(equalTo: titleLabel.bottomAnchor, constant: 8),
            pickerView.leadingAnchor.constraint(equalTo: containerView.leadingAnchor),
            pickerView.trailingAnchor.constraint(equalTo: containerView.trailingAnchor),
            pickerView.heightAnchor.constraint(equalToConstant: 160),
            
            // 分割线
            separatorLine.topAnchor.constraint(equalTo: pickerView.bottomAnchor),
            separatorLine.leadingAnchor.constraint(equalTo: containerView.leadingAnchor),
            separatorLine.trailingAnchor.constraint(equalTo: containerView.trailingAnchor),
            separatorLine.heightAnchor.constraint(equalToConstant: 1),
            
            // 按钮栈视图
            buttonStackView.topAnchor.constraint(equalTo: separatorLine.bottomAnchor),
            buttonStackView.leadingAnchor.constraint(equalTo: containerView.leadingAnchor),
            buttonStackView.trailingAnchor.constraint(equalTo: containerView.trailingAnchor),
            buttonStackView.bottomAnchor.constraint(equalTo: containerView.bottomAnchor),
            
            // 垂直分割线
//            verticalSeparator.widthAnchor.constraint(equalToConstant: 1),
//            verticalSeparator.heightAnchor.constraint(equalTo: buttonStackView.heightAnchor),
        ])
    }
    
    private func setupPickerView() {
        pickerView.delegate = self
        pickerView.dataSource = self
        
        // 设置默认选中（找到最接近的选项）
        if let defaultIndex = timeOptions.firstIndex(where: { $0 >= selectedTime }) {
            pickerView.selectRow(defaultIndex, inComponent: 0, animated: false)
            selectedTime = timeOptions[defaultIndex]
        } else if let lastIndex = timeOptions.indices.last {
            pickerView.selectRow(lastIndex, inComponent: 0, animated: false)
            selectedTime = timeOptions[lastIndex]
        }
    }
    
    private func setupActions() {
        cancelButton.addTarget(self, action: #selector(cancelButtonTapped), for: .touchUpInside)
        confirmButton.addTarget(self, action: #selector(confirmButtonTapped), for: .touchUpInside)
        
        // 点击背景关闭
        let tapGesture = UITapGestureRecognizer(target: self, action: #selector(backgroundTapped))
        view.addGestureRecognizer(tapGesture)
    }
    
    @objc private func cancelButtonTapped() {
        delegate?.timePickerDidCancel()
        dismiss(animated: true)
    }
    
    @objc private func confirmButtonTapped() {
        delegate?.timePickerDidConfirm(selectedTime: selectedTime)
        dismiss(animated: true)
    }
    
    @objc private func backgroundTapped() {
        delegate?.timePickerDidCancel()
        dismiss(animated: true)
    }
}

// MARK: - UIPickerViewDelegate & UIPickerViewDataSource
extension TimePickerViewController: UIPickerViewDelegate, UIPickerViewDataSource {
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return timeOptions.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return "\(timeOptions[row]) 分钟"
    }
    
    func pickerView(_ pickerView: UIPickerView, rowHeightForComponent component: Int) -> CGFloat {
        return 45
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        selectedTime = timeOptions[row]
    }
}

// MARK: - VPAutoMonitSwitchVC
class VPAutoMonitSwitchVC: UIViewController {
    
    private var dataSource: [VPAutoMonitTestModel] = []
    private var tableView: UITableView!
    private var currentEditingIndex: IndexPath?

    private enum Row {
        case monitor(index: Int)
        case lowOxy(index: Int)
        case sensitivity(index: Int)
    }

    // 列表行：功能项按顺序展开，低氧提醒、灵敏度作为子项紧跟各自功能项
    private var rows: [Row] {
        var result: [Row] = []
        for (index, model) in dataSource.enumerated() {
            result.append(.monitor(index: index))
            if model.type == .bloodOxygen, model.isSupLowOxy {
                result.append(.lowOxy(index: index))
            }
            if model.type == .fallReminder {
                result.append(.sensitivity(index: index))
            }
        }
        return result
    }

    private func row(forMonitorIndex index: Int) -> Int? {
        return rows.firstIndex { row in
            if case .monitor(let i) = row {
                return i == index
            }
            return false
        }
    }

    private func sensitivityText(_ value: UInt8) -> String {
        switch value {
        case 1: return "低"
        case 2: return "标准"
        case 3: return "高"
        default: return "标准"
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubViews()
        bindViewModel()
    }
}

extension VPAutoMonitSwitchVC {
    private func bindViewModel() {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKReadAutoMonitSwitchInfo { [weak self] models in
            guard let someModels = models else {
                return
            }
            print(">>> \(someModels.count)")
            self?.dataSource = someModels
            self?.tableView.reloadData()
        }
    }
}

extension VPAutoMonitSwitchVC {
    private func showSensitivityPicker(for model: VPAutoMonitTestModel, at indexPath: IndexPath) {
        let alert = UIAlertController(title: "灵敏度", message: nil, preferredStyle: .actionSheet)
        for value in 1...3 {
            let title = "\(value) \(sensitivityText(UInt8(value)))"
            alert.addAction(UIAlertAction(title: title, style: .default) { [weak self] _ in
                self?.updateSensitivity(UInt8(value), for: model, at: indexPath)
            })
        }
        alert.addAction(UIAlertAction(title: "取消", style: .cancel))
        alert.popoverPresentationController?.sourceView = tableView
        alert.popoverPresentationController?.sourceRect = tableView.rectForRow(at: indexPath)
        present(alert, animated: true)
    }

    private func updateSensitivity(_ value: UInt8, for model: VPAutoMonitTestModel, at indexPath: IndexPath) {
        let oldValue = model.sensitivity
        model.sensitivity = value

        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSetAutoMonitSwitch(with: model) { [weak self] success, _ in
            guard let self = self else { return }
            if !success {
                model.sensitivity = oldValue
            }
            self.tableView.reloadRows(at: [indexPath], with: .none)
        }
    }
}

extension VPAutoMonitSwitchVC {
    private func setupSubViews() {
        title = "自动测量时间间隔设置"
        view.backgroundColor = UIColor.white
        
        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView.dataSource = self
        tableView.delegate = self
        tableView.register(AutoMonitSwitchCell.self, forCellReuseIdentifier: "AutoMonitCell")
        tableView.register(LowOxySwitchCell.self, forCellReuseIdentifier: "LowOxyCell")
        tableView.register(SensitivityCell.self, forCellReuseIdentifier: "SensitivityCell")
        view.addSubview(tableView)
    }
}

// MARK: - 自定义Cell
class AutoMonitSwitchCell: UITableViewCell {
    
    let titleLabel: UILabel = {
        let label = UILabel()
        label.font = UIFont.systemFont(ofSize: 16)
        label.textColor = .black
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()
    
    let timeLabel: UILabel = {
        let label = UILabel()
        label.font = UIFont.systemFont(ofSize: 14)
        label.textColor = .gray
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()
    
    let switchControl: UISwitch = {
        let switchControl = UISwitch()
        switchControl.translatesAutoresizingMaskIntoConstraints = false
        return switchControl
    }()
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        setupUI()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private var titleOffsetConstraint: NSLayoutConstraint?

    private func setupUI() {
        contentView.addSubview(titleLabel)
        contentView.addSubview(timeLabel)
        contentView.addSubview(switchControl)

        let titleOffset = titleLabel.centerYAnchor.constraint(equalTo: contentView.centerYAnchor, constant: -10)
        titleOffsetConstraint = titleOffset

        NSLayoutConstraint.activate([
            titleLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            titleOffset,
            
            timeLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            timeLabel.topAnchor.constraint(equalTo: titleLabel.bottomAnchor, constant: 4),
            
            switchControl.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -16),
            switchControl.centerYAnchor.constraint(equalTo: contentView.centerYAnchor)
        ])
    }
    
    func configure(with model: VPAutoMonitTestModel) {
        let hidesTime = model.type == .fallReminder
        titleLabel.text = model.displayText
        timeLabel.isHidden = hidesTime
        timeLabel.text = hidesTime ? nil : "间隔: \(model.timeInterval)分钟"
        titleOffsetConstraint?.constant = hidesTime ? 0 : -10
        switchControl.isOn = model.on
    }
}

// MARK: - 低氧提醒开关Cell（独立行，无时间间隔设置）
class LowOxySwitchCell: UITableViewCell {

    let titleLabel: UILabel = {
        let label = UILabel()
        label.font = UIFont.systemFont(ofSize: 16)
        label.textColor = .black
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    let switchControl: UISwitch = {
        let sw = UISwitch()
        sw.translatesAutoresizingMaskIntoConstraints = false
        return sw
    }()

    var switchChanged: ((Bool) -> Void)?

    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        setupUI()
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private func setupUI() {
        contentView.addSubview(titleLabel)
        contentView.addSubview(switchControl)
        switchControl.addTarget(self, action: #selector(switchToggled(_:)), for: .valueChanged)

        NSLayoutConstraint.activate([
            titleLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            titleLabel.centerYAnchor.constraint(equalTo: contentView.centerYAnchor),

            switchControl.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -16),
            switchControl.centerYAnchor.constraint(equalTo: contentView.centerYAnchor)
        ])
    }

    @objc private func switchToggled(_ sender: UISwitch) {
        switchChanged?(sender.isOn)
    }
}

// MARK: - 灵敏度设置Cell（右侧显示当前灵敏度，点击选择）
class SensitivityCell: UITableViewCell {

    let titleLabel: UILabel = {
        let label = UILabel()
        label.font = UIFont.systemFont(ofSize: 16)
        label.textColor = .black
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    let valueLabel: UILabel = {
        let label = UILabel()
        label.font = UIFont.systemFont(ofSize: 14)
        label.textColor = .gray
        label.textAlignment = .right
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        accessoryType = .disclosureIndicator
        setupUI()
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private func setupUI() {
        contentView.addSubview(titleLabel)
        contentView.addSubview(valueLabel)

        NSLayoutConstraint.activate([
            titleLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            titleLabel.centerYAnchor.constraint(equalTo: contentView.centerYAnchor),

            valueLabel.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -8),
            valueLabel.centerYAnchor.constraint(equalTo: contentView.centerYAnchor),
            valueLabel.leadingAnchor.constraint(greaterThanOrEqualTo: titleLabel.trailingAnchor, constant: 8)
        ])
    }
}

// MARK: - TableView DataSource & Delegate
extension VPAutoMonitSwitchVC: UITableViewDataSource, UITableViewDelegate {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return rows.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        switch rows[indexPath.row] {
        case .monitor(let index):
            let cell = tableView.dequeueReusableCell(withIdentifier: "AutoMonitCell", for: indexPath) as! AutoMonitSwitchCell
            let model = dataSource[index]
            cell.configure(with: model)

            cell.switchControl.tag = index
            cell.switchControl.addTarget(self, action: #selector(switchValueChanged(_:)), for: .valueChanged)

            return cell

        case .lowOxy(let index):
            let cell = tableView.dequeueReusableCell(withIdentifier: "LowOxyCell", for: indexPath) as! LowOxySwitchCell
            let model = dataSource[index]
            cell.titleLabel.text = "低氧提醒"
            cell.switchControl.isOn = model.lowOxyOpen
            cell.switchChanged = { [weak tableView] isOn in
                model.lowOxyOpen = isOn
                VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSetAutoMonitSwitch(with: model) { success, _ in
                    if !success {
                        model.lowOxyOpen = !isOn
                        DispatchQueue.main.async {
                            tableView?.reloadRows(at: [indexPath], with: .none)
                        }
                    }
                }
            }
            return cell

        case .sensitivity(let index):
            let cell = tableView.dequeueReusableCell(withIdentifier: "SensitivityCell", for: indexPath) as! SensitivityCell
            let model = dataSource[index]
            cell.titleLabel.text = "灵敏度"
            cell.valueLabel.text = sensitivityText(model.sensitivity)
            return cell
        }
    }

    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)

        switch rows[indexPath.row] {
        case .lowOxy:
            return

        case .sensitivity(let index):
            showSensitivityPicker(for: dataSource[index], at: indexPath)

        case .monitor(let index):
            let model = dataSource[index]
            if model.type == .lorentz || model.type == .fallReminder {
                return
            }
            
            currentEditingIndex = indexPath
            
            // 获取步长值，如果minStepValue为0则使用默认值1
            let stepValue = model.minStepValue == 0 ? 0 : model.minStepValue
            
            // 创建并显示时间选择器
            let timePicker = TimePickerViewController(defaultTime: Int(model.timeInterval), stepValue: Int(stepValue))
            timePicker.delegate = self
            present(timePicker, animated: true)
        }
    }
    
    @objc private func switchValueChanged(_ sender: UISwitch) {
        let index = sender.tag
        let model = dataSource[index]
        model.on = sender.isOn
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSetAutoMonitSwitch(with: model) { [weak self] success, _ in
            guard let self = self else { return }
            if success {
                if let row = self.row(forMonitorIndex: index) {
                    self.tableView.reloadRows(at: [IndexPath(row: row, section: 0)], with: .none)
                }
            } else {
                // 如果设置失败，恢复Switch状态
                sender.isOn = !sender.isOn
            }
        }
    }
}

// MARK: - TimePickerDelegate
extension VPAutoMonitSwitchVC: TimePickerDelegate {
    func timePickerDidConfirm(selectedTime: Int) {
        guard let indexPath = currentEditingIndex,
              indexPath.row < rows.count,
              case .monitor(let index) = rows[indexPath.row] else { return }
        
        let model = dataSource[index]
        model.timeInterval = UInt16(selectedTime)
        model.on = true // 设置时间时自动开启
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSetAutoMonitSwitch(with: model) { [weak self] success, model in
            if success {
                self?.tableView.reloadRows(at: [indexPath], with: .none)
                self?.currentEditingIndex = nil
            }
        }
    }
    
    func timePickerDidCancel() {
        currentEditingIndex = nil
    }
}

extension VPAutoMonitTestModel {
    var displayText: String {
        switch self.type {
        case .heartRate:
            return "心率自动监测"
        case .bloodPressure:
            return "血压自动监测"
        case .bloodGlucose:
            return "血糖自动监测"
        case .stress:
            return "压力自动监测"
        case .bloodOxygen:
            return "血氧自动监测"
        case .bodyTemperature:
            return "体温自动监测"
        case .lorentz:
            return "洛伦兹散点图"
        case .HRV:
            return "HRV自动监测"
        case .bloodComponents:
            return "血液成分监测"
        case .fallReminder:
            return "跌倒感应"
        }
    }
    
    var onStr: String {
        on ? "开启" : "关闭"
    }
}
