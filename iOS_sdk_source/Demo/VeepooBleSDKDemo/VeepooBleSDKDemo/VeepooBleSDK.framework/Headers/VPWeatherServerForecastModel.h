//
//  VPWeatherServerForecastModel.h
//  WYPHealthyThird
//
//  Created by zhangchong on 2020/2/28.
//  Copyright © 2020 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPWeatherServerForecastModel : NSObject

//格式2020-02-28
@property(nonatomic, strong) NSString *date;

//最高温度华氏度
@property(nonatomic, assign) double maxTemp;

//最低温度华氏度
@property(nonatomic, assign) double minTemp;

//紫外线强度指数
@property(nonatomic, strong) NSNumber *uvi;

//白天天气状态码
@property(nonatomic, strong) NSNumber *dayCode;

//夜间天气状态码
@property(nonatomic, assign) NSNumber *nightCode;

//风向等级1-2
@property(nonatomic, strong) NSString *wind_sc;

//能见度
@property(nonatomic, strong) NSNumber *vis;

//转化成发送给设备的数据
- (NSData *)sendDeviceData;

- (BOOL)valid;

@end

NS_ASSUME_NONNULL_END
