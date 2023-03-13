//
//  JLWearSyncHealthWeightChart.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/11/19.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLWearSyncHealthChart.h"

NS_ASSUME_NONNULL_BEGIN


@interface JLWearWeightModel:NSObject
/// 整数
@property(nonatomic,assign)NSInteger  integer;
/// 小数
@property(nonatomic,assign)NSInteger  decimal;

@end

@interface WeightData:NSObject
/// 时间
@property(nonatomic,strong)NSDate *startDate;
/// 体重
@property(nonatomic,strong)NSArray<JLWearWeightModel *> *weights;

@end

@interface JLWearSyncHealthWeightChart : JLWearSyncHealthChart

@property(nonatomic,strong)NSArray<WeightData *> *weightDataArray;

-(instancetype)initChart:(NSData *)sourceData;

/// 生成一个二进制对象
/// 示例：
///
/// 创建体重60.25
/// JLWearWeightModel *oneModel = [JLWearWeightModel new];
/// oneModel.integer = 60;
/// oneModel.decimal = 25;
///
/// WeightData *wd = [WeightData new];
/// //当前记录体重的时间
/// wd.startDate = [NSDate new];
/// // 把体重放入
/// wd.weights = @[oneModel];
///
/// //当出现一天多次体重时：
/// JLWearWeightModel *oneModel2 = [JLWearWeightModel new];
/// oneModel2.integer = 60;
/// oneModel2.decimal = 40;
///
/// WeightData *wd2 = [WeightData new];
/// //当前记录体重的时间
/// wd2.startDate = [NSDate new];
/// // 把体重放入
/// wd2.weights = @[oneModel2];
///
/// //创建文件体重对象
/// JLWearSyncHealthWeightChart *wc = [JLWearSyncHealthWeightChart new];
/// wc.type = JL_SmallFileTypeWeight;
/// //一个文件只写了一天内多次体重测量的结果，所以这里是写上测量当天的日期
/// wc.yyyyMMdd = @"20211119";
/// wc.weightDataArray = @[wd,wd2];
///
/// NSData *dt = [wc beData];
/// JLWearSyncHealthWeightChart *wc2 = [[JLWearSyncHealthWeightChart alloc] initChart:dt];
/// NSLog(@"wc2%@",wc2);
///
-(NSData *)beData;


@end

NS_ASSUME_NONNULL_END
