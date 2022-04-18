//
//  VPMarketDialManager.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/1/27.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPDeviceMarketDialModel.h"
#import "VPServerMarketDialModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface VPMarketDialManager : NSObject

+ (instancetype)share;

/// 获取 Veepoo 服务器中的市场表盘
/// @param model 设备市场表盘的信息
/// @param success 成功回调，返回服务器市场表盘信息
/// @param fairlure 失败回调
- (void)getVeepooServerAllMarketDialsWithDeviceInfo:(VPDeviceMarketDialModel *)model
                                            success:(void(^)(NSArray<VPServerMarketDialModel *> * _Nullable response))success
                                            failure:(void(^)(NSError * _Nullable error, NSInteger errorcode))fairlure;


/// 下载市场表盘的bin文件
/// @param model 指定的市场表盘模型
/// @param deviceMarketDialModel 设备的读取上来的信息 用来校验
/// @param success 成功回调，返回 filePath
/// @param fairlure 失败回调
- (void)downloadMarketDialBinFileWithModel:(VPServerMarketDialModel *)model
                     deviceMarketDialModel:(VPDeviceMarketDialModel *)deviceMarketDialModel
                                   success:(void(^)(NSURL * _Nullable filePath))success
                                   failure:(void(^)(NSError * _Nullable error, NSInteger errorcode))fairlure;

/// 开始传输市场表盘的bin文件到设备
/// @param filePath bin 文件的路径 从 downloadMarketDialBinFileWithModel:success:failure: 中的success回调获取
/// @param transformProgress 传输进度回调
/// @param fairlure 错误回调
- (void)startTransferWithFilePath:(NSURL *)filePath transformProgress:(void(^)(double progress))transformProgress failure:(void(^)(NSError * _Nullable error))fairlure;

@end

NS_ASSUME_NONNULL_END
