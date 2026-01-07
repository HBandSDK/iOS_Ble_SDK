//
//  VPAIViewController.swift
//  VeepooBleSDKDemo
//
//  Created by fengye on 2025/12/31.
//  Copyright © 2025 veepoo. All rights reserved.
//
//AI问答的流程：设备开启AI问答，说出一个问题设备会录音，录音结束后，App会收到录音文件opusData，App需要把Opus 转成 PCM 语音文件，得到的语音文件通过第三方AI转成文字发送到设备，同时通过第三方AI得到问题的答案再发到设备。SDK只提供跟设备的交互，不提供第三方AI，请自行集成。
//AI表盘的流程：设备开启AI问答，说出一个问题设备会录音，录音结束后，App会收到录音文件opusData，App需要把Opus 转成 PCM 语音文件，得到的语音文件通过第三方AI转成文字发送到设备，设备上选择生成图片，App会收到生成图片的通过，通过第三方AI把文字生成图片后发送图片到设备，设备上可以选择是否设置成表盘，如果选择设置表盘，App会收到通知后会把图片设置成设备的图片表盘。SDK只提供跟设备的交互，不提供第三方AI，请自行集成第三方AI。
import UIKit

class VPAIViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        setupSubView()
//        setOpusData()
        // Do any additional setup after loading the view.
    }
    
    var isSupAI: Bool {
        return (VPBleCentralManage.sharedBleManager().peripheralModel.aiChatType != 0 || VPBleCentralManage.sharedBleManager().peripheralModel.aiDialType != 0) ? true : false
    }
    
    private func setupSubView() {
        view.backgroundColor = .white
        let suplab = UILabel(frame: CGRect(x: 30, y: 30, width: 120, height: 40))
        view.addSubview(suplab)
        suplab.text = "是否支持:" + (self.isSupAI ? "是" : "否")
        if self.isSupAI {
            let btn = UIButton(frame: CGRect(x: 50, y: 90, width: 160, height: 45))
            btn.setTitle("开始监听AI信息", for: .normal)
            btn.backgroundColor = .orange
            view.addSubview(btn)
            btn.addTarget(self, action: #selector(setOpusData), for: .touchUpInside)
        }
    }
    //MARK: 接收 AI 相关事件
    @objc func setOpusData() {
        //设置当前网络情况
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncAINetworkStatus(.reachableViaWiFi)
        // 监听 opus 数据通道 语言问答数据流
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncOpusDataSubscribe {[weak self] type, opusData in
            if type == .deviceAIChatUsing {//AI问答
                self?.handleAnswer(questionData: opusData!)
            } else if type == .deviceAIDialUsing {//AI表盘
                self?.handleAnswerGenerateImage(questionData: opusData!)
            }
        }
        // 监听收到再次回答
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncReceiveAnswerAgainSubscribe {[weak self] text in
            print("重新获取回答\(text!)")
            self?.handleReplyAnswerToDevice(result: "再次发送AI得出的结论")
        }
        
        // AI表盘 收到了设备再次获取图片
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncCanGetImageActionSubscribe { string, style in
            print("收到了设备再次获取图片:\(string)\(style)")
            let img = UIImage(named: "test_390_450") // 这是测试图片,正常要是AI生成的图片需自行集成AI实现
            if let pngData = UIImagePNGRepresentation(img!) {
                VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncSendImageData(pngData)
            }
        }
        
        // AI表盘 收到了设备设置表盘
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncImageTransformResultSubscribe { [weak self] start, success, image in
            if start {
                print("开始传输")
            } else {
                if success {
                    print("传输完成")
                }
            }
        }
    }
    
    private func handleAnswerGenerateImage(questionData: Data) {
        VPOpusHandle.shareInstance().decodeOpusData(toPcmData: questionData, andSaveFile: true) {[weak self] isSuccess, filePath, fileData in
            if isSuccess {
                print("Opus 转 PCM 语音文件结果成功")
                // 得到Pcm 文件通过第三方实现语音转文本,然后把识别到文本发送给设备.同时调用AI第三方进行分析.分析的结果再发送给设备
                self?.handleReplySpeechRecognition(text: "发送语音识别的文字")
            } else {
                print("Opus 转 PCM 语音文件结果失败")
            }
        }
    }
    
    private func handleAnswer(questionData: Data) {
        VPOpusHandle.shareInstance().decodeOpusData(toPcmData: questionData, andSaveFile: true) {[weak self] isSuccess, filePath, fileData in
            if isSuccess {
                print("Opus 转 PCM 语音文件结果成功")
                // 得到Pcm 文件通过第三方实现语音转文本,然后把识别到文本发送给设备.同时调用AI第三方进行分析.分析的结果再发送给设备
                self?.handleReplySpeechRecognition(text: "发送语音识别的文字")
                Timer.scheduledTimer(withTimeInterval: 2, repeats: false) {[weak self] timer in
                    self?.handleReplyAnswerToDevice(result: "发送AI得出的结论")
                }
            } else {
                print("Opus 转 PCM 语音文件结果失败")
            }
        }
    }
    
    private func handleReplySpeechRecognition(text: String) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncSendSpeechConvert(withTextResult: text)
    }
    //发送AI响应答案
    private func handleReplyAnswerToDevice(result: String) {
        VPBleCentralManage.sharedBleManager().peripheralManage.veepooSDK_aiFuncSendChatAnswer(withTextResult: result)
    }

}
