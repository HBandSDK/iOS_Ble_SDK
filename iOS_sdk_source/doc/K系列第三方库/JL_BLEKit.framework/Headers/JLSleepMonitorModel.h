//
//  JLSleepMonitorModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 睡眠监测设置
@interface JLSleepMonitorModel : JLwSettingModel
///开关类型
@property(nonatomic,assign)WatchSwitchType status;
///开始时间
@property(nonatomic,strong)WatchTimer *start;
/// 结束时间
@property(nonatomic,strong)WatchTimer *end;

-(instancetype)initWithData:(NSData *)data;

/// 构建一个睡眠监测设置
/// @param status 状态开关
/// @param begin 开始时间
/// @param end 结束时间
-(instancetype)initWithSwitchStatus:(WatchSwitchType)status Begin:(WatchTimer *)begin End:(WatchTimer *)end;


@end

NS_ASSUME_NONNULL_END
