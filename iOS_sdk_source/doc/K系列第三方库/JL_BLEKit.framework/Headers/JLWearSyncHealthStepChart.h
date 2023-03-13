//
//  JLWearSyncHealthStepChart.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/11/5.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLWearSyncHealthChart.h"

NS_ASSUME_NONNULL_BEGIN

//MARK: - 步数全天数据

@interface JLWearStepCountModel:NSObject
/// 步数 单位：步
@property(nonatomic,assign)UInt16  count;
/// 距离 单位：10米
@property(nonatomic,assign)UInt16  duration;
///热量
@property(nonatomic,assign)UInt16  Calories;

@end

@interface StepCountData :  NSObject
/// 开始时间
@property(nonatomic,strong)NSDate *startDate;
/// 步数数组
@property(nonatomic,strong)NSArray <JLWearStepCountModel *>*stepCounts;

@end

/// 全天步数图表数据
@interface JLWearSyncHealthStepChart : JLWearSyncHealthChart
///数据块内容
@property(nonatomic,strong)NSArray <StepCountData *> *stepCountlist;

-(instancetype)initChart:(NSData *)sourceData;

@end

NS_ASSUME_NONNULL_END
