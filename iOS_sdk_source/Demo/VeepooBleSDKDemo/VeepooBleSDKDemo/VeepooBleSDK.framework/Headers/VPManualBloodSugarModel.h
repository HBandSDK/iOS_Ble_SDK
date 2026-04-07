//
//  VPManualBloodSugarModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/3/26.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPManualBloodSugarModel : NSObject

// 测量时间戳
@property (nonatomic, assign) uint32_t timestamp;

// 血糖值
@property (nonatomic, assign) uint16_t bloodSugarValue;

// 是否有血糖风险等级
@property (nonatomic, assign) BOOL haveLevel;

// 血糖风险等级 (1,2,3 低 中 高)
@property (nonatomic, assign) uint8_t bloodSugarLevel;

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

@end

NS_ASSUME_NONNULL_END
