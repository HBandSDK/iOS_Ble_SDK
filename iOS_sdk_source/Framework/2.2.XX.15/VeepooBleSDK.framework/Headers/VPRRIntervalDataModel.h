//
//  VPRRIntervalDataModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/11/30.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface VPRRIntervalDataModel : NSObject

// 块号
@property (nonatomic, assign) NSInteger blockNumber;
// 日期，格式 yyyy-mm-dd
@property (nonatomic, strong) NSString *date;
// 时间, 格式 HH:mm:ss
@property (nonatomic, strong) NSString *time;
// 原始数据流 一个字节表示一个数据
@property (nonatomic, strong) NSData *dataStream;

// 转换数据流 两个字节表示一个数据 小端 0x6400十进制值为100
@property (nonatomic, strong) NSData *dataConvertStream;

@end

NS_ASSUME_NONNULL_END

