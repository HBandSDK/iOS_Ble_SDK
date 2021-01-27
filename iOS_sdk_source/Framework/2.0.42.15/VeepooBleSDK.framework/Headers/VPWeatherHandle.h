//
//  VPWeatherHandle.h
//  WYPHealthyThird
//
//  Created by zhangchong on 2020/2/28.
//  Copyright © 2020 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPWeatherConfigModel.h"
#import "VPWeatherServerModel.h"

typedef NS_ENUM(NSInteger, VPWeatherSettingState) {
    VPWeatherSettingStateNone = 0, //没有此功能
    VPWeatherSettingStateSuccess,  //成功
    VPWeatherSettingStateFailure,  //失败
};

//state==1成功，0失败
typedef void(^VPSyncWeatherResult)(VPWeatherSettingState state);

typedef void(^VPSettingWeatherResult)(VPWeatherSettingState state);

typedef void(^VPReadWeatherResult)(VPWeatherSettingState state, VPWeatherConfigModel * _Nullable cofigModel);

NS_ASSUME_NONNULL_BEGIN

@interface VPWeatherHandle : NSObject

@property(nonatomic, strong) VPWeatherConfigModel *cofigModel;

+ (instancetype)share;

//清除当前缓存信息
- (void)reset;

//SDK使用人，主要调用以下3个方法即可，Model自己配置好下发

//同步App的天气数据给设备
- (void)syncWeatherDataToDeviceWithWeatherServerModel:(VPWeatherServerModel *)serverModel result:(VPSyncWeatherResult)result;

//读取天气开关和单位
- (void)readWeatherInfo:(VPReadWeatherResult)result;

//设置天气开关和单位
- (void)settingWeatherInfo:(VPWeatherConfigModel *)settingModel result:(VPSettingWeatherResult)result;

//接收设备返回的数据，SDK内部使用
- (void)receiveData:(NSData *)receiveDeviceData;

@end

NS_ASSUME_NONNULL_END
