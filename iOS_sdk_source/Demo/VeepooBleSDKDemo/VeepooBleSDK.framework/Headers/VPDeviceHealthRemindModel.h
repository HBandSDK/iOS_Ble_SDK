//
//  VPDeviceHealthRemindModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2023/3/14.
//  Copyright © 2023 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceHealthRemindModel : NSObject

/// 提醒类型
@property (nonatomic, assign) VPDeviceHealthRemindType type;

/// 开始时间-小时，请自行限制范围在[0,24]内
@property (nonatomic, assign) uint8_t startHour;

/// 开始时间-分钟，请自行限制范围在[0, 60]内
@property (nonatomic, assign) uint8_t startMinute;

/// 结束时间-小时，请自行限制范围在[0,24]内
@property (nonatomic, assign) uint8_t endHour;

/// 结束时间-分钟，请自行限制范围在[0, 60]内
@property (nonatomic, assign) uint8_t endMinute;

/// 提醒间隔时长
@property (nonatomic, assign) uint8_t remindInterval;

/// 提醒是否开启
@property (nonatomic, assign) BOOL open;

/// 设备返回的数据解析，内部使用
- (void)parseWithDeviceData:(NSData *)deviceData;

@end

NS_ASSUME_NONNULL_END

