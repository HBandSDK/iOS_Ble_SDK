//
//  JL_SystemVolume.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/20.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SystemVolume : JL_FunctionBaseManager

#pragma mark ---> 设置系统音量
/**
 @param volume 音量值
 */
-(void)cmdSetSystemVolume:(UInt8)volume;
-(void)cmdSetSystemVolume:(UInt8)volume Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END
