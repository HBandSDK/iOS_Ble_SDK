//
//  VPDeviceRaiseHandModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/3/2.
//  Copyright © 2017年 zc.All rights reserved.
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

//This is the state of the wristlit bright screen, 0 means off 1 is on, and it is valid during setup time when it is on
//此为翻腕亮屏的状态，0代表关闭 1代表开启，开启的时候在设置时间内有效
@property (nonatomic, assign) NSUInteger raiseHandState;

//Current sensitivity of the bracelet
//手环当前灵敏度
@property (nonatomic, assign) NSUInteger sensitive;

//The default sensitivity of the bracelet, if not, it means no sensitivity setting function
//手环默认灵敏度，如果没有则代表没有灵敏度设置功能
@property (nonatomic, assign) NSUInteger defaultSensitive;

//Internal use of the SDK, tbyte is the data returned by the bracelet
//SDK内部使用，tbyte为手环返回的数据
- (instancetype)initWithRaiseHandTbyte:(const uint8_t *)tbyte;

/**
 
 @param startHour 翻腕亮屏开始的小时
 @param startMinute 翻腕亮屏开始的分钟
 @param endHour 翻腕亮屏结束的小时
 @param endMinute 翻腕亮屏结束的分钟
 @param state Turning the status of the wrist screen on or off 0 means off 1 means on 翻腕亮屏的状态开始还是关闭0代表关闭 1代表开启
 @param sensitive The sensitivity of the wristscreen bright screen, when the default wristband sensitivity is zero, 0 is transmitted here, indicating that there is no such function. 翻腕亮屏的灵敏度，默认手环灵敏度为零的时候此处传0，代表没有此功能
 @return model
 */
- (instancetype)initWithRaiseHandStartHour:(NSUInteger)startHour raiseHandStartMinute:(NSUInteger)startMinute raiseHandEndHour:(NSUInteger)endHour raiseHandEndMinute:(NSUInteger)endMinute raiseHandState:(NSUInteger)state raiseHandSensitive:(NSUInteger)sensitive;

@end
