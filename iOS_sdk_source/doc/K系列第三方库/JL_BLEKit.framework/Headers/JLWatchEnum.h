//
//  JLWatchEnum.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/2.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *_Nonnull const  JL_Watch_HeartRate;
extern NSString *_Nonnull const  JL_Watch_AirPressure;
extern NSString *_Nonnull const  JL_Watch_Altitude;
extern NSString *_Nonnull const  JL_Watch_MoveSteps;
extern NSString *_Nonnull const  JL_Watch_Stress;
extern NSString *_Nonnull const  JL_Watch_Oxsaturation;
extern NSString *_Nonnull const  JL_Watch_MaxOxg;
extern NSString *_Nonnull const  JL_Watch_RecTime;
extern NSString *_Nonnull const  JL_Watch_SportMsg;
extern NSString *_Nonnull const  JL_Watch_WatchLog;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_WATCH_LOG_MASK) {
    /// 加速度
    JL_WATCH_LOG_MASK_Acceleration = 0x80000000 >> 31,
    /// 心率和血氧
    JL_WATCH_LOG_MASK_HeartRate_BloodOxy = 0x80000000 >> 30,
};

typedef NS_ENUM(UInt8, JL_WATCH_LOG_TYPE) {
    ///设备回的加速度
    JL_WATCH_LOG_TYPE_Res_Acceleration = 0x00,
    /// 设备回的心率血氧
    JL_WATCH_LOG_TYPE_Res_HeartRate_BloodOxy = 0x01,
};

/// 运动记录标记包类型
typedef NS_ENUM(UInt8, JL_SRMDataType) {
    ///开始包
    JL_SRM_Start = 0x00,
    ///基础包
    JL_SRM_Basic = 0x01,
    ///暂停包
    JL_SRM_Pause = 0x02,
    ///每公里配速包
    JL_SRM_Pace = 0x03,
    ///结束包
    JL_SRM_End = 0xff,
};

// 运动数据类型
typedef NS_ENUM(UInt8, JL_SportDataType) {
    ///心率
    JL_SportDataTypeHeartRate           = 0,
    ///空气压强
    JL_SportDataTypeAirPressure         = 1,
    ///海拔高度
    JL_SportDataTypeAltitude            = 2,
    ///运动步数
    JL_SportDataTypeMovementSteps       = 3,
    ///压力
    JL_SportDataTypeStress              = 4,
    ///血氧饱和度
    JL_SportDataTypeOxygenSaturation    = 5,
    ///训练负荷
    JL_SportDataTypeTrainingLoad        = 6,
    ///最大摄氧量
    JL_SportDataTypeMaxOxygenUptake     = 7,
    ///运动恢复时间
    JL_SportDataTypeRecoveryTime        = 8,
    ///运动信息
    JL_SportDataTypeSportMessage        = 9,
};

// 运动模式
typedef NS_ENUM(UInt8, JL_SportPattern) {
    JL_SportPatternRun          = 0,    ///跑步
    JL_SportPatternClimb        = 1,    ///爬山
    JL_SportPatternSwim         = 2,    ///游泳
};

// 运动数据格式
typedef NS_ENUM(UInt8, JL_SportDataFormat) {
    JL_SportDataFormatBeUint8                 = 1,
    JL_SportDataFormatBeBigendUint16          = 2,
    JL_SportDataFormatBeBigendUint32          = 4,
};

typedef NS_ENUM(UInt8, JL_WATCH_SETTING_MASK) {
    JL_WATCH_SETTING_MASK_READ_INFO         = 0x00,///App读取设备信息
    JL_WATCH_SETTING_MASK_SET_INFO          = 0x01,///向设备写入设置信 息
    JL_WATCH_SETTING_MASK_RECIVE_INFO       = 0x02,///收到设备推送设置信息
};

/// 查询读取设备信息
///使用示例：
/// 如查询：传感器、连续测量心率、跌到监察
/// 则对应的uint32_t 为：0x0000008A
/// 即对应的Bit位指示为：0000 0000 0000 0000 0000 0000 1000 1010
/// Bit0：保留（考虑是否用于做功能支持位）------ 0
/// Bit1：传感器功能
/// Bit2：久坐提醒
/// Bit3：连续测量心率
/// Bit4：运动心率提醒
/// Bit5：压力自动检测
/// Bit6：睡眠检测
/// Bit7：跌到监察
/// Bit8：抬腕监察
/// Bit9：个人信息
/// Bit10：蓝牙断开提醒
typedef NS_ENUM(uint32_t, JL_WATCH_SETTING) {
    JL_WATCH_SETTING_SENSOR_FUNC                        = 0x0002,     // Bit1：传感器功能
    JL_WATCH_SETTING_SEDENTARY_REMIND                   = 0x0004,     // Bit2：久坐提醒
    JL_WATCH_SETTING_CONTINUOUS_HEARTRATE_MEASUREMENT   = 0x0008,     // Bit3：连续测量心率
    JL_WATCH_SETTING_EXERCISE_HEARTRATE_REMINDER        = 0x0010,     // Bit4：运动心率提醒
    JL_WATCH_SETTING_AUTOMATIC_PRESSURE_DETECTION       = 0x0020,     // Bit5：压力自动检测
    JL_WATCH_SETTING_SLEEP_DETECTION                    = 0x0040,     // Bit6：睡眠检测
    JL_WATCH_SETTING_FALL_DETECTION                     = 0x0080,     // Bit7：跌到监察
    JL_WATCH_SETTING_LIFTWRIST_DETECTION                = 0x0100,     // Bit8：抬腕监察
    JL_WATCH_SETTING_PERSONAL_INFO                      = 0x0200,     // Bit9：个人信息
    JL_WATCH_SETTING_BLUETOOTH_DISCONECTED_REMINDER     = 0x0400,     // Bit10：蓝牙断开提醒
};

