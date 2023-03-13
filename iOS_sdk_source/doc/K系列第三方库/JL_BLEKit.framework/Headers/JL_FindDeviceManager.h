//
//  JL_FindDeviceManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/17.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_FindDeviceManager : JL_FunctionBaseManager

#pragma mark ---> 查找设备
// 设备查找手机的通知
// 携带了响铃时长🔔
// dict = @{@"op":@(操作类型),@"timeout":@(超时时间)};
extern NSString *kJL_MANAGER_FIND_PHONE;
// 手机查找设备
// 携带是否停止响铃
// dict = @{@"op":@(操作类型),@"timeout":@(超时时间)};
extern NSString *kJL_MANAGER_FIND_DEVICE;
// 查找设备命令
// @param isVoice 是否发声
// @param timeout 超时时间
// @param isIphone 是否设备查找手机（默认是手机找设备）
// @param opDict 这是一个可选项，若tws未连接，则该值无效，默认是全部播放
// 字典键值对说明：
// 播放方式 way: 0  全部播放
//             1  左侧播放
//             2  右侧播放
// 播放源 player: 0 APP端播放
//               1 设备端播放
// etc.全部播放&APP播放音效
// opDict：{@"way":@"0",@"player":@"0"}
-(void)cmdFindDevice:(BOOL)isVoice
             timeOut:(uint16_t)timeout
          findIphone:(BOOL)isIphone
           Operation:( NSDictionary * _Nullable )opDict;


@end

NS_ASSUME_NONNULL_END
