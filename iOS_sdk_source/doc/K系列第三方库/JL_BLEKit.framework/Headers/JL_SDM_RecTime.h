//
//  JL_SDM_RecTime.h
//  Test
//
//  Created by EzioChan on 2021/4/7.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_RecTime : JLSportDataModel

@property(nonatomic,assign)int hour;
@property(nonatomic,assign)int min;

/// 处理回复数据内容
/// @param value 数据内容
/// @param submask 功能标记位
+(JL_SDM_RecTime*)responseData:(NSData *)value subMask:(NSData *)submask;

/// 请求内容
+(JL_SDM_RecTime*)require;

@end

NS_ASSUME_NONNULL_END
