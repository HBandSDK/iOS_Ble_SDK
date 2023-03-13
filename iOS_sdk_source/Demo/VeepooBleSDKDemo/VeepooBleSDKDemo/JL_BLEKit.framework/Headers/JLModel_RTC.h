//
//  JLModel_RTC.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RTC_RingInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLModel_RTC : NSObject
@property (assign,nonatomic) uint16_t       rtcYear;
@property (assign,nonatomic) uint8_t        rtcMonth;
@property (assign,nonatomic) uint8_t        rtcDay;
@property (assign,nonatomic) uint8_t        rtcHour;
@property (assign,nonatomic) uint8_t        rtcMin;
@property (assign,nonatomic) uint8_t        rtcSec;
@property (assign,nonatomic) BOOL           rtcEnable;
@property (assign,nonatomic) uint8_t        rtcMode;
@property (assign,nonatomic) uint8_t        rtcIndex;
@property (copy  ,nonatomic) NSString       *rtcName;
@property (strong,nonatomic) RTC_RingInfo   *ringInfo;
@property (strong,nonatomic) NSData         *RingData;
@end

NS_ASSUME_NONNULL_END
