//
//  VPECGMultiLeadBLEDelegate.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/11/1.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class
VPECGMultiLeadProgressInfoModel,
VPECGMultiLeadWaveFormModel,
VPECGMultiLeadDiagnosisResultModel;
/// 多导心电蓝牙数据代理
@protocol VPECGMultiLeadBLEDelegate <NSObject>

@required

/// 每秒进度信息响应触发
/// - Parameter infoModel: 进度信息
- (void)VPECGMultiLeadDidResponseProgressInfo:(VPECGMultiLeadProgressInfoModel *)infoModel;

/// 每秒波形信号响应触发
/// - Parameter waveFormModel: 每秒波形返回，波形值转电压方法可以用[VPECGMultiLeadWaveFormModel convertToMvWithValue:]
- (void)VPECGMultiLeadDidResponseWaveFormData:(VPECGMultiLeadWaveFormModel *)waveFormModel;

/// 最终诊断结果响应，仅测量成果并且解析成果才会触发，接口受限
/// - Parameter diagnosisResultModel: 诊断结果model
- (void)VPECGMultiLeadDidResponseDiagnosisResult:(VPECGMultiLeadDiagnosisResultModel *)diagnosisResultModel;

/// 测量成功并且波形返回结束(APP可以以此作为存储入库的时机)
- (void)VPECGMultiLeadDidResponseSuccess;

@optional

/// 开启测量时触发，返回前置信息
/// - Parameters:
///   - frequency: 频率，固定250
///   - leads: 多少个导联，固定6
- (void)VPECGMultiLeadDidResponsePreInfoFrequency:(uint16_t)frequency leads:(uint8_t)leads;

/// 指令响应了关闭测量时触发
- (void)VPECGMultiLeadDidResponseEndTest;

/// 测量失败时触发
- (void)VPECGMultiLeadTestFailure;

@end

NS_ASSUME_NONNULL_END
