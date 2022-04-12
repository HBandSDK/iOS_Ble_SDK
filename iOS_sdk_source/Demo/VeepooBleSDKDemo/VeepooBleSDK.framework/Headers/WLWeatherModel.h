//
//  WLWeatherModel.h
//  VeepooBleSDK
//
//  Created by zhangchong on 2020/11/27.
//  Copyright © 2020 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WLWeatherModel : NSObject

//格式2020-12-18 12:00
@property (nonatomic, strong) NSString *dateTime;

//华氏度
@property (nonatomic, assign) int temp;

//摄氏度
@property (nonatomic, assign) int temp2;

//此ID是WL提供的，客户可以自己看定义
@property (nonatomic, assign) int weatherId;

@property (nonatomic, strong) NSString *city;
//紫外线
@property (nonatomic, assign) int uvintensity;
@property (nonatomic, strong) NSString *uviText;

//data数据的crc, 要传给设备的，整个天气数据的唯一标识，用来区分当前天气和设备的是否一致，具体算法可以自己定义
@property (nonatomic, assign) int crc;

- (NSData *)dataWithIndex:(NSInteger)index andTotalCount:(NSInteger)totalCount;

- (NSString *)showTime;

//天气描述，只有中文
- (NSString *)weatherDescribe;

//紫外线的强度描述,只有中文
- (NSString *)uvintensityDescribe;

@end

NS_ASSUME_NONNULL_END
