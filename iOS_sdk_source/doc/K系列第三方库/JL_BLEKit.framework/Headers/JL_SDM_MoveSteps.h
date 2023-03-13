//
//  JL_SDM_MoveSteps.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import "JLSportDataModel.h"

NS_ASSUME_NONNULL_BEGIN

///实时步数
@interface JL_SDM_MoveSteps : JLSportDataModel
/// 实时步数
@property(nonatomic,assign)NSInteger rtStep;

/// 热量，单位：千卡
@property(nonatomic,assign)NSInteger calories;

/// 距离，单位：0.01公里
@property(nonatomic,assign)NSInteger distance;
/// 处理回复数据内容
/// @param value 数据内容
/// @param submask 功能标记位
+(JL_SDM_MoveSteps*)responseData:(NSData *)value subMask:(NSData *)submask;

/// 选择性请求内容
+(JL_SDM_MoveSteps*)require:(BOOL)rst distance:(BOOL)dts calories:(BOOL)ca;


@end

NS_ASSUME_NONNULL_END
