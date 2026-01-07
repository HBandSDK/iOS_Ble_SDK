//
//  VPDeviceSportModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2024/8/31.
//  Copyright © 2024 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceSportMinuteModel : NSObject

@property (nonatomic, assign) uint16_t packageCount;
@property (nonatomic, assign) uint8_t heartValue;
@property (nonatomic, assign) uint16_t sportValue;
@property (nonatomic, assign) uint16_t stepValue;
@property (nonatomic, assign) uint16_t calValue;
@property (nonatomic, assign) uint16_t disValue;
@property (nonatomic, assign) uint8_t isPause;

@end


@interface VPDeviceSportModel : NSObject

/// 协议类型
@property (nonatomic, assign) uint8_t dsProtocol;
/// 运动类型
@property (nonatomic, assign) uint16_t type;
/// 数据的CRC，去重使用
@property (nonatomic, assign) uint16_t crc;
/// 日期 由开始运动时间分割而得，yyyy-MM-dd
@property (nonatomic, strong) NSString *date;
/// 运动开始时间 "2023-03-24 14:38:42"
@property (nonatomic, strong) NSString *beginTime;
/// 运动结束时间
@property (nonatomic, strong) NSString *endTime;
/// 总的步数
@property (nonatomic, assign) uint32_t totalStep;
/// 总的运动量
@property (nonatomic, assign) uint32_t totalSport;
/// 总的路程单位m
@property (nonatomic, assign) uint32_t totalDis;
/// 总的卡路里 单位 kcal
@property (nonatomic, assign) uint32_t totalCal;
/// 总暂停时间
@property (nonatomic, assign) uint16_t pauseTotalTime;
/// 平均配速
@property (nonatomic, assign) uint32_t averPace;
/// 有氧运动时间 单位s
@property (nonatomic, assign) uint32_t aerobTime;
/// 运动总的时间 单位s
@property (nonatomic, assign) uint32_t totalTime;
/// 平均心率
@property (nonatomic, assign) uint8_t averHeart;
/// 暂停次数
@property (nonatomic, assign) uint8_t pauseCount;
/// 运动的总的条数
@property (nonatomic, assign) uint16_t recordCount;

@property (nonatomic, strong) NSArray<VPDeviceSportMinuteModel *> *oneMinuteData;

- (instancetype)initWithData:(NSData *)sourceData;

@end

NS_ASSUME_NONNULL_END
