//
//  VPRRIntervalDataHRVHandle.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2022/4/12.
//  Copyright © 2022 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPRRIntervalLorentzModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface VPRRIntervalDataHRVHandle : NSObject

/// 获取绘制洛伦兹图的X轴与Y轴坐标数组
/// 注意：如果传入数组的元素不足2000，则返回空； 如果传入的数据大于一天的数据，仅针对从下标0开始，一天最大的数据量进行处理
/// @param rrDataArr 由dataConvertStream集合转换而得，先把一天的dataConvertStream数据收集，再转换成数组
+ (NSArray<VPRRIntervalLorentzModel *> *)getRRIntervalLorentzModelsWithArr:(NSArray<NSNumber *> *)rrDataArr;

@end

NS_ASSUME_NONNULL_END
