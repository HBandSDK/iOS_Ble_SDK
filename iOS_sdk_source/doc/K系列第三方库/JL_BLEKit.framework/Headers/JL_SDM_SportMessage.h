//
//  JL_SDM_SportMessage.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/4/8.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLSportDataModel.h"
#import "JLWatchEnum.h"
NS_ASSUME_NONNULL_BEGIN

@interface JL_SDM_SportMessage : JLSportDataModel

/// 运动模式
@property(nonatomic,assign)JL_SportPattern sportPattern;
/// 距离，单位：0.01km
@property(nonatomic,assign)int               distance;
/// 开始时间
@property(nonatomic,strong)NSDate            *startTime;
/// 结束时间
@property(nonatomic,strong)NSDate            *endTime;
/// 热量，单位:千卡 Kcal
@property(nonatomic,assign)int               xkcal;
/// 速度。单位：0.01 km/h
@property(nonatomic,assign)int               speed;


/// 分析返回的数据
/// @param value subData
/// @param submask submask
+(JL_SDM_SportMessage *)responseData:(NSData *)value subMask:(NSData *)submask;

/// 请求要获取的内容
/// @param m 是否请求模式
/// @param d 是否请求距离
/// @param st 是否请求开始时间
/// @param et 是否请求结束时间
/// @param kcal 是否请求卡路里
/// @param sp 是否请求速度
+(JL_SDM_SportMessage *)requireModel:(BOOL)m distance:(BOOL)d start:(BOOL)st end:(BOOL)et kcal:(BOOL)kcal speed:(BOOL)sp;

/// 请求全部数据
+(JL_SDM_SportMessage *)requireAll;



@end

NS_ASSUME_NONNULL_END
