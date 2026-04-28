//
//  VPQX17HeartRateModel.h
//  VeepooBleSDK
//
//  Created by vp_app_01 on 2026/4/17.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPQX17HeartRateModel : NSObject
/// 心率值
@property (nonatomic, assign, readonly) uint8_t heartRate;
/// 时间戳（毫秒）
@property (nonatomic, assign, readonly) uint32_t timestamp;

// 初始化方法声明
- (instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
