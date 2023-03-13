//
//  JLWearSyncCustom.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/4/13.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_RCSP.h"
#import "JL_EntityM.h"
#import "JL_SDM_Header.h"



NS_ASSUME_NONNULL_BEGIN

@protocol JLWearSyncCustomPtl <NSObject>

/// 运动信息返回
/// @param model 运动信息对象
/// @param entity 设备entity
-(void)jlWearSyncSportInfo:(JLWearSyncDataModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

/// 结束运动返回内容
/// @param model 结束时间相隔信息对象
/// @param entity 设备entity
-(void)jlWearSyncStopMotion:(JLWearSyncFinishDataModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

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
-(void)jlWearSyncRealTimeData:(JLWearSyncRealTimeData *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;

@end



@interface JLWearSyncCustom : NSObject

@property(nonatomic,weak)id<JLWearSyncCustomPtl> delegate;

/// 读取运动信息
/// @param entity 设备entity
/// @param block JLWearSyncInfoModel 回调
/// 本条命令的回调通过JLWearSyncProtocol协议
///-(void)jlWearSyncSportInfo:(JLWearSyncInfoModel *_Nonnull)model;
-(void)w_requireSportInfoWith:(JL_EntityM *)entity Block:(JL_CB_SyncSportDataInfo _Nullable)block;

///开始运动命令
/// @param type 运动类型
/// @param entity 设备entity
/// @param block 命令成功与否回调
-(void)w_SportStart:(UInt8)type With:(JL_EntityM *)entity Block:(JL_CB_Status _Nullable)block;

/// 结束运动命令
/// @param entity 设备entity
///本条命令的回调通过JLWearSyncProtocol协议
///-(void)jlWearSyncStopMotion:(JLWearSyncFinishModel *_Nonnull)model With:(JL_EntityM *_Nonnull)entity;
-(void)w_SportFinishWith:(JL_EntityM*)entity;

///暂停运动命令
/// @param entity 设备entity
/// @param block 命令成功与否回调
-(void)w_SportPauseWith:(JL_EntityM*)entity Block:(JL_CB_Status _Nullable)block;

///继续运动命令
/// @param entity 设备entity
/// @param block 命令成功与否回调
-(void)w_SportContinueWith:(JL_EntityM*)entity Block:(JL_CB_Status _Nullable)block;

/// 读取运动实时数据
/// @param entity 设备entity
///本条命令的回调通过JLWearSyncProtocol协议
-(void)w_requireRealTimeSportInfoWith:(JL_EntityM *)entity;

/// 实时数据获取时间间隔设置
/// @param interval 时间间隔，单位：ms
/// @param entity 设备entity
-(void)pr_setTimeInterval:(UInt16)interval With:(JL_EntityM *)entity;


@end

NS_ASSUME_NONNULL_END
