//
//  WLWeatherManager.h
//  VeepooBleSDK
//
//  Created by zhangchong on 2020/11/27.
//  Copyright © 2020 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WLWeatherModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef void(^VPSyscResult)(BOOL success);

@interface WLWeatherManager : NSObject

+ (instancetype)share;

//读取和设置使用WPWeahterHandle中的方法

- (void)wl_updateWeatherWithModels:(NSArray <WLWeatherModel *>*)weatherModels andResult:(VPSyscResult)result;

//接收设备返回的数据，SDK内部使用
- (void)receiveData:(NSData *)receiveDeviceData;

@end

NS_ASSUME_NONNULL_END
