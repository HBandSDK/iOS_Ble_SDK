//
//  VPDeviceHeartAlarmModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/13.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDeviceHeartAlarmModel : NSObject

//Heart rate upper limit alarm value
//心率上限报警值
@property (nonatomic, assign) NSUInteger heartMaxValue;

//Heart rate lower limit alarm value
//心率下限报警值
@property (nonatomic, assign) NSUInteger heartMinValue;

//Heart rate alarm switch status has upper and lower limits, but may be in both closed and open states
//心率报警开关状态 有上限和下限，但是可能处于关闭和开启的两种状态
@property (nonatomic, assign) BOOL isOpen;

/**
 
 @param heartMaxValue Heart rate upper limit alarm value 心率报警上限值
 @param heartMinValue Heart rate lower limit alarm value 心率报警下限值
 @param open Is the heart rate alarm turned on? 心率报警是否开启
 @return 返回心率报警模型
 */
- (instancetype)initWithHeartMaxValue:(NSUInteger)heartMaxValue heartMinValue:(NSUInteger)heartMinValue openState:(BOOL)open;

@end




