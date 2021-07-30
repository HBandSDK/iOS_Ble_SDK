//
//  VPWearthServerHourlyModel.h
//  WYPHealthyThird
//
//  Created by zhangchong on 2020/2/28.
//  Copyright © 2020 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPWeatherServerHourlyModel : NSObject

//格式2020-02-28 05:00
@property(nonatomic, strong) NSString *time;

//温度华氏度
@property(nonatomic, assign) double temp;

//紫外线强度指数
@property(nonatomic, strong) NSNumber *uvi;

//天气状态码 下方注释有详细对应天气状态关系
@property(nonatomic, assign) int code;

//风向等级1-2
@property(nonatomic, strong) NSString *wind_sc;

//能见度
@property(nonatomic, strong) NSNumber *vis;

//转化成发送给设备的数据
- (NSData *)sendDeviceData;

- (BOOL)valid;

@end

NS_ASSUME_NONNULL_END

/** VPWeatherServerHourlyModel
 天气状态码对应天气状态关系 逐小时的状态与此关系一致
 “()” 表示不包含
 "[]" 表示包含
 
 [0,   4]          表示 - 晴天
 (4, 12]          表示 - 晴转多云
 (12, 16]        表示 - 阴天
 (16, 20]        表示 - 阵雨
 (20, 24]        表示 - 雷阵雨
 (24, 32]        表示 - 冰雹
 (32, 40]        表示 - 小雨
 (40, 48]        表示 - 中雨
 (48, 56]        表示 - 大雨
 (56, 72]        表示 - 暴雨
 (72, 84]        表示 - 小雪
 (84, 100]      表示 - 大雪
 (100, 155]    表示 - 多云
 其它 - 未知
 
 */
