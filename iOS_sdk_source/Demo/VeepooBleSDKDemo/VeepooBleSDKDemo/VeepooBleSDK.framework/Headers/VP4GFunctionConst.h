//
//  VP4GFunctionConst.h
//  VeepooBleSDK
//
//  Created by vp_app_01 on 2025/10/20.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

/**------------------------------------状态枚举------------------------------------**/
// 协议指令类型
typedef NS_ENUM(uint8_t, VP4GOrderTagType) {
    VP4GOrderTagTypeSetServerACKInfo = 0x01,             // 设备回应设置服务信息结果
    VP4GOrderTagTypeReportedConfigurationInfo = 0x02,    // 设备回应 4G 配置信息
    VP4GOrderTagTypeVerifyInfoSuccess = 0x03,            // 信息核准成功
    VP4GOrderTagTypeServerInfoChange = 0x04,             // 设备上报 4G 信息变更
};


// 4G 设备配置信息标签
typedef NS_ENUM(UInt8, VP4GConfigContentTag) {
    VP4GConfigContentTagTotalLength = 0xA0,      // 内容总长
    VP4GConfigContentTagIPAddress = 0xA1,        // IP地址
    VP4GConfigContentTagPort = 0xA2,             // 端口
    VP4GConfigContentTagUsername = 0xA3,         // 用户名
    VP4GConfigContentTagPassword = 0xA4,         // 密码
    VP4GConfigContentTagTimestamp = 0xA5,        // 同步服务器的时间戳
    VP4GConfigContentTagMobileSwitch = 0xA6,     // 4G 开关
    VP4GConfigContentTagUploadSwitch = 0xA7,     // 数据上传开关
    VP4GConfigContentTagReportInterval = 0xA8,   // 上报时间间隔
    VP4GConfigContentTagRecoverTimestamp = 0xA9  // 恢复时间戳
};


// 标记当前修改 4G 服务的类型
typedef NS_ENUM(uint8_t, VP4GSetInfoType) {
    VP4GSetInfoTypeNull = 0,
    VP4GSetInfoType4GSwitchEnableState = 1,
    VP4GSetInfoType4GUploadSwitchEnableState = 2,
    VP4GSetInfoType4GUploadInterval = 3,
    VP4GSetInfoTypeBindAccount = 4,
    VP4GSetInfoTypeModifyAccountValidState = 5,
    VP4GSetInfoTypeModifyMQTT = 6
};
