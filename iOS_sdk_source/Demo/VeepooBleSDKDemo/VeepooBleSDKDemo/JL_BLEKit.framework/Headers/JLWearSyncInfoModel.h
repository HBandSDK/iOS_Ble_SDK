//
//  JLWearSyncInfoModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/27.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLWearSyncDataModel : NSObject

/// 基础返回对象
@property(nonatomic,strong)NSData *basicData;

@end


@interface JLWearSyncInfoModel : JLWearSyncDataModel

///运动模式类型
@property(nonatomic,assign)WatchSportType sportType;

/// 运动状态
@property(nonatomic,assign)WatchSportStatus status;

///运动Id
@property(nonatomic,assign)double sportID;

///设备是否包含GPS
@property(nonatomic,assign)BOOL  hasGPS;

///心率模式
@property(nonatomic,assign)WatchHeartRateType heartRateType;

///建议实时数据读取时间间隔，单位：ms
@property(nonatomic,assign)UInt16   interval;

/// 利用设备返回的数据初始化一个运动信息对象
/// @param data 设备返回数据
+(JLWearSyncInfoModel *)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
