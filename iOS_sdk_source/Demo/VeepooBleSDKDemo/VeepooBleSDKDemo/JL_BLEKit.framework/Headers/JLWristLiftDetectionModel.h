//
//  JLWristLiftDetectionModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 抬腕监测设置
@interface JLWristLiftDetectionModel : JLwSettingModel
///开关
@property(nonatomic,assign)WatchSwitchType status;
/// 提醒模式
@property(nonatomic,assign)WatchRemindType rType;
/// 开始时间
@property(nonatomic,strong)WatchTimer *start;

/// 结束时间
@property(nonatomic,strong)WatchTimer *end;


-(instancetype)initWithData:(NSData *)data;

/// 构建一个抬腕提醒设置对象
/// @param type 提醒类型
/// @param status 开关类型
/// @param begin 开始时间
/// @param ed 结束时间
- (instancetype)initWithModel:(WatchRemindType)type Status:(WatchSwitchType )status Begin:(WatchTimer *)begin End:(WatchTimer *)ed;

@end

NS_ASSUME_NONNULL_END
