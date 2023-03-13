//
//  RTC_RingInfo.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RTC_RingInfo : NSObject
@property (assign,nonatomic) uint8_t        type;
@property (assign,nonatomic) uint8_t        dev;
@property (assign,nonatomic) uint32_t       clust;
@property (assign,nonatomic) uint8_t        len;
@property (strong,nonatomic) NSData         *data;
@end

NS_ASSUME_NONNULL_END
