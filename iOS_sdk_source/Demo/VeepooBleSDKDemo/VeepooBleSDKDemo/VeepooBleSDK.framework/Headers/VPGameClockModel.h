//
//  VPGameClockModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/11/5.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"

NS_ASSUME_NONNULL_BEGIN

/// ZT79定制项目-游戏控制单条时段数据
@interface VPGameClockModel : NSObject<NSCopying>

/// 1~10（从1开始，最多10个）
@property (nonatomic, assign) uint8_t clockID;

/// 时段类型（见 VPGameClockType 枚举：1 星期重复，2 单次不重复，3 临时）
@property (nonatomic, assign) VPGameClockType clockType;

/// 开始年月日，仅在非重复和临时数据有效。年使用单字节表示，实际年份-2000，clockType为星期重复时此数据为全0
@property (nonatomic, assign) uint8_t clockYear;
@property (nonatomic, assign) uint8_t clockMonth;
@property (nonatomic, assign) uint8_t clockDay;

/// 重复星期（见 VPGameClockWeekday：bit0~bit6 对应周一~周日，VPGameClockWeekdayEveryDay 为每天）；clockType为临时和单次的时候此处值为 VPGameClockWeekdayNone
@property (nonatomic, assign) VPGameClockWeekday clockRepeat;

/// 开始时、分、秒，0x010203表示的时间为 01:02:03
@property (nonatomic, assign) uint8_t clockHour;
@property (nonatomic, assign) uint8_t clockMinute;
@property (nonatomic, assign) uint8_t clockSecond;

/// 从开始到结束的时长，单位分钟（持续时长，不小于5）
@property (nonatomic, assign) uint16_t clockDuration;

/// 开关状态，0是关，1是开
@property (nonatomic, assign) uint8_t clockState;

/// 非重复的，获取剩余时间(秒)，过期后返回0
- (NSInteger)getGameModelRemainTimeValue;

@end

NS_ASSUME_NONNULL_END
