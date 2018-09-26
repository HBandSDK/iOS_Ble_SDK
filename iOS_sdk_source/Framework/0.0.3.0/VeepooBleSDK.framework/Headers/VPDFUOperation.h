//
//  VPDFUOperation.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/7.
//  Copyright © 2017年 veepoo. All rights reserved.
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
 升级调用的接口

 @param dfuBlock 返回的状态和进度的block
 */
- (void)veepooSDKStartDfu:(DeviceDFUBlock)dfuBlock;

@end
