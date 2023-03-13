//
//  JL_CustomManager.h
//  JL_BLEKit
//
//  Created by 李放 on 2021/12/21.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_CustomManager : JL_FunctionBaseManager

#pragma mark ---> 设备返回的自定义数据
extern NSString *kJL_MANAGER_CUSTOM_DATA;

#pragma mark ---> 用户自定义数据
/**
 @param data 数据
 @param result 回复
 */
-(void)cmdCustomData:(NSData* __nullable)data
              Result:(JL_CMD_RESPOND __nullable)result;

@end

NS_ASSUME_NONNULL_END
