//
//  JL_FileManager.h
//  JL_BLEKit
//
//  Created by 凌煊峰 on 2021/12/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JLModel_File.h>
#import "JL_FunctionBaseManager.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_FileOperationEnvironmentType) {
    JL_FileOperationEnvironmentTypeBigFileTransmission      = 0x00, //大文件传输
    JL_FileOperationEnvironmentTypeDeleteFile               = 0x01, //删除文件
    JL_FileOperationEnvironmentTypeFormatting               = 0x02, //格式化
    JL_FileOperationEnvironmentTypeFatfsTransmission        = 0x03, //FAT文件传输
};
typedef NS_ENUM(UInt8, JL_DeleteFileLastType) {
    JL_DeleteFileLastTypeIsNotLast                  = 0x00, //不是最后一个文件
    JL_DeleteFileLastTypeIsLast                     = 0x01, //是最后一个文件
};
typedef NS_ENUM(UInt8, JL_BrowseReason) {
    JL_BrowseReasonCommandEnd       = 0,    //读取完当前命令请求的文件
    JL_BrowseReasonFolderEnd        = 1,    //读取完当前目录的文件
    JL_BrowseReasonPlaySuccess      = 2,    //点播成功
    JL_BrowseReasonBusy             = 3,    //设备繁忙
    JL_BrowseReasonDataFail         = 4,    //目录数据发送失败
    JL_BrowseReasonReading          = 0x0f, //正在读取中
    JL_BrowseReasonUnknown,                 //未知原因
};
typedef NS_ENUM(UInt8, JL_FileContentResult) {
    JL_FileContentResultStart       = 0x00, //开始传输
    JL_FileContentResultReading     = 0x01, //正在读取
    JL_FileContentResultEnd         = 0x02, //读取结束
    JL_FileContentResultCancel      = 0x03, //取消读取
    JL_FileContentResultFail        = 0x04, //读取失败
    JL_FileContentResultNull        = 0x05, //文件不存在
    JL_FileContentResultDataError   = 0x06, //数据错误
    JL_FileContentResultCrcFail     = 0x07, //crc校验失败
};
typedef NS_ENUM(UInt8, JL_FileDataType) {
    JL_FileDataTypeDo               = 0,    //开始传输文件数据
    JL_FileDataTypeDone             = 1,    //结束传输文件数据
    JL_FileDataTypeDoing            = 2,    //正在传输文件数据
    JL_FileDataTypeCancel           = 3,    //取消传输文件数据
    JL_FileDataTypeError            = 4,    //传输文件数据出错
    JL_FileDataTypeUnknown,
};
typedef NS_ENUM(UInt8, JL_BigFileTransferCode) {
    JL_BigFileTransferCodeSuccess       = 0x00, //成功
    JL_BigFileTransferCodeFail          = 0x01, //写失败
    JL_BigFileTransferCodeOutOfRange    = 0x02, //数据超出范围
    JL_BigFileTransferCodeCrcFail       = 0x03, //crc校验失败
    JL_BigFileTransferCodeOutOfMemory   = 0x04, //内存不足
};
typedef NS_ENUM(UInt8, JL_BigFileResult) {
    JL_BigFileTransferStart         = 0x00, //开始大文件数据传输
    JL_BigFileTransferDownload      = 0x01, //传输大文件有效数据
    JL_BigFileTransferEnd           = 0x02, //结束大文件数据传输
    JL_BigFileTransferOutOfRange    = 0x03, //大文件传输数据超范围
    JL_BigFileTransferFail          = 0x04, //大文件传输失败
    JL_BigFileCrcError              = 0x05, //大文件校验失败
    JL_BigFileOutOfMemory           = 0x06, //空间不足
    JL_BigFileTransferCancel        = 0x07, //取消传输
    JL_BigFileTransferNoResponse    = 0xF1, //设备没有响应
};

