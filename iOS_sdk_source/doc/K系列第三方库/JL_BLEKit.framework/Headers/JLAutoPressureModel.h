//
//  JLAutoPressureModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/10/12.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

///压力自动检测模式
typedef NS_ENUM(UInt8, WatchAPLeveType) {
    ///放松
    WatchAPLeve_Relex = 0x00,
    /// 正常
    WatchAPLeve_Normal = 0x01,
    /// 中等
    WatchAPLeve_Middle = 0x02,
    /// 偏高
    WatchAPLeve_Hight = 0x03
};

@interface JLAutoPressureModel : JLwSettingModel

///开关
@property(nonatomic,assign)BOOL status;
/// 模式
@property(nonatomic,assign)WatchAPLeveType model;

-(instancetype)initWithData:(NSData *)data;

-(instancetype)initWithModel:(WatchAPLeveType)model switchStatus:(BOOL)status;

@end

NS_ASSUME_NONNULL_END
