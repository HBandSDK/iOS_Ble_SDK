//
//  JLSedentaryRmdModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 久坐提醒
@interface JLSedentaryRmdModel : JLwSettingModel

///开关
@property(nonatomic,assign)BOOL status;

/// 提醒模式
@property(nonatomic,assign)WatchRemindType rType;

/// 午休免打扰：关闭/打开（午休时段为12：00-14：00)
@property(nonatomic,assign)BOOL doNotDisturb;

/// 开始时间
@property(nonatomic,strong)WatchTimer *begin;

/// 结束时间
@property(nonatomic,strong)WatchTimer *end;

- (instancetype)initWithData:(NSData *)data;

/// 创建一个设置久坐提醒的位置
/// @param type 提醒模式
/// @param status 开关
/// @param dnd 午休免打扰
/// @param start 开始时间
/// @param ed 结束时间
- (instancetype)initWithModel:(WatchRemindType)type Status:(BOOL)status DoNotDisturb:(BOOL)dnd Begin:(WatchTimer *)start End:(WatchTimer *)ed;

@end

NS_ASSUME_NONNULL_END
