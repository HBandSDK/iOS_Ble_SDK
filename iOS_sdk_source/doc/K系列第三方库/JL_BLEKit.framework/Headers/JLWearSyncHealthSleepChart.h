//
//  JLWearSyncHealthSleepChart.h
//  JL_BLEKit
//
//  Created by JLee on 2021/11/1.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLWearSyncHealthChart.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, SleepScoreLevel) {
    ///未更新
    SleepScoreLevel_UnKnow,
    ///偏低
    SleepScoreLevel_Low,
    ///正常
    SleepScoreLevel_Normal,
    ///偏高
    SleepScoreLevel_Hight
};

//MARK: - 全天睡眠统计分析
@interface JLAnalyzeSleep : NSObject
///夜间睡眠得分
@property(nonatomic,assign)NSInteger sleepScore;
///深睡比例
@property(nonatomic,assign)NSInteger deepSleepPresent;
/// 浅睡比例
@property(nonatomic,assign)NSInteger shallowSleepPresent;
/// rem比例
@property(nonatomic,assign)NSInteger remSleepPresent;
///总睡眠时长评价
@property(nonatomic,assign)SleepScoreLevel allSleepLevel;
///深睡时长评价
@property(nonatomic,assign)SleepScoreLevel deepSleepLevel;
///浅睡时长评价
@property(nonatomic,assign)SleepScoreLevel shallowSleepLevel;
///rem睡眠时长评价
@property(nonatomic,assign)SleepScoreLevel remSleepLevel;
/// 深睡连续性得分
@property(nonatomic,assign)NSInteger deepSleepScre;
///夜间醒来次数
@property(nonatomic,assign)NSInteger weakupNum;

@end


@interface JLWearSleepModel:NSObject
/// 睡眠类型
@property(nonatomic,assign)WatchSleepType type;
/// 睡眠时长
@property(nonatomic,assign)NSInteger  duration;

@end

@interface SleepData:NSObject
/// 开始时间
@property(nonatomic,strong)NSDate *startDate;
/// 睡眠类型数组
@property(nonatomic,strong)NSArray<JLWearSleepModel *> *sleeps;

@end

@interface JLWearSyncHealthSleepChart : JLWearSyncHealthChart

/// 睡眠数据
@property(nonatomic,strong)NSArray<SleepData *> *sleepDataArray;
///睡眠结果分析
@property(nonatomic,strong)JLAnalyzeSleep *analyze;

-(instancetype)initChart:(NSData *)sourceData;

@end


NS_ASSUME_NONNULL_END
