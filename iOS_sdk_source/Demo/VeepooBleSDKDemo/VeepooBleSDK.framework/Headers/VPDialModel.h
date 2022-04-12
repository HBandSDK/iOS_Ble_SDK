//
//  VPDialModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/1/23.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDialModel : NSObject

//当前选中表盘的类型0是手表固件烧录的表盘、1是更多表盘、2是自定义表盘
@property (nonatomic, assign) int dailType;

//当前选中表盘的风格，如表盘1、表盘2
@property (nonatomic, assign) int dailStyle;

//设备上已经存在的表盘库ID
@property (nonatomic, strong) NSArray<NSNumber *>*dailIDs;

- (void)receiveDevcieData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
