//
//  VPScreenDurationModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/9/14.
//  Copyright © 2018年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPScreenDurationModel : NSObject<NSCopying>

//当前的亮屏时长
@property (nonatomic, assign) NSInteger currentDuration;
//设备默认的亮屏时长
@property (nonatomic, assign) NSInteger defaultDuration;
//设备可设置最小的亮屏时长
@property (nonatomic, assign) NSInteger minDuration;
//设备可设置最大的亮屏时长
@property (nonatomic, assign) NSInteger maxDuration;

- (instancetype)initWithDurationData:(NSData *)data;

@end
