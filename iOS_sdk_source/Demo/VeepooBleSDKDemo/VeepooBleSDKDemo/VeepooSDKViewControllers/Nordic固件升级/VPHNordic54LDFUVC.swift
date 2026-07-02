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
        button.backgroundColor = .systemGray2
        button.isEnabled = false
        button.setTitleColor(.white, for: .normal)
        button.layer.cornerRadius = 6
        return button
    }()
    
    private let prepareButton: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("进入升级模式", for: .normal)
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
    
    private let testC11Button: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("C1110403", for: .normal)
        button.backgroundColor = .systemGray2
        button.isEnabled = false
        button.setTitleColor(.white, for: .normal)
        button.layer.cornerRadius = 6
        return button
    }()
    
    private let testC21Button: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("C2110403", for: .normal)
        button.backgroundColor = .systemGray2
        button.isEnabled = false
        button.setTitleColor(.white, for: .normal)
        button.layer.cornerRadius = 6
        return button
    }()
    
    private let testC31Button: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("C3110403", for: .normal)
        button.backgroundColor = .systemGray2
        button.isEnabled = false
        button.setTitleColor(.white, for: .normal)
        button.layer.cornerRadius = 6
        return button
    }()
    
    // MARK: - Properties
    private var isSupport: Bool {
        return VPBleCentralManage.sharedBleManager().peripheralModel.isSupportNordic
    }
    
    private var timer: Timer!
    
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
        view.addSubview(prepareButton)
        view.addSubview(otaButton)
        view.addSubview(stateLabel)
        view.addSubview(tipLabel)
        
        view.addSubview(testC11Button)
        view.addSubview(testC21Button)
        view.addSubview(testC31Button)
        setupConstraints()
    }
    
    private func setupConstraints() {
        let padding: CGFloat = 20
        let buttonWidth: CGFloat = 100
        let buttonHeight: CGFloat = 36
        
        titleLabel.frame = CGRect(x: padding, y: padding + 44, width: view.bounds.width - 2 * padding, height: 40)
        prepareButton.frame = CGRect(x: padding, y: titleLabel.frame.maxY + 20, width: buttonWidth, height: buttonHeight)
        otaButton.frame = CGRect(x: prepareButton.frame.maxX + 10, y: titleLabel.frame.maxY + 20, width: buttonWidth, height: buttonHeight)
        stateLabel.frame = CGRect(x: otaButton.frame.maxX + 15, y: otaButton.frame.minY, width: 180, height: buttonHeight)
        tipLabel.frame = CGRect(x: padding, y: otaButton.frame.maxY + 20, width: view.bounds.width - 2 * padding, height: 100)
        
        testC11Button.frame = CGRect(x: padding, y: tipLabel.frame.maxY + 20, width: buttonWidth, height: buttonHeight)
        testC21Button.frame = CGRect(x: testC11Button.frame.maxX + 10, y: tipLabel.frame.maxY + 20, width: buttonWidth, height: buttonHeight)
        testC31Button.frame = CGRect(x: testC21Button.frame.maxX + 10, y: tipLabel.frame.maxY + 20, width: buttonWidth, height: buttonHeight)
    }
    
    // MARK: - Configuration
    private func configureBasedOnLibraryAvailability() {
        #if canImport(iOSMcuManagerLibrary)
            // 库存在时的配置
            titleLabel.text = "是否支持Nordic升级: \(isSupport ? "支持" : "不支持")"
            otaButton.isHidden = !isSupport
            testC11Button.isHidden = !isSupport
            testC21Button.isHidden = !isSupport
            testC31Button.isHidden = !isSupport
            otaButton.addTarget(self, action: #selector(otaAction), for: .touchUpInside)
            testC11Button.addTarget(self, action: #selector(testC11Action), for: .touchUpInside)
            testC21Button.addTarget(self, action: #selector(testC21Action), for: .touchUpInside)
            testC31Button.addTarget(self, action: #selector(testC31Action), for: .touchUpInside)
        
            prepareButton.isHidden = !isSupport
            prepareButton.addTarget(self, action: #selector(prepareAction), for: .touchUpInside)
            
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
        startNordicOTA(fileName: "xxxx.bin")
    }
    
    @objc private func testC11Action() {
        startNordicOTA(fileName: "NM11_8600_C1110403_OTA_260618_09.bin")
    }
    
    @objc private func testC21Action() {
        startNordicOTA(fileName: "NM11_8600_C2110403_OTA_260618_09.bin")
    }
    
    @objc private func testC31Action() {
        startNordicOTA(fileName: "NM11_8600_C3110403_OTA_260618_09.bin")
    }
    
    @objc private func prepareAction() {
        /// 开启3秒定时,有的设备不支持进入升级模式响应
        self.timer = Timer.scheduledTimer(withTimeInterval: 3, repeats: false, block: {[weak self] timer in
            timer.invalidate()
            guard let self = self else { return }
            self.otaButton.isEnabled = true
            self.otaButton.backgroundColor = .systemBlue
            
            self.testC11Button.isEnabled = true
            self.testC11Button.backgroundColor = .systemBlue
            
            self.testC21Button.isEnabled = true
            self.testC21Button.backgroundColor = .systemBlue
            
            self.testC31Button.isEnabled = true
            self.testC31Button.backgroundColor = .systemBlue
        })
        /// 让设备进入升级模式
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDKSendUpdateFirmCommand {[weak self] in
            guard let self = self else { return }
            self.otaButton.isEnabled = true
            self.otaButton.backgroundColor = .systemBlue
            
            self.testC11Button.isEnabled = true
            self.testC11Button.backgroundColor = .systemBlue
            
            self.testC21Button.isEnabled = true
            self.testC21Button.backgroundColor = .systemBlue
            
            self.testC31Button.isEnabled = true
            self.testC31Button.backgroundColor = .systemBlue
            
            self.timer.invalidate()
            self.timer = nil
        }
    }
    
    // MARK: - OTA Methods
    private func startNordicOTA(fileName: String) {
        #if canImport(iOSMcuManagerLibrary)
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
