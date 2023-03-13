//
//  JL_WatchProtocolDelegate.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/8/11.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_SDM_Header.h"


NS_ASSUME_NONNULL_BEGIN

@protocol JL_WatchProtocol <NSObject>

@optional
/// 设备回调心率相关内容
/// @param heartRate 心率对象
-(void)jlWatchHeartRate:(JL_SDM_HeartRate *)heartRate;

/// 设备回调大气压强相关内容
/// @param airPressure 气压对象
-(void)jlWatchAirPressure:(JL_SDM_AirPressure *)airPressure;

/// 设备回调海拔高度相关内容
/// @param alititude 海拔对象
-(void)jlWatchAltitude:(JL_SDM_Altitude *)alititude;

/// 设备回调步数相关内容
/// @param moveStep 步数对象
-(void)jlWatchMoveSteps:(JL_SDM_MoveSteps *)moveStep;

/// 设备回调压力相关内容
/// @param stress 压力对象
-(void)jlWatchStress:(JL_SDM_Stress *)stress;

/// 设备回调血氧饱和度相关内容
/// @param oxStaturation 血氧饱和度对象
-(void)jlWatchOxsaturation:(JL_SDM_OxSaturation*)oxStaturation;

/// 设备回调训练负荷相关内容
/// @param trainLoad 训练负荷对象
-(void)jlWatchTrainLoad:(JL_SDM_TrainLoad *)trainLoad;

/// 设备回调最大摄氧量相关内容
/// @param maxOxg 最大摄氧量对象
-(void)jlWatchMaxOxg:(JL_SDM_MaxOxg *)maxOxg;

/// 设备回调运动恢复时间相关内容
/// @param rectime 运动恢复时间对象
-(void)jlWatchRecTime:(JL_SDM_RecTime *)rectime;

/// 设备回调运动数据的相关内容
/// @param sportMsg 运动数据对象
-(void)jlWatchSportMessage:(JL_SDM_SportMessage *)sportMsg;

/// 设备回调传感器相关数据
/// @param type 数据类型
/// @param data 数据内容
-(void)jlWatchWatchLog:(JL_WATCH_LOG_TYPE) type with:(NSData *)data;

//MARK: - 健康设置回调

/// 接收整个设置返回的数组
/// @param models JLwSettingModels
-(void)jlWatchSetAllFunc:(NSArray<JLwSettingModel *> *)models;

/// 回调传感器相关设置
/// @param model 传感器功能
-(void)jlWatchSetSensorFunc:(JLSensorFuncModel *)model;

/// 久坐提醒
/// @param model 久坐提醒功能
-(void)jlWatchSetSedentaryRmd:(JLSedentaryRmdModel *)model;

/// 心率测量功能
/// @param model 心率模块
-(void)jlWatchSetConsequentHeartRate:(JLConsequentHeartRateModel *)model;

/// 运动心率测试功能
/// @param model 运动心率
-(void)jlWatchSetExerciseHeartRateRemind:(JLExerciseHeartRateRemindModel *)model;

/// 自动压力测试
/// @param model 压力测试
-(void)jlWatchSetAutoPressure:(JLAutoPressureModel *)model;

/// 睡眠监测
/// @param model 睡眠
-(void)jlWatchSetSleepMonitor:(JLSleepMonitorModel *)model;

/// 跌到监测
/// @param model 跌倒监测
-(void)jlWatchSetFallDetectionModel:(JLFallDetectionModel *)model;

/// 抬腕监测
/// @param model 抬腕监测
-(void)jlWatchSetWristLiftDetectionModel:(JLWristLiftDetectionModel *)model;

/// 个人信息
/// @param model 个人信息
-(void)jlWatchSetPersonInfoModel:(JLPersonInfoModel *)model;

/// 蓝牙断开设置
/// @param model 断开设置
-(void)jlWatchSetDisconnectRemindModel:(JLDisconnectRemindModel *)model;

/// 紧急联系人
/// @param model 紧急联系人设置
-(void)jlWatchSetEmergencyContactModel:(JLEmergencyContactModel *)model;

/// 血氧测量
/// @param model 血氧测量模式
-(void)jlWatchSetOxygenSturationRemindModel:(JLOxygenSturationRemindModel *)model;

@end

NS_ASSUME_NONNULL_END
