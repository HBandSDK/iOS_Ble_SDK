//
//  JL_RCSP.h
//  JL_BLEKit
//
//  Created by zhihui liang on 2018/11/9.
//  Copyright © 2018 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kJL_DATA_CMD                0x0001
#define kJL_GET_TARGET_FEATURE_MAP  0x0002  //保留
#define kJL_GET_TARGET_FEATURE      0x0003
#define kJL_VOICE_START             0x0004
#define kJL_VOICE_STOP              0x0005
#define kJL_VOICE_DISCONNECT_EDR    0x0006
#define kJL_SYS_INFO_GET            0x0007
#define kJL_SYS_INFO_SET            0x0008
#define kJL_SYS_INFO_AUTO_UPDATE    0x0009
#define kJL_PHONE_CALL_REQUEST      0x000a
#define kJL_FILE_BROWSE_START       0x000c
#define kJL_FILE_BROWSE_STOP        0x000d
#define kJL_FUNCTION_CMD            0x000e
#define kJL_LRC_GET_START           0x000f
#define kJL_LRC_GET_STOP            0x0010
#define kJL_A2F_TTS_START           0x0011
#define kJL_BT_SCAN_START           0x0012
#define kJL_BT_SCAN_RESULT          0x0013
#define kJL_BT_SCAN_STOP            0x0014
//#define kJL_BT_CONNECT              0x0015
#define kJL_FILE_START              0x0016
#define kJL_FILE_STOP               0x0017
#define kJL_FIND_DEVICE             0x0019
#define kJL_CUSTOMER_USER           0x00ff

#define kJL_OTA_INFO_OFFSET         0x00e1
#define kJL_OTA_CAN_UPDATE          0x00e2
#define kJL_OTA_ENTER_UPDATE        0x00e3
#define kJL_OTA_EXIT_UPDATE         0x00e4
#define kJL_OTA_GET_DATA            0x00e5
#define kJL_OTA_STATUS_UPDATE       0x00e6
#define kJL_OTA_REBOOT              0x00e7
#define kJL_OTA_BLE_SPP             0x000b
#define kJL_OTA_LENGTH              0x00e8

#define kJL_SET_ADV                 0x00C0
#define kJL_GET_ADV                 0x00C1
#define kJL_ADV_NOTIFY_DEVICE       0x00C2
#define kJL_ADV_NOTIFY_ENABLE       0x00C3
#define kJL_ADV_NOTIFY_TIPS         0x00C4  //主要用于ADV设置同步后需要主机操作的行为。

#define kJL_SET_APP_INFO            0x00D0
#define kJL_SET_MTU                 0x00D1
#define kJL_GET_MD5                 0x00D4
#define kJL_GET_LOW_DELAY           0x00D5
#define kJL_GET_FLASH_INFO          0x00D6
#define kJL_GET_FLASH_W_R           0x001A

#define kJL_BIGFILE_START           0x001B
#define kJL_BIGFILE_END             0x001C
#define kJL_BIGFILE_GET_FILE        0x001D
#define kJL_BIGFILE_STOP            0x001E
#define kJL_FILE_DELETE             0x001F
#define kJL_GET_FILENAME            0x0020
#define kJL_PRE_ENVIRONMENT         0x0021
#define kJL_FILE_FORMAT             0x0022
#define kJL_FILE_NAME_DEL           0x0023
#define kJL_FILE_READ_CONTENT       0x0024

#define kJL_RTC_PLUS                0x0025
#define kJL_BATCH_OPERATE           0x0026
#define kJL_FILE_GET_CRC            0x0027
#define kJL_SMALL_FILE              0x0028

#define kJL_DEVICE_LOG              0X0029


#define kJL_WEAR_REQ_OPCODE         0x00A0   //获取运动信息
#define kJL_WEAR_SET_OPCODE         0x00A1   //设置运动信息
#define kJL_WEAR_RES_OPCODE         0x00A2   //设备主动推的运动信息
#define kJL_WEAR_CMD_LOG            0x00A3   //传感器log传输命令
#define kJL_WEAR_CMD_SETTING        0x00A5   //健康设备设置命令
#define kJL_WEAR_SYNC_SPORT         0x00A6   //运动模式相关命令(同步数据）

#define kJL_PHONE_NUMBER_WAY        0x00F1

NS_ASSUME_NONNULL_BEGIN

@class JL_PKG;
@interface JL_RCSP : NSObject

/**
 解析JL数据包
 
 @param data 把数据转成JL_PKG模型。
 @return JL_PKG数据模型
 */
+(JL_PKG*)rcspAnalysisData:(NSData*)data;

/**
 生成XM数据包
 
 @param pkg 把JL_PKG模型转成data。
 @return 数据
 */
+(NSData*)rcspMakePackage:(JL_PKG*)pkg;

/**
 分析JL_PKG参数
 
 @param pkg 把JL_PKG的xmData参数部分解析成一列数组。
 @return 参数数组
 */
+(NSArray*)rcspAnalysisParams:(JL_PKG*)pkg;

/**
 分解dJL_PKG信息

 @param data JL_PKG中的信息数据
 @return 参数c数组
 */
+(NSArray*)rcspInfoArrFromData:(NSData*)data;

/**
 生成JL_PKG参数
 
 @param array 把参数数组变成data（注意：数组元素必须是NSData类型）。
 @return 数据
 */
+(NSData*)rcspMakeParams:(NSArray*)array;
@end

@interface JL_PKG : NSObject
@property(assign,nonatomic) uint16_t pkgIsCommand;       //1Bit
@property(assign,nonatomic) uint16_t pkgNeedResponse;    //1Bit
@property(assign,nonatomic) uint16_t pkgUnused;          //6Bits
@property(assign,nonatomic) uint16_t pkgOpCode;          //8Bits
@property(assign,nonatomic) uint16_t pkgLength;          //参数长度(本身不计)
@property(strong,nonatomic) NSData   *pkgData;           //参数数据
@end
NS_ASSUME_NONNULL_END
