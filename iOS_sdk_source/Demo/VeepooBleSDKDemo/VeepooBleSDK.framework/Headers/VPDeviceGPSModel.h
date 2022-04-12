//
//  VPDeviceGPSModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/3/11.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceGPSModel : NSObject

// 经度 int32（保留5位小数，放大100000倍）  ex: 116.405289 则传 （116.40528 * 100000）= 11640528
@property (nonatomic, assign) int longitude;

// 纬度 int32 ex: -39.904987 同上=> -3990498
@property (nonatomic, assign) int latitude;

// 时区 int16 单位分钟，必须是15的倍数 ex: 480表示东八区（8*60=480）
@property (nonatomic, assign) short timezone;

// UTC时间戳(获取到经纬度的时间戳 秒级) ex: 1615433584
@property (nonatomic, assign) long timestamp;

// 海拔高度(单位米，带正负) ex: -100
@property (nonatomic, assign) short altitude;

@end

NS_ASSUME_NONNULL_END
