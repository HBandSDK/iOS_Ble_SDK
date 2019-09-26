//
//  VPDeviceAlarmModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/8.
//  Copyright © 2017年 veepoo. All rights reserved.
//

/*
 说明:此模型包含闹钟的小时、分钟、及状态，总结就是此闹钟是几点几分状态是开启还是关闭状态
 小时和分钟一定要传入正确的参数
 */
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, VPOperationAlarmMode) {//设置某个功能完成之后的状态
    VPClearAlarmMode = 0x00, //清除所有闹钟
    VPSettingAlarmMode = 0x01,//设置闹钟
    VPReadAlarmMode = 0x06,//读取闹钟
    VPTestAlarmMode = 0x10,//测试闹钟，立即响应
};

@interface VPDeviceAlarmModel : NSObject

//闹钟的小时 区间为0-23
@property (nonatomic, assign) NSUInteger alarmHour;

//闹钟的分钟 区间为0-59
@property (nonatomic, assign) NSUInteger alarmMinute;

//此闹钟的状态，0代表关闭 1代表开启
@property (nonatomic, assign) NSUInteger alarmState;

/**
 初始化

 @param hour 闹钟的小时
 @param minute 闹钟的分钟
 @param state 闹钟的状态
 @return 一个闹钟的模型
 */
- (instancetype)initWithAlarmHour:(NSUInteger)hour alarmMinute:(NSUInteger)minute alarmState:(NSUInteger)state;

@end





