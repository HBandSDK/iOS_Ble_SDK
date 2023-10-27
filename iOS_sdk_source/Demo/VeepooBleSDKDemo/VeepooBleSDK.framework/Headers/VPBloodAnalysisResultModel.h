//
//  VPBloodAnalysisResultModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/10/18.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPBloodAnalysisResultModel : NSObject

/// 尿酸 ，一位小数点，单位μmol/L
@property (nonatomic, assign) double uricAcidValue;

/// 总胆固醇，二位小数点，单位mmol/L
@property (nonatomic, assign) double totalCholesterolValue;

/// 甘油三酸酯，二位小数点，单位mmol/L
@property (nonatomic, assign) double triglycerideValue;

/// 高密度脂蛋白，二位小数点，单位mmol/L
@property (nonatomic, assign) double highDensityLipoproteinValue;

/// 低密度脂蛋白，二位小数点，单位mmol/L
@property (nonatomic, assign) double lowDensityLipoproteinValue;


/// 内部初始化方法
/// - Parameter data: 原始数据
- (instancetype)initWithData:(NSData *)data;

/// 获取要发送的数据，内部使用
- (NSData *)getSendData;

@end

NS_ASSUME_NONNULL_END
