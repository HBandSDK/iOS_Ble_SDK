//
//  VPManualGSRModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/6/22.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPManualGSRModel : NSObject

/// 测量时间戳
@property (nonatomic, assign) uint32_t timestamp;
/// 情绪 [-10,10]
@property (nonatomic, assign) NSInteger emotionLevel;
/// 皮肤含水量 [1,99]
@property (nonatomic, assign) UInt8 skinMoisture;
/// 抑郁症风险 [0,2] 0:低风险 1:中风险 2:高风险
@property (nonatomic, assign) UInt8 depressionRisk;
/// 交感神经活跃度 [1,99]
@property (nonatomic, assign) UInt8 snsActivation;
/// 皮质醇浓度，有效范围 [0,500]ug/L
@property (nonatomic, assign) UInt16 cortisolValue;

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

@end

NS_ASSUME_NONNULL_END
