//
//  VPScreenDurationModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/9/14.
//  Copyright © 2018年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPScreenDurationModel : NSObject<NSCopying>

//Current bright screen duration
//当前的亮屏时长
@property (nonatomic, assign) NSInteger currentDuration;

//The default brightness time of the device
//设备默认的亮屏时长
@property (nonatomic, assign) NSInteger defaultDuration;

//The device can set the minimum brightness time
//设备可设置最小的亮屏时长
@property (nonatomic, assign) NSInteger minDuration;

//The device can set the maximum brightness time
//设备可设置最大的亮屏时长
@property (nonatomic, assign) NSInteger maxDuration;

- (instancetype)initWithDurationData:(NSData *)data;

@end
