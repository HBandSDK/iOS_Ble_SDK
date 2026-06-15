//
//  VPHNordic54LDFUVC.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2026/4/15.
//  Copyright © 2026 veepoo. All rights reserved.
//

import UIKit

#if canImport(iOSMcuManagerLibrary)
    import iOSMcuManagerLibrary
    typealias DFUManagerType = VPHNordic54LDFUManager
#else
    // 库不存在时，定义一个空的协议和类型
    protocol VPHNordic54LDFUManagerDelegate: AnyObject {}
    class VPHNordic54LDFUManager: NSObject {
        weak var delegate: VPHNordic54LDFUManagerDelegate?
        func setFileInfo(_ url: URL) {}
        func startOTA() {}
    }
    typealias DFUManagerType = VPHNordic54LDFUManager
#endif

class VPHNordic54LDFUVC: UIViewController {
    
    // MARK: - UI Components
    private let titleLabel: UILabel = {
        let label = UILabel()
        label.font = .systemFont(ofSize: 16)
        return label
    }()
    
    private let otaButton: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("固件升级", for: .normal)
        button.backgroundColor = .systemBlue
        button.setTitleColor(.white, for: .normal)
        button.layer.cornerRadius = 6
        return button
    }()
    
    private let stateLabel: UILabel = {
        let label = UILabel()
        label.font = .systemFont(ofSize: 14)
        label.textColor = .darkGray
        return label
    }()
    
    private let tipLabel: UILabel = {
        let label = UILabel()
        label.numberOfLines = 0
        label.font = .systemFont(ofSize: 12)
        label.textColor = .gray
        label.text = "固件升级流程，我们只提供固件传输方法，不提供检测是否可以升级和固件下载的方法，这需要使用者自行实现。"
        return label
    }()
    
    // MARK: - Properties
    private var isSupport: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupportNordic
    }
    
    private lazy var nordicDfuManager: DFUManagerType = {
        let manager = VPHNordic54LDFUManager()
        #if canImport(iOSMcuManagerLibrary)
            (manager as? VPHNordic54LDFUManager)?.delegate = self
        #endif
        return manager
    }()
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        configureBasedOnLibraryAvailability()
    }
    
    // MARK: - UI Setup
    private func setupUI() {
        title = "Nordic固件升级"
        view.backgroundColor = .white
        
        view.addSubview(titleLabel)
        view.addSubview(otaButton)
        view.addSubview(stateLabel)
        view.addSubview(tipLabel)
        
        setupConstraints()
    }
    
    private func setupConstraints() {
        let padding: CGFloat = 20
        let buttonWidth: CGFloat = 100
        let buttonHeight: CGFloat = 36
        
        titleLabel.frame = CGRect(x: padding, y: padding + 44, width: view.bounds.width - 2 * padding, height: 40)
        otaButton.frame = CGRect(x: padding, y: titleLabel.frame.maxY + 20, width: buttonWidth, height: buttonHeight)
        stateLabel.frame = CGRect(x: otaButton.frame.maxX + 15, y: otaButton.frame.minY, width: 180, height: buttonHeight)
        tipLabel.frame = CGRect(x: padding, y: otaButton.frame.maxY + 20, width: view.bounds.width - 2 * padding, height: 100)
    }
    
    // MARK: - Configuration
    private func configureBasedOnLibraryAvailability() {
        #if canImport(iOSMcuManagerLibrary)
            // 库存在时的配置
            titleLabel.text = "是否支持Nordic升级: \(isSupport ? "支持" : "不支持")"
            otaButton.isHidden = !isSupport
            otaButton.addTarget(self, action: #selector(otaAction), for: .touchUpInside)
            stateLabel.isHidden = false
        #else
            // 库不存在时的配置
            titleLabel.text = "请先通过 pod 安装 iOSMcuManagerLibrary"
            titleLabel.textColor = .red
            otaButton.isHidden = true
            stateLabel.isHidden = true
            tipLabel.isHidden = true
        #endif
    }
    
    // MARK: - Actions
    @objc private func otaAction() {
        startNordicOTA()
    }
    
    // MARK: - OTA Methods
    private func startNordicOTA() {
        #if canImport(iOSMcuManagerLibrary)
            let fileName = "xxxx.bin"
            guard let filePath = Bundle.main.path(forResource: fileName, ofType: nil) else {
                stateLabel.text = "没找到升级固件"
                return
            }
            let fileURL = URL(fileURLWithPath: filePath)
            nordicDfuManager.setFileInfo(fileURL)
            nordicDfuManager.startOTA()
        #else
            // 库不存在时的提示
            let alert = UIAlertController(
                title: "功能不可用",
                message: "请先通过 pod 安装 iOSMcuManagerLibrary",
                preferredStyle: .alert
            )
            alert.addAction(UIAlertAction(title: "确定", style: .default))
            present(alert, animated: true)
        #endif
    }
}

// MARK: - Delegate Extension
#if canImport(iOSMcuManagerLibrary)
extension VPHNordic54LDFUVC: VPHNordic54LDFUManagerDelegate {
    
    func nordicOtaDidStart() {
        print("nordicOtaDidStart")
        stateLabel.text = "Start"
    }
    
    func nordicOtaStateDidChange(from previousState: String, to newState: String) {
        print("nordicOtaStateDidChange from: \(previousState) to: \(newState)")
        stateLabel.text = newState
    }
    
    func nordicOtaDidComplete() {
        print("nordicOtaDidComplete")
        stateLabel.text = "Complete"
    }
    
    func nordicOtaDidFail(inState state: String, error: NSError) {
        print("nordicOtaDidFail in state: \(state), error: \(error)")
        stateLabel.text = "Fail: \(error.localizedDescription)"
    }
    
    func nordicOtaUploadProgress(bytesSent: Int, imageSize: Int, progress: Float) {
        print("nordicOtaUploadProgress: \(progress)")
        stateLabel.text = "Progress: \(Int(progress * 100))%"
    }
}
#endif
