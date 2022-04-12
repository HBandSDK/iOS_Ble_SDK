//
//  VPMarketDialModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/1/26.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 服务器市场表盘返回的模型
@interface VPServerMarketDialModel : NSObject

//bin的协议
@property(nonatomic, assign) int binProtocol;
//bin的crc
@property(nonatomic, assign) int crc;
//表盘形状
@property(nonatomic, assign) int dialShape;
//bin文件下载链接
@property(nonatomic, strong) NSString *fileUrl;
//预览图
@property(nonatomic, strong) NSString *previewUrl;


@end

NS_ASSUME_NONNULL_END
