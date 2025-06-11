//
//  VPManualBloodPressureModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2024/10/19.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPManualBloodPressureModel : NSObject

/// 测量时间戳
@property (nonatomic, assign) uint32_t timestamp;
/// 测量模式 0光电，1气囊
@property (nonatomic, assign) uint8_t testModel;
/// 心率
@property (nonatomic, assign) uint8_t heart;
/// 收缩压
@property (nonatomic, assign) uint16_t h_bp;
/// 舒张压
@property (nonatomic, assign) uint16_t l_bp;
/// 测试状态
/// 2 测量完成，测量姿势错误，可以获取输出结果，结束测量
/// 9 测量完成，期间未保持静止，可以获取输出結果，结束测量
@property (nonatomic, assign) uint8_t state;
/// 结果可信度
@property (nonatomic, assign) uint8_t credibility;
/// 身高
@property (nonatomic, assign) uint8_t height;
/// 体重
@property (nonatomic, assign) uint8_t weight;
/// 年龄
@property (nonatomic, assign) uint8_t age;
/// 性别 0:女 1:男
@property (nonatomic, assign) uint8_t sex;

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

@end

NS_ASSUME_NONNULL_END
