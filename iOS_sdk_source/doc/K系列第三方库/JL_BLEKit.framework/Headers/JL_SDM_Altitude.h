//
//  JL_SDM_Altitude.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

///海拔高度相关
@interface JL_SDM_Altitude : JLSportDataModel

/// 最大值
@property(nonatomic,assign)float max;
/// 最小值
@property(nonatomic,assign)float min;
/// 实时的
@property(nonatomic,assign)float realTime;

/// 处理回复数据内容
/// @param value 数据内容
/// @param submask 功能标记位
+(JL_SDM_Altitude*)responseData:(NSData *)value subMask:(NSData *)submask;

/// 请求海拔内容设置
/// @param rt 是否需要实时海拔
/// @param min 是否需要最小海拔
/// @param max 是否需要最大海拔
+(JL_SDM_Altitude*)requireRealTime:(BOOL)rt min:(BOOL)min Max:(BOOL)max;



@end

NS_ASSUME_NONNULL_END
