//
//  JL_WatchSyncProtocol.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "JL_SDM_Header.h"
#import "JL_EntityM.h"

#ifndef JL_WatchSyncProtocol_h
#define JL_WatchSyncProtocol_h

@protocol JLWearSyncProtocol <NSObject>

@optional
/// 运动信息返回
/// @param model 运动信息对象
/// @param entity 设备entity
-(void)jlWearSyncSportInfo:(JLWearSyncInfoModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

/// 结束运动返回内容
/// @param model 结束时间相隔信息对象
/// @param entity 设备entity
-(void)jlWearSyncStopMotion:(JLWearSyncFinishModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

/// 开始运动返回消息
/// @param entity 设备entity
-(void)jlWearSyncStartMotionWith:(JL_EntityM *_Nonnull)entity;

/// 暂停运动
/// @param entity 设备entity
-(void)jlWearSyncStatusPauseWith:(JL_EntityM *_Nonnull)entity;

/// 继续运动
/// @param entity 设备entity
-(void)jlWearSyncStatusContiuneWith:(JL_EntityM *_Nonnull)entity;

/// 实时数据回调
/// @param model 实时数据模型
/// @param entity 设备entity
-(void)jlWearSyncRealTimeData:(JLWearSyncRealTimeModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

@end

#endif /* JL_WatchSyncProtocol_h */
