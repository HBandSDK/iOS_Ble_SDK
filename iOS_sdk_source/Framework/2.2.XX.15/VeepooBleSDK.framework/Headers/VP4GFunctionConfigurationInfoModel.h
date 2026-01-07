//
//  VP4GFunctionConfigurationInfoModel.h
//  VeepooBleSDK
//
//  Created by vp_app_01 on 2025/10/20.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VP4GFunctionConst.h"

NS_ASSUME_NONNULL_BEGIN

// TLV 数据结构
@interface VP4GTagInfo : NSObject

@property (nonatomic, assign) VP4GConfigContentTag contentTag;

@property (nonatomic, strong) NSData *value;

@end


@interface VP4GFunctionConfigurationInfoModel : NSObject

/// 设备端域名信息（IP 地址）
@property (nonatomic, copy) NSString *deviceHost;
/// 设备端口信息
@property (nonatomic, assign) uint16_t devicePort;
/// 设备端登录的账号名称
@property (nonatomic, copy) NSString *account;
/// 设备端登录的账号密码
@property (nonatomic, copy) NSString *password;
/// 4G 开关， 0为关，1为开
@property (nonatomic, assign) BOOL is4GSwitchEnable;
/// 数据上传开关， 0为关，1为开
@property (nonatomic, assign) BOOL isSyncDataSwitchEnable;
/// 上报时间间隔
@property (nonatomic, assign) uint8_t intervalTime;
/// 同步服务器时间戳
@property (nonatomic, assign) uint8_t syncTimestamp;
/// 恢复时间戳
@property (nonatomic, assign) uint8_t recoveryTimestamp;

- (void)changeValueWithData:(NSData *)data;


@end



NS_ASSUME_NONNULL_END
