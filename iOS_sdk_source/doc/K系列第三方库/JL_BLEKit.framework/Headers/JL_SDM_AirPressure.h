//
//  JL_SDM_AirPressure.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 压力实时
@interface JL_SDM_AirPressure : JLSportDataModel
/// 实时
@property(nonatomic,assign)int realTime;
/// 最高
@property(nonatomic,assign)int max;
/// 最低
@property(nonatomic,assign)int min;

/// 处理回复数据内容
/// @param value 数据内容
/// @param submask 功能标记位
+(JL_SDM_AirPressure*)responseData:(NSData *)value subMask:(NSData *)submask;

/// 请求内容设置
/// @param rt 是否需要实时气压
/// @param min 是否需要最小气压
/// @param max 是否需要最大气压
+(JL_SDM_AirPressure*)requireRealTime:(BOOL)rt min:(BOOL)min Max:(BOOL)max;



@end

NS_ASSUME_NONNULL_END
