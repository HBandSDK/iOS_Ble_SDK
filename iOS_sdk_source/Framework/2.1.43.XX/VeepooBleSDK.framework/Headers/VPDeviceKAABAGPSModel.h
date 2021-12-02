//
//  VPKAABAGPSModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/4/9.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceKAABAGPSModel : NSObject

/// 经度 int32（保留5位小数，放大100000倍）  ex: 116.405289 则传 （116.40528 * 100000）= 11640528
@property (nonatomic, assign) int longitude;

/// 纬度 int32 ex: -39.904987 同上=> -3990498
@property (nonatomic, assign) int latitude;

/// 海拔高度(单位米，带正负) ex: -100
@property (nonatomic, assign) short altitude;

- (instancetype)initWithReceiveData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
