//
//  JL_SDM_OxSaturation.h
//  Test
//
//  Created by EzioChan on 2021/4/7.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JLOxSaturationType) {
    //当前血氧饱和度
    JLOxSaturation_nowSta = 0x01,
    //最大血氧
    JLOxSaturation_max = 0x01 << 1,
    //最小血氧
    JLOxSaturation_min = 0x01 << 2,
    //单次测量
    JLOxSaturation_single = 0x01 << 3
};

/// 血氧饱和度
@interface JL_SDM_OxSaturation : JLSportDataModel

/// 饱和度
@property(nonatomic,assign)int staturation;
/// 最大饱和度
@property(nonatomic,assign)uint8_t max;
/// 最小饱和度
@property(nonatomic,assign)uint8_t min;

/// 单次测量的饱和度
@property(nonatomic,assign)uint8_t singleStaturation;

/// 是否为单次测量的数据
@property(nonatomic,assign)BOOL isSingle;


/// 血氧饱和度
/// 处理回复数据内容
/// @param value 数据内容
/// @param submask 功能标记位
+(JL_SDM_OxSaturation*)responseData:(NSData *)value subMask:(NSData *)submask;

/// 请求内容
+(JL_SDM_OxSaturation*)require;


/// 请求血氧浓度
/// @param type 类型
/// 该类型可以同时请求多个，诸如：JLOxSaturation_nowSta | JLOxSaturation_max | JLOxSaturation_min
+(JL_SDM_OxSaturation*)requireByBit:(JLOxSaturationType)type;


@end

NS_ASSUME_NONNULL_END
