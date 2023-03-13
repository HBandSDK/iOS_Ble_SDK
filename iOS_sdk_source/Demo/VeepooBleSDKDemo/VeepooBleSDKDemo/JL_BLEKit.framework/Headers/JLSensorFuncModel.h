//
//  JLSensorFuncModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"
#import "JLWatchEnum.h"

NS_ASSUME_NONNULL_BEGIN


/// 传感器开关设置
@interface JLSensorFuncModel : JLwSettingModel

/// 计步器开关
@property(nonatomic,assign)BOOL pedometerStatus;
/// 计步器记录开关
@property(nonatomic,assign)BOOL pedometerRecordStatus;
/// 心率传感器开关
@property(nonatomic,assign)BOOL heartRateStatus;
/// 心率传感器记录开关
@property(nonatomic,assign)BOOL heartRateRecordStatus;
/// 血氧传感器开关
@property(nonatomic,assign)BOOL bloodOxygenStatus;
/// 血氧传感器记录开关
@property(nonatomic,assign)BOOL bloodOxygenRecordStatus;
///海拔气压传感器开关
@property(nonatomic,assign)BOOL AltitudeAirPressureStatus;
///海拔气压传感器记录开关
@property(nonatomic,assign)BOOL AltitudeAirPressureRecordStatus;


/// 传感器功能
/// @param status 功能的开关状态
-(void)setFuncBy:(JL_SENSOR_FUNC_SWITCH)status;

/// @param funcByte 功能的开关状态
-(instancetype)initWhthFuncByte:(JL_SENSOR_FUNC_SWITCH)funcByte;

-(instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
