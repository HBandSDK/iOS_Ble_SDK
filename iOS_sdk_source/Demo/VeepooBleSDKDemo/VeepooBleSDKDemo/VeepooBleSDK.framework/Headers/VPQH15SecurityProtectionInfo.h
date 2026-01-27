//
//  VPQH15SecurityProtectionInfo.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/1/7.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPQH15SecurityProtectionInfo : NSObject

+ (instancetype)shareInstance;

@property (nonatomic, assign) BOOL protectionOpenState;

@property (nonatomic, assign) int32_t openTime;

@end

NS_ASSUME_NONNULL_END
