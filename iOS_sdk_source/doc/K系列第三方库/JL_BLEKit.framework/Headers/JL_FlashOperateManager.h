//
//  JL_FlashOperateManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - 外挂FLASH操作命令
typedef NS_ENUM(UInt8, JL_FlashOperationOPType) {
    JL_FlashOperationOPTypeWriteData             = 0x00, //写数据
    JL_FlashOperationOPTypeReadData              = 0x01, //读数据
    JL_FlashOperationOPTypeInsertFile            = 0x02, //插入文件
    JL_FlashOperationOPTypeDialOperation         = 0x03, //表盘操作
    JL_FlashOperationOPTypeEraseData             = 0x04, //擦除数据
    JL_FlashOperationOPTypeDeleteFile            = 0x05, //删除文件
    JL_FlashOperationOPTypeWriteFileProtection   = 0x06, //写文件保护
    JL_FlashOperationOPTypeUpdateDialResource    = 0x07, //更新表盘资源
    JL_FlashOperationOPTypeCheckWriteDataSuccess = 0x08, //查询写数据是否成功
    JL_FlashOperationOPTypeUpdateResourceFlag    = 0x09, //升级资源标志操作
    JL_FlashOperationOPTypeRestoreSystem         = 0x0A, //还原系统
    JL_FlashOperationOPTypeGetFileInfo           = 0x0B, //获取文件信息
    JL_FlashOperationOPTypeGetRemainingSpace     = 0x0C, //获取剩余空间
};

typedef NS_ENUM(UInt8, JL_DialSetting) {
    JL_DialSettingReadCurrentDial               = 0x00, //读取当前表盘
    JL_DialSettingSetDial                       = 0x01, //设置表盘
    JL_DialSettingVersion                       = 0x03, //获取表盘额外信息，如版本
    JL_DialSettingActivateCustomDial            = 0x04, //激活自定义表盘
    JL_DialSettingGetDialName                   = 0x05, //获取对应的自定义表盘名字
};
typedef NS_ENUM(UInt8, JL_FlashOperateFlag) {
    JL_FlashOperateFlagFinish           = 0x00, //结束
    JL_FlashOperateFlagStart            = 0x01, //开始
};

@interface JL_FlashOperateManager : JL_FunctionBaseManager

typedef void(^JL_FlashInfo_BK)(JLModel_Flash* __nullable model);
typedef void(^JL_FlashWrite_BK)(uint8_t flag);
typedef void(^JL_FlashWriteStatus_BK)(uint8_t flag,uint16_t leftSize);
typedef void(^JL_FlashWriteSize_BK)(uint8_t flag,uint32_t size);
typedef void(^JL_FlashRead_BK)(uint8_t flag,NSData *__nullable data);
typedef void(^JL_FlashAddOrDel_BK)(uint8_t flag);
typedef void(^JL_FlashWatch_BK)(uint8_t flag, uint32_t size,
                                NSString *__nullable path,
                                NSString *__nullable describe);
typedef void(^JL_FlashClean_BK)(uint8_t flag);
typedef void(^JL_FlashProtect_BK)(uint8_t flag);
typedef void(^JL_FlashUpdate_BK)(uint8_t flag);
typedef void(^JL_FlashFileInfo_BK)(uint32_t size,uint16_t crc16);
typedef void(^JL_FlashLeftSize_BK)(uint32_t leftSize);

#pragma mark ---> 获取外置Flash信息
/**
 获取外置Flash信息
 @param result 回复
 */
-(void)cmdGetFlashInfoResult:(JL_FlashInfo_BK __nullable)result;

#pragma mark ---> 写数据到Flash
/**
 写数据到Flash
 @param data        数据
 @param offset   偏移
 @param mtu         每包大小
 @param result   回复
 */
-(void)cmdWriteToFlashAllData:(NSData*)data
                       Offset:(uint32_t)offset
                          Mtu:(uint16_t)mtu
                       Result:(JL_FlashWriteSize_BK __nullable)result;

#pragma mark ---> 读数据从Flash
/**
 读数据从Flash
 @param offset  偏移
 @param size    大小
 @param mtu     每包大小
 @param result  回复
 */
-(void)cmdReadFromFlashAllDataOffset:(uint32_t)offset
                                Size:(uint16_t)size
                                 Mtu:(uint16_t)mtu
                              Result:(JL_FlashRead_BK __nullable)result;

#pragma mark ---> [开始/结束]增加表盘(文件)
/**
 开始/结束 插入文件
 @param path        路径
 @param size        大小
 @param flag        开始:0x01  结束:0x00
 @param result    回复
 */
-(void)cmdInsertFlashPath:(NSString* __nullable)path
                     Size:(uint32_t)size
                     Flag:(JL_FlashOperateFlag)flag
                   Result:(JL_FlashAddOrDel_BK __nullable)result;

#pragma mark ---> 设置表盘(文件)

/**
 表盘操作
 @param path    路径
 @param flag    0x00:读取当前表盘
                0x01:设置表盘
                0x03:获取表盘额外信息，如版本
                0x04:激活自定义表盘
                0x05:获取对应的自定义表盘名字
 @param result  回复
 */
-(void)cmdWatchFlashPath:(NSString*__nullable)path
                    Flag:(JL_DialSetting)flag
                  Result:(JL_FlashWatch_BK __nullable)result;

#pragma mark ---> 设备更新表盘(文件) 【kJL_MANAGER_WATCH_FACE】?// 返回 字符串
extern NSString *kJL_MANAGER_WATCH_FACE;

#pragma mark ---> [开始/结束]删除表盘(文件)
/**
 开始/结束 删除文件
 @param path        路径
 @param flag        开始:0x01  结束:0x00
 @param result    回复
 */
-(void)cmdDeleteFlashPath:(NSString* __nullable)path
                     Flag:(JL_FlashOperateFlag)flag
                   Result:(JL_FlashAddOrDel_BK __nullable)result;

#pragma mark ---> 外挂Flash【写保护】操作
/**
 开始/结束
 @param flag        开始:0x01  结束:0x00
 */
-(void)cmdWriteProtectFlashFlag:(JL_FlashOperateFlag)flag Result:(JL_FlashProtect_BK __nullable)result;

#pragma mark ---> 外挂Flash【资源更新】操作
/**
 开始/结束 更新UI
 @param flag        开始:0x01  结束:0x00
 */
-(void)cmdUpdateResourceFlashFlag:(JL_FlashOperateFlag)flag Result:(JL_FlashUpdate_BK __nullable)result;

#pragma mark ---> 断开连接，对FATFS处理。
-(void)cmdFlashActionDisconnect;

#pragma mark ---> 外挂Flash 手表资源更新标志位
-(void)cmdWatchUpdateResource;

#pragma mark ---> 外挂Flash 还原系统
-(void)cmdFlashRecovery;

#pragma mark ---> 外挂Flash 获取文件信息
-(void)cmdFlashInformationOfFile:(NSString*)file Result:(JL_FlashFileInfo_BK)result;

#pragma mark ---> 外挂Flash 剩余空间
-(void)cmdFlashLeftSizeResult:(JL_FlashLeftSize_BK)result;
@end

NS_ASSUME_NONNULL_END
