//
//  VPQX17PublicDefine.h
//  VeepooBleSDK
//
//  Created by vp_app_01 on 2026/4/17.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

// QX17 数据采集开启状态
typedef NS_ENUM(uint8_t, VPQX17DataAcqState) {
    VPQX17DataAcqStateOpening = 0x36,    // 开启
    VPQX17DataAcqStateClosed = 0x37,     // 关闭
};

// QX17 数据采集开启、继续采集、关闭结果
typedef NS_ENUM(uint8_t, VPQX17DataAcqSetResult) {
    VPQX17DataAcqSetResultBleConnectFail = 0x00,  // 失败，检测蓝牙连接异常
    VPQX17DataAcqSetSetResultFail = 0x01,         // 失败
    VPQX17DataAcqSetSetResultSucc = 0x02,         // 成功
};

// QX17 振动模式设置结果
typedef NS_ENUM(uint8_t, VPQX17VibrationModeSetResultCode) {
    VPQX17VibrationModeSetResultCodeBleConnectFail = 0x00,  // 失败，检测蓝牙连接异常
    VPQX17VibrationModeSetResultCodeDurationErr = 0x01,     // 失败，密码长度异常
    VPQX17VibrationModeSetResultCodeSucc = 0x02,            // 成功
};

// QX17 振动模式
typedef NS_ENUM(uint8_t, VPQX17VibrationMode) {
    VPQX17VibrationModeStart = 0x00,         // 开始
    VPQX17VibrationModeEnd = 0x01,           // 结束
    VPQX17VibrationModeNotify = 0x02,        // 通知
    VPQX17VibrationModeReminder = 0x03,      // 提醒
    VPQX17VibrationModeEnsure = 0x04,        // 确认
    VPQX17VibrationModeBeat = 0x05,          // 节拍
    VPQX17VibrationModeConnected = 0x06,     // 已连接
    VPQX17VibrationModeError = 0x07,         // 错误
};

