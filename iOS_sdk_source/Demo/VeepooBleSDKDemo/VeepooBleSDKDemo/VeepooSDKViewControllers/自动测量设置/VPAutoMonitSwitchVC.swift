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
            self?.dataSource = someModels
            print(">>> \(someModels.count)")
            self?.tableView.reloadData()
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
    
    private func setupUI() {
        contentView.addSubview(titleLabel)
        contentView.addSubview(timeLabel)
        contentView.addSubview(switchControl)
        
        NSLayoutConstraint.activate([
            titleLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            titleLabel.centerYAnchor.constraint(equalTo: contentView.centerYAnchor, constant: -10),
            
            timeLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16),
            timeLabel.topAnchor.constraint(equalTo: titleLabel.bottomAnchor, constant: 4),
            
            switchControl.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -16),
            switchControl.centerYAnchor.constraint(equalTo: contentView.centerYAnchor)
        ])
    }
    
    func configure(with model: VPAutoMonitTestModel) {
        titleLabel.text = model.displayText
        timeLabel.text = "间隔: \(model.timeInterval)分钟"
        switchControl.isOn = model.on
    }
}

// MARK: - TableView DataSource & Delegate
extension VPAutoMonitSwitchVC: UITableViewDataSource, UITableViewDelegate {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return dataSource.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "AutoMonitCell", for: indexPath) as! AutoMonitSwitchCell
        let model = dataSource[indexPath.row]
        cell.configure(with: model)
        
        // 为Switch添加事件
        cell.switchControl.tag = indexPath.row
        cell.switchControl.addTarget(self, action: #selector(switchValueChanged(_:)), for: .valueChanged)
        
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        let model = dataSource[indexPath.row]
        if model.type == .lorentz {
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
    
    @objc private func switchValueChanged(_ sender: UISwitch) {
        let index = sender.tag
        let model = dataSource[index]
        model.on = sender.isOn
        
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSetAutoMonitSwitch(with: model) { [weak self] success, model in
            if success {
                self?.tableView.reloadRows(at: [IndexPath(row: index, section: 0)], with: .none)
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
        guard let indexPath = currentEditingIndex else { return }
        
        let model = dataSource[indexPath.row]
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
        }
    }
    
    var onStr: String {
        on ? "开启" : "关闭"
    }
}
