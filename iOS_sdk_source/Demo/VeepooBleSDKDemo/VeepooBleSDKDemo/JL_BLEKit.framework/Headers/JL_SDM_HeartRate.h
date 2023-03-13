//
//  JL_SDM_HeartBeat.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//
/*
 * 这是一个Sport Data Model的对象
 */
///心率model
#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 心率相关内容
@interface JL_SDM_HeartRate : JLSportDataModel
/// 实时心率
@property(nonatomic,assign)uint8_t realTime;
/// 静息心率
@property(nonatomic,assign)uint8_t resting;
/// 最大心率
@property(nonatomic,assign)uint8_t max;

/// 单次测量的心率
@property(nonatomic,assign)uint8_t singleRate;

/// 是否为单次测量的数据
@property(nonatomic,assign)BOOL isSingle;

/// 处理回复数据内容
/// @param value 数据内容
/// @param submask 功能标记位
+(JL_SDM_HeartRate*)responseData:(NSData *)value subMask:(NSData *)submask;

/// 请求心率内容设置
/// @param rt 是否需要实时心率
/// @param rting 是否需要静息心率
/// @param max 是否需要最大心率
+(JL_SDM_HeartRate*)requireRealTime:(BOOL)rt Resting:(BOOL)rting Max:(BOOL)max;

/// 单次测量
+(JL_SDM_HeartRate*)requireSingle;



@end

NS_ASSUME_NONNULL_END
