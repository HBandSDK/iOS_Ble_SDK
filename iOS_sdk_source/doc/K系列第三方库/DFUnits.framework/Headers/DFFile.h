//
//  DFFile.h
//  DVRunning
//
//  Created by Mac on 15/11/13.
//  Copyright (c) 2015年 DevinVon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DFFile : NSObject
/**
 *  用途：在存在的路径上，创建一个文件。
 *  @param path  你喜欢的路径
 */
+(BOOL)createPath:(NSString*)path;

/**
 *  用途:【创建】一个文件，在你想要的路径下。
 *  @param   sPath     系统路径
 *  @param   mPath     中途路径    -->> @"test1/test2/test3" <<--
 *  @param   file      文件名
 */
+(NSString*)createOn:(NSSearchPathDirectory)sPath
          MiddlePath:(NSString*)mPath
                File:(NSString*)file;
/**
 *  用途:生成一个文件路径字符串。
 *  @param   sPath     系统路径
 *  @param   mPath     中途路径    -->> @"test1/test2/test3" <<--
 *  @param   file      文件名
 */
+(NSString*)listPath:(NSSearchPathDirectory)sPath
          MiddlePath:(NSString*)mPath
                File:(NSString*)file;
/**
 *  用途:【查找】一个文件，在你想要的路径下。
 *  @param   sPath     系统路径
 *  @param   mPath     中途路径    -->> @"test1/test2/test3" <<--
 *  @param   file      文件名
 */
+(NSString*)findPath:(NSSearchPathDirectory)sPath
          MiddlePath:(NSString*)mPath
                File:(NSString*)file;
/**
 *  用途:Byte单位转换成KB,MB,GB
 *  @param   byte   多少bytes？
 */
+(NSString*)fileByte:(long long)byte;

/**
 *  用途:重命名。
 *  @param   oldName     旧的文件(路径)    -->> @"test1/test2/test3" <<--
 *  @param   NewName     新的文件(路径)    -->> @"test1/test2/test3" <<--
 */
+(BOOL)renameOldName:(NSString*)oldName
             NewName:(NSString*)newName;
/**
 *  用途:删除文件。
 *  @param   path      文件路径
 */
+(BOOL)removePath:(NSString*)path;

/**
 *  用途:把数据写进文件(覆盖)。
 *  @param   data      数据字节
 *  @param   path      文件路径
 */
+(BOOL)writeData:(NSData*)data fillFile:(NSString*)path;

/**
 *  用途:把数据写进文件(文件末尾)。
 *  @param   data      数据字节
 *  @param   path      文件路径
 */
+(void)writeData:(NSData*)data endFile:(NSString*)path;

/**
 *  用途:从bundle里寻找文件。
 *  @param   bundle    @"*.bundle"
 *  @param   file      文件名
 */
+(NSString*)find:(NSString*)bundle File:(NSString*)file;

/**
 *  用途:从Project资源里寻找文件。
 * （先把资源文件添加至工程内的Copy Bundle Resources内。）
 *  @param   file      文件名
 *  @return 该文件的路径。
 */
+(NSString*)find:(NSString *)file;

/**
 *  用途:解析JSON文件。
 *  @param   path      文件路径
 */
+(id)JsonPath:(NSString*)path;

/**
 *  用途:解析JSON数据。
 *  @param   data      jsonData
 */
+(id)JsonData:(NSData*)data;

/**
 *  用途:读取文件字符串。
 *  @param   path      文件路径
 */
+(NSString*)stringPath:(NSString*)path;

/**
 *  用途:文件夹内文件元素。
 *  @param   path      文件夹路径
 */
+(NSArray*)subPaths:(NSString*)path;

/**
 *  用途:文件大小。
 *  @param   path      文件夹路径
 *  @return  该文件的大小。
 */
+(long long)sizeOfFile:(NSString*)path;


@end
