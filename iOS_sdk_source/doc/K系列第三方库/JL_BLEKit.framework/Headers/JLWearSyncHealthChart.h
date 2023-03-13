//
//  JLWearSyncHealthChart.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/30.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLWatchEnum.h"
#import "JLModel_SmallFile.h"


NS_ASSUME_NONNULL_BEGIN

/// 数据格式
@interface JLWearSyncHealthDataModel : NSObject

/// 时间（时分）
@property(nonatomic,strong)NSString *HHmm;

/// 数据内容
@property(nonatomic,strong)NSData *data;


@end

@interface JLWearSyncHealthChart : NSObject

/// 文件类型
@property(nonatomic,assign)JL_SmallFileType type;

/// 日期
@property(nonatomic,strong)NSString *yyyyMMdd;

/// 版本
@property(nonatomic,assign)UInt8 version;

/// 存储间隔
@property(nonatomic,assign)UInt8 interval;

/// CRC校验码
@property(nonatomic,assign)UInt16 crcCode;

/// 保留位
@property(nonatomic,assign)UInt16 reserved;

/// N*数据格式
@property(nonatomic,strong)NSArray<JLWearSyncHealthDataModel *> *dataArray;

/// 源数据
@property(nonatomic,strong)NSData *sourceData;

-(void)createHeadInfo:(NSData *)dt;

@end





NS_ASSUME_NONNULL_END
