//
//  VPManualHealthGlanceModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/6/1.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

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
/// 收缩压
@property (nonatomic, assign) uint16_t h_bp;
/// 舒张压
@property (nonatomic, assign) uint16_t l_bp;
/// HRV
@property (nonatomic, assign) UInt8 hrv;
/// 情绪 [-10,10]
@property (nonatomic, assign) NSInteger emotionLevel;

@property (nonatomic, assign) NSInteger healthGlanceId;

@property (nonatomic, assign) NSInteger protocol;

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

@end

NS_ASSUME_NONNULL_END
