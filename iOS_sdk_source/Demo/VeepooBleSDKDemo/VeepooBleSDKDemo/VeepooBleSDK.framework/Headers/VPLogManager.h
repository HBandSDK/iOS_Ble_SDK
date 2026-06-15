//
//  VPLogManager.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2024/11/22.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPLogManager : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// 单例实例
+ (instancetype)sharedInstance;

/// 设置最大日志文件大小（单位：字节）
@property (nonatomic, assign) NSUInteger maxLogFileSize;

/// 配置日志文件路径
- (void)configureLogFilePath:(NSString *)filePath;

/// 写入日志
- (void)writeLog:(NSString *)log;

/// 获取当前日志文件路径
- (NSString *)currentLogFilePath;


@end

NS_ASSUME_NONNULL_END
