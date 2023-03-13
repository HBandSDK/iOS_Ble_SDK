//
//  JLWearSyncHealthBloodOxyganChar.h
//  JL_BLEKit
//
//  Created by JLee on 2021/11/1.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLWearSyncHealthChart.h"

NS_ASSUME_NONNULL_BEGIN

//MARK: - 血氧全天数据
@interface BloodOxyganData :  NSObject
/// 开始时间
@property(nonatomic,strong)NSDate *startDate;
/// 血氧数组
@property(nonatomic,strong)NSArray *bloodOxygans;

@end

/// 血氧全天数据
@interface JLWearSyncHealthBloodOxyganChart : JLWearSyncHealthChart
/// 数据块内容
@property(nonatomic,strong)NSArray <BloodOxyganData *> *bloodOxyganlist;
/// max
@property(nonatomic,assign)UInt8 maxValue;
///min
@property(nonatomic,assign)UInt8 minValue;

-(instancetype)initChart:(NSData *)sourceData;

@end


NS_ASSUME_NONNULL_END
