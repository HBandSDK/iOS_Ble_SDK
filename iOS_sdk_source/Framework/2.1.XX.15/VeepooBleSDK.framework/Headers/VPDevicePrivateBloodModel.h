//
//  VPDevicePrivateBloodModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/6/17.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDevicePrivateBloodModel : NSObject

//收缩压即为高压
@property (nonatomic, assign) NSUInteger systolicPressure;

//舒张压即为低压
@property (nonatomic, assign) NSUInteger diastolicPressure;

//Private mode status, 0 is off 1 is on
//私人模式状态, 0为关闭 1为开启
@property (nonatomic, assign) NSUInteger privateMode;

//Is it a private mode that requires dynamic calibration?
//是否是需要动态校准的私人模式
@property (nonatomic, assign) BOOL dynamicCalibration;

//0 is the setting failure, 1 is the setting success, 6 is the dynamic calibration, 7 is the calibration failure, 8 is the calibration success, 9 is the device is also used as a calibration failure.
//0 是设置失败，1是设置成功，6是动态校准中，7是校准失败，8是校准成功，9是设备在被使用也属于校准失败的一种
@property (nonatomic, assign) NSUInteger settingState;

//Calibration progress, only devices with dynamic calibration are useful
//校准进度，仅带有动态校准功能的设备有用
@property (nonatomic, assign) NSUInteger calibrationProgress;

/**
 Initialize the model by returning the data from the bracelet
 通过手环返回来的数据进行初始化模型

 @param tbyte The data returned by the bracelet 手环返回来的数据
 @return model
 */
- (instancetype)initWithBloodTbyte:(const uint8_t *)tbyte;

//Converting a model to a Data developer to send
//把model转换为要发送的Data 开发者用不到
- (NSData *)changeModelToDataWithSettingType:(NSUInteger)type;

@end
