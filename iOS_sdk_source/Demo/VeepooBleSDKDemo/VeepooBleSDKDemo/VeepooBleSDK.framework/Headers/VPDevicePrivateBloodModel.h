//
//  VPDevicePrivateBloodModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/6/17.
//  Copyright © 2017年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDevicePrivateBloodModel : NSObject
//收缩压即为高压
@property (nonatomic, assign) NSUInteger systolicPressure;

//舒张压即为低压
@property (nonatomic, assign) NSUInteger diastolicPressure;

//私人模式0为关闭 1为开启
@property (nonatomic, assign) NSUInteger privateMode;

//是否是需要动态校准的私人模式
@property (nonatomic, assign) BOOL dynamicCalibration;

//0 是设置失败，1是设置成功，6是动态校准中，7是校准失败，8是校准成功，9是设备在被使用也属于校准失败的一种
@property (nonatomic, assign) NSUInteger settingState;

//校准进度，仅带有动态校准功能的设备有用
@property (nonatomic, assign) NSUInteger calibrationProgress;

/**
 通过手环返回来的数据进行初始化模型

 @param tbyte 手环返回来的数据
 @return model
 */
- (instancetype)initWithBloodTbyte:(const uint8_t *)tbyte;

//把model转换为要发送的Data 开发者用不到
- (NSData *)changeModelToDataWithSettingType:(NSUInteger)type;

@end