typedef void(^JL_FILE_BK)(NSArray* __nullable array,JL_BrowseReason reason);
typedef void(^JL_FILE_CONTENT_BK)(JL_FileContentResult result, uint32_t size, NSData* __nullable data, float progress);
typedef void(^JL_FILE_DATA_BK)(NSData* __nullable data, NSString* __nullable path, uint16_t size, JL_FileDataType type);
typedef void(^JL_BIGFILE_BK)(NSArray* __nullable array);
typedef void(^JL_BIGFILE_RT)(JL_BigFileResult result, float progress);

@interface JL_FileManager : JL_FunctionBaseManager

- (void)closeTimer;

#pragma mark ---> 监听目录数据
/**
 @param result 状态回复
 */
-(void)cmdBrowseMonitorResult:(JL_FILE_BK __nullable)result;

#pragma mark ---> 浏览目录
/**
 @param model 文件Model
 @param number 读取的数量
 */
-(void)cmdBrowseModel:(JLModel_File*)model
               Number:(uint8_t)number
               Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 删除文件(必须异步执行)
/**
 @param array 文件Model数组
 */
-(BOOL)cmdDeleteFileModels:(NSArray*)array;
/**
 *  删除单个JLModel_File文件
 *  @param model JLModel_File对象
 *  @param last 是否最后一个文件
 *  @param result 删除成功回调
 */
-(void)cmdDeleteFile:(JLModel_File*)model
             IsLast:(JL_DeleteFileLastType)last
             Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark 设备格式化
//@param model 设备句柄
-(void)cmdDeviceFormat:(NSString*)handle Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 清除设备音乐缓存记录
/**
 @param type 卡的类型
 */
-(void)cmdCleanCacheType:(JL_CardType)type;

#pragma mark --->【文件传输 固件-->APP】
#pragma mark 1.监听文件数据
-(void)cmdFileDataMonitorResult:(JL_FILE_DATA_BK __nullable)result;

#pragma mark 2.允许传输文件数据
-(void)cmdAllowFileData;

#pragma mark 3.拒绝传输文件数据
-(void)cmdRejectFileData;

#pragma mark 4.停止传输文件数据
-(void)cmdStopFileData;

#pragma mark --->【文件传输 APP-->固件】
#pragma mark 5.请求传输文件给设备
-(void)cmdFileDataSize:(uint8_t)size
              SavePath:(NSString*)path;

#pragma mark 6.推送文件数据给设备
-(void)cmdPushFileData:(NSData*)data;

#pragma mark 【大文件传输 App-->固件】
// @param  path       大文件下载文件路径
// @param  fileName   大文件下载文件名称
// @param  result     大文件下载结果
-(void)cmdBigFileData:(NSString *)path WithFileName:(NSString *)fileName
               Result:(JL_BIGFILE_RT __nullable)result;

#pragma mark 取消文件传输
-(void)cmdStopBigFileData;

#pragma mark 通知固件进行环境准备
// @param  environment 0:大文件传输 1:删除文件 2：格式化
-(void)cmdPreEnvironment:(JL_FileOperationEnvironmentType)environment Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark 通过名字删除文件
-(void)cmdFileDeleteWithName:(NSString*)name Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark 设置文件传输句柄
/**
 *  大文件传输，设置当前传输句柄 for crc16
 */
- (void)setCurrentFileHandleType:(JL_FileHandleType)currentFileHandleType;
- (JL_FileHandleType)getCurrentFileHandleType;

#pragma mark ---> 读取外置卡的文件内容
-(void)cmdFileReadContentWithName:(NSString*)name Result:(JL_FILE_CONTENT_BK __nullable)result;

#pragma mark ---> 簇号方式读取外置卡的文件内容
- (void)cmdFileReadContentWithFileClus:(uint32_t)fileClus Result:(JL_FILE_CONTENT_BK __nullable)result;

#pragma mark ---> 取消读取外置卡的文件内容
-(void)cmdFileReadContentCancel;

@end

NS_ASSUME_NONNULL_END
