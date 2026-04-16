import Foundation
import CoreBluetooth
import iOSMcuManagerLibrary

@objc public protocol VPHNordic54LDFUManagerDelegate {
    func nordicOtaDidStart()
    func nordicOtaStateDidChange(from previousState: String, to newState: String)
    func nordicOtaDidComplete()
    func nordicOtaDidFail(inState state: String, error: NSError)
    func nordicOtaUploadProgress(bytesSent: Int, imageSize: Int, progress: Float)
    @objc optional func nordicOtaDidCancel(state: String)
}

@objcMembers
public class VPHNordic54LDFUManager: NSObject, FirmwareUpgradeDelegate {
    public weak var delegate: VPHNordic54LDFUManagerDelegate?

    private var transporter: McuMgrTransport?
    private var dfuManager: FirmwareUpgradeManager?
    private var package: McuMgrPackage?

    public override init() {
        super.init()
    }

    public func setFileInfo(_ fileURL: URL) {
        let ext = fileURL.pathExtension.lowercased()
        guard ext == "zip" || ext == "hex" || ext == "bin" else {
            return
        }
        do {
            package = try .init(from: fileURL)
        } catch {
            package = nil
        }
    }

    public func setupWithPeripheral(_ peripheral: CBPeripheral) {
        transporter = McuMgrBleTransport(peripheral)
        dfuManager = FirmwareUpgradeManager(transport: transporter!, delegate: self)
    }

    public func clear() {
        dfuManager = nil
        transporter = nil
    }
    
    public func enterDfu() {
//        let model: PeripherModel = AppDelegate.shared().connectPeriperModel
//        UserDefaults.standard.setValue(model.bleAddress, forKey: VPHStoreDfuPeriphera)
//        UserDefaults.standard.setValue(model.peripheral?.identifier.uuidString, forKey: VPHStoreDfuPeripheraUUID)
//        UserDefaults.standard.synchronize()
    }

    public func startOTA() {
        if dfuManager == nil {
            if let model: VPPeripheralModel = VPBleCentralManage.sharedBleManager().peripheralModel {
                if let peripheral = model.peripheral {
                    setupWithPeripheral(peripheral)
                }
            }
            
            
        }
        guard let dfuManager = dfuManager, let package = package else { return }
        do {
            try dfuManager.start(package: package)
        } catch {
        }
    }

    public func upgradeDidStart(controller: any FirmwareUpgradeController) {
        delegate?.nordicOtaDidStart()
    }

    public func upgradeStateDidChange(from previousState: FirmwareUpgradeState, to newState: FirmwareUpgradeState) {
        delegate?.nordicOtaStateDidChange(from: String(describing: previousState), to: String(describing: newState))
    }

    public func upgradeDidComplete() {
        delegate?.nordicOtaDidComplete()
    }

    public func upgradeDidFail(inState state: FirmwareUpgradeState, with error: any Error) {
        delegate?.nordicOtaDidFail(inState: String(describing: state), error: error as NSError)
    }

    public func upgradeDidCancel(state: FirmwareUpgradeState) {
        delegate?.nordicOtaDidCancel?(state: String(describing: state))
    }

    public func uploadProgressDidChange(bytesSent: Int, imageSize: Int, timestamp: Date) {
        let progress = imageSize > 0 ? Float(bytesSent) / Float(imageSize) : 0
        delegate?.nordicOtaUploadProgress(bytesSent: bytesSent, imageSize: imageSize, progress: progress)
    }
}
