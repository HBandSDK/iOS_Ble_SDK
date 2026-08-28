//
//  VPAGPSDataModel.h
//  WYPHealthyThird
//
//  Created by fengye on 2024/6/3.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPAGPSDataModel : NSObject

//数据接收地址
@property(nonatomic, assign) NSInteger address;

//可写入数据长度
@property(nonatomic, assign) NSInteger length;

//crc,小端
@property(nonatomic, assign) uint16_t crc;

//星历文件有效总时长，单位天
@property(nonatomic, assign) int validDay;

//星历剩余有效时长，小端，单位分钟
@property(nonatomic, assign) int validMin;

- (void)receiveByte:(const uint8_t *)tbyte;

@end

NS_ASSUME_NONNULL_END
