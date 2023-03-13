//
//  JLWearSyncHealthHeartRateChart.h
//  JL_BLEKit
//
//  Created by JLee on 2021/11/1.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLWearSyncHealthChart.h"

NS_ASSUME_NONNULL_BEGIN

//MARK: - 心率全天数据
@interface HeartRateData :  NSObject
/// 开始时间
@property(nonatomic,strong)NSDate *startDate;
/// 心率数组
@property(nonatomic,strong)NSArray *heartRates;

@end

/// 心率全天数据
@interface JLWearSyncHealthHeartRateChart : JLWearSyncHealthChart

///数据块内容
@property(nonatomic,strong)NSArray <HeartRateData *> *heartRatelist;
/// 静息心率
@property(nonatomic,assign)UInt8  restingHeartRate;
/// max
@property(nonatomic,assign)UInt8 maxHeartRate;
///min
@property(nonatomic,assign)UInt8 minHeartRate;

-(instancetype)initChart:(NSData *)sourceData;

@end


NS_ASSUME_NONNULL_END
