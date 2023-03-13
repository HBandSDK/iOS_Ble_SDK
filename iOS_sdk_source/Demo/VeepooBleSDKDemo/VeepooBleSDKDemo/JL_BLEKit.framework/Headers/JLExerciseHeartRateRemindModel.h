//
//  JLExerciseHeartRateRemindModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"
#import "JLWatchEnum.h"
NS_ASSUME_NONNULL_BEGIN

/// 运动心率提醒设置
@interface JLExerciseHeartRateRemindModel : JLwSettingModel
///开关
@property(nonatomic,assign)BOOL status;
/// 上限心率0~255
@property(nonatomic,assign)uint8_t maxRate;

/// 心率区间划分方式：
///  0x00:最大心率百分比
///  0x01:存储心率百分比s
@property(nonatomic,assign)WatchHeartRateType way;

-(instancetype)initWithWay:(WatchHeartRateType)way maxRate:(uint8_t)max switchStatus:(BOOL)status;

-(instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
