//
//  VPDeviceRaiseHandModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/3/2.
//  Copyright © 2017年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDeviceRaiseHandModel : NSObject

//翻腕亮屏开始的小时 区间为0-23
@property (nonatomic, assign) NSUInteger raiseHandStartHour;

//翻腕亮屏开始的分钟 区间为0-59
@property (nonatomic, assign) NSUInteger raiseHandStartMinute;

//翻腕亮屏结束的小时 区间为0-23
@property (nonatomic, assign) NSUInteger raiseHandEndHour;

//翻腕亮屏结束的分钟 区间为0-59
@property (nonatomic, assign) NSUInteger raiseHandEndMinute;

//此为翻腕亮屏的状态，0代表关闭 1代表开启，开启的时候在设置时间内有效
@property (nonatomic, assign) NSUInteger raiseHandState;

//手环当前灵敏度
@property (nonatomic, assign) NSUInteger sensitive;
//手环默认灵敏度，如果没有则代表没有灵敏度设置功能
@property (nonatomic, assign) NSUInteger defaultSensitive;

//SDK内部使用，tbyte为手环返回的数据
- (instancetype)initWithRaiseHandTbyte:(const uint8_t *)tbyte;

/**
 翻腕亮屏的初始化
 
 @param startHour 翻腕亮屏开始的小时
 @param startMinute 翻腕亮屏开始的分钟
 @param endHour 翻腕亮屏结束的小时
 @param endMinute 翻腕亮屏结束的分钟
 @param state 翻腕亮屏的状态开始还是关闭0代表关闭 1代表开启
 @param sensitive 翻腕亮屏的灵敏度，默认手环灵敏度为零的时候此处传0，代表没有此功能
 @return 返回翻腕亮屏的模型
 */
- (instancetype)initWithRaiseHandStartHour:(NSUInteger)startHour raiseHandStartMinute:(NSUInteger)startMinute raiseHandEndHour:(NSUInteger)endHour raiseHandEndMinute:(NSUInteger)endMinute raiseHandState:(NSUInteger)state raiseHandSensitive:(NSUInteger)sensitive;

@end
