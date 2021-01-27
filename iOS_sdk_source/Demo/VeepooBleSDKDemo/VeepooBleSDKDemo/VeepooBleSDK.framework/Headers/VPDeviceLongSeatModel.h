//
//  VPDeviceLongSeatModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/8.
//  Copyright © 2017年 zc.All rights reserved.
//

/*
 Description: This model contains the hours, minutes, and status of sedentary start and end. The summary is how long it takes to sit for a few minutes and the end of a few minutes. How long does it take for a long time to stay, whether the status is on or off?
   The hour and minute must be passed in the correct parameters. The end time must be greater than the start time. The time is passed in the 24-hour system. The unit of the gate value is minute, at least 30 minutes, but the end time - start. Time > gate value
 说明:此模型包含久坐开始和结束的小时、分钟、及状态，总结就是此久坐在几点几分开始到几点几分结束 久坐超过多久提醒，状态是开启还是关闭
 小时和分钟一定要传入正确的参数 结束时间一定要大于开始时间，时间传入的都是以24小时制式传入，闸值传入的单位为分钟，最少为30分钟，但是结束时间-开始时间 > 闸值
 */

#import <Foundation/Foundation.h>

@interface VPDeviceLongSeatModel : NSObject

//久坐提醒开始的小时 区间为0-23
@property (nonatomic, assign) NSUInteger longSeatStartHour;

//久坐提醒开始的分钟 区间为0-59
@property (nonatomic, assign) NSUInteger longSeatStartMinute;

//久坐提醒结束的小时 区间为0-23
@property (nonatomic, assign) NSUInteger longSeatEndHour;

//久坐提醒结束的分钟 区间为0-59
@property (nonatomic, assign) NSUInteger longSeatEndMinute;

//The number of minutes for the sedentary reminder is [30 240]
//久坐提醒的闸值 为多少分钟 区间为【30 240】
@property (nonatomic, assign) NSUInteger longSeatGateValue;

//This is the state of sedentary reminder, 0 means off 1 means on
//此为久坐提醒的状态，0代表关闭 1代表开启
@property (nonatomic, assign) NSUInteger longSeatState;


/**

 @param startHour 久坐开始的小时
 @param startMinute 久坐开始的分钟
 @param endHour 久坐结束的小时
 @param endMinute 久坐结束的分钟
 @param gateValue 久坐的闸值
 @param state 久坐的状态开始还是关闭0代表关闭 1代表开启
 @return 返回久坐的模型
 */
- (instancetype)initWithLongSeatStartHour:(NSUInteger)startHour longSeatStartMinute:(NSUInteger)startMinute LongSeatEndHour:(NSUInteger)endHour longSeatEndMinute:(NSUInteger)endMinute longSeatGateValue:(NSUInteger)gateValue longSeatState:(NSUInteger)state;

@end





