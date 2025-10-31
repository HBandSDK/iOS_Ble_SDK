//
//  VPFileHandleManager.h
//  VeepooBleSDK
//
//  Created by fengye on 2025/10/27.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPFileHandleManager : NSObject

@property (nonatomic, assign) NSUInteger maxLogFileSize;

- (void)configureFilePath:(NSString *)fileName;

- (void)clearFile;

- (void)writeText:(NSString *)text;

- (NSString *)currentFilePath;

- (NSString *)currentFileName;

- (NSArray<NSDictionary *> *)getFilesWithDetails;
@end

NS_ASSUME_NONNULL_END
