//
//  JLWearSync.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/26.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_RCSP.h"
#import "JLWatchEnum.h"
#import "JL_EntityM.h"
#import "JL_SDM_Header.h"
#import "JL_WatchSyncProtocol.h"


NS_ASSUME_NONNULL_BEGIN

/// 穿戴设备状态同步指令
@interface JLWearSync : NSObject

+(instancetype)share;

/// 加入协议响应
/// @param delegate 对象
-(void)addProtocol:(id<JLWearSyncProtocol>)delegate;

/// 移除协议响应
/// @param delegate 对象
-(void)removeProtocol:(id<JLWearSyncProtocol>)delegate;

/// 读取运动信息
/// @param entity 设备entity
/// @param block JLWearSyncInfoModel 回调
/// 本条命令的回调通过JLWearSyncProtocol协议
///-(void)jlWearSyncSportInfo:(JLWearSyncInfoModel *_Nonnull)model;
-(void)w_requireSportInfoWith:(JL_EntityM *)entity Block:(JL_CB_SyncSportInfo _Nullable)block;

///开始运动命令
/// @param type 运动类型
/// @param entity 设备entity
/// @param block 命令成功与否回调
-(void)w_SportStart:(WatchSportType)type With:(JL_EntityM *)entity Block:(JL_CB_Status _Nullable)block;

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
