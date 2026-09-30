//
//  VPQH15SecurityProtectionModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2026/9/29.
//  Copyright © 2026 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPQH15SecurityProtectionConst.h"
#import <CoreLocation/CoreLocation.h>
NS_ASSUME_NONNULL_BEGIN

@interface VPQH15SecurityProtectionModel : NSObject

//蓝牙RSSI
@property (nonatomic, assign) int rssi;

//经纬度(保留小数点后5位)
@property (nonatomic, assign) CLLocationCoordinate2D location;

//GNSS状态
@property (nonatomic, assign) VPQH15SecurityProtectionState gnssState;

//海拔
@property (nonatomic, assign) int alt;

- (instancetype)initWithByte:(const uint8_t *)byte;

@end

NS_ASSUME_NONNULL_END
