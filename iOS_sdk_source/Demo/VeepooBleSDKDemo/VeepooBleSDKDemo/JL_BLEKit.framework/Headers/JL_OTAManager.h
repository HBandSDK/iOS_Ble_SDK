//
//  JL_OTAManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/11/16.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_Device.h>

#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN


typedef NS_ENUM(UInt8, JL_OTAResult) {
    JL_OTAResultSuccess             = 0x00, //OTA升级成功
    JL_OTAResultFail                = 0x01, //OTA升级失败
    JL_OTAResultDataIsNull          = 0x02, //OTA升级数据为空
    JL_OTAResultCommandFail         = 0x03, //OTA指令失败
    JL_OTAResultSeekFail            = 0x04, //OTA标示偏移查找失败
    JL_OTAResultInfoFail            = 0x05, //OTA升级固件信息错误
    JL_OTAResultLowPower            = 0x06, //OTA升级设备电压低
    JL_OTAResultEnterFail           = 0x07, //未能进入OTA升级模式
    JL_OTAResultUpgrading           = 0x08, //OTA升级中
    JL_OTAResultReconnect           = 0x09, //OTA需重连设备(uuid方式)
    JL_OTAResultReboot              = 0x0a, //OTA需设备重启
    JL_OTAResultPreparing           = 0x0b, //OTA准备中
    JL_OTAResultPrepared            = 0x0f, //OTA准备完成
    JL_OTAResultFailVerification    = 0xf1, //升级数据校验失败
    JL_OTAResultFailCompletely      = 0xf2, //升级失败
    JL_OTAResultFailKey             = 0xf3, //升级数据校验失败
    JL_OTAResultFailErrorFile       = 0xf4, //升级文件出错
    JL_OTAResultFailUboot           = 0xf5, //uboot不匹配
    JL_OTAResultFailLenght          = 0xf6, //升级过程长度出错
    JL_OTAResultFailFlash           = 0xf7, //升级过程flash读写失败
    JL_OTAResultFailCmdTimeout      = 0xf8, //升级过程指令超时
    JL_OTAResultFailSameVersion     = 0xf9, //相同版本
    JL_OTAResultFailTWSDisconnect   = 0xfa, //TWS耳机未连接
    JL_OTAResultFailNotInBin        = 0xfb, //耳机未在充电仓
    JL_OTAResultReconnectWithMacAddr= 0xfc, //OTA需重连设备(mac方式)
    JL_OTAResultUnknown,                    //OTA未知错误
};
typedef NS_ENUM(UInt8, JL_OTAUrlResult) {
    JL_OTAUrlResultSuccess          = 0x00, //OTA文件获取成功
    JL_OTAUrlResultFail             = 0x01, //OTA文件获取失败
    JL_OTAUrlResultDownloadFail     = 0x02, //OTA文件下载失败
};
typedef NS_ENUM(UInt8, JL_OTAReconnectType) {
    JL_OTAReconnectTypeUUID          = 0x00, //OTA升级回连使用uuid
    JL_OTAReconnectTypeMACAddr       = 0x01, //OTA升级回连使用mac地址
};
typedef void(^JL_OTA_URL)(JL_OTAUrlResult result,
                          NSString* __nullable version,
                          NSString* __nullable url,
                          NSString* __nullable explain);
typedef void(^JL_OTA_RT)(JL_OTAResult result, float progress);


@interface JL_OTAManager : JL_FunctionBaseManager

-(void)noteEntityConnected;
-(void)noteEntityDisconnected;

#pragma mark - OTA升级
#pragma mark ---> OTA升级文件下载
/**
 @param key 授权key
 @param code 授权code
 @param result 回复
 */
-(void)cmdGetOtaFileKey:(NSString*)key
                   Code:(NSString*)code
                 Result:(JL_OTA_URL __nullable)result;

#pragma mark ---> OTA升级文件下载【MD5】
/**
@param key 授权key
@param code 授权code
@param hash  MD5值
@param result 回复
*/
-(void)cmdGetOtaFileKey:(NSString*)key
                   Code:(NSString*)code
                   hash:(NSString*)hash
                 Result:(JL_OTA_URL __nullable)result;

#pragma mark ---> OTA单备份，是否正在回连
-(BOOL)cmdOtaIsRelinking;

#pragma mark ---> OTA升级设备
/**
 @param data 升级数据
 @param result 升级结果
 */
-(void)cmdOTAData:(NSData*)data
           Result:(JL_OTA_RT __nullable)result;

#pragma mark ---> OTA升级取消
/**
 @param result 回复
 */
-(void)cmdOTACancelResult:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 重启设备
-(void)cmdRebootDevice;

#pragma mark ---> 强制重启设备
-(void)cmdRebootForceDevice;

@end

NS_ASSUME_NONNULL_END
