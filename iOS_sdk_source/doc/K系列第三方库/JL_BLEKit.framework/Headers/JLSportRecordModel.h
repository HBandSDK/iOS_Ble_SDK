//
//  JLSportRecordModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/4/29.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"

@class JLWatchExerciseIntens;

NS_ASSUME_NONNULL_BEGIN


//MARK:- JL_SRM_DataFormat
/*
 属性字段说明：
 type决定了数据包的类型，以及其他属性的值
 ///开始包
 JL_SRM_Start = 0x00,
 startDate 具备意义
 
 ///基础包
 JL_SRM_Basic = 0x01,
 heartRate 具备意义
 speed 具备意义
 stride 具备意义
 
 ///暂停包
 JL_SRM_Pause = 0x02,
 pauseDate 具备意义
 
 ///每公里配速包
 JL_SRM_Pace = 0x03,
 pace 具备意义
 numKm 具备意义
 
 ///结束包
 JL_SRM_End = 0xff,
 endDate
 */
@interface JL_SRM_DataFormat : NSObject
/// 数据包类型
@property(nonatomic,assign)JL_SRMDataType type;
/// 开始运动时间
/// 当type为JL_SRM_Start时，具备值意义
@property(nonatomic,strong)NSDate *startDate;
/// 暂停时间包
///当type为JL_SRM_Pause时，具备值意义
@property(nonatomic,strong)NSDate *pauseDate;
/// 结束时间包
/// 当type为JL_SRM_End时，具备值意义
@property(nonatomic,strong)NSDate *endDate;
/// 心率
/// 当type为JL_SRM_Basic时，具备值意义
@property(nonatomic,assign)NSInteger heartRate;
/// 速度
/// 当type为JL_SRM_Basic时，具备值意义
@property(nonatomic,assign)NSInteger speed;
/// 步频
/// 当type为JL_SRM_Basic时，具备值意义
@property(nonatomic,assign)NSInteger stride;
///配速， 单位：秒
///当type为JL_SRM_Pace时，具备值意义
@property(nonatomic,assign)NSInteger pace;
/// 第N公里
/// 当type为JL_SRM_Pace时，具备值意义
@property(nonatomic,assign)NSInteger numKm;
///原始数据长度
@property(nonatomic,assign)NSInteger length;

@end


//MARK:- JLSportRecordModel
@interface JLSportRecordModel : NSObject

/// 运动模式
@property(nonatomic,assign)WatchSportType modelType;
/// 版本号
@property(nonatomic,assign)UInt8 version;

///保留位2
@property(nonatomic,strong)NSData *reservedBit2;
///间隔
///有效范围:1~180 , 单位是秒
@property(nonatomic,assign)NSInteger interval;

/// 保留位
@property(nonatomic,strong)NSData *reservedBit;

///运动数据列表
@property(nonatomic,strong)NSArray<JL_SRM_DataFormat*> *dataArray;

/// 运动时长
///有效范围: 1-28800，单位是秒
@property(nonatomic,assign)NSInteger duration;

/// 距离
/// 有效范围: 1- 65535，单位是0.01公里（10米）
@property(nonatomic,assign)NSInteger distance;

/// 热量
///有效范围: 1- 65535 ,  单位是千卡，Kcal
@property(nonatomic,assign)NSInteger calories;

///步数
///有效范围: 0 - 200000, 单位是步
@property(nonatomic,assign)NSInteger step;

/// 恢复时间
/// 时间格式是：HH:mm
@property(nonatomic,strong)NSString *recoveryTime;

///心率模式
@property(nonatomic,assign)WatchHeartRateType heartRateType;

/// 运动强度类型数组
@property(nonatomic,strong)NSArray <JLWatchExerciseIntens *> *exerciseIntensArray;

/// 源数据
@property(nonatomic,strong)NSData *sourceData;

/// 初始化一个运动记录数据
/// @param data 数据内容
-(instancetype)initWithData:(NSData *)data;

/// 用于检查数据中的开始时间
/// @param data 文件数据
+(NSDate *)startDate:(NSData *)data;



@end

NS_ASSUME_NONNULL_END
