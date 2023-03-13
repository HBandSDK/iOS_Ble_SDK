//
//  DialManager.h
//  JLDialUnit
//
//  Created by 杰理科技 on 2021/7/20.
//

#import <Foundation/Foundation.h>
#import <JLDialUnit/FatfsObject.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, DialOperateType) {
    DialOperateTypeNoSpace     = 0,     //空间不足
    DialOperateTypeDoing       = 1,     //正在操作
    DialOperateTypeFail        = 2,     //操作失败
    DialOperateTypeSuccess     = 3,     //操作成功
    DialOperateTypeUnnecessary = 4,     //无需重复打开文件系统
    DialOperateTypeResetFial   = 5,     //重置文件系统失败
    DialOperateTypeNormal      = 6,     //文件系统正常
    DialOperateTypeCmdFail     = 7,     //流程命令执行失败
};
typedef NS_ENUM(NSInteger, DialUpdateResult) {
    DialUpdateResultFinished    = 0,    //更新资源完成
    DialUpdateResultNewest      = 1,    //资源已最新
    DialUpdateResultInvalid     = 2,    //资源无效
    DialUpdateResultEmpty       = 3,    //资源为空
    DialUpdateResultReplace     = 4,    //资源替换
    DialUpdateResultAdd         = 5,    //资源新增
    DialUpdateResultNoSpace     = 6,    //空间不足
    DialUpdateResultZipError    = 7,    //ZIP资源文件错误
};
typedef void(^DialOperateBK)(DialOperateType type, float progress);
typedef void(^DialListBK)(DialOperateType type, NSArray* __nullable array);
typedef void(^DialUpdateBK)(DialUpdateResult updateResult,
                            NSArray* __nullable array,
                            NSInteger index ,float progress);

@interface DialManager : NSObject

//打开表盘文件系统
#pragma mark - 连接成功后，必须调用一次！
+(void)openDialFileSystemWithCmdManager:(JL_ManagerM *)manager withResult:(DialOperateBK)result;

//重置表盘系统
+(void)resetDialFileSystemWithCmdManager:(JL_ManagerM *)manager withResult:(DialOperateBK)result;

/// 查询文件
+(void)listFile:(DialListBK __nullable)result;

/// 添加文件
/// @param file 文件名需要加斜杠，类似@“/WACTH1”。
/// @param content 文件数据
/// @param result 操作回调
+(void)addFile:(NSString*)file
       Content:(NSData*)content
        Result:(DialOperateBK)result;

/// 删除文件
/// @param file  文件名需要加斜杠，类似@“/WACTH1”。
/// @param result 操作回调
+(void)deleteFile:(NSString*)file
           Result:(DialOperateBK)result;

/// 替换文件
/// @param file  文件名需要加斜杠，类似@“/WACTH1”。
/// @param content 文件数据
/// @param result 操作回调
+(void)repaceFile:(NSString*)file
          Content:(NSData*)content
           Result:(DialOperateBK)result;

/// 格式化外部Flash操作
/// @param handle   设备句柄
/// @param result   操作回调
+(void)formatFlash:(NSString*)handle Result:(DialOperateBK)result;

/// 更新设备的表盘资源（异步调用）
/// @param path     资源文件
/// @param array   表盘列表(当前)
/// @param result   更新结果
+(void)updateResourcePath:(NSString*)path
                     List:(NSArray*)array
                   Result:(DialUpdateBK)result;

#pragma mark -
/// 删除文件
/// @param fileModel JLModel_File类型
/// @param result 操作回调
+(void)deleteDialResourceWithFileModel:(JLModel_File*)fileModel Result:(DialOperateBK)result;
+(void)setFileSize:(uint32_t)size FileName:(NSString*)fileName;
+(uint32_t)getSizeOfFileName:(NSString*)fileName;

@end

NS_ASSUME_NONNULL_END
