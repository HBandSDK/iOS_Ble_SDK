//
//  VPMultiBloodGlucoseModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/9/20.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPMultiBloodGlucoseItemModel : NSObject<NSCopying>

/// 小时，24制式，[0, 23]
@property (nonatomic, assign) uint8_t hour;
/// 分钟，[0, 59]
@property (nonatomic, assign) uint8_t minute;
/// 对应的血糖值，值域[300, 1500]，实际值域为[3.0, 15.0]
@property (nonatomic, assign) uint16_t value;

- (instancetype)initWithHour:(uint8_t)hour minute:(uint8_t)minute value:(uint16_t)value;

/// 内部使用，根据参数输出指令
- (NSData *)outPutCmdData;

@end

@interface VPMultiBloodGlucoseModel : NSObject<NSCopying>

/// 是否已开启私人模式
@property (nonatomic, assign) BOOL open;
/// 早餐前 只能设置在凌晨2:00点到12:00点之间
@property (nonatomic, strong) VPMultiBloodGlucoseItemModel *beforeBreakfast;
/// 早餐后
@property (nonatomic, strong) VPMultiBloodGlucoseItemModel *afterBreakfast;
/// 午餐前
@property (nonatomic, strong) VPMultiBloodGlucoseItemModel *beforeLunch;
/// 午餐后
@property (nonatomic, strong) VPMultiBloodGlucoseItemModel *afterLunch;
/// 晚餐前
@property (nonatomic, strong) VPMultiBloodGlucoseItemModel *beforeDinner;
/// 晚餐后
@property (nonatomic, strong) VPMultiBloodGlucoseItemModel *afterDinner;


@end

NS_ASSUME_NONNULL_END

