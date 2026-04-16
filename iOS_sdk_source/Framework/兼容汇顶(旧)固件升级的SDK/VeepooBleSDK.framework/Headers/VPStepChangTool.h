//
//  VPStepChangTool.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/9.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPStepChangTool : NSObject

/**
 *  通过步数和身高获取用户的 step cal dis 这个用于数据库存储，结构如下
 @{
    @"Step":sum_Sp,
    @"Dis":dis_Sp,
    @"Cal":cal_Sp
 };
 *
 *  @param step_cnt        步数
 *  @param user_stature 身高
 *
 *  @return 获取用户的详细信息
 */
+ (NSDictionary *)veepooSDKGetStepDictionaryWithStep:(NSInteger)step_cnt userStature:(NSUInteger)user_stature;

/**
 通过身高和手环返回的计步数据获取Step Cal Dis，内部使用，结构如下
@{
    @"Step":sum_Sp,
    @"Dis":dis_Sp,
    @"Cal":cal_Sp
 };
 @param stepData 读取计步返回的数据
 @param user_stature 用户的身高
 @return 用户计步的数据
 */
+ (NSDictionary *)veepooSDKGetStepDictionaryWithStepData:(NSData *)stepData userStature:(NSUInteger)user_stature;

@end
