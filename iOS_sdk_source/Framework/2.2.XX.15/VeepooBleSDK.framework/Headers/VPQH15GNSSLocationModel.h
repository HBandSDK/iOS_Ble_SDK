//
//  VPQH15GNSSLocationModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/1/7.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPQH15SecurityProtectionConst.h"
#import <CoreLocation/CoreLocation.h>
NS_ASSUME_NONNULL_BEGIN

@interface VPQH15GNSSLocationModel : NSObject

//蓝牙RSSI
@property (nonatomic, assign) uint8_t rssi;

//经纬度
@property (nonatomic, assign) CLLocationCoordinate2D location;

//功能
@property (nonatomic, assign) VPQH15SPFunctionType funcType;

//GNSS状态
@property (nonatomic, assign) VPQH15SPGNSSState gnssState;

//海拔
@property (nonatomic, assign) int alt;

- (instancetype)initWithByte:(const uint8_t *)byte;

@end

NS_ASSUME_NONNULL_END
