//
//  VPAutoMonitTestModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2025/3/4.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, VPAutoMonitTestType) {
    VPAutoMonitTestTypeHeartRate = 0x00,    // 脉率
    VPAutoMonitTestTypeBloodPressure,       // 血压
    VPAutoMonitTestTypeBloodGlucose,        // 血糖
    VPAutoMonitTestTypeStress,              // 压力
    VPAutoMonitTestTypeBloodOxygen,         // 血氧
    VPAutoMonitTestTypeBodyTemperature,     // 体温
    VPAutoMonitTestTypeLorentz,             // 洛伦兹
    VPAutoMonitTestTypeHRV,                 // HRV
    VPAutoMonitTestTypeBloodComponents      // 血液成分
};

/// 自动测量模型
@interface VPAutoMonitTestModel : NSObject

/// 数据类型
@property (nonatomic, assign, readonly) VPAutoMonitTestType type;

/// 是否开启
@property (nonatomic, assign) BOOL on;

/// 最小的步进
@property (nonatomic, assign, readonly) uint16_t minStepValue;

/// 是否支持时间范围调整
@property (nonatomic, assign, readonly) BOOL supportRangeTime;

/// 开始时间参考
@property (nonatomic, assign, readonly) uint8_t startHourRef;
@property (nonatomic, assign, readonly) uint8_t startMinuteRef;
/// 结束时间参考
@property (nonatomic, assign, readonly) uint8_t endHourRef;
@property (nonatomic, assign, readonly) uint8_t endMinuteRef;

/// 当前的测量时间间隔，分钟
@property (nonatomic, assign) uint16_t timeInterval;

/// 当前的开始测量时间
@property (nonatomic, assign) uint8_t startHour;
@property (nonatomic, assign) uint8_t startMinute;
/// 当前的结束测量时间
@property (nonatomic, assign) uint8_t endHour;
@property (nonatomic, assign) uint8_t endMinute;

#pragma mark - 内部函数

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

- (NSData *)getDataWithPageSize:(NSInteger)pageSize;

@end

NS_ASSUME_NONNULL_END
