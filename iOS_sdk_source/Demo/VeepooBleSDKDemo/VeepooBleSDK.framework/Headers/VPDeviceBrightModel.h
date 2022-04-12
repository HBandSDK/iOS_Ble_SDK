//
//  VPDeviceBrightModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/3/10.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDeviceBrightModel : NSObject<NSCopying>
/*
 For example, if you set a time period of 22:00-8:00, the gear position is firstBrightValue, and the brightness position of other time zones is otherBrightValue. The wristband displays brightness according to the firstBrightValue position during the time period of 22:00-8:00. , other times display the brightness of otherBrightValue
   If it is set to automatic, it will display different gear positions according to different devices in different time periods. This is determined by the bracelet.
   The maximum gear position of each device is also different.
 比如你设置一个作用时间段为22：00-8：00 档位为firstBrightValue 其他时间段的亮度档位为otherBrightValue，那手环在22：00-8：00这个时间段按照firstBrightValue的档位显示亮度，其他时间显示otherBrightValue这个档位的亮度
 如果设置为自动，会根据不同设备在不同时间段显示不同的档位，这个具体由手环决定
 每个设备的最大档位也是不同的
 */

//The first gear starts to work
//第一个档位作用开始小时
@property (nonatomic, assign) NSInteger firstBrightStartHour;

//The first gear starts to play minutes
//第一个档位作用开始分钟
@property (nonatomic, assign) NSInteger firstBrightStartMinute;

//The first gear ends the hour
//第一个档位作用结束小时
@property (nonatomic, assign) NSInteger firstBrightEndHour;

//The first gear ends the minute
//第一个档位作用结束分钟
@property (nonatomic, assign) NSInteger firstBrightEndMinute;

//Set the first gear of the time period
//设置时间段的第一个档位
@property (nonatomic, assign) NSInteger firstBrightValue;

//Brightness gears in other time periods
//其他时间段亮度档位
@property (nonatomic, assign) NSInteger otherBrightValue;

//Whether to adjust automatically
//是否自动调节
@property (nonatomic, assign) BOOL isAutomatic;

//Maximum brightness adjustment gear
//最大的亮度调节档位
@property (nonatomic, assign) NSInteger maxBrightValue;

//The last gear of otherBrightValue manually set each time
//每次连接手动设置的otherBrightValue最后档位
@property (nonatomic, assign) NSInteger lastManualBrightValue;

/**

 @param startH The first hour of brightness 第一个亮度的开始小时
 @param startM The first minute of the first brightness 第一个亮度的开始分钟
 @param endH The end of the second brightness 第二个亮度的结束小时
 @param endM The end of the second brightness 第二个亮度的结束分钟
 @param firstValue The first gear is associated with the set time 第一个档位与设置的时间相关联
 @param otherValue Brightness gears for other time periods 其他时间段的亮度档位
 @return model
 */
- (instancetype)initWithStartHour:(NSInteger)startH startMinute:(NSInteger)startM endHour:(NSInteger)endH endMinute:(NSInteger)endM firstBrightValue:(NSInteger)firstValue otherBrightValue:(NSInteger)otherValue;


/**
 Model based on data returned by the device
 根据设备返回的数据建立模型
 @param brightData Data returned by the device 设备返回的数据
 @return VPDeviceBrightModel
 */
- (instancetype)initWithData:(NSData *)brightData;

@end







