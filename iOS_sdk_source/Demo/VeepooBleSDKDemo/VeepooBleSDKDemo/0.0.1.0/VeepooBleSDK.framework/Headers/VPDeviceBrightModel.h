//
//  VPDeviceBrightModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/3/10.
//  Copyright © 2017年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDeviceBrightModel : NSObject<NSCopying>
/*
 比如你设置一个作用时间段为22：00-8：00 档位为firstBrightValue 其他时间段的亮度档位为otherBrightValue，那手环在22：00-8：00这个时间段按照firstBrightValue的档位显示亮度，其他时间显示otherBrightValue这个档位的亮度
 如果设置为自动，会根据不同设备在不同时间段显示不同的档位，这个具体由手环决定
 每个设备的最大档位也是不同的
 */
//第一个档位作用开始小时
@property (nonatomic, assign) NSInteger firstBrightStartHour;
//第一个档位作用开始分钟
@property (nonatomic, assign) NSInteger firstBrightStartMinute;
//第一个档位作用结束小时
@property (nonatomic, assign) NSInteger firstBrightEndHour;
//第一个档位作用结束分钟
@property (nonatomic, assign) NSInteger firstBrightEndMinute;

//设置时间段的第一个档位
@property (nonatomic, assign) NSInteger firstBrightValue;

//其他时间段亮度档位
@property (nonatomic, assign) NSInteger otherBrightValue;

//是否自动调节
@property (nonatomic, assign) BOOL isAutomatic;

//最大的亮度调节档位
@property (nonatomic, assign) NSInteger maxBrightValue;

//每次连接手动设置的otherBrightValue最后档位
@property (nonatomic, assign) NSInteger lastManualBrightValue;

/**
 初始化调节亮度的模型

 @param startH 第一个亮度的开始小时
 @param startM 第一个亮度的开始分钟
 @param endH 第二个亮度的结束小时
 @param endM 第二个亮度的结束分钟
 @param firstValue 第一个档位  与设置的时间相关联
 @param otherValue 其他时间段的亮度档位
 @return 返回model
 */
- (instancetype)initWithStartHour:(NSInteger)startH startMinute:(NSInteger)startM endHour:(NSInteger)endH endMinute:(NSInteger)endM firstBrightValue:(NSInteger)firstValue otherBrightValue:(NSInteger)otherValue;


/**
 根据设备返回的数据建立模型
 @param brightData 返回的数据
 @return VPDeviceBrightModel
 */
- (instancetype)initWithData:(NSData *)brightData;

@end







