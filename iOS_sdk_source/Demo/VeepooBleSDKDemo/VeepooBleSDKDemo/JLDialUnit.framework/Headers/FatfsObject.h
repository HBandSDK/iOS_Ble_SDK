//
//  FatfsObject.h
//  JLDialUnit
//
//  Created by 杰理科技 on 2021/7/20.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_BLEKit.h>
#import <ZipZap/ZipZap.h>


NS_ASSUME_NONNULL_BEGIN

@interface FatfsObject : NSObject

#pragma mark ---> FATFS API
/// 输入命令中心类，在JL_Entity内。
/// @param manager 命令中心类
+(void)makeCmdManager:(JL_ManagerM*)manager;

/// 返回 当前 JL_ManagerM
+(JL_ManagerM*)outputCmdManager;

/// 设置外挂Flash的大小，FATFS的大小。
/// @param flashSize Flash大小
/// @param fatsSize FATFS的大小
+(BOOL)makeFlashSize:(uint32_t)flashSize
            FatsSize:(uint32_t)fatsSize;

/// 获取Flash上的文件
/// @param path 文件名数组，其中"JL"，“FONT”不能操作。
+(NSArray*)makeListPath:(NSString*)path;

typedef void(^FatfsCreateFile_BK)(float progress);
/// 新增文件
/// @param path “/文件名”
/// @param data 文件数据内容
/// @param result 进度
+(BOOL)makeCreateFile:(NSString*)path
              Content:(NSData* __nullable)data
               Result:(FatfsCreateFile_BK __nullable)result;

typedef void(^FatfsReplaceFile_BK)(float progress);
/// 替换文件
/// @param path “/文件名”
/// @param data 文件数据内容
+(BOOL)makeReplaceFile:(NSString*)path
               Content:(NSData* __nullable)data
                Result:(FatfsReplaceFile_BK __nullable)result;

/// 删除文件
/// @param path “/文件名”
+(BOOL)makeRemoveFile:(NSString*)path;

/*---------------------------------------------------------------------------------
 FatSize -- FAT文件系统认为自己的大小
 因为小机的FAT项按4K对齐了大小，所以实际上会认为FAT系统占用的空间比FLASH实际大小还要大
 用 f_getfree 获取的是 FAT文件系统认为自己剩余的空间的簇个数，其中有一部分是在Flash上实际不存在的
 所以需要减掉这部分
 计算方式如下：
 FatUsed = FatSize - FreeSize
 FlashRemainSize = FlashSize - FatUsed
 ----------------------------------------------------------------------------------*/
/// 获取FATFS系统剩余空间，“FreeSize”。
+(uint32_t)makeGetFree;

/// 查看watch本间版本
/// @param path 文件路径
+(NSString*)makeVersionWatch:(NSString*)path;

/// 获取文件前面512个字节
/// @param path 文件路径
+(NSData *)makeFileHead:(NSString*)path;

/// 读文件
/// @param path 文件路径
+(NSData*)makeFileContent:(NSString*)path;

/// 解压资源文件
/// @param path 文件路径
/// @param aimDirection 存放的路径
+(NSArray*)unzipFileAtPath:(NSString *)path toDestination:(NSString *)aimDirection;

/// 重置外部flash
+(BOOL)makeResetFlash;

@end

NS_ASSUME_NONNULL_END

