//
//  VPWeatherSetingModel.h
//  WYPHealthyThird
//
//  Created by zhangchong on 2020/2/28.
//  Copyright © 2020 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPWeatherConfigModel : NSObject

//0是关，1是开
@property(nonatomic, assign) int switchState;

//0是摄氏度，1华氏度
@property(nonatomic, assign) int weatherUnit;

//设备的crc
@property(nonatomic, assign) uint16_t crc;

- (instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
