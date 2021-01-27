//
//  VPHRVPublicTool.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/11/21.
//  Copyright © 2018 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPHRVLorentAnalysisModel.h"

@interface VPHRVPublicTool : NSObject

/**
 获取某一天HRV的健康评分

 @param hrvDatas 从SDK数据库中取出某一天的hrv数据
 @return 健康评分
 */
+ (NSInteger)vp_hrvScoreWithOneDayHrvData:(NSArray *)hrvDatas;

/**
 获取hrv 10分钟列表数据其中每个数组下十个字典, 内容包含10分钟hrv的平均值和这10分钟每1分钟的hrv值

 @param hrvDatas 从SDK数据库中取出某一天的hrv数据
 @return 10分钟列表的数据
 */
+ (NSArray *)vp_hrvTenMinuteArrayWithWithOneDayHrvData:(NSArray *)hrvDatas;

/**
 获取洛伦兹散点图的评论
 当返回nil使用vp_noAnalysisReportTipLocal这个方法去提示用户
 @param hrvDatas 从SDK数据库中取出某一天的hrv数据
 @return 返回分析的结果, 如果nil则代表数据太少,无法获取分析结果
 */
+ (NSArray<VPHRVLorentAnalysisModel *>*)vp_hrvLerentAnalysisWithOneDayHrvData:(NSArray *)hrvDatas;

//洛伦兹散点图报告 这句话的本地化
+ (NSString *)vp_lorentReportTitleLocal;

//没有分析报告的本地话提示语
+ (NSString *)vp_noAnalysisReportTipLocal;

@end
