//
//  VPManualStressModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/6/22.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPManualStressModel : NSObject

/// 测量时间戳
@property (nonatomic, assign) uint32_t timestamp;

/// 压力[0,100]
@property (nonatomic, assign) int value;

- (instancetype)initWithData:(NSData *)sourceData;

- (BOOL)parseBlockData;

@end

NS_ASSUME_NONNULL_END
