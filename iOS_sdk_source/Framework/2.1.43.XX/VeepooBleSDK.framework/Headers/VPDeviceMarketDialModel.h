//
//  VPDeviceMarketDialModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/1/29.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceMarketDialModel : NSObject

//bin文件的协议类型
@property (nonatomic, assign) NSInteger binProtocol;
//屏幕的形状（尺寸）
@property (nonatomic, assign) NSInteger deviceShape;
//图片的ID，如果为0，代表设备没有数据
@property (nonatomic, assign) NSInteger imageId;

@property (nonatomic, assign) NSInteger packageIndex;

//数据传输的地址
@property (nonatomic, assign) NSInteger address;
//最大可用长度
@property (nonatomic, assign) NSInteger length;

- (instancetype)initWithData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
