//
//  VPDeviceLongSeatModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/8.
//  Copyright © 2017年 veepoo. All rights reserved.
//

/*
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

//久坐提醒的闸值 为多少分钟 区间为【30 240】
@property (nonatomic, assign) NSUInteger longSeatGateValue;

//此为久坐提醒的状态，0代表关闭 1代表开启
@property (nonatomic, assign) NSUInteger longSeatState;


/**
 久坐的初始化

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





