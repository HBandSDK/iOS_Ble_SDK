//
//  VPWearthServerHourlyModel.h
//  WYPHealthyThird
//
//  Created by zhangchong on 2020/2/28.
//  Copyright © 2020 veepoo. All rights reserved.
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

//天气状态码
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
