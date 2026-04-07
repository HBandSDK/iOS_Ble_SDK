//
//  VPManualBloodCompModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/3/26.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPManualBloodCompModel : NSObject

// 测量时间戳
@property (nonatomic, assign) uint32_t timestamp;
@property (nonatomic, assign) uint16_t totalCholesterol;//总胆固醇
@property (nonatomic, assign) uint16_t triglyceride;//甘油三酯
@property (nonatomic, assign) uint16_t highDensityLipoprotein;//高密度脂蛋白
@property (nonatomic, assign) uint16_t lowDensityLipoprotein;//低密度脂蛋白
@property (nonatomic, assign) uint16_t uricAcid;// 尿酸值

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

@end

NS_ASSUME_NONNULL_END
