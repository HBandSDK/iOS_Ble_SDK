//
//  VPECGMultiLeadModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/11/1.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface VPECGMultiLeadBaseModel : NSObject

/// 内部响应包初始化方式
/// - Parameter rspData: 响应蓝牙数据
- (instancetype)initWithData:(NSData *)rspData;

@end

@interface VPECGMultiLeadProgressInfoModel : VPECGMultiLeadBaseModel

/// 6路导联状态
@property (nonatomic, assign) BOOL leadI;
@property (nonatomic, assign) BOOL leadII;
@property (nonatomic, assign) BOOL leadIII;
@property (nonatomic, assign) BOOL leadAVR;
@property (nonatomic, assign) BOOL leadAVL;
@property (nonatomic, assign) BOOL leadAVF;

// 每秒心率、qt、hrv
@property (nonatomic, assign) uint8_t heart;
@property (nonatomic, assign) uint16_t qt;
@property (nonatomic, assign) uint8_t hrv;

// 进度 0-100
@property (nonatomic, assign) uint8_t progress;

@end

@interface VPECGMultiLeadWaveFormModel : VPECGMultiLeadBaseModel

/// 导联类型
@property (nonatomic, assign) VPECGMultiLeadType leadType;

/// 该导联类型的波形返回数据，单位mv
@property (nonatomic, strong) NSArray<NSNumber *> *waveFormArr;

/// 转换成电压值的方法，转换后的电压单位为mv
/// - Parameter value: waveFormArr 数组元素
+ (CGFloat)convertToMvWithValue:(NSNumber *)value;

@end

@interface VPECGMultiLeadDiseaseInfoModel : VPECGMultiLeadBaseModel

/// 疾病类型 对应diseasesKindArr数组的顺序+1，即值为1表示房性早搏
@property (nonatomic, assign) uint8_t diseaseType;

/// 疾病出现的概率 0-100%
@property (nonatomic, assign) uint8_t diseaseProbability;

/// 疾病出现的次数
@property (nonatomic, assign) uint8_t diseaseTime;

/// 疾病的风险等级 0~5。0，1低风险，2，3中风险，4，5高风险
@property (nonatomic, assign) uint8_t diseaseRiskLevel;

/// 疾病在波形中出现位置坐标点的数组
@property (nonatomic, strong) NSArray<NSNumber *> *diseaseLocationsArr;

@end

@interface VPECGMultiLeadWaveformImageInfoModel : VPECGMultiLeadBaseModel

@property (nonatomic, assign) VPECGMultiLeadType leadType;

/// 当前通道数据 的波形数量
@property (nonatomic, assign) uint8_t waveformCount;

/// 保存当前通道数据每个波形的对应位置信息，每2字节为一个位置信息，小端
/// 具体为波形图像的横坐标数组长度为实际波形个数为一分钟最 大 250 次心率
@property (nonatomic, strong) NSArray<NSNumber *> *waveformPositionArr;

/// 当前通道数据每一个波形对应的类别。 具体为每一个波形的种类数组
/// 数组长度为实际波形个数为一分钟最大 250 次心率，波形类别可选项为[N,S,V,P,X]，分别为[0,4]映射
@property (nonatomic, strong) NSArray<NSNumber *> *waveformTypeArr;

@end

@interface VPECGMultiLeadDiagnosisResultModel : VPECGMultiLeadBaseModel

/// 平均心率，有效范围[30,250]，单位bpm
@property (nonatomic, assign) uint8_t aveHeart;

/// 平均QT，有效范围[100,1000]，单位ms
@property (nonatomic, assign) uint16_t aveQT;

/// 平均HRV，有效范围[0,210]，单位ms
@property (nonatomic, assign) uint8_t aveHRV;

/// 疾病种类出现的有无，定长数组27种疾病，值为1表示测量的波形中有该疾病，疾病排序如下:
/// [房性早搏、 房室节期前收缩、 1 型室性早搏、 2 型室性早搏 、 早期 1 型室性早搏 、 早期 2 型室性早搏 、 R on T 1 型室性早搏 、 R on T 2 型室性早搏 、
/// 多源性室性早搏 、 房颤——粗、 房颤——细 、 房扑、 房性心动过速、 阵发性心动过速、 室上性心动过速 、 窦性心律失常 、 漏博、 结性心率 、 二联律、
///  三联律、 心室颤动 、 停博、 I 度传导阻滞、 II 度传导阻滞、 III 度传导阻滞、 右束支传导阻滞、 左束支传导阻滞]
@property (nonatomic, strong) NSArray<NSNumber *> *diseasesKindArr;

/// 疾病详情数组
@property (nonatomic, strong) NSArray<VPECGMultiLeadDiseaseInfoModel *> *diseaseInfoModelArr;

/// 6路波形图像信息数组
@property (nonatomic, strong) NSArray<VPECGMultiLeadWaveformImageInfoModel *> *waveformImageInfoModelArr;

@end

NS_ASSUME_NONNULL_END
