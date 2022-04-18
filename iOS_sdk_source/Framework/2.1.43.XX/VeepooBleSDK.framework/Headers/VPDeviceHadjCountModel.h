//
//  VPDeviceHadjCountModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/3/22.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceHadjCountModel : NSObject

// 通道 1byte
@property (nonatomic, assign) short channel;
// 所有通道总计数 4byte
@property (nonatomic, assign) long totalCount;
// 当前包诵经计数 2byte
//  单通道下，如果 currentCount == totalCount 则表示读取完成
//  多通道下，所有model的currentCount累加 == totalCount 则表示读取完成
@property (nonatomic, assign) int currentCount;
// 开始时间 时间戳 4byte
@property (nonatomic, assign) long startTimestamp;
// 结束时间 时间戳 4byte
@property (nonatomic, assign) long endTimestamp;

- (instancetype)initWithReceiveData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
