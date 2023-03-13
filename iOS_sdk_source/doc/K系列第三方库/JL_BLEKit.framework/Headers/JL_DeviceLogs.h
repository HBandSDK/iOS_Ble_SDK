//
//  JL_DeviceLogs.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/5/12.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import "JL_FunctionBaseManager.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum : UInt8 {
    LogTypeDownloading = 0x00,
    LogTypeFailed = 0x01,
    LogTypeSucceed = 0x02
} DeviceLogType;

typedef void(^JLDeviceLogBK)(DeviceLogType type,float progress,NSString *_Nullable tempSavePath);

@interface JL_DeviceLogs : JL_FunctionBaseManager


/// 检查获取设备log日志
/// @param block 回调结果
-(void)deviceLogDownload:(JLDeviceLogBK)block;


@end

NS_ASSUME_NONNULL_END
