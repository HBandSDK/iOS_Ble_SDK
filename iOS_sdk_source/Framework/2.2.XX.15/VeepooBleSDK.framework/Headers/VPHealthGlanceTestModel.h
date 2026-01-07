//
//  VPHealthGlanceTestModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2025/11/24.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"
NS_ASSUME_NONNULL_BEGIN

@interface VPHealthGlanceTestModel : NSObject
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
/// 血糖类型
@property (nonatomic, assign) UInt8 bloodSugarType;
/// 血糖等级
@property (nonatomic, assign) UInt8 bloodSugarLevel;
/// 体温
@property (nonatomic, assign) double bodyTemperature;
/// 原始体温
@property (nonatomic, assign) double orgTemperature;
/// 血压(收缩压)
@property (nonatomic, assign) UInt8 systolicBloodPressure;
/// 血压(舒缩压)
@property (nonatomic, assign) UInt8 diastolicBloodPressure;
/// HRV
@property (nonatomic, assign) UInt8 hrv;
/// 光电血压 高
@property (nonatomic, assign) UInt8 ppgBloodPressureHigh;
/// 光电血压 低
@property (nonatomic, assign) UInt8 ppgBloodPressureLow;
/// 气泵血压 高
@property (nonatomic, assign) UInt8 cuffBloodPressureHigh;
/// 气泵血压 低
@property (nonatomic, assign) UInt8 cuffBloodPressureLow;
/// 总胆固醇，两位小数点
@property (nonatomic, assign) double totalCholesterol;
/// 甘油三酯，两位小数点
@property (nonatomic, assign) double triglyceride;
/// 高密度脂蛋白，两位小数点
@property (nonatomic, assign) double highDensityLipoprotein;
/// 低密度脂蛋白，两位小数点
@property (nonatomic, assign) double lowDensityLipoprotein;
/// 尿酸值，一位小数点
@property (nonatomic, assign) double uricAcid;
/// 支持哪些功能
@property (nonatomic, assign) NSUInteger functionSupport;
/// 体重 kg
@property (nonatomic, assign) UInt8 weight;
/// 身高 cm
@property (nonatomic, assign) UInt8 height;
/// 年龄
@property (nonatomic, assign) UInt8 age;
/// 性别，0女，1男
@property (nonatomic, assign) UInt8 gender;
/// BMI
@property (nonatomic, assign) double bmi;
/// 体脂率 百分比
@property (nonatomic, assign) double bodyFatPercentage;
/// 脂肪量 单位kg
@property (nonatomic, assign) double fatMass;
/// 去脂体重 单位kg
@property (nonatomic, assign) double leanBodyMass;
/// 肌肉率 百分比
@property (nonatomic, assign) double muscleRate;
/// 肌肉量 单位kg
@property (nonatomic, assign) double muscleMass;
/// 皮下脂肪 百分比
@property (nonatomic, assign) double subcutaneousFat;
/// 体内水分 百分比
@property (nonatomic, assign) double bodyMoisture;
/// 含水量 单位kg
@property (nonatomic, assign) double waterContent;
/// 骨骼肌率 百分比
@property (nonatomic, assign) double skeletalMuscleRate;
/// 骨量 单位kg
@property (nonatomic, assign) double boneMass;
/// 蛋白质占比 百分比
@property (nonatomic, assign) double proportionOfProtein;
/// 蛋白质量 单位kg
@property (nonatomic, assign) double proteinAmount;
/// 基础代谢率 kcal
@property (nonatomic, assign) double basalMetabolicRate;
/// 情绪 [-10,10]
@property (nonatomic, assign) NSInteger emotionLevel;
/// 皮肤含水量 [1,99]
@property (nonatomic, assign) UInt8 skinMoisture;
/// 抑郁症风险 [0,2] 0:低风险 1:中风险 2:高风险
@property (nonatomic, assign) UInt8 depressionRisk;
/// 交感神经活跃度 [1,99]
@property (nonatomic, assign) UInt8 snsActivation;
/// 皮质醇浓度，有效范围 [0,500]ug/L
@property (nonatomic, assign) UInt16 cortisolValue;

- (void)parseHealthGlanceData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
