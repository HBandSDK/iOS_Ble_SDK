//
//  JLConsequentHeartRateModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 测量心率传感器设置
@interface JLConsequentHeartRateModel : JLwSettingModel
///开关
@property(nonatomic,assign)BOOL status;
/// 测量模式
@property(nonatomic,assign)WatchConsequentType rType;

/// 上限心率
@property(nonatomic,assign)UInt8    maxHeartRate;

/// 下限心率
@property(nonatomic,assign)UInt8    minHeartRate;

/// 是否包含上下心率区间
@property(nonatomic,assign)BOOL hasRange;

-(instancetype)initWithData:(NSData *)data;

/// 创建一个新的传感器设置对象
/// @param type 测量类型
/// @param status 开团状态
- (instancetype)initWithModel:(WatchConsequentType)type Status:(BOOL)status;

/// 创建一个新的传感器设置对象
/// 携带心率上下限的
/// @param type 测量类型
/// @param status 开关状态
/// @param min 心率下限
/// @param max 心率上限
- (instancetype)initWithModel:(WatchConsequentType)type Status:(BOOL)status Min:(UInt8) min Max:(UInt8)max;
@end

NS_ASSUME_NONNULL_END
