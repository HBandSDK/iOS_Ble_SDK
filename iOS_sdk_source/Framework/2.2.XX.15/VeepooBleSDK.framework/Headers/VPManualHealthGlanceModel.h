//
//  VPManualHealthGlanceModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/6/1.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPManualHGBodyComModel.h"
#import "VPPublicDefine.h"
NS_ASSUME_NONNULL_BEGIN

@interface VPManualHealthGlanceModel : NSObject
// 测量时间戳
@property (nonatomic, assign) uint32_t timestamp;
/// 心率
@property (nonatomic, assign) UInt8 heartRate;
/// 血氧
@property (nonatomic, assign) UInt8 bloodOxygen;
/// 压力
@property (nonatomic, assign) UInt8 stress;
/// 疲劳度
@property (nonatomic, assign) UInt8 fatigueLevel;
/// 血糖
@property (nonatomic, assign) double bloodSugar;
// 是否有血糖风险等级
@property (nonatomic, assign) BOOL haveLevel;
// 血糖风险等级 (1,2,3 低 中 高)
@property (nonatomic, assign) uint8_t bloodSugarLevel;
/// 体温
@property (nonatomic, assign) double bodyTemperature;
/// 原始体温
@property (nonatomic, assign) double orgTemperature;
/// 光电血压 收缩压
@property (nonatomic, assign) uint16_t h_bp;
/// 光电血压 舒张压
@property (nonatomic, assign) uint16_t l_bp;
/// HRV
@property (nonatomic, assign) UInt8 hrv;
/// 情绪 [-10,10]
@property (nonatomic, assign) NSInteger emotionLevel;

@property (nonatomic, assign) NSInteger healthGlanceId;

@property (nonatomic, assign) NSInteger protocol;
/// protocol == 1 或者 0 默认支持上面这些功能, 也可以通过VPHealthGlanceType判断,healthGlanceId 只有在 protocol == 1才有值,其他默认0
/// 支持哪些功能, 只有protocol == 2 时才会有以下数据 根据VPHealthGlanceType 判断是否有功能再显示例如: functionSupport & VPHealthGlanceTypeBloodComp != 0 支持血液成分功能, 心率 血糖 体温 HRV 情绪...也是要判断
@property (nonatomic, assign) NSUInteger functionSupport;

//血液成分
/// 总胆固醇
@property (nonatomic, assign) double totalCholesterol;
/// 甘油三酯
@property (nonatomic, assign) double triglyceride;
/// 高密度脂蛋白
@property (nonatomic, assign) double highDensityLipoprotein;
/// 低密度脂蛋白
@property (nonatomic, assign) double lowDensityLipoprotein;
/// 尿酸值
@property (nonatomic, assign) double uricAcid;

// 气泵血压
/// 气泵血压 高
@property (nonatomic, assign) UInt8 cuffBloodPressureHigh;
/// 气泵血压 低
@property (nonatomic, assign) UInt8 cuffBloodPressureLow;

/// 身体成分(目前项目都不支持)
@property (nonatomic, strong) VPManualHGBodyComModel *bodyComModel;

// 基础信息(包含,不需要判断)
/// 体重 kg
@property (nonatomic, assign) UInt8 weight;
/// 身高 cm
@property (nonatomic, assign) UInt8 height;
/// 年龄
@property (nonatomic, assign) UInt8 age;
/// 性别，0女，1男
@property (nonatomic, assign) UInt8 gender;

// 皮电
/// 皮肤含水量 [1,99]
@property (nonatomic, assign) UInt8 skinMoisture;
/// 抑郁症风险 [0,2] 0:低风险 1:中风险 2:高风险
@property (nonatomic, assign) UInt8 depressionRisk;
/// 交感神经活跃度 [1,99]
@property (nonatomic, assign) UInt8 snsActivation;
/// 皮质醇浓度，有效范围 [0,500]ug/L
@property (nonatomic, assign) UInt16 cortisolValue;

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

- (BOOL)getFuncSupport:(VPHealthGlanceType)type;

@end

NS_ASSUME_NONNULL_END
