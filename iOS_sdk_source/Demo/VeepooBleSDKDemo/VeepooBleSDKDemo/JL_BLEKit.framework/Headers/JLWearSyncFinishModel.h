//
//  JLWearSyncFinishModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"
NS_ASSUME_NONNULL_BEGIN


@interface JLWearSyncFinishDataModel:NSObject

@property(nonatomic,strong)NSData *basicData;

@end


@interface JLWatchExerciseIntens:NSObject

/// 运动强度类型
@property(nonatomic,assign)WatchExerciseIntensityType type;

/// 持续时间
@property(nonatomic,assign)UInt32 duration;

@end

@interface JLWearSyncFinishModel : JLWearSyncFinishDataModel

/// 结束时间
@property(nonatomic,strong)NSDate *endTime;

/// 运动恢复时间
/// 格式 ：hour : min
@property(nonatomic,strong)NSString *recyleTime;

/// 运动记录文件ID
@property(nonatomic,assign)UInt16 sportId;

/// 运动记录文件大小
@property(nonatomic,assign)UInt16 fileSize;

/// 运动强度类型数组
@property(nonatomic,strong)NSArray <JLWatchExerciseIntens *> *durationArray;


+(JLWearSyncFinishModel *)initWithData:(NSData*)data;

@end

NS_ASSUME_NONNULL_END
