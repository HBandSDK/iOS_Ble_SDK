//
//  JL_AlarmClockManager.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/12/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_AlarmSetting.h>
#import <JL_BLEKit/RTC_RingInfo.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JLModel_RTC.h>
#import <JL_BLEKit/JLModel_Ring.h>
#import "JL_FunctionBaseManager.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_RtcOperate) {
    JL_FlashOperateFlagRead             = 0x00, //读取
    JL_FlashOperateFlagWrite            = 0x01, //设置
};

@interface JL_AlarmClockManager : JL_FunctionBaseManager

#pragma mark ---> 设置/增加闹钟
/**
 @param array 闹钟模型数组
 @param result 回复
 */
-(void)cmdRtcSetArray:(NSArray<JLModel_RTC *>*)array Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 删除闹钟
/**
 @param array 闹钟序号数组
 @param result 回复
 */
-(void)cmdRtcDeleteIndexArray:(NSArray<NSNumber *>*)array Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 停止闹钟响声
-(void)cmdRtcStopResult:(JL_CMD_RESPOND __nullable)result;
#pragma mark --> 闹钟试听响铃
-(void)cmdRtcAudition:(JLModel_RTC *)rtc Option:(BOOL)option result:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 闹钟响与停止
extern NSString *kJL_MANAGER_RTC_RINGING;       //闹钟正在响
extern NSString *kJL_MANAGER_RTC_RINGSTOP;      //闹钟停止响
extern NSString *kJL_MANAGER_RTC_AUDITION;      //闹钟铃声试听

typedef void(^JL_RTC_ALARM_BK)(NSArray <JLModel_AlarmSetting *>* __nullable array, uint8_t flag);
#pragma mark ---> 闹铃设置

/**
 @param operate 0x00:读取 0x01:设置
 @param index     掩码 (0x01设置第1个闹钟，0x03设置第一个和第二个闹钟)
 @param setting 设置选项，读取时无需传入
 @param result 回复
 */
-(void)cmdRtcOperate:(JL_RtcOperate)operate
               Index:(uint8_t)index
             Setting:(JLModel_AlarmSetting* __nullable)setting
              Result:(JL_RTC_ALARM_BK __nullable)result;

#pragma mark ---> 【闹钟信息】解析
+(NSMutableArray<JLModel_RTC*> *)makeOutRtc:(NSData*)data RtcType:(uint8_t)rtcType;

#pragma mark ----> [默认闹钟铃声]解析
+(NSMutableArray<JLModel_Ring*> *)makeOutRtcDefaultRing:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
