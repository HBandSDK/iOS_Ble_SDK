//
//  VPQX17GPSModel.h
//  VeepooBleSDK
//
//  Created by vp_app_01 on 2026/4/17.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPQX17GPSModel : NSObject
// 纬度
@property (nonatomic, assign, readonly) float latitude;
// 经度
@property (nonatomic, assign, readonly) float longitude;
// 定位精度（单位：米）
@property (nonatomic, assign, readonly) float accuracy;
// 时间戳（毫秒）
@property (nonatomic, assign, readonly) uint32_t timestamp;

// 初始化方法声明
- (instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
