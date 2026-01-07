//
//  VPDeviceSportControlModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2025/7/9.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VPSportControlProtocolCommandType) {
    VPSportControlProtocolCommandTypeSetting = 0x01,
    VPSportControlProtocolCommandTypeReading = 0x02,
    VPSportControlProtocolCommandTypeReporting = 0x03
};

typedef NS_ENUM(NSInteger, VPSportControlProtocolAckType) {
    VPSportControlProtocolAckTypeFailure = 0x00,
    VPSportControlProtocolAckTypeSuccess = 0x01
};

typedef NS_ENUM(NSInteger, VPSportControlProtocolSportMode) {
    VPSportControlProtocolSportModeApp = 0x00,
    // 其他值对应设备的运动模式
};

typedef NS_ENUM(NSInteger, VPSportControlRunState) {
    VPSportControlRunStateNotStarted = 0x00,
    VPSportControlRunStateRunning = 0x01,
    VPSportControlRunStatePaused = 0x02
};

typedef NS_ENUM(NSInteger, VPSportControlDeviceState) {
    VPSportControlDeviceStateNormal = 0x00,
    VPSportControlDeviceStateLowBattery = 0x01,
    VPSportControlDeviceStateCharging = 0x02,
    VPSportControlDeviceStateMaxDurationReached = 0x03,
    VPSportControlDeviceStateBatteryBelow10Percent = 0x04
};

@interface VPDeviceSportControlModel : NSObject

// 运动模式
@property (nonatomic, assign) VPSportControlProtocolSportMode sportMode;
// 操作码
@property (nonatomic, assign) NSInteger operationCode;
// 运动状态
@property (nonatomic, assign) VPSportControlRunState runState;
// 设备状态
@property (nonatomic, assign) VPSportControlDeviceState deviceState;
// 运动时间(秒)
@property (nonatomic, assign) uint32_t duration;
// 运动距离
@property (nonatomic, assign) uint32_t distance;
// 心率值
@property (nonatomic, assign) uint8_t heartRate;
// 卡路里
@property (nonatomic, assign) uint32_t calories;
// 配速
@property (nonatomic, assign) uint16_t pace;
// 速度
@property (nonatomic, assign) uint16_t speed;

@end

NS_ASSUME_NONNULL_END
