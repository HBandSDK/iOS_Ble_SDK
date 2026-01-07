//
//  VPDeviceSportWithGPSModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2025/07/05.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class VPDSOneMinuteModel, VPDSMinuteGPSModel;
@interface VPDeviceSportWithGPSModel : NSObject

/// 协议类型
@property (nonatomic, assign) uint8_t dsProtocol;
/// 运动开始时间戳
@property (nonatomic, assign) uint32_t startTimestamp;
/// 运动结束时间戳
@property (nonatomic, assign) uint32_t stopTimestamp;
/// 运动总的时间 秒数
@property (nonatomic, assign) uint32_t duration;

@property (nonatomic, assign) uint32_t step;
@property (nonatomic, assign) uint32_t dis;
@property (nonatomic, assign) uint32_t cal;
@property (nonatomic, assign) uint32_t sport;

/// 心率
@property (nonatomic, assign) uint8_t maxHeart;
@property (nonatomic, assign) uint8_t aveHeart;
@property (nonatomic, assign) uint8_t minHeart;

/// 配速
@property (nonatomic, assign) uint16_t maxPace;
@property (nonatomic, assign) uint16_t avePace;
@property (nonatomic, assign) uint16_t minPace;

/// 速度
@property (nonatomic, assign) uint16_t maxSpeed;
@property (nonatomic, assign) uint16_t aveSpeed;
@property (nonatomic, assign) uint16_t minSpeed;

/// 步频
@property (nonatomic, assign) uint16_t maxCadence;
@property (nonatomic, assign) uint16_t aveCadence;
@property (nonatomic, assign) uint16_t minCadence;

/// 运动总的有氧时间
@property (nonatomic, assign) uint16_t aerobicCount;
/// 总记录条数，与分钟数量应相等
@property (nonatomic, assign) uint16_t recordCount;
/// 暂停次数
@property (nonatomic, assign) uint8_t pauseCount;
/// 暂停总时长
@property (nonatomic, assign) uint16_t pauseDuration;
@property (nonatomic, assign) uint16_t crc;
@property (nonatomic, assign) uint16_t sportType;
/// 显示类型
/// 0未知
/// 1有GPS+有步数;
/// 2有GPS+无步数，如骑行;
/// 3无GPS+有步数;
/// 4无GPS+无步数(一定无距离);
/// 5有GPS+有步数+有海拔
/// 6有GPS+无步数+有海拔，如骑行;
/// 7无GPS+有步数+有海拔
@property (nonatomic, assign) uint8_t showType;

/// 运动详细数据-每分钟数组
@property (nonatomic, strong) NSArray<VPDSOneMinuteModel *> *minutes;

- (instancetype)initWithDsProtocol:(uint8_t)dsProtocol data:(NSData *)data;

@end

@interface VPDSOneMinuteModel : NSObject

/// 包号-应该是分钟数
@property (nonatomic, assign) uint16_t packageCount;
@property (nonatomic, assign) uint8_t heart;
@property (nonatomic, assign) uint16_t step;
@property (nonatomic, assign) uint16_t dis;
@property (nonatomic, assign) uint16_t cal;
@property (nonatomic, assign) uint16_t sport;
/// 暂停标志
@property (nonatomic, assign) uint8_t pause;

@property (nonatomic, strong) NSArray<VPDSMinuteGPSModel *> *gpsDatas;

@end

@interface VPDSMinuteGPSModel : NSObject

/// 信号强弱
@property (nonatomic, assign) uint8_t rssi;
/// 经度
@property (nonatomic, assign) double longitude;
/// 纬度
@property (nonatomic, assign) double latitude;

@end

NS_ASSUME_NONNULL_END
