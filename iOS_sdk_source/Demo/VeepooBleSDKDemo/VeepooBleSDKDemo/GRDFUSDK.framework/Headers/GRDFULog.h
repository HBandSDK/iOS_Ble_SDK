//
//  GRDFULog.h
//  GRDFU
//
//  Created by Goodix_BLE on 2020/2/14.
//  Copyright © 2020 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>

#define GRDFULogInfo(format,...)  [[GRDFULog sharedInstance] logWithFunction:__FUNCTION__ lineNumber:__LINE__ formatString:[NSString stringWithFormat:format, ##__VA_ARGS__]]

typedef void(^GRDFULogCacheContent)(NSString* logContent);

NS_ASSUME_NONNULL_BEGIN

@interface GRDFULog : NSObject

+ (instancetype)sharedInstance;
- (void)setEnableLog:(BOOL)enable;

- (void)initLogContentWithTaskType:(NSInteger)taskType;
- (void)cacheLogContent;
@property (nonatomic, copy) GRDFULogCacheContent logContentBlock;

- (void)logWithFunction:(const char *)function
             lineNumber:(int)lineNumber
           formatString:(NSString *)formatString;
@end

NS_ASSUME_NONNULL_END
