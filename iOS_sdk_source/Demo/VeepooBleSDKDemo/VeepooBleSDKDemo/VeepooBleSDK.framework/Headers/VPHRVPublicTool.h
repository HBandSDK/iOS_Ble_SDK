//
//  VPHRVPublicTool.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/11/21.
//  Copyright © 2018 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPHRVPublicTool : NSObject


/**
 获取某一天HRV的健康评分

 @param hrvDatas 从SDK数据库中取出某一天的hrv数据
 @return 健康评分
 */
+ (NSInteger)vp_hrvScoreWithOneDayHrvData:(NSArray *)hrvDatas;

@end

NS_ASSUME_NONNULL_END
