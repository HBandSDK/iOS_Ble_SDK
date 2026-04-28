//
//  VPQX17IMUModel.h
//  VeepooBleSDK
//
//  Created by vp_app_01 on 2026/4/17.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

// 加速度计结构体，用于存储传感器数据
typedef struct {
    int16_t ax; // 加速度计 x 轴
    int16_t ay; // 加速度计 y 轴
    int16_t az; // 加速度计 z 轴
} AccelerometerData;

// 陀螺仪结构体，用于存储传感器数据
typedef struct {
    int16_t gx; // 陀螺仪 x 轴
    int16_t gy; // 陀螺仪 y 轴
    int16_t gz; // 陀螺仪 z 轴
} GyroscopeData;

// 磁力计结构体，用于存储传感器数据
typedef struct {
    int16_t mx; // 磁力计 x 轴
    int16_t my; // 磁力计 y 轴
    int16_t mz; // 磁力计 z 轴
} MagnetometerData;


@interface VPQX17IMUModel : NSObject
/// 加速度计数据
@property (nonatomic, readonly) AccelerometerData accelerometer;
/// 陀螺仪数据
@property (nonatomic, readonly) GyroscopeData gyroscope;
/// 磁力计数据
@property (nonatomic, readonly) MagnetometerData magnetometer;
/// 时间戳（毫秒）
@property (nonatomic, readonly) uint32_t timestamp;

// 方法声明
- (instancetype)initWithData:(NSData *)data;

@end

