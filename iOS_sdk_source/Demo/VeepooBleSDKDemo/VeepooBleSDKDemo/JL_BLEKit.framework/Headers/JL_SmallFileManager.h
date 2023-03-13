//
//  JL_SmallFileManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/13.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "JL_FunctionBaseManager.h"
#import "JLModel_SmallFile.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_SmallFileOperate) {
    JL_SmallFileOperateFail        = 0x00, //失败
    JL_SmallFileOperateDoing       = 0x01, //操作中
    JL_SmallFileOperateSuceess     = 0x02, //成功
    JL_SmallFileOperateUnknown     = 0x03, //未知
    JL_SmallFileOperateExcess      = 0x04, //超量
    JL_SmallFileOperateCrcError    = 0x05, //CRC错误
    JL_SmallFileOperateTimeout     = 0x06, //超时
};
typedef void(^JL_SMALLFILE_DEL)(JL_SmallFileOperate status);
typedef void(^JL_SMALLFILE_READ)(JL_SmallFileOperate status,
                                 float progress, NSData* __nullable data);
typedef void(^JL_SMALLFILE_NEW)(JL_SmallFileOperate status,
                                 float progress, uint16_t fileID);
typedef void(^JL_SMALLFILE_UPDATE)(JL_SmallFileOperate status,
                                 float progress);
typedef void(^JL_SMALLFILE_LIST)(NSArray <JLModel_SmallFile*>* __nullable array);
typedef void(^JL_SMALLFILE_RT)(uint8_t flag, uint16_t fileID,NSData* __nullable data);

@interface JL_SmallFileManager : JL_FunctionBaseManager

#pragma mark - 查询文件

/// 查询文件
/// @param type 文件类型
/// 文件类型除了已有的文件外，还可以扩展类型是Uint8的值
/// @param result 列表回调
-(void)cmdSmallFileQueryType:(JL_SmallFileType)type
                      Result:(JL_SMALLFILE_LIST __nullable)result;

#pragma mark - 删除文件

/// 删除文件
/// @param file 文件模型：JLModel_SmallFile
/// @param result 操作回调结果
-(void)cmdSmallFileDelete:(JLModel_SmallFile*)file Result:(JL_SMALLFILE_DEL)result;

#pragma mark - 读取文件

/// 读取文件
/// @param file 文件模型：JLModel_SmallFile
/// @param result 回调文件数据以及进度，通过分包式回调。
-(void)cmdSmallFileRead:(JLModel_SmallFile*)file
                 Result:(JL_SMALLFILE_READ)result;

-(void)cmdSmallFileReadSync:(JLModel_SmallFile*)file
                     Result:(JL_SMALLFILE_READ)result;//同步

#pragma mark - 新增文件

/// 新增文件
/// @param data 文件数据
/// @param type 文件类型
/// @param result 回调的结果，包含分包进度
-(void)cmdSmallFileNew:(NSData*)data
                  Type:(JL_SmallFileType)type
                Result:(JL_SMALLFILE_NEW)result;

-(void)cmdSmallFileNewSync:(NSData*)data
                      Type:(JL_SmallFileType)type
                    Result:(JL_SMALLFILE_NEW)result;

#pragma mark - 更新文件

/// 更新文件
/// @param file 文件模型：JLModel_SmallFile
/// @param data 文件数据
/// @param result 回调进度
-(void)cmdSmallFileUpdate:(JLModel_SmallFile*)file
                     Data:(NSData*)data
                   Result:(JL_SMALLFILE_UPDATE)result;

-(void)cmdSmallFileUpdateSync:(JLModel_SmallFile*)file
                         Data:(NSData*)data
                       Result:(JL_SMALLFILE_UPDATE)result;

#pragma mark - 底层API

/// 读取文件，更低等级的API
/// @param type 文件类型
/// @param fileId 文件ID
/// @param offset 偏移值
/// @param fileSize 数据大小
/// @param flag 是否为第一包查询
/// @param result 回调文件结果
-(void)cmdSmallFileReadType:(uint8_t)type
                     FileID:(uint16_t)fileId
                     Offset:(uint16_t)offset
                   FileSize:(uint16_t)fileSize
                       Flag:(uint8_t)flag
                     Result:(JL_SMALLFILE_RT __nullable)result;


/// 插入新文件，更低等级的API
/// @param type 文件类型
/// @param offset 偏移值
/// @param fileSize 数据量大小
/// @param crc16 crc校验码
/// @param data 要插入的数据
/// @param result 回调结果
-(void)cmdSmallFileNewType:(uint8_t)type
                    Offset:(uint16_t)offset
                  FileSize:(uint16_t)fileSize
                     Crc16:(uint16_t)crc16
                  FileData:(NSData*)data
                    Result:(JL_SMALLFILE_RT __nullable)result;

/// 更新文件，更低等级的API
/// @param type 文件类型
/// @param fileId 文件ID
/// @param offset 偏移值
/// @param fileSize 数据包的大小
/// @param crc16 数据包的crc校验
/// @param data 数据包
/// @param result 回调结果
-(void)cmdSmallFileUpdateType:(uint8_t)type
                       FileID:(uint16_t)fileId
                       Offset:(uint16_t)offset
                     FileSize:(uint16_t)fileSize
                        Crc16:(uint16_t)crc16
                     FileData:(NSData*)data
                       Result:(JL_SMALLFILE_RT __nullable)result;

/// 小文件删除，更低等级的API
/// @param type 文件类型
/// @param fileId 文件id
/// @param result 回调结果
-(void)cmdSmallFileDeleteType:(uint8_t)type
                       FileID:(uint16_t)fileId
                       Result:(JL_SMALLFILE_RT __nullable)result;

-(void)closeTimer;
@end

NS_ASSUME_NONNULL_END
