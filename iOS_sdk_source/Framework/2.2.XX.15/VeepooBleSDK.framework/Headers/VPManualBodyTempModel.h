//
//  VPManualBodyTempModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/3/26.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPManualBodyTempModel : NSObject

/// 测量时间戳
@property (nonatomic, assign) uint32_t timestamp;
/// 体温
@property (nonatomic, assign) uint16_t bodyTemp;
/// 原始温度-皮肤温度
@property (nonatomic, assign) uint16_t origTemp;

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

@end

NS_ASSUME_NONNULL_END
