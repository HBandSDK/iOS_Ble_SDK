//
//  VPWeatherServerModel.h
//  WYPHealthyThird
//
//  Created by zhangchong on 2020/2/28.
//  Copyright © 2020 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPWeatherServerHourlyModel.h"
#import "VPWeatherServerForecastModel.h"


#define VPWEATHER_INFO_KEY @"vp_weather_info_key"

NS_ASSUME_NONNULL_BEGIN

@interface VPWeatherServerModel : NSObject

//经度
@property(nonatomic, assign) double lon;

//纬度
@property(nonatomic, assign) double lat;

//温度的城市或区域
@property(nonatomic, strong) NSString *city;

//返回天气的数据来源或等级免费还是付费等精准度信息
@property(nonatomic, assign) int type;

//最后更新时间2020-05-09 09:08:34
@property(nonatomic, strong) NSString *update;

//逐3小时天气数组
@property(nonatomic, strong) NSArray <VPWeatherServerHourlyModel *>*hourly;

//未来逐天的天气数组
@property(nonatomic, strong) NSArray <VPWeatherServerForecastModel *>*forecast;

//获取完成后把本地请求的地理位置也保存下来，用来判断地理城市是否有变化
@property(nonatomic, strong) NSString *cnty;
@property(nonatomic, strong) NSString *admin;
@property(nonatomic, strong) NSString *locality;
@property(nonatomic, strong) NSString *subLocality;

//获取当前模型的crc
- (uint16_t)currentModelCrc;

//保存当前的model
- (void)save;

//获取上次存储的model
+ (VPWeatherServerModel *)lastSaveModel;

//转化成发送给设备的数据
- (NSData *)sendDeviceContentData;

//获取逐三小时有效数据
- (NSData *)hourlysData;

//获取逐天有效数据
- (NSData *)forecastsData;

//根据设备的天气类型判断天气是否有效
- (BOOL)weatherValidWithWeatherType:(int)type;

@end


NS_ASSUME_NONNULL_END
