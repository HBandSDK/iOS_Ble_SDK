//
//  JL_CallManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"
NS_ASSUME_NONNULL_BEGIN

@interface JL_CallManager : JL_FunctionBaseManager

#pragma mark ---> 拨打电话
/**
 @param number 电话号码
 @param result 回复
 */
-(void)cmdPhoneCall:(NSString*)number Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 设备通话状态
extern NSString *kJL_MANAGER_CALL_STATUS;

#pragma mark - 案子API
#pragma mark ---> 通知设备播放来电号码的方式
/**
 通知设备播放来电号码的方式
 @param way        正常模式:0x00  播放文件模式:0x01
 */
-(void)cmdPhoneNumberOnWay:(uint8_t)way;

@end

NS_ASSUME_NONNULL_END
