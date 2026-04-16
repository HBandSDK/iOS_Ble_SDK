//
//  VPDFUOperation.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/7.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"


/**
 升级接口中的回调

 @param progress 升级进度
 @param deviceDFUState 升级的状态变化
 */
typedef void(^DeviceDFUBlock)(NSInteger progress, DeviceDFUState deviceDFUState);

@interface VPDFUOperation : NSObject

@property (nonatomic, copy) DeviceDFUBlock dfuBlock;

@property (nonatomic, strong) NSString *filePath;

+ (instancetype)dfuOperationShare;


/**
 升级调用的接口，SDK从我司服务器自动获取固件直接升级就可以

 @param dfuBlock 返回的状态和进度的block
 */
- (void)veepooSDKStartDfu:(DeviceDFUBlock)dfuBlock;


/// 开发者自己传入升级文件路径升级
/// @param filePath 升级文件路径
/// @param dfuBlock 升级回掉,文件路径不存在和文件格式不对都反回文件路径不存在
- (void)veepooSDKStartDfuWithFilePath:(NSString *)filePath result:(DeviceDFUBlock)dfuBlock;

@end
