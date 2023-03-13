//
//  JLWearSyncRealTimeModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"

NS_ASSUME_NONNULL_BEGIN


@interface JLWearSyncRealTimeData : NSObject

@property(nonatomic,strong)NSData *basicData;

@end

@interface JLWearSyncRealTimeModel : JLWearSyncRealTimeData

/// 类型
@property(nonatomic,assign)UInt8 type;

/// 运动步数
@property(nonatomic,assign)UInt32 sportStep;

/// 运动距离，单位：0.01公里
@property(nonatomic,assign)UInt16 distance;

/// 运动时长：单位：秒
@property(nonatomic,assign)UInt32 exerciseTime;

/// 速度，单位0：0.01公里/小时，（倒数为配速，单位：秒/公里）
@property(nonatomic,assign)UInt16 speed;

/// 热量，单位：千卡
@property(nonatomic,assign)UInt16 calories;

/// 步频，单位：步/分钟
@property(nonatomic,assign)UInt16 cadence;

///步幅,单位:厘米
@property(nonatomic,assign)UInt16 stride;

///实时运动强度状态
@property(nonatomic,assign)WatchExerciseIntensityType statusType;

///运动实时心率
@property(nonatomic,assign)UInt8 heartRate;

+(JLWearSyncRealTimeModel *)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
