//
//  VPGSRResultModel.h
//  VeepooBleSDK
//
//  Created by vp_app_01 on 2025/12/1.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPGSRResultModel : NSObject
/// 情绪 [-10,10]
@property (nonatomic, assign) int emotin_level;

/// 皮肤含水量 [1,99]
@property (nonatomic, assign) int skin_moisture;

/// 抑郁症风险 [0,2] 0:低风险 1：中风险 2：高风险
@property (nonatomic, assign) int depression_risk;

/// 交感神经活跃度 [1,99]
@property (nonatomic, assign) int sns_activation;

/// 皮质醇浓度，[0,500]，单位ug/L
@property (nonatomic, assign) int cortisol_value;


/// 内部初始化方法
/// - Parameter data: 原始数据
- (instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
