//
//  VPDeviceAlarmModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/8.
//  Copyright © 2017年 zc.All rights reserved.
//

/*
 Description: This model contains the hour, minute, and status of the alarm. The summary is whether the alarm is on or off.
   Must pass in the correct parameters for hours and minutes
 说明:此模型包含闹钟的小时、分钟、及状态，总结就是此闹钟是几点几分状态是开启还是关闭状态, 小时和分钟一定要传入正确的参数
 */
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, VPOperationAlarmMode) {//Set the status after a feature is completed 设置某个功能完成之后的状态
    VPClearAlarmMode = 0x00, //Clear all alarms 清除所有闹钟
    VPSettingAlarmMode = 0x01,//Set alarm 设置闹钟
    VPReadAlarmMode = 0x06,//Reading alarm clock 读取闹钟
    VPTestAlarmMode = 0x10,//Test the alarm and respond immediately 测试闹钟，立即响应
};

@interface VPDeviceAlarmModel : NSObject

//The hour of the alarm clock is 0-23
//闹钟的小时 区间为0-23
@property (nonatomic, assign) NSUInteger alarmHour;

//The minute of the alarm clock is 0-59
//闹钟的分钟 区间为0-59
@property (nonatomic, assign) NSUInteger alarmMinute;

//The status of this alarm, 0 means off 1 means on
//此闹钟的状态，0代表关闭 1代表开启
@property (nonatomic, assign) NSUInteger alarmState;

/**

 @param hour Alarm hour 闹钟的小时
 @param minute Minute of the alarm clock 闹钟的分钟
 @param state Alarm clock status 闹钟的状态
 @return An alarm clock model 一个闹钟的模型
 */
- (instancetype)initWithAlarmHour:(NSUInteger)hour alarmMinute:(NSUInteger)minute alarmState:(NSUInteger)state;

@end