/// 传感器功能开关
/// ///使用示例：
/// 如设置打开：计步器、计步器记录、血氧、血氧记录、海拔
/// 则对应的uint16_t 为：0x73
/// 即对应的Bit位指示为： 0111 0011
/// Bit0：计步器开关
/// Bit1：计步器记录开关
/// Bit2：心率传感器开关
/// Bit3：心率传感器记录开关
/// Bit4：血氧传感器开关
/// Bit5：血氧传感器记录开关
/// Bit6：海拔气压传感器开关
/// Bit7：海拔气压传感器记录开关
typedef NS_ENUM(uint16_t, JL_SENSOR_FUNC_SWITCH) {
    JL_SENSOR_FUNC_SWITCH_PEDOMETER                     = 0x01,     // Bit0：计步器开关
    JL_SENSOR_FUNC_SWITCH_PEDOMETER_RECORD              = 0x02,     // Bit1：计步器记录开关
    JL_SENSOR_FUNC_SWITCH_HEARTRATE                     = 0x04,     // Bit2：心率传感器开关
    JL_SENSOR_FUNC_SWITCH_HEARTRATE_RECORD              = 0x08,     // Bit3：心率传感器记录开关
    JL_SENSOR_FUNC_SWITCH_BLOODOXYGEN                   = 0x10,     // Bit4：血氧传感器开关
    JL_SENSOR_FUNC_SWITCH_BLOODOXYGEN_RECORD            = 0x20,     // Bit5：血氧传感器记录开关
    JL_SENSOR_FUNC_SWITCH_ALTITUDE_AIRPRESSURE          = 0x40,     // Bit6：海拔气压传感器开关
    JL_SENSOR_FUNC_SWITCH_ALTITUDE_AIRPRESSURE_RECORD   = 0x80,     // Bit7：海拔气压传感器记录开关
};

///运动状态同步相关命令
typedef NS_ENUM(UInt8, JL_WearSyncStatus) {
    /// 读取运动信息
    JL_WearSyncStatus_ReadInfo              = 0x00,
    /// 开始运动
    JL_WearSyncStatus_Start                 = 0x01,
    /// APP结束运动
    JL_WearSyncStatus_EndByApp              = 0x02,
    /// 固件结束运动
    JL_WearSyncStatus_EndByDevice           = 0x03,
    /// 暂停运动
    JL_WearSyncStatus_Pause                 = 0x04,
    /// 继续运动
    JL_WearSyncStatus_Continue              = 0x05,
    /// 请求运动实时数据
    JL_WearSyncStatus_RealTimeInfoRequire   = 0x06,
};

///运动模式类型
typedef NS_ENUM(UInt8, WatchSportType) {
    /// 非运动模式
    WatchSportType_NonExercise       = 0x00,
    /// 室外运动
    WatchSportType_OutDoor            = 0x01,
    /// 室内运动
    WatchSportType_InDoor           = 0x02,
};
///运动状态
typedef NS_ENUM(UInt8, WatchSportStatus) {
    /// 暂停
    WatchSportStatus_Pause  = 0x00,
    /// 运动中
    WatchSportStatus_Motion = 0x01
};

///心率模式
typedef NS_ENUM(UInt8, WatchHeartRateType) {
    ///最大心率模式
    WatchHeartRate_Max  = 0x00,
    ///存储心率模式
    WatchHeartRate_Save = 0x01
};
/// 运动强度类型
typedef NS_ENUM(UInt8, WatchExerciseIntensityType) {
    ///非运动模式
    WatchExercise_Not    = 0x00,
    ///最大心率模式:热身           储备心率模式：有氧基础
    WatchExercise_Level1 = 0x01,
    ///最大心率模式:燃脂           储备心率模式：有氧进阶
    WatchExercise_Level2 = 0x02,
    ///最大心率模式:有氧耐力    储备心率模式：乳酸阈值
    WatchExercise_Level3 = 0x03,
    ///最大心率模式:无氧耐力    储备心率模式：无氧基础
    WatchExercise_Level4 = 0x04,
    ///最大心率模式:极限           储备心率模式：无氧进阶
    WatchExercise_Level5 = 0x05
};
///睡眠类型
typedef NS_ENUM(UInt8, WatchSleepType) {
    ///清醒
    WatchSleep_WideAwake         = 0xFF,
    /// 浅睡
    WatchSleep_Light             = 0x01,
    /// 深睡
    WatchSleep_Deep              = 0x02,
    /// 快速眼动
    WatchSleep_RapidEyeMovement  = 0x03,
    /// 零星小睡
    WatchSleep_SporadicNaps      = 0x04
};


@interface JLWatchEnum : NSObject

/**
 *  运动数据类型转换为运动数据格式
 *  @param sportDataType 运动数据类型
 *  @return JL_SportDataFormat 运动数据格式
 */
+ (JL_SportDataFormat)sportDataFormatFromSportDataType:(JL_SportDataType)sportDataType;

@end

NS_ASSUME_NONNULL_END
