//
//  VPDailyBloodAnalysisModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/10/18.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// DF指令自动测量的血液成分数据，每5分钟数据
@interface VPDailyBloodAnalysisModel : NSObject

/// 时间 HH:mm
@property (nonatomic, strong) NSString *time;
/// 总胆固醇，两位小数点
@property (nonatomic, strong) NSArray<NSString *> *totalCholesterols;
/// 甘油三酯，两位小数点
@property (nonatomic, strong) NSArray<NSString *> *triglycerides;
/// 高密度脂蛋白，两位小数点
@property (nonatomic, strong) NSArray<NSString *> *highDensityLipoproteins;
/// 低密度脂蛋白，两位小数点
@property (nonatomic, strong) NSArray<NSString *> *lowDensityLipoproteins;
/// 尿酸值，一位小数点
@property (nonatomic, strong) NSArray<NSString *> *uricAcids;

- (BOOL)isEmpty;

@end

NS_ASSUME_NONNULL_END
