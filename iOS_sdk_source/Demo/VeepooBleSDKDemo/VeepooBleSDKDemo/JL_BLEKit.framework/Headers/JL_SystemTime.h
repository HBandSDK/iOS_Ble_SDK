//
//  JL_SystemTime.h
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

@interface JL_SystemTime : JL_FunctionBaseManager

#pragma mark ---> 设置系统时间
/**
 @param date 时间类
 */
-(void)cmdSetSystemTime:(NSDate*)date;

@end

NS_ASSUME_NONNULL_END
